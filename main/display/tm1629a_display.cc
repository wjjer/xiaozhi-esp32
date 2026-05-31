#include "tm1629a_display.h"
#include "board.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <cstring>
#include <ctime>

// static const char* TAG = "TM1629A";

// ============================================================================
// 字体数据 - 7段数码管字体 (共阴极)
// ============================================================================
// 段映射: SEG1-SEG7 = bits 0-6 (a,b,c,d,e,f,g)
const uint8_t TM1629ADisplay::seven_segment_font_[10] = {
    0x3F,  // 0: a+b+c+d+e+f
    0x06,  // 1: b+c
    0x5B,  // 2: a+b+g+e+d
    0x4F,  // 3: a+b+g+c+d
    0x66,  // 4: f+g+b+c
    0x6D,  // 5: a+f+g+c+d
    0x7D,  // 6: a+f+g+c+d+e
    0x07,  // 7: a+b+c
    0x7F,  // 8: 全亮
    0x6F   // 9: a+b+c+d+f+g
};

// ============================================================================
// 表情图案数据 - 5×8 点阵表情图案
// ============================================================================

#if TM1629A_LICHUANG_LAYOUT
// ========================================================================
// lichuang-dev-ml307c 硬件映射: 行布局 (5行 x 8列)
// ========================================================================
// GRID1 SEG1-8: 行1 (LED1-8) - pattern[0]的B0-B7对应LED1-8
// GRID1 SEG9-16: 行2 (LED9-16) - pattern[1]的B0-B7对应LED9-16
// GRID2 SEG1-8: 行3 (LED17-24) - pattern[2]的B0-B7对应LED17-24
// GRID2 SEG9-16: 行4 (LED25-32) - pattern[3]的B0-B7对应LED25-32
// GRID3 SEG1-8: 行5 (LED33-40) - pattern[4]的B0-B7对应LED33-40
//
// 位映射: B0=LED最右边(列8), B7=LED最左边(列1) (从右到左)
// 行映射: pattern[0]=行1, pattern[1]=行2, pattern[2]=行3, pattern[3]=行4, pattern[4]=行5
const uint8_t TM1629ADisplay::emoji_patterns_[EMOJI_COUNT][5] = {
    // HAPPY - 开心笑脸 (^_^)
    //    1 1 1 1 1 1
    //  1 1 1 1 1 1 1 1
    //  1 1 1 0 0 1 1 1
    //  1 1 1 1 1 1 1 1
    //  1 1 0 1 1 0 1 1
    {0x00, 0x3C, 0x42, 0x7E, 0x66},  // 行1-5 (更灿烂的笑脸)

    // SAD - 伤心脸 (T_T)
    //  1 1 1 1 1 1 1 1
    //  1 1 0 0 0 0 1 1
    //  1 1 1 1 1 1 1 1
    //  0 0 1 1 1 1 0 0
    //  0 1 0 0 0 0 1 0
    {0x3C, 0x42, 0x7E, 0x18, 0x24},  // 带眼泪的伤心脸

    // NEUTRAL - 中性脸 (-_-)n    //  1 1 1 1 1 1 1 1
    //  1 1 0 0 0 0 1 1
    //  1 1 0 0 0 0 1 1
    //  0 0 1 1 1 1 0 0
    //    1 1 1 1 1 1
    {0x3C, 0x42, 0x42, 0x18, 0x3C},  // 更自然的中性脸

    // EYES - 眨眼 (•_•)
    //  1 1 1 1 1 1 1 1
    //  1 1 0 0 0 0 1 1
    //  1 1 0 0 0 0 1 1
    //  1 1 1 1 1 1 1 1
    //    1 1 1 1 1 1
    {0x3C, 0x42, 0x42, 0x7E, 0x3C},  // 更生动的眨眼

    // HEART - 爱心 (❤)
    //     1 1 1 1 1
    //   1 1 1 1 1 1 1
    //  1 1 1 1 1 1 1 1
    //  0 1 1 1 1 1 1 0
    //  0 0 1 1 1 1 0 0
    {0x0E, 0x1F, 0x3F, 0x7F, 0x3E},  // 更饱满的爱心

    // MUSIC - 音符 (♪)
    //      1 1 1 1
    //    1 1 1 1 1 1
    //  1 1 1 1 1 1 1 1
    //  1 1 1 0 0 0 0 0
    //  1 1 0 0 0 0 0 0
    {0x06, 0x1E, 0x3F, 0x30, 0x60},  // 更有动感的音符

    // LISTEN - 聆听 (ear)
    //    1 1 1 1 1 1
    //  1 1 1 1 1 1 1 1
    //  1 1 1 1 1 1 1 1
    //  0 1 1 1 1 1 1 0
    //  0 0 1 1 1 1 0 0
    {0x06, 0x1E, 0x3F, 0x7F, 0x3C},  // 更形象的耳朵

    // SPEAK - 说话 (speaking)
    //  1 1 1 1 1 1 1 1
    //  0 1 1 1 1 1 1 0
    //  0 0 1 1 1 1 0 0
    //  0 0 1 1 1 1 0 0
    //  0 0 0 1 1 0 0 0
    {0x3C, 0x18, 0x0C, 0x06, 0x03},  // 更有层次感的声波

    // ANGRY - 生气 (angry)
    //  1 1 1 1 1 1 1 1
    //  1 1 0 0 0 0 1 1
    //  1 1 1 1 1 1 1 1
    //  1 1 0 1 1 0 1 1
    //  1 1 1 1 1 1 1 1
    {0x3C, 0x42, 0x7E, 0x66, 0x7E},  // 更愤怒的表情

    // CONFUSED - 困惑 (confused)
    //  1 1 1 1 1 1 1 1
    //  1 1 0 0 0 0 1 1
    //  0 0 1 1 1 1 0 0
    //  1 1 0 1 1 0 1 1
    //  0 0 1 1 1 1 0 0
    {0x3C, 0x42, 0x18, 0x66, 0x18},  // 更困惑的表情

    // SURPRISED - 惊讶 (surprised)
    //  1 1 1 1 1 1 1 1
    //  1 1 0 0 0 0 1 1
    //  0 0 1 1 1 1 0 0
    //  0 0 1 1 1 1 0 0
    //  0 1 0 0 0 0 1 0
    {0x3C, 0x42, 0x18, 0x18, 0x24},  // 更惊讶的表情

    // COOL - 酷 (cool)
    //  1 1 1 1 1 1 1 1
    //  1 1 0 0 0 0 1 1
    //  1 1 1 0 0 1 1 1
    //  1 1 0 1 1 0 1 1
    //  1 1 0 0 0 0 1 1
    {0x3C, 0x42, 0x66, 0x5A, 0x42},

    // SLEEPY - 困倦 (sleepy)
    //  1 1 1 1 1 1 1 1
    //  1 1 0 0 0 0 1 1
    //  1 1 0 0 0 0 1 1
    //  0 0 1 1 1 1 0 0
    //  0 0 0 1 1 0 0 0
    {0x3C, 0x42, 0x42, 0x18, 0x0C},  // 更困倦的表情

    // THINKING - 思考 (thinking)
    //  1 1 1 1 1 1 1 1
    //  1 1 0 0 0 0 1 1
    //  1 1 1 1 1 1 1 1
    //  0 0 1 1 1 1 0 0
    //  0 0 0 0 1 0 0 0
    {0x3C, 0x42, 0x7E, 0x18, 0x02},  // 更思考的表情
};
#else
// ========================================================================
// 默认硬件映射: 列布局
// ========================================================================
// GRID1 SEG1-8: 列0 (LED1-8)
// GRID1 SEG9-16: 列1 (LED9-16)
// GRID2 SEG1-8: 列2 (LED17-24)
// GRID2 SEG9-16: 列3 (LED25-32)
// GRID3 SEG8-16: 列4 (LED33-40)
// 每个字节8位，B0-B7对应从下到上或从上到下的行
//
// 假设: B0=第1行(底部), B7=第8行(顶部)
// 设计: 简单、清晰、避免重叠
const uint8_t TM1629ADisplay::emoji_patterns_[EMOJI_COUNT][5] = {
    // HAPPY - 开心笑脸 (^_^)
    {0x00, 0x66, 0xFF, 0x66, 0x3C},  // 更灿烂的笑脸

    // SAD - 伤心脸 (T_T)
    {0x00, 0x66, 0x00, 0x7E, 0x5A},  // 带眼泪的伤心脸

    // NEUTRAL - 中性脸 (-_-)
    {0x00, 0x66, 0x00, 0x18, 0x00},

    // EYES - 眨眼 (•_•)
    {0x00, 0x66, 0x66, 0x60, 0x00},

    // HEART - 爱心 (❤)
    {0x00, 0x66, 0xFF, 0x7E, 0x3C},

    // MUSIC - 音符 (♪)
    {0x00, 0x18, 0x3C, 0x18, 0x00},

    // LISTEN - 聆听 (ear)
    {0x00, 0x3C, 0x7E, 0x7E, 0x3C},

    // SPEAK - 说话 (speaking)
    {0x00, 0x00, 0x18, 0x18, 0x00},

    // ANGRY - 生气 (angry)
    {0x00, 0x66, 0x7E, 0x66, 0x7E},

    // CONFUSED - 困惑 (confused)
    {0x00, 0x66, 0x00, 0x66, 0x00},

    // SURPRISED - 惊讶 (surprised)
    {0x00, 0x66, 0x18, 0x18, 0x66},

    // COOL - 酷 (cool)
    {0x00, 0x66, 0x66, 0x5A, 0x66},

    // SLEEPY - 困倦 (sleepy)
    {0x00, 0x66, 0x66, 0x18, 0x18},

    // THINKING - 思考 (thinking)
    {0x00, 0x66, 0x7E, 0x18, 0x0C}
};
#endif // TM1629A_LICHUANG_LAYOUT

// ============================================================================
// 构造函数 - 初始化 TM1629A 显示
// ============================================================================
TM1629ADisplay::TM1629ADisplay(gpio_num_t stb_pin, gpio_num_t clk_pin, gpio_num_t dio_pin)
    : stb_pin_(stb_pin), clk_pin_(clk_pin), dio_pin_(dio_pin),
      brightness_(7), power_save_mode_(false), hour_(0), minute_(0),
      show_colon_(true), indicators_(0), display_mode_(MODE_EMOJI), emoji_(0),
      colon_blink_enabled_(true), colon_blink_task_(nullptr),
      emoji_animation_enabled_(false), emoji_animation_interval_ms_(200),
      emoji_current_frame_(0), emoji_total_frames_(1), emoji_animation_task_(nullptr),
      volume_display_timer_(nullptr) {

    memset(display_buffer_, 0, sizeof(display_buffer_));
    memset(spectrum_data_, 0, sizeof(spectrum_data_));

    width_ = 160;
    height_ = 64;

    Init();
    Clear();
    SetBrightness(7);

    // Start colon blink task
    StartColonBlinkTask();
}

// ============================================================================
// 析构函数
// ============================================================================
TM1629ADisplay::~TM1629ADisplay() {
    StopColonBlinkTask();
    StopEmojiAnimationTask();
    StopVolumeDisplayTimer();
    if (volume_display_timer_ != nullptr) {
        esp_timer_delete(volume_display_timer_);
        volume_display_timer_ = nullptr;
    }
}

// ============================================================================
// GPIO 初始化函数
// ============================================================================
void TM1629ADisplay::Init() {
    // ESP_LOGI(TAG, "=== TM1629A Init ===");
    // ESP_LOGI(TAG, "GPIO: STB=%d, CLK=%d, DIO=%d", stb_pin_, clk_pin_, dio_pin_);

    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << stb_pin_) | (1ULL << clk_pin_) | (1ULL << dio_pin_);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    esp_err_t ret = gpio_config(&io_conf);
    if (ret != ESP_OK) {
        // ESP_LOGE(TAG, "GPIO config failed: %s", esp_err_to_name(ret));
        return;
    }

    // 初始状态
    gpio_set_level(stb_pin_, 1);
    gpio_set_level(clk_pin_, 1);
    gpio_set_level(dio_pin_, 1);

    // ESP_LOGI(TAG, "GPIO initial states: STB=%d, CLK=%d, DIO=%d",
            //  gpio_get_level(stb_pin_), gpio_get_level(clk_pin_), gpio_get_level(dio_pin_));

    vTaskDelay(pdMS_TO_TICKS(10));

    // TM1629A 初始化命令序列
    // ESP_LOGI(TAG, "Sending init commands...");
    SendCommand(0x40);  // 数据命令: 地址自动增加
    // ESP_LOGI(TAG, "Command 0x40 sent");
    SendCommand(0x8F);  // 显示控制: 显示开, 亮度7
    // ESP_LOGI(TAG, "Command 0x8F sent (Display ON, Brightness 7)");

    // ESP_LOGI(TAG, "=== Init completed ===");
    // ESP_LOGI(TAG, "Layout: %s", TM1629A_LICHUANG_LAYOUT ? "LICHUANG" : "DEFAULT");
}

// ============================================================================
// 发送字节函数（串行通信底层实现）
// ============================================================================
void TM1629ADisplay::SendByte(uint8_t data) {
    // TM1629A数据格式：LSB先发送，时钟上升沿取数
    for (int i = 0; i < 8; i++) {
        gpio_set_level(clk_pin_, 0);
        gpio_set_level(dio_pin_, (data >> i) & 0x01);
        esp_rom_delay_us(2);
        gpio_set_level(clk_pin_, 1);
        esp_rom_delay_us(2);
    }
}

// ============================================================================
// 发送命令函数
// ============================================================================
void TM1629ADisplay::SendCommand(uint8_t cmd) {
    // ESP_LOGV(TAG, "SendCommand: 0x%02X", cmd);
    gpio_set_level(stb_pin_, 0);
    esp_rom_delay_us(1);
    SendByte(cmd);
    gpio_set_level(stb_pin_, 1);
    esp_rom_delay_us(1);
}

// ============================================================================
// 更新显示缓冲区函数
// ============================================================================
// TM1629A 内存映射 (SOP32封装):
// 地址00H-01H: GRID1 (SEG1-8, SEG9-16)
// 地址02H-03H: GRID2 (SEG1-8, SEG9-16)
// 地址04H-05H: GRID3 (SEG1-8, SEG9-16)
// 地址06H-07H: GRID4 (SEG1-8, SEG9-16)
// 地址08H-09H: GRID5 (SEG1-8, SEG9-16)
// 地址0AH-0BH: GRID6 (SEG1-8, SEG9-16)
// 地址0CH-0DH: GRID7 (SEG1-8, SEG9-16)
// 地址0EH-0FH: GRID8 (SEG1-8, SEG9-16)
void TM1629ADisplay::UpdateDisplayBuffer() {
    if (power_save_mode_) {
        memset(display_buffer_, 0, sizeof(display_buffer_));
    } else {
        memset(display_buffer_, 0, sizeof(display_buffer_));

#if TM1629A_LICHUANG_LAYOUT
        // ====================================================================
        // lichuang-dev-ml307c 硬件布局: 行映射
        // ====================================================================
        // 表情图案: 5行 x 8列
        // GRID1 SEG1-8: 行1 (pattern[0])
        // GRID1 SEG9-16: 行2 (pattern[1])
        // GRID2 SEG1-8: 行3 (pattern[2])
        // GRID2 SEG9-16: 行4 (pattern[3])
        // GRID3 SEG1-8: 行5 (pattern[4])
        if (display_mode_ == MODE_EMOJI) {
            const uint8_t* pattern = emoji_patterns_[emoji_];
            display_buffer_[0] = pattern[0];  // GRID1 SEG1-8 (行1)
            display_buffer_[1] = pattern[1];  // GRID1 SEG9-16 (行2)
            display_buffer_[2] = pattern[2];  // GRID2 SEG1-8 (行3)
            display_buffer_[3] = pattern[3];  // GRID2 SEG9-16 (行4)
            display_buffer_[4] = pattern[4];  // GRID3 SEG1-8 (行5)

            // 应用动画帧效果
            if (emoji_animation_enabled_) {
                ApplyEmojiAnimation();
            }
        } else if (display_mode_ == MODE_VOLUME) {
            // 音量显示模式 - 在GRID4-GRID8显示音量值
            int vol_digits[3];
            vol_digits[0] = volume_display_ / 100;
            vol_digits[1] = (volume_display_ % 100) / 10;
            vol_digits[2] = volume_display_ % 10;

            display_buffer_[6] = seven_segment_font_[vol_digits[0]];  // GRID4: 百位
            display_buffer_[8] = seven_segment_font_[vol_digits[1]];  // GRID5: 十位
            display_buffer_[10] = seven_segment_font_[vol_digits[2]]; // GRID6: 个位
            display_buffer_[12] = 0;  // GRID7: 不显示
        } else {
            // 频谱模式 - 8列 x 5行 (需要转置为行布局)
            for (int col = 0; col < 8; col++) {
                uint8_t level = spectrum_data_[col] > 5 ? 5 : spectrum_data_[col];
                for (int row = 0; row < level; row++) {
                    // 将列数据转换为行数据
                    int buffer_index = (row < 2) ? row : ((row == 2) ? 2 : ((row == 3) ? 3 : 4);
                    display_buffer_[buffer_index] |= (1 << col);
                }
            }
        }

        // ====================================================================
        // lichuang-dev-ml307c 时钟显示
        // ====================================================================
        // 第1位（时十位）: GRID4 SEG1-7
        // 第2位（时个位）: GRID5 SEG1-7
        // 第3位（冒号）: GRID8 SEG1-2
        // 第4位（分十位）: GRID6 SEG1-7
        // 第5位（分个位）: GRID7 SEG1-7
        if (display_mode_ != MODE_VOLUME) {
            int h1 = hour_ / 10;
            int h2 = hour_ % 10;
            int m1 = minute_ / 10;
            int m2 = minute_ % 10;

            display_buffer_[6] = seven_segment_font_[h1];   // GRID4: 小时十位
            display_buffer_[8] = seven_segment_font_[h2];   // GRID5: 小时个位
            display_buffer_[10] = seven_segment_font_[m1];  // GRID6: 分钟十位
            display_buffer_[12] = seven_segment_font_[m2];  // GRID7: 分钟个位
        }

        // ====================================================================
        // lichuang-dev-ml307c 指示灯和冒号映射
        // ====================================================================
        // 指示灯1: GRID8 SEG3
        // 指示灯2: GRID8 SEG4
        // 指示灯3: GRID8 SEG5
        // 指示灯4: GRID8 SEG6
        // 冒号LED1: GRID8 SEG1
        // 冒号LED2: GRID8 SEG2
        uint8_t buffer_14 = 0;

        // 冒号LED1-2
        if (show_colon_) {
            buffer_14 |= 0x01;  // 冒号LED1 = SEG1 (B0)
            buffer_14 |= 0x02;  // 冒号LED2 = SEG2 (B1)
        }

        // 指示灯 SEG3-6
        buffer_14 |= (indicators_ & 0x01) ? 0x04 : 0x00;  // 指示灯1 = SEG3 (B2)
        buffer_14 |= (indicators_ & 0x02) ? 0x08 : 0x00;  // 指示灯2 = SEG4 (B3)
        buffer_14 |= (indicators_ & 0x04) ? 0x10 : 0x00;  // 指示灯3 = SEG5 (B4)
        buffer_14 |= (indicators_ & 0x08) ? 0x20 : 0x00;  // 指示灯4 = SEG6 (B5)

        display_buffer_[14] = buffer_14;
#else
        // ====================================================================
        // 默认硬件布局: 列映射
        // ====================================================================
        // GRID 1-3: 5×8 LED矩阵
        // 列0->GRID1低地址, 列1->GRID1高地址
        // 列2->GRID2低地址, 列3->GRID2高地址
        // 列4->GRID3高地址(只用SEG8-16)
        if (display_mode_ == MODE_EMOJI) {
            const uint8_t* pattern = emoji_patterns_[emoji_];
            display_buffer_[0] = pattern[0];  // GRID1 SEG1-8 (列0)
            display_buffer_[1] = pattern[1];  // GRID1 SEG9-16 (列1)
            display_buffer_[2] = pattern[2];  // GRID2 SEG1-8 (列2)
            display_buffer_[3] = pattern[3];  // GRID2 SEG9-16 (列3)
            display_buffer_[5] = pattern[4];  // GRID3 SEG9-16 (列4)

            // 应用动画帧效果
            if (emoji_animation_enabled_) {
                ApplyEmojiAnimation();
            }
        } else if (display_mode_ == MODE_VOLUME) {
            // 音量显示模式 - 在GRID4-GRID8显示音量值
            int vol_digits[3];
            vol_digits[0] = volume_display_ / 100;
            vol_digits[1] = (volume_display_ % 100) / 10;
            vol_digits[2] = volume_display_ % 10;

            display_buffer_[6] = seven_segment_font_[vol_digits[0]];  // GRID4: 百位
            display_buffer_[8] = seven_segment_font_[vol_digits[1]];  // GRID5: 十位
            display_buffer_[10] = seven_segment_font_[vol_digits[2]]; // GRID6: 个位
            display_buffer_[12] = 0;  // GRID7: 不显示
        } else {
            // 频谱模式 - 8列 x 5行
            // GRID1 (00H/01H) = 列0/1, GRID2 (02H/03H) = 列2/3
            // GRID3 (04H/05H) = 列4/5, GRID4 (06H/07H) = 列6/7
            for (int col = 0; col < 8; col++) {
                uint8_t level = spectrum_data_[col] > 5 ? 5 : spectrum_data_[col];
                uint8_t val = 0;
                for (int row = 0; row < level; row++) {
                    val |= (1 << row);
                }
                if (col == 0) display_buffer_[0] = val;      // GRID1低地址 = 列0
                else if (col == 1) display_buffer_[1] = val; // GRID1高地址 = 列1
                else if (col == 2) display_buffer_[2] = val; // GRID2低地址 = 列2
                else if (col == 3) display_buffer_[3] = val; // GRID2高地址 = 列3
                else if (col == 4) display_buffer_[4] = val; // GRID3低地址 = 列4
                else if (col == 5) display_buffer_[5] = val; // GRID3高地址 = 列5
                else if (col == 6) display_buffer_[6] = val; // GRID4低地址 = 列6 (不用作时钟)
                else if (col == 7) display_buffer_[7] = val; // GRID4高地址 = 列7 (不用作时钟)
            }
        }

        // GRID 4-7: 时钟显示（7段数码管）
        if (display_mode_ != MODE_VOLUME) {
            int h1 = hour_ / 10;
            int h2 = hour_ % 10;
            int m1 = minute_ / 10;
            int m2 = minute_ % 10;

            display_buffer_[6] = seven_segment_font_[h1];   // GRID4: 小时十位
            display_buffer_[8] = seven_segment_font_[h2];   // GRID5: 小时个位
            display_buffer_[10] = seven_segment_font_[m1];  // GRID6: 分钟十位
            display_buffer_[12] = seven_segment_font_[m2];  // GRID7: 分钟个位
        }

        // GRID8: 冒号LED1-2 + 指示灯1-4 (SEG3-6)
        // - 冒号LED1 = SEG1 (B0)
        // - 冒号LED2 = SEG2 (B1)
        // - 指示灯1 = SEG3 (B2)
        // - 指示灯2 = SEG4 (B3)
        // - 指示灯3 = SEG5 (B4)
        // - 指示灯4 = SEG6 (B5)
        uint8_t buffer_14 = 0;

        // 指示灯 SEG3-6
        buffer_14 |= (indicators_ & 0x01) ? 0x04 : 0x00;  // 指示灯1 = SEG3 (B2)
        buffer_14 |= (indicators_ & 0x02) ? 0x08 : 0x00;  // 指示灯2 = SEG4 (B3)
        buffer_14 |= (indicators_ & 0x04) ? 0x10 : 0x00;  // 指示灯3 = SEG5 (B4)
        buffer_14 |= (indicators_ & 0x08) ? 0x20 : 0x00;  // 指示灯4 = SEG6 (B5)

        // 冒号LED1-2
        if (show_colon_) {
            buffer_14 |= 0x01;  // 冒号LED1 = SEG1 (B0)
            buffer_14 |= 0x02;  // 冒号LED2 = SEG2 (B1)
        }

        display_buffer_[14] = buffer_14;
#endif // TM1629A_LICHUANG_LAYOUT
    }

    // 发送显示数据到 TM1629A
    // ESP_LOGV(TAG, "Sending display buffer (16 bytes) to TM1629A...");
    gpio_set_level(stb_pin_, 0);
    esp_rom_delay_us(1);
    SendByte(0xC0);  // 起始地址00H
    // ESP_LOGV(TAG, "Start address command: 0xC0");
    for (int i = 0; i < 16; i++) {
        SendByte(display_buffer_[i]);
    }
    gpio_set_level(stb_pin_, 1);
    // ESP_LOGV(TAG, "Display buffer sent successfully");
}

// ============================================================================
// 清空显示函数
// ============================================================================
void TM1629ADisplay::Clear() {
    // ESP_LOGI(TAG, "Clear: Clearing display buffer");
    memset(display_buffer_, 0, sizeof(display_buffer_));
    UpdateDisplayBuffer();
}

// ============================================================================
// 应用表情动画
// ============================================================================
void TM1629ADisplay::ApplyEmojiAnimation() {
    // 根据表情类型和当前帧数应用动画效果
    // 动画基于 display_buffer_[0-3, 5] (对应 emoji_patterns_ 的 5 列)

    switch (emoji_) {
        case EMOJI_HAPPY:
            // 眨眼效果：交替清除左眼或右眼
            // HAPPY: {0x00, 0x66, 0xFF, 0x7E, 0x3C}
            // 左眼在列1 (0x66行5-7)，右眼在列2 (0xFF行5-7)
            if (emoji_current_frame_ == 0) {
                display_buffer_[1] = 0x66;  // 左眼开
                display_buffer_[2] = 0xFF;  // 右眼开
            } else {
                display_buffer_[1] = 0x60;  // 左眼闭 (只留行7)
                display_buffer_[2] = 0xF8;  // 右眼闭 (只留行5-7)
            }
            break;

        case EMOJI_SAD:
            // 眼泪效果：在右眼下添加眼泪点
            // SAD: {0x00, 0x66, 0x00, 0x7E, 0x3C}
            if (emoji_current_frame_ == 0) {
                display_buffer_[1] = 0x66;  // 无眼泪
                display_buffer_[2] = 0x00;
            } else {
                display_buffer_[1] = 0xE6;  // 添加眼泪 (行3)
                display_buffer_[2] = 0x01;  // 添加眼泪点 (行0)
            }
            break;

        case EMOJI_NEUTRAL:
            // 嘴型变化：横嘴 <-> 圆嘴
            // NEUTRAL: {0x00, 0x66, 0x00, 0x18, 0x00}
            if (emoji_current_frame_ == 0) {
                display_buffer_[3] = 0x18;  // 横嘴 (行3)
                display_buffer_[5] = 0x00;
            } else {
                display_buffer_[3] = 0x3C;  // 圆嘴 (行2-3)
                display_buffer_[5] = 0x18;  // 底部
            }
            break;

        case EMOJI_EYES:
            // 交替眨眼
            // EYES: {0x00, 0x66, 0x66, 0x60, 0x00}
            if (emoji_current_frame_ == 0) {
                display_buffer_[1] = 0x60;  // 左眼闭
                display_buffer_[2] = 0x66;  // 右眼开
            } else {
                display_buffer_[1] = 0x66;  // 左眼开
                display_buffer_[2] = 0x60;  // 右眼闭
            }
            break;

        case EMOJI_HEART:
            // 心跳效果：大小变化
            // HEART: {0x00, 0x66, 0xFF, 0x7E, 0x3C}
            if (emoji_current_frame_ == 0) {
                display_buffer_[1] = 0x66;  // 小爱心
                display_buffer_[2] = 0x81;
                display_buffer_[3] = 0x42;
                display_buffer_[5] = 0x3C;
            } else {
                display_buffer_[1] = 0x66;  // 大爱心
                display_buffer_[2] = 0xFF;
                display_buffer_[3] = 0x7E;
                display_buffer_[5] = 0x3C;
            }
            break;

        case EMOJI_MUSIC:
            // 音符跳动
            // MUSIC: {0x00, 0x18, 0x3C, 0x18, 0x00}
            if (emoji_current_frame_ == 0) {
                display_buffer_[1] = 0x18;  // 低位置
                display_buffer_[2] = 0x3C;
                display_buffer_[3] = 0x18;
            } else {
                display_buffer_[1] = 0x00;  // 高位置 (上移)
                display_buffer_[2] = 0x18;
                display_buffer_[3] = 0x3C;
            }
            break;

        case EMOJI_LISTEN:
            // 耳朵动：大小变化
            // LISTEN: {0x00, 0x3C, 0x7E, 0x7E, 0x3C}
            if (emoji_current_frame_ == 0) {
                display_buffer_[0] = 0x3C;  // 小耳朵
                display_buffer_[2] = 0x7E;
                display_buffer_[3] = 0x7E;
                display_buffer_[5] = 0x3C;
            } else {
                display_buffer_[0] = 0x7E;  // 大耳朵
                display_buffer_[2] = 0xFF;
                display_buffer_[3] = 0xFF;
                display_buffer_[5] = 0x7E;
            }
            break;

        case EMOJI_SPEAK:
            // 声波扩散：3帧动画
            // SPEAK: {0x00, 0x00, 0x18, 0x18, 0x00}
            emoji_total_frames_ = 3;
            if (emoji_current_frame_ == 0) {
                display_buffer_[2] = 0x18;  // 小波
                display_buffer_[3] = 0x18;
            } else if (emoji_current_frame_ == 1) {
                display_buffer_[2] = 0x3C;  // 中波
                display_buffer_[3] = 0x3C;
            } else {
                display_buffer_[2] = 0x7E;  // 大波
                display_buffer_[3] = 0x7E;
            }
            break;

        case EMOJI_ANGRY:
            // 愤怒表情：眼睛闪烁
            // ANGRY: {0x00, 0x66, 0x7E, 0x66, 0x7E}
            if (emoji_current_frame_ == 0) {
                display_buffer_[1] = 0x66;  // 眼睛开
                display_buffer_[3] = 0x66;
            } else {
                display_buffer_[1] = 0x60;  // 眼睛闭
                display_buffer_[3] = 0x60;
            }
            break;

        case EMOJI_CONFUSED:
            // 困惑表情：眼睛左右移动
            // CONFUSED: {0x00, 0x66, 0x00, 0x66, 0x00}
            if (emoji_current_frame_ == 0) {
                display_buffer_[1] = 0x66;  // 眼睛居中
                display_buffer_[3] = 0x66;
            } else {
                display_buffer_[1] = 0x60;  // 眼睛左移
                display_buffer_[3] = 0x06;  // 眼睛右移
            }
            break;

        case EMOJI_SURPRISED:
            // 惊讶表情：嘴巴大小变化
            // SURPRISED: {0x00, 0x66, 0x18, 0x18, 0x66}
            if (emoji_current_frame_ == 0) {
                display_buffer_[2] = 0x18;  // 小嘴巴
                display_buffer_[3] = 0x18;
            } else {
                display_buffer_[2] = 0x3C;  // 大嘴巴
                display_buffer_[3] = 0x3C;
            }
            break;

        case EMOJI_COOL:
            // 酷表情：墨镜闪烁
            // COOL: {0x00, 0x66, 0x66, 0x5A, 0x66}
            if (emoji_current_frame_ == 0) {
                display_buffer_[1] = 0x66;  // 墨镜暗
                display_buffer_[3] = 0x5A;
            } else {
                display_buffer_[1] = 0x7E;  // 墨镜亮
                display_buffer_[3] = 0x7E;
            }
            break;

        case EMOJI_SLEEPY:
            // 困倦表情：眼睛慢慢闭合
            // SLEEPY: {0x00, 0x66, 0x66, 0x18, 0x18}
            if (emoji_current_frame_ == 0) {
                display_buffer_[1] = 0x66;  // 眼睛开
                display_buffer_[2] = 0x66;
            } else {
                display_buffer_[1] = 0x60;  // 眼睛闭
                display_buffer_[2] = 0x60;
            }
            break;

        case EMOJI_THINKING:
            // 思考表情：脑袋上的问号闪烁
            // THINKING: {0x00, 0x66, 0x7E, 0x18, 0x0C}
            if (emoji_current_frame_ == 0) {
                display_buffer_[4] = 0x0C;  // 问号显示
            } else {
                display_buffer_[4] = 0x00;  // 问号隐藏
            }
            break;
    }
}

// ============================================================================
// 设置时间函数
// ============================================================================
void TM1629ADisplay::SetTime(int hour, int minute) {
    hour_ = hour % 24;
    minute_ = minute % 60;
    UpdateDisplayBuffer();
}

// ============================================================================
// 显示音量函数
// ============================================================================
void TM1629ADisplay::ShowVolume(int volume, int duration_ms) {
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;

    volume_display_ = volume;
    display_mode_ = MODE_VOLUME;

    UpdateDisplayBuffer();

    // 启动定时器，duration_ms后恢复时钟显示
    StartVolumeDisplayTimer(duration_ms);
}

// ============================================================================
// 音量显示定时器回调
// ============================================================================
void TM1629ADisplay::VolumeDisplayTimerCallback(void* arg) {
    TM1629ADisplay* display = static_cast<TM1629ADisplay*>(arg);
    if (display) {
        display->UpdateStatusBar();  // 恢复时钟显示
    }
}

// ============================================================================
// 启动音量显示定时器
// ============================================================================
void TM1629ADisplay::StartVolumeDisplayTimer(int duration_ms) {
    if (volume_display_timer_ == nullptr) {
        esp_timer_create_args_t timer_args = {
            .callback = VolumeDisplayTimerCallback,
            .arg = this,
            .dispatch_method = ESP_TIMER_TASK,
            .name = "volume_display_timer",
            .skip_unhandled_events = true
        };
        esp_timer_create(&timer_args, &volume_display_timer_);
    }
    esp_timer_stop(volume_display_timer_);
    esp_timer_start_once(volume_display_timer_, duration_ms * 1000);  // 转换为微秒
}

// ============================================================================
// 停止音量显示定时器
// ============================================================================
void TM1629ADisplay::StopVolumeDisplayTimer() {
    if (volume_display_timer_ != nullptr) {
        esp_timer_stop(volume_display_timer_);
    }
}

// ============================================================================
// 设置指示灯函数
// ============================================================================
void TM1629ADisplay::SetIndicator(int index, bool state) {
    // ESP_LOGI(TAG, "SetIndicator: index=%d, state=%d, current indicators=0x%02X",
    //          index, state, indicators_);
    // 默认布局: 只支持3个指示灯
    if (index >= 0 && index < 4) {
        if (state) {
            indicators_ |= (1 << index);
            // ESP_LOGI(TAG, "  -> Setting indicator %d ON, new indicators=0x%02X", index, indicators_);
        } else {
            indicators_ &= ~(1 << index);
            // ESP_LOGI(TAG, "  -> Setting indicator %d OFF, new indicators=0x%02X", index, indicators_);
        }
        UpdateDisplayBuffer();
    }
}

// ============================================================================
// 获取指示灯状态函数
// ============================================================================
bool TM1629ADisplay::GetIndicator(int index) {
#if TM1629A_LICHUANG_LAYOUT
    // lichuang-dev-ml307c: 支持4个指示灯
    if (index >= 0 && index < 4) {
        return (indicators_ & (1 << index)) != 0;
    }
#else
    // 默认布局: 只支持3个指示灯
    if (index >= 0 && index < 3) {
        return (indicators_ & (1 << index)) != 0;
    }
#endif // TM1629A_LICHUANG_LAYOUT
    return false;
}

// ============================================================================
// 设置亮度函数
// ============================================================================
void TM1629ADisplay::SetBrightness(uint8_t level) {
    if (level > 7) level = 7;
    brightness_ = level;
    if (level == 0) {
        // 亮度为0时，完全关闭显示
        SendCommand(0x80);
    } else {
        // 亮度为1-7时，设置相应亮度
        uint8_t cmd = 0x88 | (level - 1);
        // ESP_LOGI(TAG, "SetBrightness: level=%d, command=0x%02X", level, cmd);
        SendCommand(cmd);
    }
}

// ============================================================================
// 设置频谱显示函数
// ============================================================================
void TM1629ADisplay::SetSpectrum(const uint8_t* levels) {
    if (levels) {
        memcpy(spectrum_data_, levels, 8);  // 8 columns
        display_mode_ = MODE_SPECTRUM;
        UpdateDisplayBuffer();
    }
}

// ============================================================================
// 设置表情函数
// ============================================================================
void TM1629ADisplay::SetEmoji(Emoji emoji) {
    if (emoji >= 0 && emoji < EMOJI_COUNT) {
        emoji_ = emoji;
        display_mode_ = MODE_EMOJI;
        UpdateDisplayBuffer();
    }
}

// ============================================================================
// 设置表情（Display基类接口实现）
// ============================================================================
void TM1629ADisplay::SetEmotion(const char* emotion) {
    if (strcmp(emotion, "happy") == 0) {
        SetEmoji(EMOJI_HAPPY);
    } else if (strcmp(emotion, "sad") == 0) {
        SetEmoji(EMOJI_SAD);
    } else if (strcmp(emotion, "neutral") == 0) {
        SetEmoji(EMOJI_NEUTRAL);
    } else if (strcmp(emotion, "eyes") == 0) {
        SetEmoji(EMOJI_EYES);
    } else if (strcmp(emotion, "heart") == 0) {
        SetEmoji(EMOJI_HEART);
    } else if (strcmp(emotion, "music") == 0) {
        SetEmoji(EMOJI_MUSIC);
    } else if (strcmp(emotion, "listen") == 0) {
        SetEmoji(EMOJI_LISTEN);
    } else if (strcmp(emotion, "speak") == 0) {
        SetEmoji(EMOJI_SPEAK);
    } else if (strcmp(emotion, "angry") == 0) {
        SetEmoji(EMOJI_ANGRY);
    } else if (strcmp(emotion, "confused") == 0) {
        SetEmoji(EMOJI_CONFUSED);
    } else if (strcmp(emotion, "surprised") == 0) {
        SetEmoji(EMOJI_SURPRISED);
    } else if (strcmp(emotion, "cool") == 0) {
        SetEmoji(EMOJI_COOL);
    } else if (strcmp(emotion, "sleepy") == 0) {
        SetEmoji(EMOJI_SLEEPY);
    } else if (strcmp(emotion, "thinking") == 0) {
        SetEmoji(EMOJI_THINKING);
    } else {
        SetEmoji(EMOJI_NEUTRAL);
    }
}

// ============================================================================
// 设置状态（Display基类接口实现）
// ============================================================================
void TM1629ADisplay::SetStatus(const char* status) {
}

// ============================================================================
// 显示通知（Display基类接口实现）
// ============================================================================
void TM1629ADisplay::ShowNotification(const char* notification, int duration_ms) {
    uint8_t old_indicators = indicators_;
#if TM1629A_LICHUANG_LAYOUT
    // lichuang-dev-ml307c: 4个指示灯
    for (int i = 0; i < 3; i++) {
        indicators_ = 0x0F;  // 4个指示灯全部亮起 (0x0F = B0-B3)
        UpdateDisplayBuffer();
        vTaskDelay(pdMS_TO_TICKS(100));
        indicators_ = 0;
        UpdateDisplayBuffer();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
#else
    // 默认布局: 3个指示灯
    for (int i = 0; i < 3; i++) {
        indicators_ = 0x07;  // 3个指示灯全部亮起 (0x07 = B0-B2)
        UpdateDisplayBuffer();
        vTaskDelay(pdMS_TO_TICKS(100));
        indicators_ = 0;
        UpdateDisplayBuffer();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
#endif // TM1629A_LICHUANG_LAYOUT
    indicators_ = old_indicators;
    UpdateDisplayBuffer();
}

// ============================================================================
// 清空聊天消息（Display基类接口实现）
// ============================================================================
void TM1629ADisplay::ClearChatMessages() {
}

// ============================================================================
// 更新状态栏（Display基类接口实现）
// ============================================================================
void TM1629ADisplay::UpdateStatusBar(bool update_all) {
    // 恢复到表情/时钟显示模式
    display_mode_ = MODE_EMOJI;

    // 更新时间显示
    time_t now = time(nullptr);
    if (now > 0) {
        struct tm* timeinfo = localtime(&now);
        if (timeinfo) {
            // 调整为中国标准时间（UTC+8）
            int hour = (timeinfo->tm_hour + 8) % 24;
            SetTime(hour, timeinfo->tm_min);
        }
    }

    // 更新充电状态指示灯（指示灯0）
    int battery_level;
    bool charging, discharging;
    if (Board::GetInstance().GetBatteryLevel(battery_level, charging, discharging)) {
        // 充电时亮起指示灯0，否则熄灭
        SetIndicator(0, charging);
    }
}

// ============================================================================
// 设置节能模式（Display基类接口实现）
// ============================================================================
void TM1629ADisplay::SetPowerSaveMode(bool on) {
    power_save_mode_ = on;
    if (on) {
        SendCommand(0x80);
    } else {
        SendCommand(0x88 | brightness_);
    }
    UpdateDisplayBuffer();
}

// ============================================================================
// 设置主题（Display基类接口实现）
// ============================================================================
void TM1629ADisplay::SetTheme(Theme* theme) {
}

// ============================================================================
// 锁定显示（Display基类接口实现）
// ============================================================================
bool TM1629ADisplay::Lock(int timeout_ms) {
    return true;
}

// ============================================================================
// 解锁显示（Display基类接口实现）
// ============================================================================
void TM1629ADisplay::Unlock() {
}

// ============================================================================
// 启动冒号闪烁任务
// ============================================================================
void TM1629ADisplay::StartColonBlinkTask() {
    if (colon_blink_task_ == nullptr) {
        xTaskCreate(ColonBlinkTask, "ColonBlink", 2048, this, 5, &colon_blink_task_);
        // ESP_LOGI(TAG, "Colon blink task started");
    }
}

// ============================================================================
// 停止冒号闪烁任务
// ============================================================================
void TM1629ADisplay::StopColonBlinkTask() {
    if (colon_blink_task_ != nullptr) {
        vTaskDelete(colon_blink_task_);
        colon_blink_task_ = nullptr;
        // ESP_LOGI(TAG, "Colon blink task stopped");
    }
}

// ============================================================================
// 冒号闪烁任务
// ============================================================================
void TM1629ADisplay::ColonBlinkTask(void* arg) {
    TM1629ADisplay* display = static_cast<TM1629ADisplay*>(arg);
    bool colon_state = true;

    while (true) {
        if (display->colon_blink_enabled_) {
            colon_state = !colon_state;
            display->show_colon_ = colon_state;
            display->UpdateDisplayBuffer();
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// ============================================================================
// 启用/禁用冒号闪烁
// ============================================================================
void TM1629ADisplay::EnableColonBlink(bool enable) {
    colon_blink_enabled_ = enable;
    if (!enable) {
        show_colon_ = true;  // 默认显示冒号
        UpdateDisplayBuffer();
    }
}

// ============================================================================
// 启用/禁用表情动画
// ============================================================================
void TM1629ADisplay::EnableEmojiAnimation(bool enable, uint16_t interval_ms) {
    if (enable && emoji_animation_task_ == nullptr) {
        emoji_animation_enabled_ = true;
        emoji_animation_interval_ms_ = interval_ms;
        // 获取当前表情的帧数
        emoji_total_frames_ = (emoji_ < EMOJI_COUNT) ? 2 : 1;  // 默认2帧
        emoji_current_frame_ = 0;
        StartEmojiAnimationTask();
        // ESP_LOGI(TAG, "Emoji animation enabled with interval %d ms", interval_ms);
    } else if (!enable) {
        emoji_animation_enabled_ = false;
        StopEmojiAnimationTask();
        // ESP_LOGI(TAG, "Emoji animation disabled");
    }
}

// ============================================================================
// 设置动画帧
// ============================================================================
void TM1629ADisplay::SetAnimationFrame(uint8_t frame) {
    emoji_current_frame_ = frame % emoji_total_frames_;
    UpdateDisplayBuffer();
}

// ============================================================================
// 启动表情动画任务
// ============================================================================
void TM1629ADisplay::StartEmojiAnimationTask() {
    if (emoji_animation_task_ == nullptr) {
        xTaskCreate(EmojiAnimationTask, "EmojiAnim", 2048, this, 5, &emoji_animation_task_);
        // ESP_LOGI(TAG, "Emoji animation task started");
    }
}

// ============================================================================
// 停止表情动画任务
// ============================================================================
void TM1629ADisplay::StopEmojiAnimationTask() {
    if (emoji_animation_task_ != nullptr) {
        vTaskDelete(emoji_animation_task_);
        emoji_animation_task_ = nullptr;
        // ESP_LOGI(TAG, "Emoji animation task stopped");
    }
}

// ============================================================================
// 表情动画任务
// ============================================================================
void TM1629ADisplay::EmojiAnimationTask(void* arg) {
    TM1629ADisplay* display = static_cast<TM1629ADisplay*>(arg);

    while (true) {
        if (display->emoji_animation_enabled_ && display->display_mode_ == MODE_EMOJI) {
            display->emoji_current_frame_++;
            if (display->emoji_current_frame_ >= display->emoji_total_frames_) {
                display->emoji_current_frame_ = 0;
            }
            display->UpdateDisplayBuffer();
        }
        vTaskDelay(pdMS_TO_TICKS(display->emoji_animation_interval_ms_));
    }
}

