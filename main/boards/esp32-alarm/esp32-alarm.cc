#include "dual_network_board.h"
#include "application.h"
#include "assets/lang_config.h"
#include "backlight.h"
#include "button.h"
#include "config.h"
#include "display/lcd_display.h"
#include "led/single_led.h"
#include "audio/codecs/es8311_audio_codec.h"
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
#include "ui_router.h"
#include "ui_system.h"
#endif

#include <driver/i2c_master.h>
#include <driver/spi_common.h>
#include <esp_lcd_panel_io.h>
#include <esp_lcd_panel_ops.h>
#include <esp_lcd_panel_vendor.h>
#include <esp_log.h>
#include <esp_timer.h>
#include <driver/gpio.h>
#include <ctime>
#include <cstdlib>
#include <cJSON.h>
#include "esp_lcd_touch_cst226se.h"

static const char* TAG = "Esp32AlarmBoard";

class Esp32AlarmBoard : public DualNetworkBoard {
private:
    Button key_ai_button_;
    Button key_up_button_;
    Button key_back_button_;
    LcdDisplay* display_ = nullptr;
    AudioCodec* audio_codec_ = nullptr;
    Led* led_ = nullptr;
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
    esp_timer_handle_t home_clock_timer_ = nullptr;
#endif
    i2c_master_bus_handle_t codec_i2c_bus_ = nullptr;
    esp_lcd_touch_handle_t touch_handle_ = nullptr;

    void InitializeCodecI2c() {
        i2c_master_bus_config_t i2c_bus_cfg = {
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
        ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_cfg, &codec_i2c_bus_));
    }

    void InitializeSpi() {
        spi_bus_config_t buscfg = {};
        buscfg.mosi_io_num = DISPLAY_MOSI_PIN;
        buscfg.miso_io_num = GPIO_NUM_NC;
        buscfg.sclk_io_num = DISPLAY_CLK_PIN;
        buscfg.quadwp_io_num = GPIO_NUM_NC;
        buscfg.quadhd_io_num = GPIO_NUM_NC;
        buscfg.max_transfer_sz = DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(uint16_t);
        ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));
    }

    void InitializeSt7789Display() {
        esp_lcd_panel_io_handle_t panel_io = nullptr;
        esp_lcd_panel_handle_t panel = nullptr;

        esp_lcd_panel_io_spi_config_t io_config = {};
        io_config.cs_gpio_num = DISPLAY_CS_PIN;
        io_config.dc_gpio_num = DISPLAY_DC_PIN;
        io_config.spi_mode = DISPLAY_SPI_MODE;
        io_config.pclk_hz = 80 * 1000 * 1000;
        io_config.trans_queue_depth = 10;
        io_config.lcd_cmd_bits = 8;
        io_config.lcd_param_bits = 8;
        ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi(SPI2_HOST, &io_config, &panel_io));

        esp_lcd_panel_dev_config_t panel_config = {};
        panel_config.reset_gpio_num = DISPLAY_RST_PIN;
        panel_config.rgb_ele_order = DISPLAY_RGB_ORDER;
        panel_config.bits_per_pixel = 16;
        panel_config.data_endian = LCD_RGB_DATA_ENDIAN_BIG;
        ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(panel_io, &panel_config, &panel));
        ESP_ERROR_CHECK(esp_lcd_panel_reset(panel));
        ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel, DISPLAY_INVERT_COLOR));
        ESP_ERROR_CHECK(esp_lcd_panel_init(panel));
        ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel, DISPLAY_SWAP_XY));
        ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel, DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y));
        ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel, true));

        display_ = new SpiLcdDisplay(
            panel_io,
            panel,
            DISPLAY_WIDTH,
            DISPLAY_HEIGHT,
            DISPLAY_OFFSET_X,
            DISPLAY_OFFSET_Y,
            DISPLAY_MIRROR_X,
            DISPLAY_MIRROR_Y,
            DISPLAY_SWAP_XY);
    }

    void InitializeTouch() {
        if (codec_i2c_bus_ == nullptr) {
            ESP_LOGW(TAG, "Touch skipped: I2C bus not ready");
            return;
        }
        esp_lcd_touch_cst226se_config_t touch_cfg = {
            .i2c_bus = codec_i2c_bus_,
            .i2c_addr = 0x5A,
            .rst_gpio_num = TOUCH_RST_PIN,
            .int_gpio_num = TOUCH_INT_PIN,
            .x_max = DISPLAY_WIDTH,
            .y_max = DISPLAY_HEIGHT,
            .raw_min_x = TOUCH_RAW_MIN_X,
            .raw_min_y = TOUCH_RAW_MIN_Y,
            .raw_max_x = TOUCH_RAW_MAX_X,
            .raw_max_y = TOUCH_RAW_MAX_Y,
            .offset_x = TOUCH_OFFSET_X,
            .offset_y = TOUCH_OFFSET_Y,
            .swap_xy = false,
            .mirror_x = TOUCH_MIRROR_X,
            .mirror_y = TOUCH_MIRROR_Y,
        };
        ESP_ERROR_CHECK(esp_lcd_touch_new_i2c_cst226se(&touch_cfg, &touch_handle_));
        ESP_LOGI(TAG, "Touch (CST226SE) initialized");
        if (display_ != nullptr) {
            display_->AttachTouchHandle(touch_handle_);
        }
    }

    void InitializeBacklight() {
        auto backlight = GetBacklight();
        if (backlight != nullptr) {
            backlight->RestoreBrightness();
        }
    }

    void InitializeUiBridge() {
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
        UiSystem::GetInstance().Initialize();
        if (auto* lcd_display = dynamic_cast<LcdDisplay*>(display_)) {
            UiRouter::GetInstance().SetNavigateCallback(
                [lcd_display](const std::string&, const std::string& to_route) {
                    lcd_display->ShowRoute(to_route);
                });
        }
#endif
    }

    void InitializeTimezone() {
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
        setenv("TZ", "CST-8", 1);
        tzset();
#endif
    }

    void UpdateHomeClock() {
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
        if (auto* lcd_display = dynamic_cast<LcdDisplay*>(display_)) {
            time_t now = time(nullptr);
            struct tm* tm_info = localtime(&now);
            if (tm_info == nullptr) {
                return;
            }
            char time_str[16];
            strftime(time_str, sizeof(time_str), "%H:%M", tm_info);
            lcd_display->SetHomeTime(time_str);
        }
#endif
    }

    void InitializeHomeClockTimer() {
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
        const esp_timer_create_args_t timer_args = {
            .callback = [](void* arg) {
                static_cast<Esp32AlarmBoard*>(arg)->UpdateHomeClock();
            },
            .arg = this,
            .dispatch_method = ESP_TIMER_TASK,
            .name = "alarm_home_clock",
            .skip_unhandled_events = true,
        };
        ESP_ERROR_CHECK(esp_timer_create(&timer_args, &home_clock_timer_));
        ESP_ERROR_CHECK(esp_timer_start_periodic(home_clock_timer_, 1000 * 1000));
#endif
    }

    void InitializeNetworkUiBridge() {
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
        SetNetworkEventCallback([this](NetworkEvent event, const std::string& data) {
            std::string home_status;
            switch (event) {
                case NetworkEvent::Scanning:
                    home_status = "Searching Wi-Fi";
                    break;
                case NetworkEvent::Connecting:
                    home_status = data.empty() ? "Connecting network" : ("Connecting " + data);
                    break;
                case NetworkEvent::Connected:
                    home_status = data.empty() ? "Network connected" : ("Connected " + data);
                    break;
                case NetworkEvent::Disconnected:
                    home_status = "Network disconnected";
                    break;
                case NetworkEvent::WifiConfigModeEnter:
                    home_status = "Enter Wi-Fi config";
                    break;
                case NetworkEvent::WifiConfigModeExit:
                    home_status = "Exit Wi-Fi config";
                    break;
                default:
                    home_status = "Network update";
                    break;
            }

            UiSystem::GetInstance().SetHomeStatus(home_status);
            if (auto* lcd_display = dynamic_cast<LcdDisplay*>(display_)) {
                lcd_display->SetHomeStatus(home_status.c_str());
                lcd_display->SetStatus(home_status.c_str());
                lcd_display->UpdateStatusBar(true);
            }
        });
#endif
    }

    void HandleKeyUp() {
        auto& app = Application::GetInstance();
        if (app.GetDeviceState() == kDeviceStateStarting) {
            return;
        }
        app.StopListening();
        app.SetDeviceState(kDeviceStateIdle);
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
        auto& router = UiRouter::GetInstance();
        router.NavigateTo(UiRouter::RouteHome);
#endif
    }

    void InitializeButtons() {
        gpio_config_t key_ai_probe_cfg = {};
        key_ai_probe_cfg.mode = GPIO_MODE_INPUT;
        key_ai_probe_cfg.pull_up_en = GPIO_PULLUP_ENABLE;
        key_ai_probe_cfg.pull_down_en = GPIO_PULLDOWN_DISABLE;
        key_ai_probe_cfg.intr_type = GPIO_INTR_DISABLE;
        key_ai_probe_cfg.pin_bit_mask = 1ULL << KEY_AI_GPIO;
        ESP_ERROR_CHECK(gpio_config(&key_ai_probe_cfg));
        ESP_LOGI(TAG, "KEY_AI probe level=%d", gpio_get_level(KEY_AI_GPIO));

        key_ai_button_.OnPressDown([this]() {
            ESP_LOGI(TAG, "key_ai_button_.OnPressDown level=%d", gpio_get_level(KEY_AI_GPIO));
        });

        key_ai_button_.OnPressUp([this]() {
            ESP_LOGI(TAG, "key_ai_button_.OnPressUp level=%d", gpio_get_level(KEY_AI_GPIO));
        });

        key_ai_button_.OnClick([this]() {
            ESP_LOGI(TAG, "key_ai_button_.OnClick begin");
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
            auto& router = UiRouter::GetInstance();
            if (router.CurrentRoute() != UiRouter::RouteAI) {
                router.NavigateTo(UiRouter::RouteAI);
            }
#endif
            Application::GetInstance().ToggleChatState();
            ESP_LOGI(TAG, "key_ai_button_.OnClick end");
        });

        key_up_button_.OnMultipleClick([this]() {
            ESP_LOGI(TAG, "key_up_button_.OnMultipleClick");
            SwitchNetworkType();
        }, 3);

        key_up_button_.OnClick([this]() {
            ESP_LOGI(TAG, "key_up_button_.OnClick");
            HandleKeyUp();
        });

        key_up_button_.OnLongPress([this]() {
            ESP_LOGI(TAG, "key_up_button_.OnLongPress");
            HandleKeyUp();
        });

        key_back_button_.OnClick([this]() {
            ESP_LOGI(TAG, "key_back_button_.OnClick");
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
            auto& router = UiRouter::GetInstance();
            if (!router.GoBack()) {
                router.NavigateTo(UiRouter::RouteHome);
            }
#else
            HandleKeyUp();
#endif
        });
    }

public:
    Esp32AlarmBoard()
        : DualNetworkBoard(ML307C_TX_PIN, ML307C_RX_PIN, ML307C_DTR_PIN, 1, true),
          key_ai_button_(KEY_AI_GPIO, true),
          key_up_button_(KEY_UP_GPIO, false),
          key_back_button_(KEY_BACK_GPIO, false) {
        InitializeCodecI2c();
        InitializeSpi();
        InitializeSt7789Display();
        InitializeTouch();
        InitializeButtons();
        led_ = new SingleLed(BUILTIN_LED_GPIO);
        InitializeBacklight();
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
        InitializeTimezone();
        InitializeUiBridge();
        InitializeNetworkUiBridge();
        InitializeHomeClockTimer();
#endif
    }

    ~Esp32AlarmBoard() override {
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
        if (home_clock_timer_ != nullptr) {
            esp_timer_stop(home_clock_timer_);
            esp_timer_delete(home_clock_timer_);
        }
#endif
        if (touch_handle_ != nullptr) {
            esp_lcd_touch_del(touch_handle_);
            touch_handle_ = nullptr;
        }
        if (codec_i2c_bus_ != nullptr) {
            i2c_del_master_bus(codec_i2c_bus_);
        }
    }

    std::string GetBoardType() override {
        return "esp32-alarm";
    }

    Display* GetDisplay() override {
        if (display_ != nullptr) {
            return display_;
        }
        return Board::GetDisplay();
    }

    Backlight* GetBacklight() override {
        if (DISPLAY_BACKLIGHT_PIN != GPIO_NUM_NC) {
            static PwmBacklight backlight(DISPLAY_BACKLIGHT_PIN, DISPLAY_BACKLIGHT_OUTPUT_INVERT);
            return &backlight;
        }
        return nullptr;
    }

    AudioCodec* GetAudioCodec() override {
        if (audio_codec_ == nullptr) {
            audio_codec_ = new Es8311AudioCodec(
                codec_i2c_bus_,
                I2C_NUM_1,
                AUDIO_INPUT_SAMPLE_RATE,
                AUDIO_OUTPUT_SAMPLE_RATE,
                AUDIO_I2S_GPIO_MCLK,
                AUDIO_I2S_GPIO_BCLK,
                AUDIO_I2S_GPIO_WS,
                AUDIO_I2S_GPIO_DOUT,
                AUDIO_I2S_GPIO_DIN,
                AUDIO_CODEC_PA_PIN,
                AUDIO_CODEC_ES8311_ADDR);
        }
        return audio_codec_;
    }

    Led* GetLed() override {
        return led_;
    }

    bool GetBatteryLevel(int& level, bool& charging, bool& discharging) override {
        level = 100;
        charging = false;
        discharging = false;
        return true;
    }

    std::string GetBoardJson() override {
        return "{\"type\":\"esp32-alarm\",\"name\":\"" BOARD_NAME "\",\"network\":\"dual\",\"display\":\"320x240-lcd\"}";
    }

    std::string GetDeviceStatusJson() override {
        auto root = cJSON_CreateObject();
        auto network = cJSON_CreateObject();
        cJSON_AddStringToObject(network, "mode", "dual");
        cJSON_AddStringToObject(network, "strategy", "wifi-or-4g");
        cJSON_AddItemToObject(root, "network", network);

        auto screen = cJSON_CreateObject();
        cJSON_AddStringToObject(screen, "type", "lcd");
        cJSON_AddNumberToObject(screen, "width", DISPLAY_WIDTH);
        cJSON_AddNumberToObject(screen, "height", DISPLAY_HEIGHT);
        cJSON_AddItemToObject(root, "screen", screen);

        auto features = cJSON_CreateObject();
        cJSON_AddBoolToObject(features, "voice_overlay", true);
        cJSON_AddBoolToObject(features, "app_grid", true);
        cJSON_AddBoolToObject(features, "alarm_system", true);
        cJSON_AddBoolToObject(features, "touch_screen", true);
        cJSON_AddItemToObject(root, "features", features);

        auto json_str = cJSON_PrintUnformatted(root);
        std::string json(json_str);
        cJSON_free(json_str);
        cJSON_Delete(root);
        return json;
    }

    void SetPowerSaveLevel(PowerSaveLevel level) override {
        if (level != PowerSaveLevel::LOW_POWER) {
            if (auto backlight = GetBacklight()) {
                backlight->RestoreBrightness();
            }
        }
        DualNetworkBoard::SetPowerSaveLevel(level);
    }

    void OnAudioServiceStarted() override {
        Application::GetInstance().PlaySound(Lang::Sounds::OGG_PWRON);
    }
};

DECLARE_BOARD(Esp32AlarmBoard);
