#ifndef ESP_LCD_TOUCH_CST226SE_H
#define ESP_LCD_TOUCH_CST226SE_H

#include <stdbool.h>
#include <stdint.h>

#include <driver/gpio.h>
#include <driver/i2c_master.h>
#include <esp_err.h>
#include <esp_lcd_touch.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    i2c_master_bus_handle_t i2c_bus;
    uint8_t i2c_addr;
    gpio_num_t rst_gpio_num;
    gpio_num_t int_gpio_num;
    uint16_t x_max;
    uint16_t y_max;
    uint16_t raw_min_x;
    uint16_t raw_min_y;
    uint16_t raw_max_x;
    uint16_t raw_max_y;
    int16_t offset_x;
    int16_t offset_y;
    bool swap_xy;
    bool mirror_x;
    bool mirror_y;
} esp_lcd_touch_cst226se_config_t;

esp_err_t esp_lcd_touch_new_i2c_cst226se(const esp_lcd_touch_cst226se_config_t *config,
                                         esp_lcd_touch_handle_t *ret_touch);

#ifdef __cplusplus
}
#endif

#endif // ESP_LCD_TOUCH_CST226SE_H
