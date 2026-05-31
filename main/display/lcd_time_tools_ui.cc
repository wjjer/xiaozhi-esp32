#include "lcd_display.h"

#include "board.h"
#include "lvgl_theme.h"
#include "time_tools_manager.h"

namespace {
std::string FormatMinutesSeconds(int total_seconds) {
    if (total_seconds < 0) {
        total_seconds = 0;
    }
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", total_seconds / 60, total_seconds % 60);
    return std::string(buffer);
}

std::string FormatHoursMinutesSeconds(int total_seconds) {
    if (total_seconds < 0) {
        total_seconds = 0;
    }
    char buffer[16];
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hours, minutes, seconds);
    return std::string(buffer);
}
}

void LcdDisplay::SetupTimerScreen() {
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
    UiSystem::GetInstance().SetState(UiSystemState::AppGrid);
    UiSystem::GetInstance().SetHomeStatus("Timer page");
#endif
    SetupPlaceholderScreen("Timer", "Local countdown for study and tasks");

    if (content_ == nullptr) {
        return;
    }

    DisplayLockGuard lock(this);
    auto lvgl_theme = static_cast<LvglTheme*>(current_theme_);
    auto& manager = TimeToolsManager::GetInstance();

    lv_obj_t* time_label = lv_label_create(content_);
    auto time_text = FormatMinutesSeconds(manager.GetTimerRemainingSeconds());
    lv_label_set_text(time_label, time_text.c_str());
    lv_obj_align(time_label, LV_ALIGN_CENTER, 0, 16);

    lv_obj_t* start_btn = lv_btn_create(content_);
    lv_obj_set_size(start_btn, 92, 34);
    lv_obj_align(start_btn, LV_ALIGN_CENTER, -52, 60);
    lv_obj_t* start_label = lv_label_create(start_btn);
    lv_label_set_text(start_label, manager.IsTimerRunning() ? "Pause" : "Start");
    lv_obj_center(start_label);
    lv_obj_add_event_cb(
        start_btn,
        [](lv_event_t*) {
            TimeToolsManager::GetInstance().ToggleTimer();
        },
        LV_EVENT_CLICKED,
        nullptr);

    lv_obj_t* reset_btn = lv_btn_create(content_);
    lv_obj_set_size(reset_btn, 92, 34);
    lv_obj_align(reset_btn, LV_ALIGN_CENTER, 52, 60);
    lv_obj_t* reset_label = lv_label_create(reset_btn);
    lv_label_set_text(reset_label, "Reset");
    lv_obj_center(reset_label);
    lv_obj_add_event_cb(
        reset_btn,
        [](lv_event_t*) {
            TimeToolsManager::GetInstance().ResetTimer();
        },
        LV_EVENT_CLICKED,
        nullptr);

    lv_obj_t* preset_row = lv_obj_create(content_);
    lv_obj_set_size(preset_row, LV_PCT(88), 38);
    lv_obj_align(preset_row, LV_ALIGN_BOTTOM_MID, 0, -8);
    lv_obj_set_style_bg_opa(preset_row, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(preset_row, 0, 0);
    lv_obj_set_style_pad_all(preset_row, 0, 0);
    lv_obj_set_layout(preset_row, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(preset_row, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(preset_row, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    const int presets[] = {5, 15, 25, 45};
    for (int preset : presets) {
        lv_obj_t* preset_btn = lv_btn_create(preset_row);
        lv_obj_set_size(preset_btn, 48, 28);
        lv_obj_set_style_radius(preset_btn, lvgl_theme->spacing(2), 0);
        lv_obj_t* preset_label = lv_label_create(preset_btn);
        char text[8];
        snprintf(text, sizeof(text), "%dm", preset);
        lv_label_set_text(preset_label, text);
        lv_obj_center(preset_label);
        lv_obj_add_event_cb(
            preset_btn,
            [](lv_event_t* e) {
                int minutes = static_cast<int>(reinterpret_cast<intptr_t>(lv_event_get_user_data(e)));
                TimeToolsManager::GetInstance().SetTimerPresetMinutes(minutes);
            },
            LV_EVENT_CLICKED,
            reinterpret_cast<void*>(static_cast<intptr_t>(preset)));
    }
}

void LcdDisplay::SetupStopwatchScreen() {
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
    UiSystem::GetInstance().SetState(UiSystemState::AppGrid);
    UiSystem::GetInstance().SetHomeStatus("Stopwatch page");
#endif
    SetupPlaceholderScreen("Stopwatch", "Local stopwatch with start, pause and reset");

    if (content_ == nullptr) {
        return;
    }

    DisplayLockGuard lock(this);
    auto& manager = TimeToolsManager::GetInstance();

    lv_obj_t* time_label = lv_label_create(content_);
    auto time_text = FormatHoursMinutesSeconds(manager.GetStopwatchElapsedSeconds());
    lv_label_set_text(time_label, time_text.c_str());
    lv_obj_align(time_label, LV_ALIGN_CENTER, 0, 16);

    lv_obj_t* start_btn = lv_btn_create(content_);
    lv_obj_set_size(start_btn, 92, 34);
    lv_obj_align(start_btn, LV_ALIGN_CENTER, -52, 60);
    lv_obj_t* start_label = lv_label_create(start_btn);
    lv_label_set_text(start_label, manager.IsStopwatchRunning() ? "Pause" : "Start");
    lv_obj_center(start_label);
    lv_obj_add_event_cb(
        start_btn,
        [](lv_event_t*) {
            TimeToolsManager::GetInstance().ToggleStopwatch();
        },
        LV_EVENT_CLICKED,
        nullptr);

    lv_obj_t* reset_btn = lv_btn_create(content_);
    lv_obj_set_size(reset_btn, 92, 34);
    lv_obj_align(reset_btn, LV_ALIGN_CENTER, 52, 60);
    lv_obj_t* reset_label = lv_label_create(reset_btn);
    lv_label_set_text(reset_label, "Reset");
    lv_obj_center(reset_label);
    lv_obj_add_event_cb(
        reset_btn,
        [](lv_event_t*) {
            TimeToolsManager::GetInstance().ResetStopwatch();
        },
        LV_EVENT_CLICKED,
        nullptr);
}

void LcdDisplay::SetupFocusScreen() {
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
    UiSystem::GetInstance().SetState(UiSystemState::AppGrid);
    UiSystem::GetInstance().SetHomeStatus("Focus page");
#endif
    SetupPlaceholderScreen("Focus", "Local focus mode with countdown and finish reminder");

    if (content_ == nullptr) {
        return;
    }

    DisplayLockGuard lock(this);
    auto lvgl_theme = static_cast<LvglTheme*>(current_theme_);
    auto& manager = TimeToolsManager::GetInstance();

    lv_obj_t* time_label = lv_label_create(content_);
    auto time_text = FormatMinutesSeconds(manager.GetFocusRemainingSeconds());
    lv_label_set_text(time_label, time_text.c_str());
    lv_obj_align(time_label, LV_ALIGN_CENTER, 0, 16);

    lv_obj_t* start_btn = lv_btn_create(content_);
    lv_obj_set_size(start_btn, 92, 34);
    lv_obj_align(start_btn, LV_ALIGN_CENTER, -52, 60);
    lv_obj_t* start_label = lv_label_create(start_btn);
    lv_label_set_text(start_label, manager.IsFocusRunning() ? "Pause" : "Focus");
    lv_obj_center(start_label);
    lv_obj_add_event_cb(
        start_btn,
        [](lv_event_t*) {
            TimeToolsManager::GetInstance().ToggleFocus();
        },
        LV_EVENT_CLICKED,
        nullptr);

    lv_obj_t* stop_btn = lv_btn_create(content_);
    lv_obj_set_size(stop_btn, 92, 34);
    lv_obj_align(stop_btn, LV_ALIGN_CENTER, 52, 60);
    lv_obj_t* stop_label = lv_label_create(stop_btn);
    lv_label_set_text(stop_label, "Reset");
    lv_obj_center(stop_label);
    lv_obj_add_event_cb(
        stop_btn,
        [](lv_event_t*) {
            TimeToolsManager::GetInstance().StopFocus();
        },
        LV_EVENT_CLICKED,
        nullptr);

    lv_obj_t* preset_row = lv_obj_create(content_);
    lv_obj_set_size(preset_row, LV_PCT(88), 38);
    lv_obj_align(preset_row, LV_ALIGN_BOTTOM_MID, 0, -8);
    lv_obj_set_style_bg_opa(preset_row, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(preset_row, 0, 0);
    lv_obj_set_style_pad_all(preset_row, 0, 0);
    lv_obj_set_layout(preset_row, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(preset_row, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(preset_row, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    const int presets[] = {15, 25, 45};
    for (int preset : presets) {
        lv_obj_t* preset_btn = lv_btn_create(preset_row);
        lv_obj_set_size(preset_btn, 56, 28);
        lv_obj_set_style_radius(preset_btn, lvgl_theme->spacing(2), 0);
        lv_obj_t* preset_label = lv_label_create(preset_btn);
        char text[8];
        snprintf(text, sizeof(text), "%dm", preset);
        lv_label_set_text(preset_label, text);
        lv_obj_center(preset_label);
        lv_obj_add_event_cb(
            preset_btn,
            [](lv_event_t* e) {
                int minutes = static_cast<int>(reinterpret_cast<intptr_t>(lv_event_get_user_data(e)));
                TimeToolsManager::GetInstance().SetFocusPresetMinutes(minutes);
            },
            LV_EVENT_CLICKED,
            reinterpret_cast<void*>(static_cast<intptr_t>(preset)));
    }
}
