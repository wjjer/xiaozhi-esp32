#ifndef TM1629A_DISPLAY_H
#define TM1629A_DISPLAY_H

#include "display.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

// 检查是否使用lichuang-dev-ml307c硬件布局
#ifdef TM1629A_BOARD_TYPE_LICHUANG_DEV_ML307C
    #define TM1629A_LICHUANG_LAYOUT 1
#else
    #define TM1629A_LICHUANG_LAYOUT 0
#endif

class TM1629ADisplay : public Display {
public:
    TM1629ADisplay(gpio_num_t stb_pin, gpio_num_t clk_pin, gpio_num_t dio_pin);
    virtual ~TM1629ADisplay();

    // Display interface implementation
    virtual void SetStatus(const char* status) override;
    virtual void ShowNotification(const char* notification, int duration_ms = 3000) override;
    virtual void SetEmotion(const char* emotion) override;
    virtual void ClearChatMessages() override;
    virtual void SetTheme(Theme* theme) override;
    virtual Theme* GetTheme() override { return current_theme_; }
    virtual void UpdateStatusBar(bool update_all = false) override;
    virtual void SetPowerSaveMode(bool on) override;
    virtual void SetupUI() override {}

    // TM1629A specific functions
    void SetTime(int hour, int minute);
    void ShowVolume(int volume, int duration_ms = 2000);  // Show volume on display, then restore time
    void SetIndicator(int index, bool state);
    bool GetIndicator(int index);
    void SetBrightness(uint8_t level);  // 0-7
    void SetSpectrum(const uint8_t* levels);  // Array of 8 levels for 8-column spectrum (5-row max each)
    void Clear();

    // Emoji patterns
    enum Emoji {
        EMOJI_HAPPY,
        EMOJI_SAD,
        EMOJI_NEUTRAL,
        EMOJI_EYES,
        EMOJI_HEART,
        EMOJI_MUSIC,
        EMOJI_LISTEN,
        EMOJI_SPEAK,
        EMOJI_ANGRY,
        EMOJI_CONFUSED,
        EMOJI_SURPRISED,
        EMOJI_COOL,
        EMOJI_SLEEPY,
        EMOJI_THINKING,
        EMOJI_COUNT
    };
    void SetEmoji(Emoji emoji);

    // Enable/disable colon blinking
    void EnableColonBlink(bool enable);

    // Animation control
    void EnableEmojiAnimation(bool enable, uint16_t interval_ms = 200);
    void SetAnimationFrame(uint8_t frame);

private:
    virtual bool Lock(int timeout_ms = 0) override;
    virtual void Unlock() override;

    void Init();
    void SendByte(uint8_t data);
    void SendCommand(uint8_t cmd);
    void UpdateDisplayBuffer();
    void ApplyEmojiAnimation();

    gpio_num_t stb_pin_;
    gpio_num_t clk_pin_;
    gpio_num_t dio_pin_;

    uint8_t display_buffer_[16];  // TM1629A has 16 bytes of display RAM
    uint8_t brightness_;
    bool power_save_mode_;

    // Time display state (7-segment digits)
    int hour_;
    int minute_;
    bool show_colon_;

#if TM1629A_LICHUANG_LAYOUT
    // lichuang-dev-ml307c: 4个指示灯 (GRID8 SEG3-6)
    uint8_t indicators_;
#else
    // 默认布局: 3个指示灯 (GRID8 SEG1-3)
    uint8_t indicators_;
#endif

    // Display mode
    enum DisplayMode {
        MODE_EMOJI,
        MODE_SPECTRUM,
        MODE_VOLUME
    };
    DisplayMode display_mode_;
    uint8_t emoji_;
    uint8_t spectrum_data_[8];  // 8 columns, each column 0-5 levels
    int volume_display_;  // Volume value for display (0-100)

    // Colon blinking
    bool colon_blink_enabled_;
    TaskHandle_t colon_blink_task_;
    static void ColonBlinkTask(void* arg);
    void StartColonBlinkTask();
    void StopColonBlinkTask();

    // Emoji animation
    bool emoji_animation_enabled_;
    uint16_t emoji_animation_interval_ms_;
    uint8_t emoji_current_frame_;
    uint8_t emoji_total_frames_;
    TaskHandle_t emoji_animation_task_;
    static void EmojiAnimationTask(void* arg);
    void StartEmojiAnimationTask();
    void StopEmojiAnimationTask();

    // Volume display timer
    esp_timer_handle_t volume_display_timer_;
    static void VolumeDisplayTimerCallback(void* arg);
    void StartVolumeDisplayTimer(int duration_ms);
    void StopVolumeDisplayTimer();

    // 7-segment font for digits 0-9 (segments S1-S7 = bits 0-6)
    static const uint8_t seven_segment_font_[10];

    // 5x8 emoji patterns (40 bits = 5 bytes per emoji, 8 bytes for GRID1-3)
#if TM1629A_LICHUANG_LAYOUT
    // lichuang-dev-ml307c: 行映射（每行8个LED，共5行）
    // GRID1 SEG1-8: 行1 (LED1-8)
    // GRID1 SEG9-16: 行2 (LED9-16)
    // GRID2 SEG1-8: 行3 (LED17-24)
    // GRID2 SEG9-16: 行4 (LED25-32)
    // GRID3 SEG1-8: 行5 (LED33-40)
    static const uint8_t emoji_patterns_[EMOJI_COUNT][5];
#else
    // 默认布局: 列映射
    // GRID1 SEG1-8: 列0 (LED1-8)
    // GRID1 SEG9-16: 列1 (LED9-16)
    // GRID2 SEG1-8: 列2 (LED17-24)
    // GRID2 SEG9-16: 列3 (LED25-32)
    // GRID3 SEG8-16: 列4 (LED33-40)
    static const uint8_t emoji_patterns_[EMOJI_COUNT][5];
#endif
};

#endif  // TM1629A_DISPLAY_H
