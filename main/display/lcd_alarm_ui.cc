#include "lcd_display.h"

#include "alarm_manager.h"
#include "board.h"
#include "lvgl_theme.h"
#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
#include "ui_bridge.h"
#include "gui_guider.h"
#include "ui_router.h"
#include "ui_system.h"
#endif

#include <cstdio>
#include <functional>
#include <string>

#if defined(ESP32_ALARM_USE_NEW_UI) && ESP32_ALARM_USE_NEW_UI
namespace {
constexpr int kAlarmLabelCount = 5;
constexpr const char* kAlarmLabels[kAlarmLabelCount] = {
    "Wake Up",
    "Study",
    "Nap",
    "Workout",
    "Reminder",
};

void StyleCard(lv_obj_t* obj, uint32_t bg, int radius = 14) {
    lv_obj_set_style_radius(obj, radius, 0);
    lv_obj_set_style_bg_color(obj, lv_color_hex(bg), 0);
    lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(obj, 0, 0);
    lv_obj_set_style_shadow_width(obj, 0, 0);
}

lv_obj_t* MakeLabel(lv_obj_t* parent, const char* text, uint32_t color, const lv_font_t* font = nullptr) {
    lv_obj_t* label = lv_label_create(parent);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_color(label, lv_color_hex(color), 0);
    if (font != nullptr) {
        lv_obj_set_style_text_font(label, font, 0);
    }
    return label;
}

lv_obj_t* MakeButton(lv_obj_t* parent, const char* text, int w, int h, uint32_t bg, uint32_t fg = 0xFFFFFF) {
    lv_obj_t* btn = lv_btn_create(parent);
    lv_obj_set_size(btn, w, h);
    StyleCard(btn, bg, h / 2);
    lv_obj_t* label = MakeLabel(btn, text, fg);
    lv_obj_center(label);
    return btn;
}

void AddBackToGrid(lv_obj_t* root) {
    lv_obj_t* back = MakeButton(root, "< Back", 62, 26, 0xE8ECFF, 0x1F2450);
    lv_obj_align(back, LV_ALIGN_TOP_LEFT, 8, 8);
    lv_obj_add_event_cb(back, [](lv_event_t*) {
        auto* display = dynamic_cast<LcdDisplay*>(Board::GetInstance().GetDisplay());
        if (display != nullptr) {
            UiRouter::GetInstance().NavigateTo("app_grid");
            display->SetupAppGridScreen();
        }
    }, LV_EVENT_CLICKED, nullptr);
}
}  // namespace

void LcdDisplay::SetupAlarmScreen() {
    if (!setup_ui_called_) {
        return;
    }

    UiSystem::GetInstance().SetState(UiSystemState::AppGrid);
    UiSystem::GetInstance().SetHomeStatus("Alarm page");
    DisplayLockGuard lock(this);
    if (esp32_alarm_ui.screen_alarm == nullptr) {
        return;
    }
    lv_scr_load(esp32_alarm_ui.screen_alarm);
    content_ = esp32_alarm_ui.screen_alarm;
}

void LcdDisplay::SetupAlarmEditorScreen(int alarm_id, bool is_new) {
    if (!setup_ui_called_) {
        return;
    }

    UiSystem::GetInstance().SetState(UiSystemState::AppGrid);
    UiSystem::GetInstance().SetHomeStatus(is_new ? "New alarm" : "Edit alarm");

    AlarmItem alarm;
    if (!is_new) {
        alarm = AlarmManager::GetInstance().GetAlarm(alarm_id);
    }

    bool same_target = (alarm_editor_is_new_ == is_new) &&
        ((is_new && alarm_editor_id_ == -1) || (!is_new && alarm_editor_id_ == alarm_id));
    if (!same_target) {
        alarm_editor_id_ = is_new ? -1 : alarm.id;
        alarm_editor_is_new_ = is_new;
        alarm_editor_enabled_ = is_new ? true : alarm.enabled;
        alarm_editor_repeat_daily_ = is_new ? true : alarm.repeat_daily;
        alarm_editor_hour_ = is_new ? 7 : alarm.hour;
        alarm_editor_minute_ = is_new ? 0 : alarm.minute;
        alarm_editor_label_index_ = 0;
        for (int i = 0; i < kAlarmLabelCount; ++i) {
            if (!is_new && alarm.label == kAlarmLabels[i]) {
                alarm_editor_label_index_ = i;
                break;
            }
        }
    }

    DisplayLockGuard lock(this);
    auto* theme = static_cast<LvglTheme*>(current_theme_);
    auto* root = PrepareAlarmUiContent(0xFFF7EC);
    if (root == nullptr) {
        return;
    }

    AddBackToGrid(root);
    lv_obj_t* title = MakeLabel(root, is_new ? "New Alarm" : "Edit Alarm", 0x1F2450, theme->text_font()->font());
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 12);

    lv_obj_t* panel = lv_obj_create(root);
    lv_obj_set_size(panel, 292, 156);
    lv_obj_align(panel, LV_ALIGN_BOTTOM_MID, 0, -10);
    StyleCard(panel, 0xFFFFFF, 18);
    lv_obj_set_style_pad_all(panel, 10, 0);

    auto add_row = [&](const char* name, const char* value, int x, int y, std::function<void()> cb) {
        lv_obj_t* row = lv_btn_create(panel);
        lv_obj_set_size(row, 130, 34);
        lv_obj_align(row, LV_ALIGN_TOP_LEFT, x, y);
        StyleCard(row, 0xF6F8FF, 12);
        std::string text = std::string(name) + ": " + value;
        lv_obj_t* label = MakeLabel(row, text.c_str(), 0x1F2450);
        lv_obj_center(label);
        auto* fn = new std::function<void()>(cb);
        lv_obj_add_event_cb(row, [](lv_event_t* e) {
            auto* cb = static_cast<std::function<void()>*>(lv_event_get_user_data(e));
            if (cb != nullptr) {
                (*cb)();
            }
        }, LV_EVENT_CLICKED, fn);
    };

    char time_text[16];
    snprintf(time_text, sizeof(time_text), "%02d:%02d", alarm_editor_hour_, alarm_editor_minute_);
    add_row("Time", time_text, 0, 0, [this]() {
        alarm_editor_minute_ += 5;
        if (alarm_editor_minute_ >= 60) {
            alarm_editor_minute_ = 0;
            alarm_editor_hour_ = (alarm_editor_hour_ + 1) % 24;
        }
        SetupAlarmEditorScreen(alarm_editor_id_, alarm_editor_is_new_);
    });
    add_row("Label", kAlarmLabels[alarm_editor_label_index_], 142, 0, [this]() {
        alarm_editor_label_index_ = (alarm_editor_label_index_ + 1) % kAlarmLabelCount;
        SetupAlarmEditorScreen(alarm_editor_id_, alarm_editor_is_new_);
    });
    add_row("Enabled", alarm_editor_enabled_ ? "Yes" : "No", 0, 44, [this]() {
        alarm_editor_enabled_ = !alarm_editor_enabled_;
        SetupAlarmEditorScreen(alarm_editor_id_, alarm_editor_is_new_);
    });
    add_row("Repeat", alarm_editor_repeat_daily_ ? "Daily" : "Once", 142, 44, [this]() {
        alarm_editor_repeat_daily_ = !alarm_editor_repeat_daily_;
        SetupAlarmEditorScreen(alarm_editor_id_, alarm_editor_is_new_);
    });

    lv_obj_t* save = MakeButton(panel, "Save", 82, 34, 0x4A90E2);
    lv_obj_align(save, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_add_event_cb(save, [](lv_event_t*) {
        auto* display = dynamic_cast<LcdDisplay*>(Board::GetInstance().GetDisplay());
        if (display != nullptr) {
            display->SaveAlarmEditor();
        }
    }, LV_EVENT_CLICKED, nullptr);

    lv_obj_t* del = MakeButton(panel, is_new ? "Cancel" : "Delete", 82, 34, is_new ? 0xE5E7EB : 0xFEE2E2, is_new ? 0x374151 : 0xDC2626);
    lv_obj_align(del, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_add_event_cb(del, [](lv_event_t*) {
        auto* display = dynamic_cast<LcdDisplay*>(Board::GetInstance().GetDisplay());
        if (display != nullptr) {
            display->DeleteAlarmEditor();
        }
    }, LV_EVENT_CLICKED, nullptr);

    lv_obj_t* back = MakeButton(panel, "Back", 82, 34, 0xE8ECFF, 0x4A90E2);
    lv_obj_align(back, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_add_event_cb(back, [](lv_event_t*) {
        auto* display = dynamic_cast<LcdDisplay*>(Board::GetInstance().GetDisplay());
        if (display != nullptr) {
            display->SetupAlarmScreen();
        }
    }, LV_EVENT_CLICKED, nullptr);
}

void LcdDisplay::SaveAlarmEditor() {
    AlarmItem item;
    item.id = alarm_editor_id_;
    item.hour = alarm_editor_hour_;
    item.minute = alarm_editor_minute_;
    item.enabled = alarm_editor_enabled_;
    item.repeat_daily = alarm_editor_repeat_daily_;
    item.label = kAlarmLabels[alarm_editor_label_index_];

    if (alarm_editor_is_new_) {
        AlarmManager::GetInstance().AddAlarm(item);
    } else {
        AlarmManager::GetInstance().UpdateAlarm(item);
    }

    UiRouter::GetInstance().NavigateTo("alarm");
    SetupAlarmScreen();
}

void LcdDisplay::DeleteAlarmEditor() {
    if (!alarm_editor_is_new_ && alarm_editor_id_ >= 0) {
        AlarmManager::GetInstance().DeleteAlarm(alarm_editor_id_);
    }
    UiRouter::GetInstance().NavigateTo("alarm");
    SetupAlarmScreen();
}
#endif  // ESP32_ALARM_USE_NEW_UI
