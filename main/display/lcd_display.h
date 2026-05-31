#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include "lvgl_display.h"
#include "gif/lvgl_gif.h"

#include <esp_lcd_panel_io.h>
#include <esp_lcd_panel_ops.h>
#include <esp_lcd_touch.h>
#include <font_emoji.h>

#include <functional>
#include <atomic>
#include <memory>
#include <string>
#include <vector>

#define PREVIEW_IMAGE_DURATION_MS 5000


class LcdDisplay : public LvglDisplay {
protected:
    esp_lcd_panel_io_handle_t panel_io_ = nullptr;
    esp_lcd_panel_handle_t panel_ = nullptr;
    
    lv_draw_buf_t draw_buf_;
    lv_obj_t* top_bar_ = nullptr;
    lv_obj_t* status_bar_ = nullptr;
    lv_obj_t* content_ = nullptr;
    lv_obj_t* container_ = nullptr;
    lv_obj_t* side_bar_ = nullptr;
    lv_obj_t* bottom_bar_ = nullptr;
    lv_obj_t* preview_image_ = nullptr;
    lv_obj_t* emoji_label_ = nullptr;
    lv_obj_t* emoji_image_ = nullptr;
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
    void ResetAlarmUiRefs();
    lv_obj_t* PrepareAlarmUiContent(uint32_t bg_color);
    lv_obj_t* home_time_label_ = nullptr;
    lv_obj_t* home_date_label_ = nullptr;
    lv_obj_t* home_status_label_ = nullptr;
    lv_obj_t* home_grid_ = nullptr;
    lv_obj_t* home_card_ai_ = nullptr;
    lv_obj_t* home_card_study_ = nullptr;
    lv_obj_t* home_card_alarm_ = nullptr;
    lv_obj_t* home_card_tools_ = nullptr;
    lv_obj_t* app_grid_title_label_ = nullptr;
    lv_obj_t* app_grid_container_ = nullptr;
    lv_obj_t* app_back_button_ = nullptr;
    lv_obj_t* placeholder_title_label_ = nullptr;
    lv_obj_t* placeholder_desc_label_ = nullptr;
    // AI Partner three states
    lv_obj_t* ai_state_panel_ = nullptr;
    lv_obj_t* ai_state_image_ = nullptr;
    lv_obj_t* ai_character_image_ = nullptr;
    lv_obj_t* ai_state_icon_ = nullptr;
    lv_obj_t* ai_state_label_ = nullptr;
    lv_obj_t* ai_wave_container_ = nullptr;
    lv_obj_t* ai_thinking_indicator_ = nullptr;
    lv_obj_t* ai_speaking_wave_1_ = nullptr;
    lv_obj_t* ai_speaking_wave_2_ = nullptr;
    lv_obj_t* ai_speaking_wave_3_ = nullptr;
    lv_obj_t* ai_message_label_ = nullptr;
    // Study screen members
    lv_obj_t* study_card_translate_ = nullptr;
    lv_obj_t* study_card_wordbook_ = nullptr;
    lv_obj_t* study_card_vocab_ = nullptr;
    lv_obj_t* study_card_k12_ = nullptr;
    // Dialog/Toast members
    lv_obj_t* dialog_overlay_ = nullptr;
    lv_obj_t* dialog_panel_ = nullptr;
    lv_obj_t* toast_label_ = nullptr;
    lv_obj_t* toast_timer_ = nullptr;
    // Dialog callback storage
    std::function<void()> dialog_on_confirm_;
    std::function<void()> dialog_on_cancel_;
    static void DialogConfirmCallback(lv_event_t* e);
    static void DialogCancelCallback(lv_event_t* e);
    // AI floating layer
    lv_obj_t* ai_float_panel_ = nullptr;
    lv_obj_t* ai_float_icon_ = nullptr;
    lv_obj_t* ai_float_label_ = nullptr;
    std::vector<std::unique_ptr<LvglImage>> alarm_ui_image_cache_;
    int alarm_editor_id_ = -1;
    int alarm_editor_label_index_ = 0;
    bool alarm_editor_is_new_ = false;
    bool alarm_editor_enabled_ = true;
    bool alarm_editor_repeat_daily_ = true;
    int alarm_editor_hour_ = 7;
    int alarm_editor_minute_ = 0;
#endif
    esp_lcd_touch_handle_t touch_handle_ = nullptr;
    std::unique_ptr<LvglGif> gif_controller_ = nullptr;
    lv_obj_t* emoji_box_ = nullptr;
    lv_obj_t* chat_message_label_ = nullptr;
    esp_timer_handle_t preview_timer_ = nullptr;
    std::unique_ptr<LvglImage> preview_image_cached_ = nullptr;
    bool hide_subtitle_ = false;  // Control whether to hide chat messages/subtitles

    void InitializeLcdThemes();
    virtual bool Lock(int timeout_ms = 0) override;
    virtual void Unlock() override;

protected:
    // Add protected constructor
    LcdDisplay(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_handle_t panel, int width, int height);
    
public:
    ~LcdDisplay();
    virtual void SetEmotion(const char* emotion) override;
    virtual void SetChatMessage(const char* role, const char* content) override;
    virtual void ClearChatMessages() override;
    virtual void SetPreviewImage(std::unique_ptr<LvglImage> image) override;
    virtual void SetupUI() override;
    // Add theme switching function
    virtual void SetTheme(Theme* theme) override;
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
    virtual void SetupHomeScreen();
    virtual void SetupAppGridScreen();
    virtual void SetupBootScreen();
    virtual void ShowRoute(const std::string& route);
    virtual void SetupPlaceholderScreen(const char* title, const char* description);
    virtual void SetupAiScreen();
    virtual void SetAiState(int state);  // 0=idle, 1=listening, 2=thinking, 3=speaking
    virtual void SetAiMessage(const char* message);
    virtual void SetupStudyScreen();
    virtual void SetupAlarmScreen();
    virtual void SetupAlarmEditorScreen(int alarm_id, bool is_new);
    virtual void SetupWeatherScreen();
    virtual void SetupTimerScreen();
    virtual void SetupStopwatchScreen();
    virtual void SetupFocusScreen();
    virtual void SetupNightLightScreen();
    // Study related screens
    virtual void SetupTranslateScreen();
    virtual void SetupWordbookScreen();
    virtual void SetupVocabScreen();
    virtual void SetupK12Screen();
    // Dialog/Toast system
    virtual void ShowToast(const char* message, int duration_ms = 2000);
    virtual void HideToast();
    virtual void ShowDialog(const char* title, const char* message, 
                           const char* btn_confirm, const char* btn_cancel,
                           std::function<void()> on_confirm, std::function<void()> on_cancel);
    virtual void HideDialog();
    // AI floating layer
    virtual void ShowAiFloat(const char* message);
    virtual void HideAiFloat();
    virtual void SetHomeTime(const char* time_text);
    virtual void SetHomeStatus(const char* status_text);
    virtual void AttachTouchHandle(esp_lcd_touch_handle_t touch_handle);
    virtual void RefreshAlarmPage();
    virtual void ShowAlarmRinging(const char* message);
    virtual void SaveAlarmEditor();
    virtual void DeleteAlarmEditor();
    // Override base class methods for new UI
    virtual void SetStatus(const char* status) override;
    virtual void ShowNotification(const char* notification, int duration_ms = 3000) override;
#endif
    
    // Set whether to hide chat messages/subtitles
    void SetHideSubtitle(bool hide);
};

// SPI LCD display
class SpiLcdDisplay : public LcdDisplay {
public:
    SpiLcdDisplay(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_handle_t panel,
                  int width, int height, int offset_x, int offset_y,
                  bool mirror_x, bool mirror_y, bool swap_xy);
};

// RGB LCD display
class RgbLcdDisplay : public LcdDisplay {
public:
    RgbLcdDisplay(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_handle_t panel,
                  int width, int height, int offset_x, int offset_y,
                  bool mirror_x, bool mirror_y, bool swap_xy);
};

// MIPI LCD display
class MipiLcdDisplay : public LcdDisplay {
public:
    MipiLcdDisplay(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_handle_t panel,
                   int width, int height, int offset_x, int offset_y,
                   bool mirror_x, bool mirror_y, bool swap_xy);
};

#endif // LCD_DISPLAY_H
