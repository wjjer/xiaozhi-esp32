#include <stdlib.h>
#include <sys/cdefs.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_lcd_panel_interface.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_commands.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_check.h"

#include "esp_lcd_gc9d01n.h"

// 添加缺失的宏定义
#define LCD_CMD_MADCTL_MX 0x40  // 水平镜像
#define LCD_CMD_MADCTL_MY 0x80  // 垂直镜像
#define LCD_CMD_MADCTL_ML 0x10  // 交换XY轴

static const char *TAG = "gc9d01n";

static esp_err_t panel_gc9d01n_del(esp_lcd_panel_t *panel);
static esp_err_t panel_gc9d01n_reset(esp_lcd_panel_t *panel);
static esp_err_t panel_gc9d01n_init(esp_lcd_panel_t *panel);
static esp_err_t panel_gc9d01n_draw_bitmap(esp_lcd_panel_t *panel, int x_start, int y_start, int x_end, int y_end, const void *color_data);
static esp_err_t panel_gc9d01n_invert_color(esp_lcd_panel_t *panel, bool invert_color_data);
static esp_err_t panel_gc9d01n_mirror(esp_lcd_panel_t *panel, bool mirror_x, bool mirror_y);
static esp_err_t panel_gc9d01n_swap_xy(esp_lcd_panel_t *panel, bool swap_axes);
static esp_err_t panel_gc9d01n_set_gap(esp_lcd_panel_t *panel, int x_gap, int y_gap);
static esp_err_t panel_gc9d01n_disp_on_off(esp_lcd_panel_t *panel, bool off);

typedef struct{
    esp_lcd_panel_t base;
    esp_lcd_panel_io_handle_t io;
    int reset_gpio_num;
    bool reset_level;
    int x_gap;
    int y_gap;
    uint8_t fb_bits_per_pixel;
    uint8_t madctl_val; // save current value of LCD_CMD_MADCTL register
    uint8_t colmod_val; // save current value of LCD_CMD_COLMOD register
    const gc9d01n_lcd_init_cmd_t *init_cmds;
    uint16_t init_cmds_size;
} gc9d01n_panel_t;

esp_err_t esp_lcd_new_panel_gc9d01n(const esp_lcd_panel_io_handle_t io, const esp_lcd_panel_dev_config_t *panel_dev_config, esp_lcd_panel_handle_t *ret_panel){
    esp_err_t ret = ESP_OK;
    gc9d01n_panel_t *gc9d01n = NULL;
    gpio_config_t io_conf = {0};

    ESP_GOTO_ON_FALSE(io && panel_dev_config && ret_panel, ESP_ERR_INVALID_ARG, err, TAG, "invalid argument");
    gc9d01n = (gc9d01n_panel_t *)calloc(1, sizeof(gc9d01n_panel_t));
    ESP_GOTO_ON_FALSE(gc9d01n, ESP_ERR_NO_MEM, err, TAG, "no mem for gc9d01n panel");

    if (panel_dev_config->reset_gpio_num >= 0){
        io_conf.mode = GPIO_MODE_OUTPUT;
        io_conf.pin_bit_mask = 1ULL << panel_dev_config->reset_gpio_num;
        ESP_GOTO_ON_ERROR(gpio_config(&io_conf), err, TAG, "configure GPIO for RST line failed");
    }

#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 0, 0)
    switch (panel_dev_config->color_space){
    case ESP_LCD_COLOR_SPACE_RGB:
        gc9d01n->madctl_val = 0;
        break;
    case ESP_LCD_COLOR_SPACE_BGR:
        gc9d01n->madctl_val |= LCD_CMD_BGR_BIT;
        break;
    default:
        ESP_GOTO_ON_FALSE(false, ESP_ERR_NOT_SUPPORTED, err, TAG, "unsupported color space");
        break;
    }
#else
    switch (panel_dev_config->rgb_endian){
    case LCD_RGB_ENDIAN_RGB:
        gc9d01n->madctl_val = 0;
        break;
    case LCD_RGB_ENDIAN_BGR:
        gc9d01n->madctl_val |= LCD_CMD_BGR_BIT;
        break;
    default:
        ESP_GOTO_ON_FALSE(false, ESP_ERR_NOT_SUPPORTED, err, TAG, "unsupported rgb endian");
        break;
    }
#endif

    switch (panel_dev_config->bits_per_pixel){
    case 16: // RGB565
        gc9d01n->colmod_val = 0x55;
        gc9d01n->fb_bits_per_pixel = 16;
        break;
    case 18: // RGB666
        gc9d01n->colmod_val = 0x66;
        // each color component (R/G/B) should occupy the 6 high bits of a byte, which means 3 full bytes are required for a pixel
        gc9d01n->fb_bits_per_pixel = 24;
        break;
    default:
        ESP_GOTO_ON_FALSE(false, ESP_ERR_NOT_SUPPORTED, err, TAG, "unsupported pixel width");
        break;
    }

    gc9d01n->io = io;
    gc9d01n->reset_gpio_num = panel_dev_config->reset_gpio_num;
    gc9d01n->reset_level = panel_dev_config->flags.reset_active_high;
    gc9d01n->x_gap = 0;
    gc9d01n->y_gap = 0;
    if (panel_dev_config->vendor_config) {
        const gc9d01n_vendor_config_t *vendor_config = panel_dev_config->vendor_config;
        gc9d01n->init_cmds = vendor_config->init_cmds;
        gc9d01n->init_cmds_size = vendor_config->init_cmds_size;
    }

    // install panel functions
    gc9d01n->base.del = panel_gc9d01n_del;
    gc9d01n->base.reset = panel_gc9d01n_reset;
    gc9d01n->base.init = panel_gc9d01n_init;
    gc9d01n->base.draw_bitmap = panel_gc9d01n_draw_bitmap;
    gc9d01n->base.invert_color = panel_gc9d01n_invert_color;
    gc9d01n->base.mirror = panel_gc9d01n_mirror;
    gc9d01n->base.swap_xy = panel_gc9d01n_swap_xy;
    gc9d01n->base.set_gap = panel_gc9d01n_set_gap;
    gc9d01n->base.disp_on_off = panel_gc9d01n_disp_on_off;

    *ret_panel = &gc9d01n->base;
    return ESP_OK;

err:
    if (gc9d01n) {
        free(gc9d01n);
    }
    return ret;
}

static esp_err_t panel_gc9d01n_del(esp_lcd_panel_t *panel){
    gc9d01n_panel_t *gc9d01n = __containerof(panel, gc9d01n_panel_t, base);
    free(gc9d01n);
    return ESP_OK;
}

static esp_err_t panel_gc9d01n_reset(esp_lcd_panel_t *panel){
    gc9d01n_panel_t *gc9d01n = __containerof(panel, gc9d01n_panel_t, base);
    if (gc9d01n->reset_gpio_num >= 0) {
        // reset the LCD
        gpio_set_level(gc9d01n->reset_gpio_num, gc9d01n->reset_level);
        vTaskDelay(pdMS_TO_TICKS(10));
        gpio_set_level(gc9d01n->reset_gpio_num, !gc9d01n->reset_level);
        vTaskDelay(pdMS_TO_TICKS(120));
    }
    return ESP_OK;
}

static const gc9d01n_lcd_init_cmd_t vendor_specific_init_default[] = {
    // S/W Reset
    {0x01, NULL, 0, 120},
    // Sleep Out
    {0x11, NULL, 0, 120},
    // Normal Display Mode On
    {0x13, NULL, 0, 10},
    // Display On
    {0x29, NULL, 0, 100},
    // Column Address Set
    {0x2A, (uint8_t[]){0x00, 0x00, 0x00, 0xEF}, 4, 0},
    // Row Address Set
    {0x2B, (uint8_t[]){0x00, 0x00, 0x00, 0xEF}, 4, 0},
};

static esp_err_t panel_gc9d01n_init(esp_lcd_panel_t *panel){
    gc9d01n_panel_t *gc9d01n = __containerof(panel, gc9d01n_panel_t, base);
    esp_lcd_panel_io_handle_t io = gc9d01n->io;
    const gc9d01n_lcd_init_cmd_t *init_cmds = gc9d01n->init_cmds;
    uint16_t init_cmds_size = gc9d01n->init_cmds_size;

    if (init_cmds == NULL || init_cmds_size == 0) {
        // use default initialization commands
        init_cmds = vendor_specific_init_default;
        init_cmds_size = sizeof(vendor_specific_init_default) / sizeof(vendor_specific_init_default[0]);
    }

    // send initialization commands
    for (int i = 0; i < init_cmds_size; i++) {
        const gc9d01n_lcd_init_cmd_t *cmd = &init_cmds[i];
        ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, cmd->cmd, cmd->data, cmd->data_bytes), TAG, "send command failed");
        if (cmd->delay_ms > 0) {
            vTaskDelay(pdMS_TO_TICKS(cmd->delay_ms));
        }
    }

    return ESP_OK;
}

static esp_err_t panel_gc9d01n_draw_bitmap(esp_lcd_panel_t *panel, int x_start, int y_start, int x_end, int y_end, const void *color_data){
    gc9d01n_panel_t *gc9d01n = __containerof(panel, gc9d01n_panel_t, base);
    esp_lcd_panel_io_handle_t io = gc9d01n->io;
    uint8_t x_start_hi = (x_start + gc9d01n->x_gap) >> 8;
    uint8_t x_start_lo = (x_start + gc9d01n->x_gap) & 0xff;
    uint8_t x_end_hi = (x_end - 1 + gc9d01n->x_gap) >> 8;
    uint8_t x_end_lo = (x_end - 1 + gc9d01n->x_gap) & 0xff;
    uint8_t y_start_hi = (y_start + gc9d01n->y_gap) >> 8;
    uint8_t y_start_lo = (y_start + gc9d01n->y_gap) & 0xff;
    uint8_t y_end_hi = (y_end - 1 + gc9d01n->y_gap) >> 8;
    uint8_t y_end_lo = (y_end - 1 + gc9d01n->y_gap) & 0xff;

    // column address set
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, LCD_CMD_CASET, (uint8_t[]){x_start_hi, x_start_lo, x_end_hi, x_end_lo}, 4), TAG, "set column address failed");
    // row address set
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, LCD_CMD_RASET, (uint8_t[]){y_start_hi, y_start_lo, y_end_hi, y_end_lo}, 4), TAG, "set row address failed");
    // write memory
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, LCD_CMD_RAMWR, color_data, (x_end - x_start) * (y_end - y_start) * (gc9d01n->fb_bits_per_pixel / 8)), TAG, "write memory failed");

    return ESP_OK;
}

static esp_err_t panel_gc9d01n_invert_color(esp_lcd_panel_t *panel, bool invert_color_data){
    gc9d01n_panel_t *gc9d01n = __containerof(panel, gc9d01n_panel_t, base);
    esp_lcd_panel_io_handle_t io = gc9d01n->io;
    return esp_lcd_panel_io_tx_param(io, invert_color_data ? LCD_CMD_INVON : LCD_CMD_INVOFF, NULL, 0);
}

static esp_err_t panel_gc9d01n_mirror(esp_lcd_panel_t *panel, bool mirror_x, bool mirror_y){
    gc9d01n_panel_t *gc9d01n = __containerof(panel, gc9d01n_panel_t, base);
    esp_lcd_panel_io_handle_t io = gc9d01n->io;
    if (mirror_x) {
        gc9d01n->madctl_val |= LCD_CMD_MADCTL_MX;
    } else {
        gc9d01n->madctl_val &= ~LCD_CMD_MADCTL_MX;
    }
    if (mirror_y) {
        gc9d01n->madctl_val |= LCD_CMD_MADCTL_MY;
    } else {
        gc9d01n->madctl_val &= ~LCD_CMD_MADCTL_MY;
    }
    return esp_lcd_panel_io_tx_param(io, LCD_CMD_MADCTL, &gc9d01n->madctl_val, 1);
}

static esp_err_t panel_gc9d01n_swap_xy(esp_lcd_panel_t *panel, bool swap_axes){
    gc9d01n_panel_t *gc9d01n = __containerof(panel, gc9d01n_panel_t, base);
    esp_lcd_panel_io_handle_t io = gc9d01n->io;
    if (swap_axes) {
        gc9d01n->madctl_val |= LCD_CMD_MADCTL_ML;
    } else {
        gc9d01n->madctl_val &= ~LCD_CMD_MADCTL_ML;
    }
    return esp_lcd_panel_io_tx_param(io, LCD_CMD_MADCTL, &gc9d01n->madctl_val, 1);
}

static esp_err_t panel_gc9d01n_set_gap(esp_lcd_panel_t *panel, int x_gap, int y_gap){
    gc9d01n_panel_t *gc9d01n = __containerof(panel, gc9d01n_panel_t, base);
    gc9d01n->x_gap = x_gap;
    gc9d01n->y_gap = y_gap;
    return ESP_OK;
}

static esp_err_t panel_gc9d01n_disp_on_off(esp_lcd_panel_t *panel, bool off){
    gc9d01n_panel_t *gc9d01n = __containerof(panel, gc9d01n_panel_t, base);
    esp_lcd_panel_io_handle_t io = gc9d01n->io;
    return esp_lcd_panel_io_tx_param(io, off ? LCD_CMD_DISPOFF : LCD_CMD_DISPON, NULL, 0);
}
