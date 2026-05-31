#include "ml307c_board.h"

#include "audio/audio_codec.h"
#include "display/display.h"

#include <driver/uart.h>
#include <esp_log.h>
#include <esp_sleep.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <cJSON.h>
#include <cctype>
#include <utility>

static const char *TAG = "Ml307CBoard";

namespace {
    bool IsWakeFromDeepSleep() {
        return esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT1;
    }
}

namespace {
    bool ContainsLongDigitSequence(const std::string& s, int min_len) {
        int run = 0;
        for (unsigned char ch : s) {
            if (std::isdigit(ch)) {
                run++;
                if (run >= min_len) {
                    return true;
                }
            } else {
                run = 0;
            }
        }
        return false;
    }

    bool SoftSelectSimSlotAndVerify(AtUart* uart, int slot, int timeout_ms) {
        if (uart == nullptr) {
            return false;
        }
        // ML307C-DL-CN-MBRH0S00（单卡软切版本）:
        // 1) AT*SELECTSIMSLOT=x  切换卡槽
        // 2) 等待+CPIN URC到达（+CPIN: READY或+CPIN: SIM REMOVED）
        // 3) 等待>=500ms
        // 4) AT+CIMI             读取IMSI验证有效性（返回长数字串才算有效）
        // 注意：AT*SIMDETEC命令在某些情况下会超时或不稳定，直接使用AT+CIMI验证更可靠
        // 注意：双卡场景下,模组需要更长时间稳定,增加超时时间和等待时间
        const std::string select_cmd = "AT*SELECTSIMSLOT=" + std::to_string(slot);
        ESP_LOGI(TAG, "Soft SIM select: %s", select_cmd.c_str());

        // 双卡场景下,切换卡槽需要更长时间,增加超时时间到15秒
        int extended_timeout = (timeout_ms < 15000) ? 15000 : timeout_ms;
        if (!uart->SendCommand(select_cmd, extended_timeout)) {
            ESP_LOGW(TAG, "Soft SIM select failed (slot=%d)", slot);
            return false;
        }

        // 等待+CPIN URC到达（+CPIN状态会作为URC异步到达）
        // AT*SELECTSIMSLOT先返回OK，然后+CPIN URC再到达
        // 双卡场景下增加等待时间到2秒
        vTaskDelay(pdMS_TO_TICKS(2000));  // 给+CPIN URC足够的时间到达

        ESP_LOGI(TAG, "Soft SIM verify (IMSI): AT+CIMI");
        // AT+CIMI也可能需要更长时间,使用扩展的超时时间
        if (!uart->SendCommand("AT+CIMI", extended_timeout)) {
            ESP_LOGW(TAG, "Soft SIM IMSI query failed (slot=%d)", slot);
            return false;
        }
        std::string imsi_resp = uart->GetResponse();
        ESP_LOGI(TAG, "Soft SIM IMSI response: [%s]", imsi_resp.c_str());

        // IMSI通常为 15 位数字；这里用">=14 连续数字"作为宽松判断，避免不同换行/前缀导致误判。
        if (!ContainsLongDigitSequence(imsi_resp, 14)) {
            ESP_LOGW(TAG, "Soft SIM IMSI not valid (slot=%d)", slot);
            return false;
        }

        ESP_LOGI(TAG, "Soft SIM slot %d verified OK", slot);
        return true;
    }
} // namespace

Ml307CBoard::Ml307CBoard(gpio_num_t tx_pin, gpio_num_t rx_pin, gpio_num_t dtr_pin)
    : Ml307Board(tx_pin, rx_pin, dtr_pin) {
}

Ml307CBoard::~Ml307CBoard() {
    // 停止自动模式任务
    if (auto_mode_task_handle_) {
        vTaskDelete(auto_mode_task_handle_);
        auto_mode_task_handle_ = NULL;
    }
}

bool Ml307CBoard::WaitForModemReady(AtUart* uart) {
    constexpr int kMaxRetries = 10;
    constexpr int kRetryDelayMs = 1000;
    
    ESP_LOGI(TAG, "Waiting for modem to be fully ready...");
    
    for (int retry = 0; retry < kMaxRetries; retry++) {
        // 发送AT命令测试模组是否响应
        if (uart->SendCommand("AT", 1000)) {
            ESP_LOGI(TAG, "Modem is ready after %d attempts", retry + 1);
            return true;
        }
        
        ESP_LOGW(TAG, "Modem not ready yet, retry %d/%d", retry + 1, kMaxRetries);
        vTaskDelay(pdMS_TO_TICKS(kRetryDelayMs));
    }
    
    ESP_LOGE(TAG, "Modem not ready after %d attempts", kMaxRetries);
    return false;
}

void Ml307CBoard::OnModemReady() {
    ESP_LOGI(TAG, "OnModemReady: Configuring dual SIM...");

    // 注意：此时 modem 可能还未完全准备好接收AT命令
    // ML307C 特定初始化：优先尝试主卡槽
    if (modem_) {
        auto uart = modem_->GetAtUart();
        if (uart) {
            if (IsWakeFromDeepSleep()) {
                ESP_LOGI(TAG, "Deep-sleep wake detected, rebooting ML307C before SIM initialization...");
                modem_->Reboot();
                vTaskDelay(pdMS_TO_TICKS(5000));
            }

            // 检查调制解调器状态，确保完全就绪
            if (!WaitForModemReady(uart.get())) {
                ESP_LOGE(TAG, "Modem not ready, skipping SIM selection");
                return;
            }
            
            // 检测模组型号
            std::string module_rev = modem_->GetModuleRevision();
            ESP_LOGI(TAG, "Detected modem revision: %s", module_rev.c_str());

            constexpr int kTimeoutMs = 15000;
            
            // 读取主卡槽配置（默认为0）
            int primary_slot = CONFIG_ML307C_DUAL_SIM_PRIMARY_SLOT;
            int backup_slot = (primary_slot == 1) ? 0 : 1;
            
            ESP_LOGI(TAG, "Starting Soft SIM primary slot %d detection...", primary_slot);

            bool ok_primary = SoftSelectSimSlotAndVerify(uart.get(), primary_slot, kTimeoutMs);
            // if (!ok_primary) {
            //     ESP_LOGW(TAG, "Soft SIM primary slot %d failed on first attempt, retrying once...", primary_slot);
            //     vTaskDelay(pdMS_TO_TICKS(1000));
            //     ok_primary = SoftSelectSimSlotAndVerify(uart.get(), primary_slot, kTimeoutMs);
            // }
            if (ok_primary) {
                ESP_LOGI(TAG, "Soft SIM primary slot %d verified OK", primary_slot);
                current_soft_sim_slot_ = primary_slot;
            } else {
                ESP_LOGW(TAG, "Soft SIM primary slot %d failed, trying backup slot %d", primary_slot, backup_slot);
                ESP_LOGI(TAG, "Starting Soft SIM backup slot %d detection...", backup_slot);
                bool ok_backup = SoftSelectSimSlotAndVerify(uart.get(), backup_slot, kTimeoutMs);
                if (ok_backup) {
                    ESP_LOGI(TAG, "Soft SIM backup slot %d verified OK", backup_slot);
                    current_soft_sim_slot_ = backup_slot;
                } else {
                    ESP_LOGE(TAG, "Both SIM slots failed");
                    current_soft_sim_slot_ = primary_slot; // 默认使用主卡槽
                }
            }
        } else {
            ESP_LOGW(TAG, "AT UART not available, skipping SIM selection");
        }
    }

    // 启动自动模式任务（如果配置为自动模式）
#if CONFIG_ML307C_DUAL_SIM_AUTO
    ESP_LOGI(TAG, "Starting auto mode task for SIM signal monitoring...");
    xTaskCreate(AutoModeTaskEntry, "auto_mode_task", 4096, this, 4, &auto_mode_task_handle_);
#endif


//     // todo:AT命令测试
//     ESP_LOGI(TAG, "AT test mode enabled, category: %s", "all");
//     vTaskDelay(pdMS_TO_TICKS(2000));  // 等待模组完全就绪
//     TestAtCommands();

}

// Maximum retry count for modem detection
static constexpr int MODEM_DETECT_MAX_RETRIES = 30;
// Maximum retry count for network registration
static constexpr int NETWORK_REG_MAX_RETRIES = 6;
void Ml307CBoard::StartNetwork() {
    // 创建网络初始化任务并立即返回
    xTaskCreate([](void* arg) {
        Ml307CBoard* board = static_cast<Ml307CBoard*>(arg);
        board->NetworkTaskWithSimFailover();
        vTaskDelete(NULL);
    }, "ml307c_net", 4096, this, 5, NULL);
}

void Ml307CBoard::NetworkTaskWithSimFailover() {
    // Notify modem detection started
    OnNetworkEvent(NetworkEvent::ModemDetecting);

    // ML307C模块上电后需要一段时间来初始化，等待5秒让模块完全启动
    ESP_LOGI(TAG, "Waiting 0.5s for ML307C module to initialize...");
    vTaskDelay(pdMS_TO_TICKS(500));

    // 说明：
    // - UART1（蓝牙）使用 GPIO17/GPIO18，已在 Esp32S3Ml307cTm1629aBoard 构造函数中初始化为 DMA 模式
    // - UART0（ML307C）使用 GPIO43/GPIO44，由 AtModem::Detect 中的 AtUart 初始化为 UHCI DMA 模式
    // - 两者使用不同的 GPIO 和 GDMA 通道，不会冲突
    // - 两者使用不同的 GPIO 和 GDMA 通道，理论上不应该冲突
    // 如果 AtModem::Detect 失败，尝试重置可能被占用的 GPIO
    vTaskDelay(pdMS_TO_TICKS(100));
    gpio_reset_pin(tx_pin_);
    gpio_reset_pin(rx_pin_);
    
    // Try to detect modem with retry limit at 921600 baud rate
    int detect_retries = 0;
    const int baud_rate = 921600;
    
    while (detect_retries < MODEM_DETECT_MAX_RETRIES) {
        ESP_LOGI(TAG, "Trying to detect modem at baud rate: %d, attempt %d/%d", baud_rate, detect_retries + 1, MODEM_DETECT_MAX_RETRIES);
        
        // 直接使用921600波特率检测modem，不进行波特率检测
        modem_ = AtModem::Detect(tx_pin_, rx_pin_, dtr_pin_, baud_rate, 5000);  // 5秒超时
        if (modem_ != nullptr) {
            ESP_LOGI(TAG, "Modem detected successfully at baud rate: %d", baud_rate);
            break;
        }
        detect_retries++;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    if (modem_ == nullptr) {
        ESP_LOGE(TAG, "Failed to detect modem after %d retries", MODEM_DETECT_MAX_RETRIES);
        OnNetworkEvent(NetworkEvent::ModemErrorInitFailed);
        return;
    }

    ESP_LOGI(TAG, "Modem detected successfully");

    // Call virtual function to allow subclasses to configure modem (e.g., dual SIM)
    // This is called after modem is detected but before network registration
    OnModemReady();

    // Set up network state change callback
    modem_->OnNetworkStateChanged([this](bool network_ready) {
        if (network_ready) {
            OnNetworkEvent(NetworkEvent::Connected);
        } else {
            ESP_LOGW(TAG, "Network disconnected, attempting to reconnect...");
            OnNetworkEvent(NetworkEvent::Disconnected);

            // 自动重连（与ML307R/ml307_board.cc一致）
            if (!stop_reconnect_) {
                int reconnect_retries = 0;
                const int max_reconnect_retries = 5;
                while (reconnect_retries < max_reconnect_retries && !stop_reconnect_) {
                    ESP_LOGI(TAG, "Reconnecting... attempt %d/%d", reconnect_retries + 1, max_reconnect_retries);
                    auto result = modem_->WaitForNetworkReady(30000);
                    if (result == NetworkStatus::Ready) {
                        ESP_LOGI(TAG, "Reconnected successfully");
                        OnNetworkEvent(NetworkEvent::Connected);
                        return;
                    }
                    reconnect_retries++;
                    vTaskDelay(pdMS_TO_TICKS(5000));
                }

                if (!stop_reconnect_) {
                    ESP_LOGE(TAG, "Reconnection failed after %d attempts", max_reconnect_retries);
                }
            }
        }
    });

    // Notify network registration started
    OnNetworkEvent(NetworkEvent::Connecting);

    // Wait for network ready with retry limit - with SIM failover
    int reg_retries = 0;
    int max_reg_retries = NETWORK_REG_MAX_RETRIES * 2;  // 增加重试次数以支持SIM切换
    constexpr int kNetworkRegTimeoutMs = 30000;  // 首次网络注册超时时间30秒,用于触发SIM切换

    while (reg_retries < max_reg_retries) {
        // 第一次尝试设置超时时间,以便触发SIM切换;后续尝试使用默认超时
        int timeout_ms = (reg_retries == 0) ? kNetworkRegTimeoutMs : -1;
        auto result = modem_->WaitForNetworkReady(timeout_ms);
        if (result == NetworkStatus::Ready) {
            break;
        } else if (result == NetworkStatus::ErrorInsertPin) {
            OnNetworkEvent(NetworkEvent::ModemErrorNoSim);
        } else if (result == NetworkStatus::ErrorRegistrationDenied) {
            OnNetworkEvent(NetworkEvent::ModemErrorRegDenied);
        } else if (result == NetworkStatus::ErrorTimeout) {
            ESP_LOGW(TAG, "Network registration timeout (slot=%d)", current_soft_sim_slot_);

            // 检查是否为第一次超时，尝试切换SIM卡槽
            if (reg_retries == 0) {
                int backup_slot = (current_soft_sim_slot_ == 1) ? 0 : 1;
                ESP_LOGI(TAG, "Trying backup SIM slot %d...", backup_slot);

                auto uart = modem_->GetAtUart();
                if (uart) {
                    if (SwitchSoftSimSlot(backup_slot)) {
                        ESP_LOGI(TAG, "Switched to SIM slot %d, retrying network registration", backup_slot);
                        // 继续下一次重试，不需要额外延迟
                        reg_retries++;
                        continue;
                    } else {
                        ESP_LOGE(TAG, "Failed to switch to SIM slot %d", backup_slot);
                    }
                }
            }

            OnNetworkEvent(NetworkEvent::ModemErrorTimeout);
        }
        reg_retries++;
        vTaskDelay(pdMS_TO_TICKS(10000));
    }

    if (!modem_->network_ready()) {
        ESP_LOGE(TAG, "Failed to register network after %d retries", max_reg_retries);
        return;
    }

    // Print the ML307 modem information
    std::string module_revision = modem_->GetModuleRevision();
    std::string imei = modem_->GetImei();
    std::string iccid = modem_->GetIccid();
    ESP_LOGI(TAG, "ML307 Revision: %s", module_revision.c_str());
    ESP_LOGI(TAG, "ML307 IMEI: %s", imei.c_str());
    ESP_LOGI(TAG, "ML307 ICCID: %s", iccid.c_str());
}

bool Ml307CBoard::SwitchSoftSimSlot(int target_slot) {
    if (!modem_) {
        ESP_LOGE(TAG, "Modem not initialized");
        return false;
    }

    // 验证目标卡槽
    if (target_slot != 0 && target_slot != 1) {
        ESP_LOGE(TAG, "Invalid target slot: %d, must be 0 or 1", target_slot);
        return false;
    }

    // 如果目标卡槽与当前相同，直接返回成功
    if (target_slot == current_soft_sim_slot_) {
        ESP_LOGI(TAG, "Already on SIM slot %d, no switch needed", target_slot);
        return true;
    }

    ESP_LOGI(TAG, "Switching from SIM slot %d to SIM slot %d", current_soft_sim_slot_, target_slot);

    auto uart = modem_->GetAtUart();
    if (!uart) {
        ESP_LOGE(TAG, "AT UART not available");
        return false;
    }

    constexpr int kTimeoutMs = 5000;

    // 1. 切换卡槽 - 增加重试逻辑
    const std::string select_cmd = "AT*SELECTSIMSLOT=" + std::to_string(target_slot);
    ESP_LOGI(TAG, "Soft SIM select: %s", select_cmd.c_str());

    bool select_success = false;
    for (int retry = 0; retry < CONFIG_ML307C_SIM_SWITCH_RETRY_TIMES; retry++) {
        if (uart->SendCommand(select_cmd, kTimeoutMs)) {
            select_success = true;
            break;
        }
        ESP_LOGW(TAG, "AT*SELECTSIMSLOT command failed, retry %d/%d", retry + 1, CONFIG_ML307C_SIM_SWITCH_RETRY_TIMES);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    if (!select_success) {
        ESP_LOGE(TAG, "Failed to send AT*SELECTSIMSLOT command after %d retries", CONFIG_ML307C_SIM_SWITCH_RETRY_TIMES);
        return false;
    }

    // 等待+CPIN URC到达（+CPIN状态会作为URC异步到达）
    // AT*SELECTSIMSLOT先返回OK，然后+CPIN URC再到达
    vTaskDelay(pdMS_TO_TICKS(CONFIG_ML307C_SIM_SWITCH_DELAY_MS));  // 给+CPIN URC足够的时间到达

    // 2. 检测SIM卡存在性 - 增加重试逻辑
    const std::string det_cmd = "AT*SIMDETEC=" + std::to_string(target_slot);
    ESP_LOGI(TAG, "Soft SIM detect: %s", det_cmd.c_str());
    
    bool det_success = false;
    std::string det_resp;
    for (int retry = 0; retry < CONFIG_ML307C_SIM_SWITCH_RETRY_TIMES; retry++) {
        if (uart->SendCommand(det_cmd, kTimeoutMs)) {
            det_resp = uart->GetResponse();
            det_success = true;
            break;
        }
        ESP_LOGW(TAG, "AT*SIMDETEC command failed, retry %d/%d", retry + 1, CONFIG_ML307C_SIM_SWITCH_RETRY_TIMES);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
    if (!det_success) {
        ESP_LOGE(TAG, "Failed to send AT*SIMDETEC command after %d retries", CONFIG_ML307C_SIM_SWITCH_RETRY_TIMES);
        return false;
    }

    ESP_LOGI(TAG, "Soft SIM detect response: [%s]", det_resp.c_str());
    const std::string expected = "*SIMDETEC: " + std::to_string(target_slot) + ",SIM";
    if (det_resp.find(expected) == std::string::npos) {
        ESP_LOGE(TAG, "Soft SIM slot %d not present/active", target_slot);
        return false;
    }

    // 3. 验证IMSI - 增加重试逻辑
    ESP_LOGI(TAG, "Soft SIM verify (IMSI): AT+CIMI");
    
    bool imsi_success = false;
    std::string imsi_resp;
    for (int retry = 0; retry < CONFIG_ML307C_SIM_SWITCH_RETRY_TIMES; retry++) {
        if (uart->SendCommand("AT+CIMI", kTimeoutMs)) {
            imsi_resp = uart->GetResponse();
            imsi_success = true;
            break;
        }
        ESP_LOGW(TAG, "AT+CIMI command failed, retry %d/%d", retry + 1, CONFIG_ML307C_SIM_SWITCH_RETRY_TIMES);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
    if (!imsi_success) {
        ESP_LOGE(TAG, "Failed to send AT+CIMI command after %d retries", CONFIG_ML307C_SIM_SWITCH_RETRY_TIMES);
        return false;
    }
    
    ESP_LOGI(TAG, "Soft SIM IMSI response: [%s]", imsi_resp.c_str());

    if (!ContainsLongDigitSequence(imsi_resp, 14)) {
        ESP_LOGE(TAG, "Soft SIM IMSI not valid (slot=%d)", target_slot);
        return false;
    }

    // 切换成功，更新当前卡槽
    current_soft_sim_slot_ = target_slot;
    ESP_LOGI(TAG, "Soft SIM slot %d verified OK, switch completed", target_slot);
    return true;
}

std::string Ml307CBoard::GetBoardJson() {
    // 调用基类实现
    std::string board_json = Ml307Board::GetBoardJson();

    return board_json;
}

std::string Ml307CBoard::GetDeviceStatusJson() {
    /*
     * 返回设备状态JSON（包含双卡信息）
     *
     * 返回的JSON结构如下：
     * {
     *     "audio_speaker": {
     *         "volume": 70
     *     },
     *     "screen": {
     *         "brightness": 100,
     *         "theme": "light"
     *     },
     *     "battery": {
     *         "level": 50,
     *         "charging": true
     *     },
     *     "network": {
     *         "type": "cellular",
     *         "dual_sim": {
     *             "mode": 1,
     *             "current_sim": 0,
     *             "sim1": {
     *                 "iccid": "898601...1234",
     *                 "csq": 20
     *             },
     *             "sim2": {
     *                 "iccid": "898601...5678",
     *                 "csq": 18
     *             }
     *         },
     *         "carrier": "CHINA MOBILE",
     *         "csq": 20
     *     }
     * }
     */

    // 调用基类实现
    auto& board = Board::GetInstance();
    auto root = cJSON_CreateObject();

    // Audio speaker
    auto audio_speaker = cJSON_CreateObject();
    auto audio_codec = board.GetAudioCodec();
    if (audio_codec) {
        cJSON_AddNumberToObject(audio_speaker, "volume", audio_codec->output_volume());
    }
    cJSON_AddItemToObject(root, "audio_speaker", audio_speaker);

    // Screen brightness
    auto backlight = board.GetBacklight();
    auto screen = cJSON_CreateObject();
    if (backlight) {
        cJSON_AddNumberToObject(screen, "brightness", backlight->brightness());
    }
    auto display = board.GetDisplay();
    if (display && display->height() > 64) { // For LCD display only
        auto theme = display->GetTheme();
        if (theme != nullptr) {
            cJSON_AddStringToObject(screen, "theme", theme->name().c_str());
        }
    }
    cJSON_AddItemToObject(root, "screen", screen);

    // Battery
    int battery_level = 0;
    bool charging = false;
    bool discharging = false;
    if (board.GetBatteryLevel(battery_level, charging, discharging)) {
        cJSON* battery = cJSON_CreateObject();
        cJSON_AddNumberToObject(battery, "level", battery_level);
        cJSON_AddBoolToObject(battery, "charging", charging);
        cJSON_AddItemToObject(root, "battery", battery);
    }

    // Network with dual SIM info
    auto network = cJSON_CreateObject();
    cJSON_AddStringToObject(network, "type", "cellular");

    // Current network info
    if (modem_) {
        cJSON_AddStringToObject(network, "carrier", modem_->GetCarrierName().c_str());
        int csq = modem_->GetCsq();
        if (csq == -1) {
            cJSON_AddStringToObject(network, "signal", "unknown");
        } else if (csq >= 0 && csq <= 14) {
            cJSON_AddStringToObject(network, "signal", "very weak");
        } else if (csq >= 15 && csq <= 19) {
            cJSON_AddStringToObject(network, "signal", "weak");
        } else if (csq >= 20 && csq <= 24) {
            cJSON_AddStringToObject(network, "signal", "medium");
        } else if (csq >= 25 && csq <= 31) {
            cJSON_AddStringToObject(network, "signal", "strong");
        }
    }

    cJSON_AddItemToObject(root, "network", network);

    auto json_str = cJSON_PrintUnformatted(root);
    std::string json(json_str);
    cJSON_free(json_str);
    cJSON_Delete(root);
    return json;
}

void Ml307CBoard::TestAtCommands(const std::string& category) {
    if (!modem_) {
        ESP_LOGE(TAG, "Modem未初始化，无法测试AT命令");
        return;
    }

    auto uart = modem_->GetAtUart();
    if (!uart) {
        ESP_LOGE(TAG, "AT UART不可用");
        return;
    }

    ESP_LOGI(TAG, "========== 开始AT命令测试 ==========");
    ESP_LOGI(TAG, "测试分类: %s", category.c_str());

    AtCommandTester tester(uart);

    if (category == "all") {
        tester.TestAllCommands();
    } else if (category == "basic") {
        tester.TestBasicCommands();
    } else if (category == "sim") {
        tester.TestSimCommands();
    } else if (category == "network") {
        tester.TestNetworkCommands();
    } else if (category == "dialup") {
        tester.TestDialupCommands();
    } else if (category == "tcpip") {
        tester.TestTcpIpCommands();
    } else if (category == "mqtt") {
        tester.TestMqttCommands();
    } else if (category == "http") {
        tester.TestHttpCommands();
    } else if (category == "hardware") {
        tester.TestHardwareCommands();
    } else if (category == "lowpower") {
        tester.TestLowPowerCommands();
    } else if (category == "power") {
        tester.TestPowerCommands();
    } else {
        // 尝试作为单个命令执行
        ESP_LOGI(TAG, "执行单个命令: %s", category.c_str());
        tester.TestCommand(category, "用户指定命令", 3000);
    }

    ESP_LOGI(TAG, "测试完成!");
}

void Ml307CBoard::AutoModeTaskEntry(void* arg) {
    Ml307CBoard* board = static_cast<Ml307CBoard*>(arg);
    board->AutoModeTask();
    vTaskDelete(NULL);
}

void Ml307CBoard::AutoModeTask() {
    ESP_LOGI(TAG, "Auto mode task started");
    
    // 自动模式：当前SIM卡断网时自动切换到其他网络
    while (true) {
        // 每20秒检测一次网络状态
        vTaskDelay(pdMS_TO_TICKS(20000));
        
        if (!modem_) {
            continue;
        }
        
        // 检查当前网络状态
        if (!modem_->network_ready()) {
            // 网络断开
            ESP_LOGW(TAG, "Current SIM slot %d network disconnected, trying to switch to backup SIM", current_soft_sim_slot_);
            
            // 当前SIM卡断网，尝试切换到另一个SIM卡
            int backup_slot = (current_soft_sim_slot_ == 0) ? 1 : 0;
            
            // 先检测备用SIM卡的信号强度
            int backup_signal = GetSimSignalStrength(backup_slot);
            if (backup_signal > 0) {
                ESP_LOGI(TAG, "Backup SIM slot %d has signal (strength: %d), switching...", backup_slot, backup_signal);
                if (SwitchSoftSimSlot(backup_slot)) {
                    ESP_LOGI(TAG, "Successfully switched to backup SIM slot %d", backup_slot);
                    // 等待网络注册
                    vTaskDelay(pdMS_TO_TICKS(5000));
                    continue;
                } else {
                    ESP_LOGE(TAG, "Failed to switch to backup SIM slot %d", backup_slot);
                }
            } else {
                ESP_LOGW(TAG, "Backup SIM slot %d has no signal, staying on current SIM", backup_slot);
            }
        } else {
            // 网络正常，检测是否需要切换到信号更好的SIM卡
            SwitchToStrongerSignalSim();
        }
    }
}

int Ml307CBoard::GetSimSignalStrength(int slot) {
    if (!modem_) {
        ESP_LOGE(TAG, "Modem not initialized");
        return -1;
    }
    
    // 保存当前卡槽
    int original_slot = current_soft_sim_slot_;
    int signal_strength = -1;
    
    // 如果不是当前卡槽，先切换过去
    if (slot != original_slot) {
        if (!SwitchSoftSimSlot(slot)) {
            ESP_LOGE(TAG, "Failed to switch to SIM slot %d for signal strength test", slot);
            return -1;
        }
        
        // 等待网络稳定
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
    
    // 获取信号强度
    signal_strength = modem_->GetCsq();
    ESP_LOGI(TAG, "SIM slot %d signal strength: %d", slot, signal_strength);
    
    // 切回原来的卡槽
    if (slot != original_slot) {
        SwitchSoftSimSlot(original_slot);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
    
    return signal_strength;
}

bool Ml307CBoard::SwitchToStrongerSignalSim() {
    // 检测两个SIM卡的信号强度
    int slot0_strength = GetSimSignalStrength(0);
    int slot1_strength = GetSimSignalStrength(1);
    
    // 更新信号强度历史记录
    sim0_signal_strength_ = slot0_strength;
    sim1_signal_strength_ = slot1_strength;
    
    // 只有当两个SIM卡都有有效信号时才考虑切换
    if (slot0_strength == -1 && slot1_strength == -1) {
        ESP_LOGW(TAG, "Both SIM cards have no signal");
        return false;
    }
    
    // 计算信号强度差异（至少相差5个单位才切换）
    int signal_diff = abs(slot0_strength - slot1_strength);
    
    if (slot0_strength > slot1_strength && signal_diff >= 5) {
        // SIM0信号更强
        if (current_soft_sim_slot_ != 0) {
            ESP_LOGI(TAG, "Switching to SIM slot 0 for better signal (slot0: %d, slot1: %d)", slot0_strength, slot1_strength);
            return SwitchSoftSimSlot(0);
        }
    } else if (slot1_strength > slot0_strength && signal_diff >= 5) {
        // SIM1信号更强
        if (current_soft_sim_slot_ != 1) {
            ESP_LOGI(TAG, "Switching to SIM slot 1 for better signal (slot0: %d, slot1: %d)", slot0_strength, slot1_strength);
            return SwitchSoftSimSlot(1);
        }
    }
    
    // 信号强度差异不大，不切换
    ESP_LOGI(TAG, "Signal strength difference not significant (slot0: %d, slot1: %d)", slot0_strength, slot1_strength);
    return false;
}

void Ml307CBoard::HandleBootButtonLongPress() {
    ESP_LOGI(TAG, "Boot button long press detected, toggling SIM slot");
    
    // 切换到另一个SIM卡槽
    int target_slot = (current_soft_sim_slot_ == 0) ? 1 : 0;
    
    if (SwitchSoftSimSlot(target_slot)) {
        ESP_LOGI(TAG, "Successfully switched to SIM slot %d", target_slot);
    } else {
        ESP_LOGE(TAG, "Failed to switch SIM slot");
    }
}

void Ml307CBoard::RestartModem() {
    if (!modem_) {
        ESP_LOGE(TAG, "Modem not initialized, trying to detect...");
        // 尝试重新检测modem
        ESP_LOGI(TAG, "Trying to detect modem at baud rate: %d", 921600);
        
        modem_ = AtModem::Detect(tx_pin_, rx_pin_, dtr_pin_, 921600, 10000);
        if (modem_ != nullptr) {
            ESP_LOGI(TAG, "Modem detected successfully at baud rate: %d", 921600);
        }else{
            ESP_LOGE(TAG, "Failed to detect modem");
            return;
        }
    }
    
    auto uart = modem_->GetAtUart();
    if (!uart) {
        ESP_LOGE(TAG, "AT UART not available");
        return;
    }
    
    ESP_LOGI(TAG, "Restarting ML307C...");
    // 发送AT+RST命令重启modem
    if (uart->SendCommand("AT+RST", 5000)) {
        ESP_LOGI(TAG, "ML307C restart command sent successfully");
        // 等待modem重启
        vTaskDelay(pdMS_TO_TICKS(5000));
    } else {
        ESP_LOGE(TAG, "Failed to send restart command");
    }
}

void Ml307CBoard::StopNetworkReconnect() {
    stop_reconnect_ = true;
    ESP_LOGI(TAG, "Network reconnect stopped");
}

void Ml307CBoard::ResumeNetworkReconnect() {
    stop_reconnect_ = false;
    ESP_LOGI(TAG, "Network reconnect resumed");
    
    if (!modem_) {
        ESP_LOGW(TAG, "Modem not available, skipping network reconnect");
        return;
    }
    
    auto result = modem_->WaitForNetworkReady(3000);
    if (result != NetworkStatus::Ready) {
        ESP_LOGI(TAG, "Network not ready, triggering reconnect...");
        xTaskCreate([](void* arg) {
            Ml307CBoard* board = static_cast<Ml307CBoard*>(arg);
            int reconnect_retries = 0;
            const int max_reconnect_retries = 5;
            while (reconnect_retries < max_reconnect_retries && !board->stop_reconnect_) {
                ESP_LOGI(TAG, "Reconnecting... attempt %d/%d", reconnect_retries + 1, max_reconnect_retries);
                auto result = board->modem_->WaitForNetworkReady(30000);
                if (result == NetworkStatus::Ready) {
                    ESP_LOGI(TAG, "Reconnected successfully");
                    board->OnNetworkEvent(NetworkEvent::Connected);
                    vTaskDelete(NULL);
                    return;
                }
                reconnect_retries++;
                vTaskDelay(pdMS_TO_TICKS(5000));
            }
            if (!board->stop_reconnect_) {
                ESP_LOGE(TAG, "Reconnection failed after %d attempts", max_reconnect_retries);
            }
            vTaskDelete(NULL);
        }, "ml307c_reconnect", 4096, this, 5, NULL);
    } else {
        ESP_LOGI(TAG, "Network already ready");
    }
}
