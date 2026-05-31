#include "dual_network_board.h"
#include "ml307c_board.h"
#include "application.h"
#include "button.h"
#include "codecs/box_audio_codec.h"
#include "config.h"
#include "display/tm1629a_display.h"
#include "mcp_server.h"
#include "led/single_led.h"
#include "assets/lang_config.h"
#include "sleep_timer.h"
#include "adc_battery_monitor.h"

#include <driver/i2c_master.h>
#include <driver/uart.h>
#include <esp_heap_caps.h>
#include <esp_log.h>
#include <esp_sleep.h>
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <atomic>

#define TAG "Esp32S3YHYBoard"

class YhyAudioCodec : public BoxAudioCodec {
public:
    explicit YhyAudioCodec(i2c_master_bus_handle_t i2c_bus)
        : BoxAudioCodec(i2c_bus,
                       AUDIO_INPUT_SAMPLE_RATE,
                       AUDIO_OUTPUT_SAMPLE_RATE,
                       AUDIO_I2S_GPIO_MCLK,
                       AUDIO_I2S_GPIO_BCLK,
                       AUDIO_I2S_GPIO_WS,
                       AUDIO_I2S_GPIO_DOUT,
                       AUDIO_I2S_GPIO_DIN,
                       PA_ENABLE_GPIO,
                       AUDIO_CODEC_ES8311_ADDR,
                       AUDIO_CODEC_ES7210_ADDR,
                       AUDIO_INPUT_REFERENCE) {}
};

class Esp32S3YHYBoard : public DualNetworkBoard {
private:
    static constexpr int kPowerWakeCheckStepMs = 50;
    static constexpr int kPowerWakeLongPressMs = 1000;
    static constexpr int kIgnorePowerClickAfterBootMs = 2000;
    static constexpr uint8_t kBrightnessLevels_[4] = {0, 2, 5, 7};

    enum class DeviceMode {
        AI_MODE = 0,
        BLUETOOTH_MODE = 1,
        AUX_MODE = 2,
    };

    // 电源状态机
    enum class PowerState {
        DEEP_SLEEP,       // 深度睡眠状态
        WAKING_UP,        // 唤醒中状态
        RUNNING,          // 运行状态
        GOING_TO_SLEEP    // 关机中状态
    };
    
    PowerState power_state_ = PowerState::DEEP_SLEEP;

    i2c_master_bus_handle_t i2c_bus_ = nullptr;
    Display* display_ = nullptr;

    Button boot_button_;
    Button power_button_;
    Button volume_up_button_;
    Button volume_down_button_;

    SleepTimer* sleep_timer_ = nullptr;
    AdcBatteryMonitor* battery_monitor_ = nullptr;

    bool night_light_on_ = false;
    uint8_t brightness_level_ = 2;
    DeviceMode current_mode_ = DeviceMode::AI_MODE;
    int bt_volume_ = 50;  // 蓝牙/AUX模式音量
    std::atomic<bool> mode_switching_{false};
    std::atomic<bool> shutting_down_{false};
    std::atomic<bool> ignore_power_button_until_release_{false};
    std::atomic<bool> buttons_enabled_{false};  // 按钮使能标志
    int64_t ignore_power_click_until_us_ = 0;

    void InitializeI2c() {
        i2c_master_bus_config_t bus_config = {
            .i2c_port = I2C_NUM_1,
            .sda_io_num = AUDIO_CODEC_I2C_SDA_PIN,
            .scl_io_num = AUDIO_CODEC_I2C_SCL_PIN,
            .clk_source = I2C_CLK_SRC_DEFAULT,
            .glitch_ignore_cnt = 7,
            .intr_priority = 0,
            .trans_queue_depth = 0,
            .flags = {
                .enable_internal_pullup = 1,
            },
        };
        ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &i2c_bus_));
    }

    void InitializeFunctionPins() {
        gpio_config_t output_config = {
            .pin_bit_mask = (1ULL << AI_MODE_GPIO) | (1ULL << BT_MODE_GPIO) | (1ULL << NIGHT_LIGHT_GPIO),
            .mode = GPIO_MODE_OUTPUT,
            .pull_up_en = GPIO_PULLUP_ENABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE,
        };
        ESP_ERROR_CHECK(gpio_config(&output_config));

        vTaskDelay(pdMS_TO_TICKS(100));

        gpio_set_level(AI_MODE_GPIO, 1);
        gpio_set_level(BT_MODE_GPIO, 0);
        gpio_set_level(NIGHT_LIGHT_GPIO, 0);
    }

    void InitializeDisplay() {
        display_ = new TM1629ADisplay(TM1629A_STB_PIN, TM1629A_CLK_PIN, TM1629A_DIO_PIN);
        auto tm1629a = static_cast<TM1629ADisplay*>(display_);
        tm1629a->SetBrightness(brightness_level_);
        tm1629a->SetIndicator(0, true);
    }

    int GetBrightnessIndex() const {
        for (int i = 0; i < 4; ++i) {
            if (kBrightnessLevels_[i] == brightness_level_) {
                return i;
            }
        }
        return 1;
    }

    void ApplyDisplayBrightness(uint8_t level) {
        brightness_level_ = level;
        if (!display_) {
            return;
        }

        auto tm1629a = static_cast<TM1629ADisplay*>(display_);
        tm1629a->SetBrightness(brightness_level_);
        ESP_LOGI(TAG, "Display brightness set to %u", brightness_level_);
    }

    void IncreaseDisplayBrightness() {
        int index = GetBrightnessIndex();
        if (index < 3) {
            ApplyDisplayBrightness(kBrightnessLevels_[index + 1]);
        }
    }

    void DecreaseDisplayBrightness() {
        int index = GetBrightnessIndex();
        if (index > 0) {
            ApplyDisplayBrightness(kBrightnessLevels_[index - 1]);
        }
    }

    void CycleDisplayBrightness() {
        int index = GetBrightnessIndex();
        ApplyDisplayBrightness(kBrightnessLevels_[(index + 1) % 4]);
    }

    void SetNightLight(bool on) {
        night_light_on_ = on;
        gpio_set_level(NIGHT_LIGHT_GPIO, on ? 1 : 0);
        ESP_LOGI(TAG, "Night light %s, GPIO%d level=%d", on ? "ON" : "OFF", NIGHT_LIGHT_GPIO, gpio_get_level(NIGHT_LIGHT_GPIO));
    }

    const char* ModeName(DeviceMode mode) {
        switch (mode) {
            case DeviceMode::AI_MODE:
                return "AI";
            case DeviceMode::BLUETOOTH_MODE:
                return "BT";
            case DeviceMode::AUX_MODE:
                return "AUX";
            default:
                return "UNKNOWN";
        }
    }

    void RefreshSleepTimerStateForMode(DeviceMode mode, bool wake_up = false) {
        if (!sleep_timer_) {
            return;
        }
        const bool charging = battery_monitor_ != nullptr && battery_monitor_->IsCharging();
        const bool enable = mode == DeviceMode::AI_MODE && !charging;
        sleep_timer_->SetEnabled(enable);
        if (enable && wake_up) {
            sleep_timer_->WakeUp();
        }
    }

    void RefreshSleepTimerState(bool wake_up = false) {
        RefreshSleepTimerStateForMode(current_mode_, wake_up);
    }

    void InitializePower() {
        // sleep_timer_ = new SleepTimer(300);
        // sleep_timer_->OnEnterLightSleepMode([this]() {
        //     if (display_) {
        //         display_->SetPowerSaveMode(true);
        //     }
        //     auto* ml307c_board = dynamic_cast<Ml307CBoard*>(&GetCurrentBoard());
        //     if (ml307c_board) {
        //         ml307c_board->SetPowerSaveLevel(PowerSaveLevel::LOW_POWER);
        //     }
        // });
        // sleep_timer_->OnExitLightSleepMode([this]() {
        //     if (display_) {
        //         display_->SetPowerSaveMode(false);
        //     }
        //     auto* ml307c_board = dynamic_cast<Ml307CBoard*>(&GetCurrentBoard());
        //     if (ml307c_board) {
        //         ml307c_board->SetPowerSaveLevel(PowerSaveLevel::BALANCED);
        //     }
        // });

        battery_monitor_ = new AdcBatteryMonitor(
            ADC_UNIT_1,
            ADC_CHANNEL_5,
            10000.0f,
            10000.0f,
            CHARGING_STATUS_GPIO);

        battery_monitor_->OnChargingStatusChanged([this](bool charging) {
            if (display_) {
                auto tm1629a = static_cast<TM1629ADisplay*>(display_);
                tm1629a->SetIndicator(3, charging);
            }
            RefreshSleepTimerState();
        });

        RefreshSleepTimerState();
    }

    void InitializeUart2() {
        ESP_LOGI(TAG, "=== Initializing UART2 for Bluetooth AT commands ===");
        ESP_LOGI(TAG, "BT_TX_PIN=GPIO%d, BT_RX_PIN=GPIO%d, Baud=9600", BT_TX_PIN, BT_RX_PIN);
        
        // 配置UART2参数
        uart_config_t uart_config = {
            .baud_rate = 9600,
            .data_bits = UART_DATA_8_BITS,
            .parity = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
            .source_clk = UART_SCLK_DEFAULT,
        };
        
        // 应用UART配置
        ESP_ERROR_CHECK(uart_param_config(UART_NUM_2, &uart_config));
        
        // 设置UART2的GPIO引脚
        // TX=GPIO17 (BT_TX_PIN), RX=GPIO18 (BT_RX_PIN)
        ESP_ERROR_CHECK(uart_set_pin(UART_NUM_2, BT_TX_PIN, BT_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
        
        // 安装UART驱动
        ESP_ERROR_CHECK(uart_driver_install(UART_NUM_2, 
            1024,   // rx_buffer_size
            0,      // tx_buffer_size (0 = 不使用DMA)
            0,      // event_queue_size
            nullptr, // event_queue
            0));
        
        ESP_LOGI(TAG, "UART2 initialized: TX=GPIO%d, RX=GPIO%d, Baud=9600", BT_TX_PIN, BT_RX_PIN);
    }

    // 检测蓝牙模块是否已准备好，返回成功尝试的AT响应
    bool WaitForBluetoothModuleReady(std::string& response, int max_retries = 10, int retry_delay_ms = 500) {
        ESP_LOGI(TAG, "=== Waiting for Bluetooth module to be ready ===");
        
        for (int retry = 0; retry < max_retries; retry++) {
            if (retry > 0) {
                ESP_LOGI(TAG, "Bluetooth module not ready, retry %d/%d after %dms...", 
                         retry, max_retries, retry_delay_ms);
                vTaskDelay(pdMS_TO_TICKS(retry_delay_ms));
            }
            
            // 发送简单的AT命令测试
            if (SendBluetoothCommand("AT", response, 1500)) {
                ESP_LOGI(TAG, "Bluetooth module ready on retry %d, response: %s", 
                         retry, response.c_str());
                return true;
            }
        }
        
        ESP_LOGW(TAG, "Bluetooth module not ready after %d retries", max_retries);
        return false;
    }

    // 优化版蓝牙初始化：设置名字并进入低功耗模式（合并操作，减少通信）
    void OptimizedBluetoothInit() {
        ESP_LOGI(TAG, "=== Optimized Bluetooth Initialization ===");
        
        std::string response;
        
        // 开机已经等待了1.5秒，减少重试次数
        // 只尝试3次，间隔200ms
        if (!WaitForBluetoothModuleReady(response, 3, 200)) {
            ESP_LOGW(TAG, "Bluetooth module not responding after initial wait, skipping initialization");
            return;
        }
        
        // 现在蓝牙模块已经响应，我们可以在一次通信中完成多项操作
        // 首先检查当前状态，避免不必要的设置
        ESP_LOGI(TAG, "Checking current Bluetooth state...");
        
        bool need_set_name = true;
        bool need_set_idle_mode = true;
        
        // 分析AT命令的响应，提取有用信息
        // AT命令的响应通常包含模式信息和名字信息
        if (response.find("+MODE=IDLE") != std::string::npos) {
            ESP_LOGI(TAG, "Bluetooth already in IDLE mode");
            need_set_idle_mode = false;
        }
        
        if (response.find("+NAME=YHY_BT") != std::string::npos || response.find("YHY_BT") != std::string::npos) {
            ESP_LOGI(TAG, "Bluetooth name is already YHY_BT");
            need_set_name = false;
        }
        
        // 设置名字（如果需要）
        if (need_set_name) {
            ESP_LOGI(TAG, "Setting Bluetooth name to YHY_BT...");
            if (SendBluetoothCommand("AT+NAME=YHY_BT", response, 2000)) {
                ESP_LOGI(TAG, "Bluetooth name set successfully");
            } else {
                ESP_LOGW(TAG, "Failed to set Bluetooth name");
            }
        }

        // if (SendBluetoothCommand("AT+BUAD=115200", response, 2000)) {
        //     ESP_LOGI(TAG, "Bluetooth name set BUAD 115200");
        // } else {
        //     ESP_LOGW(TAG, "Failed to set Bluetooth BUAD 115200");
        // }

        // 同步蓝牙芯片到 IDLE 模式（AI模式对应芯片IDLE状态）
        if (need_set_idle_mode) {
            SyncBluetoothChipMode(DeviceMode::AI_MODE);
        } else {
            ESP_LOGI(TAG, "Skipping IDLE mode sync, already in IDLE mode");
        }
    }


    // 查询蓝牙芯片当前真实模式（通过 AT+MODE 不带参数查询）
    // 返回: "IDLE", "BT", "AUX", 或空字符串(查询失败)
    std::string QueryBluetoothMode() {
        std::string response;
        if (!SendBluetoothCommand("AT+MODE", response, 2000)) {
            ESP_LOGW(TAG, "Failed to query BT chip mode");
            return "";
        }
        if (response.find("+MODE=IDLE") != std::string::npos) return "IDLE";
        if (response.find("+MODE=BT") != std::string::npos) return "BT";
        if (response.find("+MODE=AUX") != std::string::npos) return "AUX";
        ESP_LOGW(TAG, "Unknown BT chip mode: %s", response.c_str());
        return "";
    }

    // 将蓝牙芯片同步到目标模式（与 ESP32 DeviceMode 对应）
    // AI_MODE -> IDLE (best-effort, 芯片可能不支持从 BT/AUX 切换到 IDLE)
    // BLUETOOTH_MODE -> BT, AUX_MODE -> AUX
    // 先查询当前模式，仅在需要时才发送切换命令
    bool SyncBluetoothChipMode(DeviceMode target_mode) {
        std::string chip_mode = QueryBluetoothMode();

        const char* expected = nullptr;
        const char* at_cmd = nullptr;
        switch (target_mode) {
            case DeviceMode::AI_MODE:
                expected = "IDLE"; at_cmd = "AT+MODE=IDLE"; break;
            case DeviceMode::BLUETOOTH_MODE:
                expected = "BT";   at_cmd = "AT+MODE=BT";   break;
            case DeviceMode::AUX_MODE:
                expected = "AUX";  at_cmd = "AT+MODE=AUX";  break;
        }

        if (chip_mode == expected) {
            ESP_LOGI(TAG, "BT chip already in %s mode, no sync needed", expected);
            return true;
        }

        ESP_LOGI(TAG, "BT chip mode mismatch: chip=%s target=%s, syncing...",
                 chip_mode.c_str(), expected);

        int max_retry = (target_mode == DeviceMode::AI_MODE) ? 2 : 3;

        std::string response;
        for (int retry = 0; retry < max_retry; retry++) {
            if (retry > 0) vTaskDelay(pdMS_TO_TICKS(500));

            if (SendBluetoothCommand(at_cmd, response, 3000)) {
                std::string expected_prefix = std::string("+MODE=") + expected;
                if (response.find(expected_prefix) != std::string::npos) {
                    ESP_LOGI(TAG, "BT chip synced to %s OK", expected);
                    return true;
                }
                // 目标 IDLE 但芯片报告 BT → 断连后重试
                if (target_mode == DeviceMode::AI_MODE &&
                    response.find("+MODE=BT") != std::string::npos) {
                    ESP_LOGI(TAG, "BT chip connected, disconnecting before IDLE...");
                    SendBluetoothCommand("AT+DISC", response, 1000);
                    vTaskDelay(pdMS_TO_TICKS(800));
                    continue;
                }

                // 收到 OK 但没有 +MODE=xxx 前缀 → 查询验证实际模式
                std::string verified = QueryBluetoothMode();
                if (verified == expected) {
                    ESP_LOGI(TAG, "BT chip synced to %s OK (verified by query)", expected);
                    return true;
                }
                // 目标 IDLE 但实际仍在 BT → 断连重试（AI模式专用）
                if (target_mode == DeviceMode::AI_MODE && verified == "BT") {
                    ESP_LOGI(TAG, "BT chip still in BT mode, disconnecting before IDLE...");
                    SendBluetoothCommand("AT+DISC", response, 1000);
                    vTaskDelay(pdMS_TO_TICKS(800));
                    continue;
                }
                // AUX busy / 芯片不支持 IDLE → 不重试
                if (target_mode == DeviceMode::AI_MODE) {
                    ESP_LOGI(TAG, "BT chip stays in %s (AT+MODE=IDLE not supported, OK for audio routing)",
                             verified.c_str());
                } else {
                    ESP_LOGI(TAG, "BT chip busy (verified=%s), cannot switch to %s now",
                             verified.c_str(), expected);
                }
                break;
            }
            break;
        }

        ESP_LOGW(TAG, "BT chip sync to %s failed (best-effort)", expected);
        return false;
    }

    // 发送AT命令到蓝牙芯片
    bool SendBluetoothCommand(const std::string& command, std::string& response, int timeout_ms = 2000) {
        // 清除接收缓冲区
        uart_flush_input(UART_NUM_2);
        
        // 发送AT指令
        std::string cmd = command + "\r\n";
        ESP_LOGD(TAG, "Sending BT command: %s", cmd.c_str());
        
        int len = uart_write_bytes(UART_NUM_2, cmd.c_str(), cmd.length());
        if (len != cmd.length()) {
            ESP_LOGE(TAG, "Failed to send BT command: %s", command.c_str());
            return false;
        }
        
        // 接收响应
        uint8_t buffer[1024] = {0};
        int total_bytes = 0;
        int start_time = xTaskGetTickCount();
        bool got_ok = false;
        bool got_error = false;
        
        while (xTaskGetTickCount() - start_time < timeout_ms / portTICK_PERIOD_MS) {
            int bytes_read = uart_read_bytes(UART_NUM_2, buffer + total_bytes, sizeof(buffer) - total_bytes - 1, 10 / portTICK_PERIOD_MS);
            if (bytes_read > 0) {
                total_bytes += bytes_read;
                buffer[total_bytes] = '\0';  // 确保字符串结尾
                
                // 检查是否收到OK或ERROR
                std::string current_response((char*)buffer, total_bytes);
                if (current_response.find("OK") != std::string::npos) {
                    got_ok = true;
                }
                if (current_response.find("ERROR") != std::string::npos) {
                    got_error = true;
                }
                
                if (got_error && total_bytes > 0) {
                    break;
                }
                if (got_ok && total_bytes > 0) {
                    // 等待尾随 URC 到达（如 +MODE=IDLE、+PLAYING 等）
                    vTaskDelay(pdMS_TO_TICKS(300));
                    int remaining = uart_read_bytes(UART_NUM_2, buffer + total_bytes,
                                                     sizeof(buffer) - total_bytes - 1,
                                                     pdMS_TO_TICKS(100));
                    if (remaining > 0) {
                        total_bytes += remaining;
                        buffer[total_bytes] = '\0';
                    }
                    break;
                }
            }
            vTaskDelay(pdMS_TO_TICKS(10));
        }
        
        if (total_bytes > 0) {
            response = std::string((char*)buffer, total_bytes);
            ESP_LOGI(TAG, "BT command '%s' response: %s", command.c_str(), response.c_str());
            
            // 检查是否有错误响应
            bool has_error = (response.find("ERROR") != std::string::npos) ||
                            (response.find("NOT AT COMMOND") != std::string::npos);
            
            if (has_error) {
                ESP_LOGW(TAG, "BT command '%s' got error response", command.c_str());
                return false;
            }
            
            // 检查响应中是否包含OK
            if (response.find("OK") != std::string::npos) {
                return true;
            }
            
            // 如果没有OK也没有ERROR，但收到了响应，可能是主动上报
            // 尝试检查是否包含特定命令的响应模式
            if (response.find(command) != std::string::npos) {
                return true;
            }
            
            // 其他情况视为失败
            ESP_LOGW(TAG, "BT command response doesn't contain OK or ERROR");
            return false;
        }
        
        ESP_LOGW(TAG, "No response for BT command: %s", command.c_str());
        return false;
    }

    void InitializeTools() {
        auto& mcp_server = McpServer::GetInstance();
        mcp_server.AddTool("self.lamp.get_state", "Get the power state of the night light", PropertyList(),
            [this](const PropertyList&) -> ReturnValue {
                return night_light_on_ ? "{\"power\": true}" : "{\"power\": false}";
            });

        mcp_server.AddTool("self.lamp.turn_on", "Turn on the night light", PropertyList(),
            [this](const PropertyList&) -> ReturnValue {
                SetNightLight(true);
                return true;
            });

        mcp_server.AddTool("self.lamp.turn_off", "Turn off the night light", PropertyList(),
            [this](const PropertyList&) -> ReturnValue {
                SetNightLight(false);
                return true;
            });

        mcp_server.AddTool("self.screen.set_brightness",
            "Set the TM1629A display brightness. Valid levels are 0, 2, 5, 7. Level 0 turns the display off.",
            PropertyList({
                Property("brightness", kPropertyTypeInteger, 0, 7)
            }),
            [this](const PropertyList& properties) -> ReturnValue {
                int requested = properties["brightness"].value<int>();
                if (requested <= 0) {
                    ApplyDisplayBrightness(0);
                } else if (requested <= 2) {
                    ApplyDisplayBrightness(2);
                } else if (requested <= 5) {
                    ApplyDisplayBrightness(5);
                } else {
                    ApplyDisplayBrightness(7);
                }
                return true;
            });

        mcp_server.AddTool("self.screen.increase_brightness",
            "Increase the TM1629A display brightness to the next level. Levels are 0, 2, 5, 7.",
            PropertyList(),
            [this](const PropertyList&) -> ReturnValue {
                IncreaseDisplayBrightness();
                return true;
            });

        mcp_server.AddTool("self.screen.decrease_brightness",
            "Decrease the TM1629A display brightness to the previous level. Levels are 0, 2, 5, 7.",
            PropertyList(),
            [this](const PropertyList&) -> ReturnValue {
                DecreaseDisplayBrightness();
                return true;
            });
    }

    void SetNetworkIndicator() {
        if (!display_) {
            return;
        }
        auto tm1629a = static_cast<TM1629ADisplay*>(display_);
        const bool ml307 = GetNetworkType() == NetworkType::ML307;
        tm1629a->SetIndicator(1, ml307);
        tm1629a->SetIndicator(2, !ml307);
    }

    void SetModeIndicator(DeviceMode mode) {
        if (!display_) {
            return;
        }
        auto tm1629a = static_cast<TM1629ADisplay*>(display_);
        tm1629a->SetIndicator(0, mode == DeviceMode::AI_MODE);
        // display_->ShowNotification(ModeName(mode), 1000);
    }

    void ShowVolume(int volume) {
        if (!display_) {
            return;
        }
        auto tm1629a = static_cast<TM1629ADisplay*>(display_);
        tm1629a->ShowVolume(volume, 1000);
    }

    void PlayModePrompt(DeviceMode mode) {
        auto& app = Application::GetInstance();
        auto& audio_service = app.GetAudioService();
        audio_service.Start();

        switch (mode) {
            case DeviceMode::AI_MODE:
                app.PlaySound(Lang::Sounds::OGG_AIMODE);
                break;
            case DeviceMode::BLUETOOTH_MODE:
                app.PlaySound(Lang::Sounds::OGG_BLUTEMODE);
                break;
            case DeviceMode::AUX_MODE:
                app.PlaySound(Lang::Sounds::OGG_AUXMODE);
                break;
        }
    }

    void WaitPromptPlaybackDone(int max_wait_ms = 2000) {
        auto& audio_service = Application::GetInstance().GetAudioService();
        constexpr int kStepMs = 50;
        int waited_ms = 0;

        // 检查音频服务是否在运行
        while (!audio_service.IsIdle() && waited_ms < max_wait_ms) {
            vTaskDelay(pdMS_TO_TICKS(kStepMs));
            waited_ms += kStepMs;
        }

        if (!audio_service.IsIdle()) {
            ESP_LOGW(TAG, "Prompt wait timeout after %d ms", waited_ms);
        }
    }

    void ApplyRoutePrepare(DeviceMode target_mode) {
        if (target_mode == DeviceMode::BLUETOOTH_MODE) {
            gpio_set_level(BT_MODE_GPIO, 0);
            gpio_set_level(AI_MODE_GPIO, 1);
        } else if (target_mode == DeviceMode::AUX_MODE) {
            gpio_set_level(BT_MODE_GPIO, 0);
            gpio_set_level(AI_MODE_GPIO, 1);
        } else {
            gpio_set_level(BT_MODE_GPIO, 0);
            gpio_set_level(AI_MODE_GPIO, 1);
        }

        ESP_LOGI(TAG,
                 "Route prepare target=%s AI_MODE_GPIO=%d BT_MODE_GPIO=%d",
                 ModeName(target_mode),
                 gpio_get_level(AI_MODE_GPIO),
                 gpio_get_level(BT_MODE_GPIO));
    }

    void ApplyRouteCommit(DeviceMode target_mode) {
        if (target_mode == DeviceMode::AI_MODE) {
            gpio_set_level(AI_MODE_GPIO, 1);
            gpio_set_level(BT_MODE_GPIO, 0);
        } else if (target_mode == DeviceMode::BLUETOOTH_MODE) {
            gpio_set_level(AI_MODE_GPIO, 0);
            gpio_set_level(BT_MODE_GPIO, 0);
        } else {
            gpio_set_level(AI_MODE_GPIO, 0);
            gpio_set_level(BT_MODE_GPIO, 0);
        }

        ESP_LOGI(TAG,
                 "Route commit target=%s AI_MODE_GPIO=%d BT_MODE_GPIO=%d",
                 ModeName(target_mode),
                 gpio_get_level(AI_MODE_GPIO),
                 gpio_get_level(BT_MODE_GPIO));
    }

    void EnableAIVoice() {
        auto& app = Application::GetInstance();
        auto& audio_service = app.GetAudioService();
        auto codec = GetAudioCodec();

        ESP_LOGI(TAG, "EnableAIVoice: codec output=%s input=%s",
                 codec->output_enabled() ? "yes" : "no",
                 codec->input_enabled() ? "yes" : "no");

        // 切换到AI模式时，同步蓝牙芯片到 IDLE 状态
        SyncBluetoothChipMode(DeviceMode::AI_MODE);

        codec->EnableOutput(true);
        codec->EnableInput(true);

        ESP_LOGI(TAG, "EnableAIVoice: after enable codec output=%s input=%s",
                 codec->output_enabled() ? "yes" : "no",
                 codec->input_enabled() ? "yes" : "no");

        // 优化：快速启动音频服务
        if (!audio_service.IsAudioProcessorRunning()) {
            audio_service.Start();
            ESP_LOGI(TAG, "EnableAIVoice: audio_service.Start() done");
            // 减少初始化等待时间
            vTaskDelay(pdMS_TO_TICKS(100));
        } else {
            ESP_LOGI(TAG, "EnableAIVoice: audio service already running");
        }

        audio_service.EnableWakeWordDetection(true);
        ESP_LOGI(TAG, "EnableAIVoice: wake word detection enabled");

        // 减少稳定等待时间
        vTaskDelay(pdMS_TO_TICKS(200));
        ResumeNetworkReconnect();
        ESP_LOGI(TAG, "EnableAIVoice: network reconnect resumed");
    }

    void DisableAIVoice() {
        auto& app = Application::GetInstance();
        auto& audio_service = app.GetAudioService();
        auto codec = GetAudioCodec();

        app.StopListening();
        app.AbortSpeaking(kAbortReasonNone);
        app.SetDeviceState(kDeviceStateIdle);

        // 优化：快速停止音频服务
        ESP_LOGI(TAG, "DisableAIVoice: quickly stopping audio service");
        audio_service.EnableWakeWordDetection(false);
        
        // 停止音频服务任务
        audio_service.Stop();
        audio_service.UpdateLastOutputTime();

        gpio_set_level(PA_ENABLE_GPIO, 1);

        if (!codec->output_enabled()) {
            codec->EnableOutput(true);
        }
        codec->EnableInput(false);
    }

    void SwitchToMode(DeviceMode target_mode) {
        if (mode_switching_.exchange(true)) {
            ESP_LOGW(TAG, "Switch mode ignored: already switching");
            return;
        }

        DeviceMode previous_mode = current_mode_;
        ESP_LOGI(TAG, "Switch mode: %s -> %s, mode_switching_=true", ModeName(previous_mode), ModeName(target_mode));
        
        // 记录切换前的内存状态（仅调试时使用）
        #ifdef CONFIG_ESP32_HEAP_TRACING
        ESP_LOGI(TAG, "Heap free before switch: %u bytes", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
        ESP_LOGI(TAG, "Largest free block: %u bytes", heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT));
        #endif

        // 优化：如果切换到AI模式，先停止之前的音频服务
        if (target_mode == DeviceMode::AI_MODE && previous_mode != DeviceMode::AI_MODE) {
            // 快速停止之前的音频播放
            ESP_LOGI(TAG, "Quickly stopping previous audio before switching to AI");
            auto& audio_service = Application::GetInstance().GetAudioService();
            audio_service.Stop();  // 停止音频服务
            vTaskDelay(pdMS_TO_TICKS(50));  // 短暂延迟
        }

        ApplyRoutePrepare(target_mode);

        if (target_mode == DeviceMode::AI_MODE) {
            // 优化：先播放提示音，再启动音频服务（减少等待时间）
            ESP_LOGI(TAG, "Prompt start for mode=%s", ModeName(target_mode));
            PlayModePrompt(target_mode);
            
            // 同时启动音频服务（异步）
            EnableAIVoice();
            
            // 等待提示音播放完成（较短时间）
            WaitPromptPlaybackDone(1500);
            ESP_LOGI(TAG, "Prompt done for mode=%s", ModeName(target_mode));
        } else {
            // BT/AUX 模式：先播放提示音，再停止音频服务
            // 注意：audio_service.Stop() 会清空队列并设置 service_stopped_=true，
            // 导致 AudioOutputTask 立即退出（不处理队列中数据），所以提示音必须先播放
            auto& audio_service = Application::GetInstance().GetAudioService();
            audio_service.EnableWakeWordDetection(false);

            ESP_LOGI(TAG, "Prompt start for mode=%s", ModeName(target_mode));
            PlayModePrompt(target_mode);

            // 同时处理模式切换
            if (target_mode == DeviceMode::BLUETOOTH_MODE || target_mode == DeviceMode::AUX_MODE) {
                std::string at_command;
                std::string expected_response_prefix;
                std::string mode_name;

                if (target_mode == DeviceMode::BLUETOOTH_MODE) {
                    at_command = "AT+MODE=BT";
                    expected_response_prefix = "+MODE=BT";
                    mode_name = "Bluetooth";
                } else {
                    at_command = "AT+MODE=AUX";
                    expected_response_prefix = "+MODE=AUX";
                    mode_name = "AUX";
                }

                ESP_LOGI(TAG, "=== Switching to %s Mode via UART2 ===", mode_name.c_str());

                // 清除可能残留的响应
                uart_flush_input(UART_NUM_2);
                vTaskDelay(pdMS_TO_TICKS(100));  // 减少等待时间

                // 发送模式切换命令，带重试机制
                std::string switch_response;
                bool mode_switch_success = false;
                for (int retry = 0; retry < 2; retry++) {
                    if (retry > 0) {
                        ESP_LOGW(TAG, "Mode switch retry %d/2 for %s...", retry, mode_name.c_str());
                        vTaskDelay(pdMS_TO_TICKS(100));
                        uart_flush_input(UART_NUM_2);
                    }

                    ESP_LOGI(TAG, "Sending %s (attempt %d)...", at_command.c_str(), retry + 1);

                    if (SendBluetoothCommand(at_command, switch_response, 3000)) {
                        // 检查响应是否包含期望的模式
                        if (switch_response.find(expected_response_prefix) != std::string::npos) {
                            ESP_LOGI(TAG, "%s mode switch: OK (response: %s)", mode_name.c_str(), switch_response.c_str());
                            mode_switch_success = true;
                            break;
                        } else {
                            ESP_LOGW(TAG, "%s mode switch: unexpected response '%s' (expected '%s')",
                                        mode_name.c_str(), switch_response.c_str(), expected_response_prefix.c_str());
                        }
                    } else {
                        ESP_LOGW(TAG, "%s mode switch: command failed, response: %s", mode_name.c_str(), switch_response.c_str());
                    }
                }

                if (!mode_switch_success) {
                    ESP_LOGE(TAG, "%s mode switch failed after retries, continuing...", mode_name.c_str());
                }

                // 验证芯片是否已切换到目标模式（先查询，不匹配则用 Sync 重试）
                std::string expected_mode = (target_mode == DeviceMode::BLUETOOTH_MODE) ? "BT" : "AUX";
                std::string verified = QueryBluetoothMode();
                if (verified == expected_mode) {
                    ESP_LOGI(TAG, "BT chip verified in %s mode", expected_mode.c_str());
                } else if (!verified.empty()) {
                    ESP_LOGW(TAG, "BT chip mode mismatch: expected=%s actual=%s, retrying sync...",
                             expected_mode.c_str(), verified.c_str());
                    SyncBluetoothChipMode(target_mode);
                }
                
            }

            // 等待提示音播放完成（较短时间）
            WaitPromptPlaybackDone(500);
            ESP_LOGI(TAG, "Prompt done for mode=%s", ModeName(target_mode));

            // 最后完全停止音频服务（确保 AudioOutputTask 退出）
            DisableAIVoice();

            // 确保网络重连机制在 BT/AUX 模式下也保持活跃
            // 与 AI 模式的 EnableAIVoice() 中 ResumeNetworkReconnect() 对应
            ResumeNetworkReconnect();
        }

        ApplyRouteCommit(target_mode);

        ESP_LOGI(TAG, "SwitchToMode: updating current_mode_ from %s to %s",
                 ModeName(current_mode_), ModeName(target_mode));
        current_mode_ = target_mode;
        SetModeIndicator(current_mode_);
        RefreshSleepTimerStateForMode(current_mode_, true);

        ESP_LOGI(TAG, "SwitchToMode: completed, current_mode_=%s, mode_switching_=false",
                 ModeName(current_mode_));
        
        // 记录切换后的内存状态（仅调试时使用）
        #ifdef CONFIG_ESP32_HEAP_TRACING
        ESP_LOGI(TAG, "Heap free after switch: %u bytes", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
        ESP_LOGI(TAG, "Largest free block after: %u bytes", heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT));
        #endif
        
        mode_switching_.store(false);
    }

    void SwitchMode() {
        DeviceMode next_mode = static_cast<DeviceMode>(
            (static_cast<int>(current_mode_) + 1) % (static_cast<int>(DeviceMode::AUX_MODE) + 1));
        SwitchToMode(next_mode);
    }

    bool ShouldIgnorePowerClick() const {
        return esp_timer_get_time() < ignore_power_click_until_us_;
    }

    bool IsWakeFromPowerButton() const {
        esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
        if (cause != ESP_SLEEP_WAKEUP_EXT1) {
            return false;
        }

        uint64_t wakeup_pin_mask = esp_sleep_get_ext1_wakeup_status();
        return (wakeup_pin_mask & (1ULL << POWER_BUTTON_GPIO)) != 0;
    }

    bool ShouldIgnorePowerButtonAction(const char* action, bool check_boot_guard = false) const {
        if (ignore_power_button_until_release_.load()) {
            ESP_LOGI(TAG, "Ignore power %s until wake button is released", action);
            return true;
        }

        if (check_boot_guard && ShouldIgnorePowerClick()) {
            ESP_LOGI(TAG, "Ignore power %s during boot guard window", action);
            return true;
        }

        return false;
    }

    void EnterDeepSleep() {
        auto codec = GetAudioCodec();
        codec->EnableInput(false);
        codec->EnableOutput(false);

        if (display_) {
            display_->SetPowerSaveMode(true);
        }

        while (gpio_get_level(POWER_BUTTON_GPIO) == 0) {
            vTaskDelay(pdMS_TO_TICKS(kPowerWakeCheckStepMs));
        }

        // 防止蓝牙芯片在深度睡眠时被误唤醒：
        // ESP32 进 deep sleep 后 GPIO 变高阻，BT_TX 电平跳变会被蓝牙芯片
        // 检测为 UART 活动从而退出 IDLE 模式。拉高并保持 BT_TX 可避免此问题。
        gpio_set_level(BT_TX_PIN, 1);
        gpio_hold_en(BT_TX_PIN);
        gpio_hold_en(BT_RX_PIN);
        gpio_deep_sleep_hold_en();

        ESP_ERROR_CHECK(esp_sleep_enable_ext1_wakeup_io(1ULL << POWER_BUTTON_GPIO, ESP_EXT1_WAKEUP_ANY_LOW));
        ESP_LOGI(TAG, "Entering deep sleep");
        esp_deep_sleep_start();
    }

    void StartShutdown() {
        if (shutting_down_.exchange(true)) {
            ESP_LOGW(TAG, "Shutdown ignored: already shutting down");
            return;
        }

        xTaskCreate([](void* arg) {
            auto* board = static_cast<Esp32S3YHYBoard*>(arg);
            board->DoShutdown();
            vTaskDelete(nullptr);
        }, "yhy_shutdown", 4096, this, 5, nullptr);
    }

    void DoShutdown() {

        power_state_ = PowerState::GOING_TO_SLEEP;
        buttons_enabled_.store(false);  // 禁用按钮，防止关机过程中误触发
        ESP_LOGI(TAG, "Shutdown start, power_state=GOING_TO_SLEEP");

        auto* ml307C_board = dynamic_cast<Ml307CBoard*>(&GetCurrentBoard());
        if (ml307C_board) {
            ml307C_board->SetModemDeepSleep(true);
        }

        SwitchToMode(DeviceMode::AI_MODE);

        if (sleep_timer_) {
            sleep_timer_->SetEnabled(false);
        }

        auto& app = Application::GetInstance();
        auto& audio_service = app.GetAudioService();
        auto codec = GetAudioCodec();

        app.StopListening();
        app.AbortSpeaking(kAbortReasonNone);
        audio_service.EnableWakeWordDetection(false);
        // EnableVoiceProcessing需要AudioService已初始化，暂不调用
        audio_service.Start();
        audio_service.UpdateLastOutputTime();
        audio_service.ResetDecoder();

        if (!codec->output_enabled()) {
            codec->EnableOutput(true);
        }
        codec->EnableInput(false);

        // Force the local prompt back onto the ESP audio route before shutdown.
        ApplyRouteCommit(DeviceMode::AI_MODE);

        vTaskDelay(pdMS_TO_TICKS(600));

        // 播放关机音效，确保有足够时间播放完成
        ESP_LOGI(TAG, "Playing shutdown sound");
        app.PlaySound(Lang::Sounds::OGG_PWROFF);
        vTaskDelay(pdMS_TO_TICKS(1500));  // 等待提示音播放完成
        ESP_LOGI(TAG, "Prompt done for shutdown");
        
        // 先停止网络重连，等待正在进行的重连结束（WaitForNetworkReady 最长 30 秒可能阻塞 UART）
        // StopNetworkReconnect();
        // vTaskDelay(pdMS_TO_TICKS(1000));  // 等正在进行的 AT 命令完成

     

        if (display_) {
            display_->SetPowerSaveMode(true);
        }
        EnterDeepSleep();
    }

    void InitializeButtons() {
        // 检查按钮当前状态，用于忽略初始化时按钮已按下的情况
        bool boot_button_pressed = (gpio_get_level(BOOT_BUTTON_GPIO) == 0);
        bool power_button_pressed = (gpio_get_level(POWER_BUTTON_GPIO) == 0);
        
        if (boot_button_pressed) {
            ESP_LOGI(TAG, "Boot button is pressed during init, will ignore until release");
        }
        if (power_button_pressed) {
            ESP_LOGI(TAG, "Power button is pressed during init, will ignore until release");
        }
        
        // 初始化期间忽略按钮按下
        ignore_power_button_until_release_.store(boot_button_pressed || power_button_pressed);
        
        power_button_.OnPressUp([this]() {
            if (ignore_power_button_until_release_.exchange(false)) {
                ESP_LOGI(TAG, "Power button released after wake, re-enabling power button actions");
            }
        });
        boot_button_.OnClick([this]() {
            if (!buttons_enabled_.load()) {
                ESP_LOGW(TAG, "Boot button ignored: buttons not enabled");
                return;
            }
            if (ignore_power_button_until_release_.load()) {
                ESP_LOGW(TAG, "Boot button ignored: waiting for release after init");
                return;
            }
            ESP_LOGI(TAG, "Boot button clicked, current_mode_=%s", ModeName(current_mode_));
            if (current_mode_ == DeviceMode::AI_MODE) {
                auto& app = Application::GetInstance();
                ESP_LOGI(TAG, "Calling WakeWordInvoke, state=%d", app.GetDeviceState());
                static const std::string wake_word = "你好小智";
                app.WakeWordInvoke(wake_word);
            }
            RefreshSleepTimerState(true);
        });

        boot_button_.OnDoubleClick([this]() {
            if (!buttons_enabled_.load()) {
                ESP_LOGW(TAG, "Boot button double-click ignored: buttons not enabled");
                return;
            }
            CycleDisplayBrightness();
            RefreshSleepTimerState(true);
        });

        boot_button_.OnMultipleClick([this]() {
            if (!buttons_enabled_.load()) {
                ESP_LOGW(TAG, "Boot button multi-click ignored: buttons not enabled");
                return;
            }
            SwitchNetworkType();
            SetNetworkIndicator();
            RefreshSleepTimerState(true);
        }, 3);

        boot_button_.OnLongPress([this]() {
            if (!buttons_enabled_.load()) {
                ESP_LOGW(TAG, "Boot button long-press ignored: buttons not enabled");
                return;
            }
            if (current_mode_ == DeviceMode::AI_MODE) {
                Application::GetInstance().ToggleChatState();
            }
            RefreshSleepTimerState(true);
        });

        power_button_.OnClick([this]() {
            if (ShouldIgnorePowerButtonAction("click", true)) {
                return;
            }
            SwitchMode();
        });

        power_button_.OnLongPress([this]() {
            if (ShouldIgnorePowerButtonAction("long press")) {
                return;
            }
            StartShutdown();
        });

        power_button_.OnDoubleClick([this]() {
            if (ShouldIgnorePowerButtonAction("double click")) {
                return;
            }
            SetNightLight(!night_light_on_);
            if (display_) {
                // display_->ShowNotification(night_light_on_ ? "NIGHT ON" : "NIGHT OFF", 1500);
            }
            RefreshSleepTimerState(true);
        });

        power_button_.OnMultipleClick([this]() {
            if (ShouldIgnorePowerButtonAction("five-click")) {
                return;
            }
            auto* ml307c_board = dynamic_cast<Ml307CBoard*>(&GetCurrentBoard());
            if (ml307c_board) {
                ml307c_board->HandleBootButtonLongPress();
            }
            RefreshSleepTimerState(true);
        }, 5);

        volume_up_button_.OnClick([this]() {
            if (!buttons_enabled_.load()) {
                ESP_LOGW(TAG, "Volume up ignored: buttons not enabled");
                return;
            }
            auto codec = GetAudioCodec();
            
            if (current_mode_ == DeviceMode::AI_MODE) {
                // AI模式：通过codec调节音量
                int volume = codec->output_volume() + 10;
                if (volume > 100) {
                    volume = 100;
                }
                codec->SetOutputVolume(volume);
                ShowVolume(volume);
            } else {
                // BT/AUX模式：通过AT指令调节音量（模块范围 0-16）
                // 每次点击增加1级
                if (bt_volume_ < 16) {
                    std::string response;
                    if (SendBluetoothCommand("AT+SPKVOL=+", response, 1000)) {
                        bt_volume_++;
                        // 将模块音量 (0-16) 转换为 ESP32 音量显示 (0-100)
                        // 映射关系：模块音量 * 100 / 16 = ESP32 音量
                        int display_vol = (bt_volume_ * 100 + 8) / 16;
                        ESP_LOGI(TAG, "BT volume up: module=%d display=%d", bt_volume_, display_vol);
                        ShowVolume(display_vol);
                    } else {
                        ESP_LOGW(TAG, "BT volume up failed: %s", response.c_str());
                    }
                } else {
                    ESP_LOGI(TAG, "BT volume already at max (16)");
                }
            }
            RefreshSleepTimerState(true);
        });

        volume_down_button_.OnClick([this]() {
            if (!buttons_enabled_.load()) {
                ESP_LOGW(TAG, "Volume down ignored: buttons not enabled");
                return;
            }
            auto codec = GetAudioCodec();
            
            if (current_mode_ == DeviceMode::AI_MODE) {
                // AI模式：通过codec调节音量
                int volume = codec->output_volume() - 10;
                if (volume < 0) {
                    volume = 0;
                }
                codec->SetOutputVolume(volume);
                ShowVolume(volume);
            } else {
                // BT/AUX模式：通过AT指令调节音量（模块范围 0-16）
                // 每次点击减少1级
                if (bt_volume_ > 0) {
                    std::string response;
                    if (SendBluetoothCommand("AT+SPKVOL=-", response, 1000)) {
                        bt_volume_--;
                        int display_vol = (bt_volume_ * 100 + 8) / 16;
                        ESP_LOGI(TAG, "BT volume down: module=%d display=%d", bt_volume_, display_vol);
                        ShowVolume(display_vol);
                    } else {
                        ESP_LOGW(TAG, "BT volume down failed: %s", response.c_str());
                    }
                } else {
                    ESP_LOGI(TAG, "BT volume already at min (0)");
                }
            }
            RefreshSleepTimerState(true);
        });
    }

public:
    Esp32S3YHYBoard()
        : DualNetworkBoard(ML307C_TX_PIN, ML307C_RX_PIN, ML307C_DTR_PIN, 1, true),
          boot_button_(BOOT_BUTTON_GPIO),
          power_button_(POWER_BUTTON_GPIO),
          volume_up_button_(VOLUME_UP_BUTTON_GPIO),
          volume_down_button_(VOLUME_DOWN_BUTTON_GPIO) {
        
        // 默认禁用按钮，等待初始化完成后启用
        buttons_enabled_.store(false);
        
        // ========== 深度睡眠唤醒流程 ==========
        bool woke_from_deep_sleep = IsWakeFromPowerButton();
        
        if (woke_from_deep_sleep) {
            power_state_ = PowerState::WAKING_UP;
            ESP_LOGI(TAG, "=== Waking from deep sleep ===");
            
            // 先初始化基本GPIO
            InitializeFunctionPins();
            
            // 等待并确认长按2秒
            if (!WaitForWakeConfirm()) {
                ESP_LOGI(TAG, "Wake not confirmed, returning to deep sleep");
                EnterDeepSleepImmediately();
                return;  // 不会执行到这里
            }
            
            ESP_LOGI(TAG, "Wake confirmed, continuing initialization...");
            // 释放蓝牙 UART GPIO hold（EnterDeepSleep 中设置，防止蓝牙芯片误唤醒）
            gpio_hold_dis(BT_TX_PIN);
            gpio_hold_dis(BT_RX_PIN);
        } else {
            ESP_LOGI(TAG, "=== Normal boot (not from deep sleep) ===");
            InitializeFunctionPins();  // 正常启动也需要初始化GPIO
        }
        
        // ========== 正常运行初始化 ==========
        power_state_ = PowerState::RUNNING;
        
        InitializeI2c();
        InitializeDisplay();
        InitializeUart2();  // 初始化蓝牙 UART2
        InitializeButtons();
        InitializePower();
        InitializeTools();

        // 等待蓝牙模块稳定（至少1.5秒）
        vTaskDelay(pdMS_TO_TICKS(1500));
        
        // 优化版蓝牙初始化：合并名字检查和低功耗模式设置
        OptimizedBluetoothInit();
        
        ApplyRouteCommit(DeviceMode::AI_MODE);
        ignore_power_click_until_us_ = esp_timer_get_time() + (static_cast<int64_t>(kIgnorePowerClickAfterBootMs) * 1000);
        current_mode_ = DeviceMode::AI_MODE;
        // 确认唤醒后再设置LED指示灯
        SetModeIndicator(current_mode_);
        SetNetworkIndicator();
        RefreshSleepTimerStateForMode(current_mode_);
        
        // 初始化完成，启用按钮
        buttons_enabled_.store(true);
        ESP_LOGI(TAG, "Power state: RUNNING, buttons enabled");
    }

    // 唤醒确认：等待长按2秒，如果期间松开则返回false
    bool WaitForWakeConfirm() {
        ESP_LOGI(TAG, "Waiting for wake confirm (long press %d ms)...", kPowerWakeLongPressMs);
        
        int held_ms = 0;
        while (held_ms < kPowerWakeLongPressMs) {
            if (gpio_get_level(POWER_BUTTON_GPIO) != 0) {
                ESP_LOGI(TAG, "Wake not confirmed, button released at %d ms", held_ms);
                return false;
            }
            vTaskDelay(pdMS_TO_TICKS(kPowerWakeCheckStepMs));
            held_ms += kPowerWakeCheckStepMs;
        }
        
        ESP_LOGI(TAG, "Wake confirmed! Long press %d ms detected", held_ms);
        return true;
    }
    
    // 立即进入深度睡眠（用于唤醒确认失败）
    void EnterDeepSleepImmediately() {
        ESP_LOGI(TAG, "Entering deep sleep immediately");
        
        // 关闭显示
        if (display_) {
            display_->SetPowerSaveMode(true);
        }
        
        // 防止蓝牙芯片被误唤醒
        gpio_set_level(BT_TX_PIN, 1);
        gpio_hold_en(BT_TX_PIN);
        gpio_hold_en(BT_RX_PIN);
        gpio_deep_sleep_hold_en();
        
        // 配置唤醒源
        gpio_hold_en(POWER_BUTTON_GPIO);
        ESP_ERROR_CHECK(esp_sleep_enable_ext1_wakeup_io(1ULL << POWER_BUTTON_GPIO, ESP_EXT1_WAKEUP_ANY_LOW));
        
        esp_deep_sleep_start();
    }

    ~Esp32S3YHYBoard() {
        if (battery_monitor_ != nullptr) {
            delete battery_monitor_;
            battery_monitor_ = nullptr;
        }
        if (sleep_timer_ != nullptr) {
            delete sleep_timer_;
            sleep_timer_ = nullptr;
        }
        if (display_ != nullptr) {
            delete display_;
            display_ = nullptr;
        }
        if (i2c_bus_ != nullptr) {
            i2c_del_master_bus(i2c_bus_);
            i2c_bus_ = nullptr;
        }
    }

    virtual Led* GetLed() override {
        static SingleLed led(BUILTIN_LED_GPIO);
        return &led;
    }

    virtual Display* GetDisplay() override {
        return display_ ? display_ : Board::GetDisplay();
    }

    virtual AudioCodec* GetAudioCodec() override {
        static YhyAudioCodec* audio_codec = nullptr;
        if (audio_codec == nullptr) {
            audio_codec = new YhyAudioCodec(i2c_bus_);
        }
        return audio_codec;
    }

    virtual bool GetBatteryLevel(int& level, bool& charging, bool& discharging) override {
        if (battery_monitor_ == nullptr) {
            return false;
        }
        level = battery_monitor_->GetBatteryLevel();
        charging = battery_monitor_->IsCharging();
        discharging = !charging;
        return true;
    }

    virtual bool IsPlaybackMode() override {
        return current_mode_ == DeviceMode::BLUETOOTH_MODE || current_mode_ == DeviceMode::AUX_MODE;
    }

    virtual void OnAudioServiceStarted() override {
        ESP_LOGI(TAG, "Prompt start for boot");
        Application::GetInstance().PlaySound(Lang::Sounds::OGG_PWRON);
        WaitPromptPlaybackDone();
        ESP_LOGI(TAG, "Prompt done for boot");

        ESP_LOGI(TAG, "Prompt start for mode=%s", ModeName(current_mode_));
        PlayModePrompt(current_mode_);
        WaitPromptPlaybackDone();
        ESP_LOGI(TAG, "Prompt done for mode=%s", ModeName(current_mode_));

        EnableAIVoice();
    }

    virtual void Shutdown() override {
        StartShutdown();
    }

    virtual std::string GetBoardType() override {
        return "esp32-s3-yhy";
    }

    virtual void SetPowerSaveLevel(PowerSaveLevel level) override {
        if (sleep_timer_) {
            sleep_timer_->WakeUp();
        }
        DualNetworkBoard::SetPowerSaveLevel(level);
    }
};

DECLARE_BOARD(Esp32S3YHYBoard);
