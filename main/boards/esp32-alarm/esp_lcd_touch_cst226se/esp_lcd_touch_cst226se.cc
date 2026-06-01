#include "esp_lcd_touch_cst226se.h"

#include <cstring>

#include <esp_check.h>
#include <esp_log.h>
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

static const char *TAG = "CST226SE";

typedef struct {
    i2c_master_bus_handle_t bus;
    i2c_master_dev_handle_t dev;
    esp_lcd_touch_cst226se_config_t cfg;
    uint8_t read_buffer[6];
    uint16_t raw_x_max;
    uint16_t raw_y_max;
    bool pressed;
    uint16_t x;
    uint16_t y;
    uint16_t strength;
} cst226se_ctx_t;

static void destroy_ctx(cst226se_ctx_t *ctx)
{
    if (ctx == nullptr) {
        return;
    }
    if (ctx->dev != nullptr && ctx->bus != nullptr) {
        i2c_master_bus_rm_device(ctx->dev);
        ctx->dev = nullptr;
    }
    delete ctx;
}

static cst226se_ctx_t *get_ctx(esp_lcd_touch_handle_t tp)
{
    if (tp == nullptr) {
        return nullptr;
    }
    return static_cast<cst226se_ctx_t *>(tp->config.driver_data);
}

static bool read_touch_point(cst226se_ctx_t *ctx)
{
    if (ctx == nullptr || ctx->dev == nullptr) {
        return false;
    }

    uint8_t reg = 0x00;
    esp_err_t err = i2c_master_transmit_receive(
        ctx->dev, &reg, 1, ctx->read_buffer, sizeof(ctx->read_buffer), pdMS_TO_TICKS(100));
    if (err != ESP_OK) {
        static int64_t last_warn_us = 0;
        int64_t now_us = esp_timer_get_time();
        if (now_us - last_warn_us > 1000 * 1000) {
            ESP_LOGW(TAG, "I2C read failed: %s", esp_err_to_name(err));
            last_warn_us = now_us;
        }
        ctx->pressed = false;
        return false;
    }

    int touch_num = ctx->read_buffer[5] & 0x0F;
    if (touch_num <= 0) {
        ctx->pressed = false;
        return true;
    }

    // CST226SE packs 12-bit coordinates across bytes 1/2/3.
    // The existing board orientation uses the chip's Y axis for screen X and X axis for screen Y.
    uint16_t raw_x = (static_cast<uint16_t>(ctx->read_buffer[1]) << 4) | ((ctx->read_buffer[3] >> 4) & 0x0F);
    uint16_t raw_y = (static_cast<uint16_t>(ctx->read_buffer[2]) << 4) | (ctx->read_buffer[3] & 0x0F);

    uint16_t raw_x_min = ctx->cfg.raw_min_x;
    uint16_t raw_y_min = ctx->cfg.raw_min_y;
    uint16_t raw_x_max = ctx->cfg.raw_max_x > ctx->cfg.raw_min_x ? ctx->cfg.raw_max_x : (ctx->cfg.raw_min_x + 1);
    uint16_t raw_y_max = ctx->cfg.raw_max_y > ctx->cfg.raw_min_y ? ctx->cfg.raw_max_y : (ctx->cfg.raw_min_y + 1);

    int32_t norm_x = static_cast<int32_t>(raw_y) - static_cast<int32_t>(raw_y_min);
    int32_t norm_y = static_cast<int32_t>(raw_x) - static_cast<int32_t>(raw_x_min);
    if (norm_x < 0) {
        norm_x = 0;
    }
    if (norm_y < 0) {
        norm_y = 0;
    }
    if (static_cast<uint32_t>(norm_x) > (raw_y_max - raw_y_min)) {
        norm_x = raw_y_max - raw_y_min;
    }
    if (static_cast<uint32_t>(norm_y) > (raw_x_max - raw_x_min)) {
        norm_y = raw_x_max - raw_x_min;
    }

    uint32_t x = (static_cast<uint32_t>(norm_x) * (ctx->cfg.x_max - 1)) / (raw_y_max - raw_y_min);
    uint32_t y = (static_cast<uint32_t>(norm_y) * (ctx->cfg.y_max - 1)) / (raw_x_max - raw_x_min);

    if (ctx->cfg.swap_xy) {
        uint32_t tmp = x;
        x = y;
        y = tmp;
    }
    if (ctx->cfg.mirror_x) {
        x = ctx->cfg.x_max - 1 - x;
    }
    if (ctx->cfg.mirror_y) {
        y = ctx->cfg.y_max - 1 - y;
    }

    if (ctx->cfg.offset_x != 0) {
        int32_t shifted_x = static_cast<int32_t>(x) + ctx->cfg.offset_x;
        if (shifted_x < 0) {
            shifted_x = 0;
        }
        if (shifted_x >= ctx->cfg.x_max) {
            shifted_x = ctx->cfg.x_max - 1;
        }
        x = static_cast<uint32_t>(shifted_x);
    }
    if (ctx->cfg.offset_y != 0) {
        int32_t shifted_y = static_cast<int32_t>(y) + ctx->cfg.offset_y;
        if (shifted_y < 0) {
            shifted_y = 0;
        }
        if (shifted_y >= ctx->cfg.y_max) {
            shifted_y = ctx->cfg.y_max - 1;
        }
        y = static_cast<uint32_t>(shifted_y);
    }

    if (x >= ctx->cfg.x_max) {
        x = ctx->cfg.x_max - 1;
    }
    if (y >= ctx->cfg.y_max) {
        y = ctx->cfg.y_max - 1;
    }

    static int64_t last_touch_log_us = 0;
    int64_t now_us = esp_timer_get_time();
    if (now_us - last_touch_log_us > 200 * 1000) {
        ESP_LOGI(TAG,
                 "touch raw=(%u,%u) norm=(%ld,%ld) mapped=(%lu,%lu) points=%d",
                 raw_x,
                 raw_y,
                 static_cast<long>(norm_y),
                 static_cast<long>(norm_x),
                 static_cast<unsigned long>(x),
                 static_cast<unsigned long>(y),
                 touch_num);
        last_touch_log_us = now_us;
    }

    ctx->x = static_cast<uint16_t>(x);
    ctx->y = static_cast<uint16_t>(y);
    ctx->strength = 1000;
    ctx->pressed = true;
    return true;
}

static esp_err_t cst226se_read_data(esp_lcd_touch_handle_t tp)
{
    cst226se_ctx_t *ctx = get_ctx(tp);
    if (ctx == nullptr) {
        return ESP_OK;
    }
    read_touch_point(ctx);
    return ESP_OK;
}

static bool cst226se_get_xy(esp_lcd_touch_handle_t tp, uint16_t *x, uint16_t *y, uint16_t *strength,
                            uint8_t *point_num, uint8_t max_point_num)
{
    cst226se_ctx_t *ctx = get_ctx(tp);
    if (ctx == nullptr || x == nullptr || y == nullptr || point_num == nullptr || max_point_num == 0) {
        return false;
    }

    if (!ctx->pressed) {
        *point_num = 0;
        return false;
    }

    x[0] = ctx->x;
    y[0] = ctx->y;
    if (strength != nullptr) {
        strength[0] = ctx->strength;
    }
    *point_num = 1;
    return true;
}

static esp_err_t cst226se_del(esp_lcd_touch_handle_t tp)
{
    cst226se_ctx_t *ctx = get_ctx(tp);
    destroy_ctx(ctx);
    delete tp;
    return ESP_OK;
}

esp_err_t esp_lcd_touch_new_i2c_cst226se(const esp_lcd_touch_cst226se_config_t *config,
                                         esp_lcd_touch_handle_t *ret_touch)
{
    ESP_RETURN_ON_FALSE(config != nullptr, ESP_ERR_INVALID_ARG, TAG, "config can't be NULL");
    ESP_RETURN_ON_FALSE(ret_touch != nullptr, ESP_ERR_INVALID_ARG, TAG, "ret_touch can't be NULL");
    ESP_RETURN_ON_FALSE(config->i2c_bus != nullptr, ESP_ERR_INVALID_ARG, TAG, "i2c_bus can't be NULL");

    auto *ctx = new cst226se_ctx_t{};
    ESP_RETURN_ON_FALSE(ctx != nullptr, ESP_ERR_NO_MEM, TAG, "Failed to allocate CST226SE context");

    ctx->cfg = *config;
    ctx->bus = config->i2c_bus;

    i2c_device_config_t i2c_device_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = config->i2c_addr,
        .scl_speed_hz = 400 * 1000,
        .scl_wait_us = 0,
        .flags = {
            .disable_ack_check = 0,
        },
    };
    esp_err_t err = i2c_master_bus_add_device(config->i2c_bus, &i2c_device_cfg, &ctx->dev);
    if (err != ESP_OK) {
        delete ctx;
        return err;
    }

    if (config->rst_gpio_num != GPIO_NUM_NC) {
        gpio_config_t rst_cfg = {};
        rst_cfg.pin_bit_mask = 1ULL << config->rst_gpio_num;
        rst_cfg.mode = GPIO_MODE_OUTPUT;
        rst_cfg.pull_up_en = GPIO_PULLUP_DISABLE;
        rst_cfg.pull_down_en = GPIO_PULLDOWN_DISABLE;
        rst_cfg.intr_type = GPIO_INTR_DISABLE;
        ESP_ERROR_CHECK(gpio_config(&rst_cfg));
        gpio_set_level(config->rst_gpio_num, 0);
        vTaskDelay(pdMS_TO_TICKS(10));
        gpio_set_level(config->rst_gpio_num, 1);
        vTaskDelay(pdMS_TO_TICKS(50));
    }

    if (config->int_gpio_num != GPIO_NUM_NC) {
        gpio_config_t int_cfg = {};
        int_cfg.pin_bit_mask = 1ULL << config->int_gpio_num;
        int_cfg.mode = GPIO_MODE_INPUT;
        int_cfg.pull_up_en = GPIO_PULLUP_ENABLE;
        int_cfg.pull_down_en = GPIO_PULLDOWN_DISABLE;
        int_cfg.intr_type = GPIO_INTR_NEGEDGE;
        ESP_ERROR_CHECK(gpio_config(&int_cfg));
    }

    uint8_t chip_id = 0;
    uint8_t reg = 0x06;
    if (i2c_master_transmit_receive(ctx->dev, &reg, 1, &chip_id, 1, pdMS_TO_TICKS(100)) == ESP_OK) {
        ESP_LOGI(TAG, "Get CST226SE chip ID: 0x%02X", chip_id);
    } else {
        ESP_LOGW(TAG, "Failed to read CST226SE chip ID");
    }

    esp_lcd_touch_handle_t tp = new esp_lcd_touch_t{};
    if (tp == nullptr) {
        destroy_ctx(ctx);
        return ESP_ERR_NO_MEM;
    }

    tp->enter_sleep = nullptr;
    tp->exit_sleep = nullptr;
    tp->read_data = cst226se_read_data;
    tp->get_xy = cst226se_get_xy;
    tp->get_track_id = nullptr;
    tp->set_swap_xy = nullptr;
    tp->get_swap_xy = nullptr;
    tp->set_mirror_x = nullptr;
    tp->get_mirror_x = nullptr;
    tp->set_mirror_y = nullptr;
    tp->get_mirror_y = nullptr;
    tp->del = cst226se_del;
    tp->config.x_max = config->x_max;
    tp->config.y_max = config->y_max;
    tp->config.rst_gpio_num = config->rst_gpio_num;
    tp->config.int_gpio_num = config->int_gpio_num;
    tp->config.levels.reset = 0;
    tp->config.levels.interrupt = 0;
    tp->config.flags.swap_xy = false;
    tp->config.flags.mirror_x = false;
    tp->config.flags.mirror_y = false;
    tp->config.process_coordinates = nullptr;
    tp->config.interrupt_callback = nullptr;
    tp->config.user_data = nullptr;
    tp->config.driver_data = ctx;
    tp->io = nullptr;
    memset(&tp->data, 0, sizeof(tp->data));

    *ret_touch = tp;
    return ESP_OK;
}
