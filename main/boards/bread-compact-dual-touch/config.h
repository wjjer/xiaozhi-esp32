#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

#include <driver/gpio.h>
#include <driver/ledc.h>
#include <esp_lcd_panel_io.h>
#include <esp_lcd_panel_vendor.h>

// ==================== 音频配置 ====================
#define AUDIO_INPUT_SAMPLE_RATE  24000
#define AUDIO_OUTPUT_SAMPLE_RATE 24000

#define AUDIO_INPUT_REFERENCE    true

// I2S 音频引脚 (ES8311 输出 + ES7210 输入)
#define AUDIO_I2S_GPIO_MCLK GPIO_NUM_38
#define AUDIO_I2S_GPIO_WS   GPIO_NUM_13
#define AUDIO_I2S_GPIO_BCLK GPIO_NUM_14
#define AUDIO_I2S_GPIO_DIN  GPIO_NUM_12
#define AUDIO_I2S_GPIO_DOUT GPIO_NUM_45

// 音频编解码器 I2C 引脚
#define AUDIO_CODEC_I2C_SDA_PIN  GPIO_NUM_1
#define AUDIO_CODEC_I2C_SCL_PIN  GPIO_NUM_2
#define AUDIO_CODEC_ES8311_ADDR  ES8311_CODEC_DEFAULT_ADDR
#define AUDIO_CODEC_ES7210_ADDR  0x82

// ==================== 按键配置 ====================
#define BUILTIN_LED_GPIO        GPIO_NUM_3
#define BOOT_BUTTON_GPIO        GPIO_NUM_0
#define VOLUME_UP_BUTTON_GPIO   GPIO_NUM_NC
#define VOLUME_DOWN_BUTTON_GPIO GPIO_NUM_NC

// ==================== LCD 显示配置 ====================
// SPI 接口引脚
#define DISPLAY_SDA    GPIO_NUM_43  // SPI MOSI
#define DISPLAY_SCL    GPIO_NUM_44  // SPI CLK
#define DISPLAY_RES    GPIO_NUM_46  // 复位
#define DISPLAY_DC     GPIO_NUM_8   // 数据/命令选择
#define DISPLAY_CS     GPIO_NUM_NC  // 片选

// 屏幕尺寸
#define DISPLAY_WIDTH   240
#define DISPLAY_HEIGHT  240

// 屏幕方向
#define DISPLAY_SWAP_XY  true
#define DISPLAY_MIRROR_X true
#define DISPLAY_MIRROR_Y false
#define DISPLAY_OFFSET_X  0
#define DISPLAY_OFFSET_Y  0

// 背光配置
#define DISPLAY_BACKLIGHT_PIN GPIO_NUM_42
#define DISPLAY_BACKLIGHT_OUTPUT_INVERT false

// ==================== 4G 模块配置 (ML307) ====================
#define ML307_RX_PIN GPIO_NUM_48
#define ML307_TX_PIN GPIO_NUM_47

// ==================== 触摸传感器配置 ====================
// 使用 ESP32 内置 Touch Pad
// 注意：Touch Pad 编号不等于 GPIO 编号，需查阅芯片手册
// ESP32-S3 支持 Touch Pad 0-14
#define TOUCH_LEFT_PAD   TOUCH_PAD_NUM4   // 左侧触摸 (对应 GPIO 需查芯片手册)
#define TOUCH_RIGHT_PAD  TOUCH_PAD_NUM5   // 右侧触摸 (对应 GPIO 需查芯片手册)

// 触摸检测阈值 (需根据实际硬件校准)
#define TOUCH_THRESHOLD 30000

// 触摸检测间隔 (毫秒)
#define TOUCH_READ_INTERVAL_MS 500

// ==================== 舵机配置 ====================
// 摇头舵机 (左右摆动)
#define SERVO_HEAD_PIN      GPIO_NUM_10  // 摇头舵机 GPIO

// 甩尾巴舵机 (上下摆动)
#define SERVO_TAIL_PIN      GPIO_NUM_11  // 甩尾巴舵机 GPIO

// 舵机控制参数
#define SERVO_HEAD_AMPLITUDE   30  // 摇头幅度 (度)
#define SERVO_HEAD_PERIOD    500  // 摇头周期 (毫秒)
#define SERVO_TAIL_AMPLITUDE   45  // 尾巴摆动幅度 (度)
#define SERVO_TAIL_PERIOD    600  // 尾巴摆动周期 (毫秒)

// 动作持续时间 (毫秒)
#define SERVO_ACTION_DURATION  2000

#endif // _BOARD_CONFIG_H_
