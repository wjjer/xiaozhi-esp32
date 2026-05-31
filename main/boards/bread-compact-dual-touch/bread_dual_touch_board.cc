#include "dual_network_board.h"
#include "display/lcd_display.h"
#include "audio/codecs/box_audio_codec.h"
#include "application.h"
#include "button.h"
#include "led/single_led.h"
#include "config.h"
#include "assets/lang_config.h"
#include <font_awesome.h>
#include "oscillator.h"

#include <esp_lcd_panel_vendor.h>
#include <esp_lcd_gc9a01.h>
#include "esp_lcd_gc9d01n.h"
#include <wifi_station.h>
#include <esp_log.h>
#include <driver/i2c_master.h>
#include <driver/spi_common.h>
#include <esp_lcd_panel_io.h>
#include <esp_lcd_panel_ops.h>
#include <driver/touch_pad.h>
#include <esp_timer.h>
#include <esp_deep_sleep.h>

#define TAG "BreadDualTouchBoard"

// 定义 millis() 函数供 Oscillator 使用
unsigned long IRAM_ATTR millis() {
    return (unsigned long)(esp_timer_get_time() / 1000ULL);
}

LV_FONT_DECLARE(font_puhui_16_4);
LV_FONT_DECLARE(font_awesome_16_4);

class BreadDualTouchBoard : public DualNetworkBoard {
private:
    i2c_master_bus_handle_t i2c_bus_;
    Button boot_button_;
    LcdDisplay* display_;
    esp_lcd_panel_io_handle_t panel_io_ = nullptr;
    esp_lcd_panel_handle_t panel_ = nullptr;

    // 触摸传感器相关变量
    uint32_t touch_left_value_ = 0;
    uint32_t touch_right_value_ = 0;

    // 舵机控制相关变量
    Oscillator* head_servo_;
    Oscillator* tail_servo_;
    esp_timer_handle_t servo_timer_;
    bool servos_enabled_;

    // ==================== 触摸传感器初始化 ====================
    void touch_init() {
        ESP_LOGI(TAG, "Initializing touch sensors...");

        // 初始化触摸传感器 (使用旧 API)
        touch_pad_init();
        touch_pad_config(TOUCH_LEFT_PAD);
        touch_pad_config(TOUCH_RIGHT_PAD);
        touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);
        touch_pad_fsm_start();

        // 等待初始化完成
        vTaskDelay(40 / portTICK_PERIOD_MS);

        ESP_LOGI(TAG, "Touch sensors initialized: LEFT=%d, RIGHT=%d", TOUCH_LEFT_PAD, TOUCH_RIGHT_PAD);
    }

    // ==================== 舵机初始化 ====================
    void servos_init() {
        ESP_LOGI(TAG, "Initializing servos...");

        // 创建摇头舵机
        head_servo_ = new Oscillator(0);  // trim=0, 无偏移
        head_servo_->Attach(SERVO_HEAD_PIN, false);  // 不反向
        head_servo_->SetA(SERVO_HEAD_AMPLITUDE);  // 设置摆动幅度
        head_servo_->SetT(SERVO_HEAD_PERIOD);    // 设置摆动周期
        head_servo_->SetO(0);  // 偏移角度
        head_servo_->Stop();  // 初始停止

        // 创建甩尾巴舵机
        tail_servo_ = new Oscillator(0);  // trim=0, 无偏移
        tail_servo_->Attach(SERVO_TAIL_PIN, false);  // 不反向
        tail_servo_->SetA(SERVO_TAIL_AMPLITUDE);  // 设置摆动幅度
        tail_servo_->SetT(SERVO_TAIL_PERIOD);    // 设置摆动周期
        tail_servo_->SetO(0);  // 偏移角度
        tail_servo_->Stop();  // 初始停止

        servos_enabled_ = false;

        // 创建舵机刷新定时器 (30ms 刷新一次)
        esp_timer_create_args_t timer_args = {
            .callback = [](void* arg) {
                BreadDualTouchBoard* self = static_cast<BreadDualTouchBoard*>(arg);
                if (self->servos_enabled_) {
                    self->head_servo_->Refresh();
                    self->tail_servo_->Refresh();
                }
            },
            .arg = this,
            .dispatch_method = ESP_TIMER_TASK,
            .name = "servo_refresh_timer",
            .skip_unhandled_events = true,
        };
        ESP_ERROR_CHECK(esp_timer_create(&timer_args, &servo_timer_));
        ESP_ERROR_CHECK(esp_timer_start_periodic(servo_timer_, 30000));  // 30ms

        ESP_LOGI(TAG, "Servos initialized: HEAD=%d, TAIL=%d", SERVO_HEAD_PIN, SERVO_TAIL_PIN);
    }

    // ==================== 摇头动作 ====================
    void shake_head() {
        ESP_LOGI(TAG, "Shaking head...");
        servos_enabled_ = true;
        head_servo_->Play();

        // 动作持续时间后停止
        esp_timer_create_args_t timer_args = {
            .callback = [](void* arg) {
                BreadDualTouchBoard* self = static_cast<BreadDualTouchBoard*>(arg);
                self->head_servo_->Stop();
                self->head_servo_->Reset();
                self->head_servo_->SetPosition(90);  // 回到中间位置
                ESP_LOGI(TAG, "Head shake completed");
            },
            .arg = this,
            .dispatch_method = ESP_TIMER_TASK,
            .name = "head_shake_timer",
            .skip_unhandled_events = true,
        };

        esp_timer_handle_t timer;
        ESP_ERROR_CHECK(esp_timer_create(&timer_args, &timer));
        ESP_ERROR_CHECK(esp_timer_start_once(timer, SERVO_ACTION_DURATION * 1000));
        ESP_ERROR_CHECK(esp_timer_delete(timer));
    }

    // ==================== 甩尾巴动作 ====================
    void wag_tail() {
        ESP_LOGI(TAG, "Wagging tail...");
        servos_enabled_ = true;
        tail_servo_->Play();

        // 动作持续时间后停止
        esp_timer_create_args_t timer_args = {
            .callback = [](void* arg) {
                BreadDualTouchBoard* self = static_cast<BreadDualTouchBoard*>(arg);
                self->tail_servo_->Stop();
                self->tail_servo_->Reset();
                self->tail_servo_->SetPosition(90);  // 回到中间位置
                ESP_LOGI(TAG, "Tail wag completed");
            },
            .arg = this,
            .dispatch_method = ESP_TIMER_TASK,
            .name = "tail_wag_timer",
            .skip_unhandled_events = true,
        };

        esp_timer_handle_t timer;
        ESP_ERROR_CHECK(esp_timer_create(&timer_args, &timer));
        ESP_ERROR_CHECK(esp_timer_start_once(timer, SERVO_ACTION_DURATION * 1000));
        ESP_ERROR_CHECK(esp_timer_delete(timer));
    }

    // ==================== 同时摇头甩尾巴 ====================
    void shake_head_and_wag_tail() {
        ESP_LOGI(TAG, "Shaking head and wagging tail...");
        servos_enabled_ = true;
        head_servo_->Play();
        tail_servo_->Play();

        // 动作持续时间后停止
        esp_timer_create_args_t timer_args = {
            .callback = [](void* arg) {
                BreadDualTouchBoard* self = static_cast<BreadDualTouchBoard*>(arg);
                self->head_servo_->Stop();
                self->tail_servo_->Stop();
                self->head_servo_->Reset();
                self->tail_servo_->Reset();
                self->head_servo_->SetPosition(90);  // 回到中间位置
                self->tail_servo_->SetPosition(90);  // 回到中间位置
                ESP_LOGI(TAG, "Head shake and tail wag completed");
            },
            .arg = this,
            .dispatch_method = ESP_TIMER_TASK,
            .name = "both_action_timer",
            .skip_unhandled_events = true,
        };

        esp_timer_handle_t timer;
        ESP_ERROR_CHECK(esp_timer_create(&timer_args, &timer));
        ESP_ERROR_CHECK(esp_timer_start_once(timer, SERVO_ACTION_DURATION * 1000));
        ESP_ERROR_CHECK(esp_timer_delete(timer));
    }

    // ==================== 触摸读取任务 ====================
    static void touch_read_task(void* arg) {
        BreadDualTouchBoard* self = static_cast<BreadDualTouchBoard*>(arg);
        auto& app = Application::GetInstance();

        ESP_LOGI(TAG, "Touch read task started");

        while (1) {
            // 读取触摸传感器数据 (使用旧 API)
            touch_pad_read_raw_data(TOUCH_LEFT_PAD, &self->touch_left_value_);
            touch_pad_read_raw_data(TOUCH_RIGHT_PAD, &self->touch_right_value_);

            // 左侧触摸检测 (触摸头部) - 摇头回应
            if (self->touch_left_value_ > TOUCH_THRESHOLD) {
                if (app.GetDeviceState() == kDeviceStateIdle) {
                    ESP_LOGI(TAG, "Left touch detected (head), triggering wake word and shaking head");
                    self->shake_head();  // 摇头
                    app.WakeWordInvoke("(正在抚摸你的头，请提供相关的情绪价值，回答)");
                }
            }

            // 右侧触摸检测 (触摸身体) - 甩尾巴回应
            if (self->touch_right_value_ > TOUCH_THRESHOLD) {
                if (app.GetDeviceState() == kDeviceStateIdle) {
                    ESP_LOGI(TAG, "Right touch detected (body), triggering wake word and wagging tail");
                    self->wag_tail();  // 甩尾巴
                    app.WakeWordInvoke("(正在抚摸你的身体，请提供相关的情绪价值，回答)");
                }
            }

            // 延时后继续检测
            vTaskDelay(TOUCH_READ_INTERVAL_MS / portTICK_PERIOD_MS);
        }
    }

    // ==================== I2C 编解码器初始化 ====================
    void InitializeCodecI2c() {
        ESP_LOGI(TAG, "Initializing I2C for audio codec...");

        i2c_master_bus_config_t i2c_bus_cfg = {
            .i2c_port = I2C_NUM_0,
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
        ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_cfg, &i2c_bus_));

        ESP_LOGI(TAG, "I2C initialized: SDA=%d, SCL=%d", AUDIO_CODEC_I2C_SDA_PIN, AUDIO_CODEC_I2C_SCL_PIN);
    }

    // ==================== 按键初始化 ====================
    void InitializeButtons() {
        ESP_LOGI(TAG, "Initializing buttons...");

        boot_button_.OnClick([this]() {
            auto& app = Application::GetInstance();
            // 切换对话状态
            app.ToggleChatState();
        });

        boot_button_.OnMultipleClick([this]() {
            // 多击切换网络类型
            SwitchNetworkType();
        });

        boot_button_.OnLongPress([this]() {
            // 长按进入WiFi配置模式
            if (GetNetworkType() == NetworkType::WIFI) {
                auto& wifi_board = static_cast<WifiBoard&>(GetCurrentBoard());
                wifi_board.EnterWifiConfigMode();
            }
        });

        ESP_LOGI(TAG, "Buttons initialized");
    }

    // ==================== SPI 总线初始化 ====================
    void InitializeSpi() {
        ESP_LOGI(TAG, "Initializing SPI bus for LCD...");

        spi_bus_config_t buscfg = {};
        buscfg.mosi_io_num = DISPLAY_SDA;
        buscfg.miso_io_num = GPIO_NUM_NC;
        buscfg.sclk_io_num = DISPLAY_SCL;
        buscfg.quadwp_io_num = GPIO_NUM_NC;
        buscfg.quadhd_io_num = GPIO_NUM_NC;
        buscfg.max_transfer_sz = DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(uint16_t);
        ESP_ERROR_CHECK(spi_bus_initialize(SPI3_HOST, &buscfg, SPI_DMA_CH_AUTO));

        ESP_LOGI(TAG, "SPI bus initialized: MOSI=%d, CLK=%d", DISPLAY_SDA, DISPLAY_SCL);
    }

    // ==================== LCD 显示初始化 ====================
    void InitializeLcdDisplay() {
        ESP_LOGI(TAG, "Initializing LCD display...");

        // 配置面板 IO
        esp_lcd_panel_io_spi_config_t io_config = {};
        io_config.cs_gpio_num = DISPLAY_CS;
        io_config.dc_gpio_num = DISPLAY_DC;
        io_config.spi_mode = 0;
        io_config.pclk_hz = 40 * 1000 * 1000;  // 40MHz
        io_config.trans_queue_depth = 10;
        io_config.lcd_cmd_bits = 8;
        io_config.lcd_param_bits = 8;
        ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi(SPI3_HOST, &io_config, &panel_io_));

        // 配置面板
        ESP_LOGI(TAG, "Installing LCD driver");
        esp_lcd_panel_dev_config_t panel_config = {};
        panel_config.reset_gpio_num = DISPLAY_RES;
        panel_config.rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB;
        panel_config.bits_per_pixel = 16;

        // 根据配置选择 LCD 驱动芯片
#if CONFIG_USE_LCD_240X240_GIF1 || CONFIG_USE_LCD_240X240_GIF2
        ESP_ERROR_CHECK(esp_lcd_new_panel_gc9a01(panel_io_, &panel_config, &panel_));
#else
        ESP_ERROR_CHECK(esp_lcd_new_panel_gc9d01n(panel_io_, &panel_config, &panel_));
#endif

        // 重置面板
        esp_lcd_panel_reset(panel_);
        esp_lcd_panel_init(panel_);

        // 设置显示参数
        esp_lcd_panel_invert_color(panel_, false);
        esp_lcd_panel_swap_xy(panel_, DISPLAY_SWAP_XY);
        esp_lcd_panel_mirror(panel_, DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y);

        ESP_LOGI(TAG, "LCD driver installed: %dx%d", DISPLAY_WIDTH, DISPLAY_HEIGHT);

        // 创建 LCD 显示对象
        display_ = new SpiLcdDisplay(panel_io_, panel_,
            DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_OFFSET_X, DISPLAY_OFFSET_Y, DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y, DISPLAY_SWAP_XY);

        ESP_LOGI(TAG, "LCD display initialized");
    }

public:
    // ==================== 构造函数 ====================
    BreadDualTouchBoard() : DualNetworkBoard(ML307_TX_PIN, ML307_RX_PIN, GPIO_NUM_NC, 1, false),
        boot_button_(BOOT_BUTTON_GPIO) {

        ESP_LOGI(TAG, "=== BreadDualTouchBoard Initializing ===");

        // 初始化顺序
        InitializeCodecI2c();
        InitializeButtons();
        InitializeSpi();
        InitializeLcdDisplay();
        touch_init();
        servos_init();  // 初始化舵机

        // 设置初始音量
        GetAudioCodec()->SetOutputVolume(100);

        // 启动触摸读取任务
        xTaskCreate(
            touch_read_task,
            "touch_read_task",
            2048,        // 栈大小
            this,        // 参数
            5,           // 优先级
            NULL
        );

        ESP_LOGI(TAG, "=== BreadDualTouchBoard Initialization Complete ===");
    }

    // ==================== 析构函数 ====================
    ~BreadDualTouchBoard() {
        if (servo_timer_) {
            esp_timer_stop(servo_timer_);
            esp_timer_delete(servo_timer_);
        }
        if (head_servo_) {
            delete head_servo_;
        }
        if (tail_servo_) {
            delete tail_servo_;
        }
    }

    // ==================== 获取 LED ====================
    virtual Led* GetLed() override {
        static SingleLed led(BUILTIN_LED_GPIO);
        return &led;
    }

    // ==================== 获取音频编解码器 ====================
    virtual AudioCodec* GetAudioCodec() override {
        static BoxAudioCodec audio_codec(
            i2c_bus_,
            AUDIO_INPUT_SAMPLE_RATE,
            AUDIO_OUTPUT_SAMPLE_RATE,
            AUDIO_I2S_GPIO_MCLK,
            AUDIO_I2S_GPIO_BCLK,
            AUDIO_I2S_GPIO_WS,
            AUDIO_I2S_GPIO_DOUT,
            AUDIO_I2S_GPIO_DIN,
            GPIO_NUM_NC,
            AUDIO_CODEC_ES8311_ADDR,
            AUDIO_CODEC_ES7210_ADDR,
            AUDIO_INPUT_REFERENCE
        );
        return &audio_codec;
    }

    // ==================== 获取显示器 ====================
    virtual Display* GetDisplay() override {
        return display_;
    }

    // ==================== 获取背光控制 ====================
    virtual Backlight* GetBacklight() override {
        static PwmBacklight backlight(DISPLAY_BACKLIGHT_PIN, DISPLAY_BACKLIGHT_OUTPUT_INVERT);
        return &backlight;
    }

    // ==================== 获取电池电量 (可选实现) ====================
    virtual bool GetBatteryLevel(int& level, bool& charging, bool& discharging) override {
        // 如果板子有电池管理芯片，在此实现
        // 简单版本返回默认值
        level = 100;
        charging = false;
        discharging = false;
        return true;
    }

    // ==================== 获取温度 (可选实现) ====================
    virtual bool GetTemperature(float& esp32temp) override {
        // 如果板子有温度传感器，在此实现
        esp32temp = 0.0f;
        return false;
    }

    // ==================== 关机功能 ====================
    virtual void Shutdown() override {
        ESP_LOGI(TAG, "Shutting down BreadDualTouchBoard...");
        
        // 停止所有服务和任务
        if (servo_timer_) {
            esp_timer_stop(servo_timer_);
            esp_timer_delete(servo_timer_);
            servo_timer_ = nullptr;
        }
        
        // 停止舵机
        if (head_servo_) {
            head_servo_->Stop();
            head_servo_->Reset();
        }
        if (tail_servo_) {
            tail_servo_->Stop();
            tail_servo_->Reset();
        }
        
        // 关闭显示
        if (display_) {
            // 显示关机消息
            auto lvgl_display = dynamic_cast<LvglDisplay*>(display_);
            if (lvgl_display) {
                lvgl_display->SetChatMessage("system", "Shutting down...");
                // 等待显示完成
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
        }
        
        // 关闭背光
        auto backlight = GetBacklight();
        if (backlight) {
            backlight->SetBrightness(0);
        }
        
        // 关闭LED
        auto led = GetLed();
        if (led) {
            led->TurnOff();
        }
        
        ESP_LOGI(TAG, "Board shutdown complete");
        
        // 进入深度睡眠模式
        esp_deep_sleep_start();
    }

};

DECLARE_BOARD(BreadDualTouchBoard);
