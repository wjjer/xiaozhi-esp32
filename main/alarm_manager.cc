#include "alarm_manager.h"

#include "settings.h"
#include "ui/ui_system.h"

#include <algorithm>
#include <ctime>
#include <esp_log.h>
#include <cJSON.h>

#define TAG "AlarmManager"

namespace {
constexpr const char* kNamespace = "alarm";
constexpr const char* kKeyData = "data";
} // namespace

AlarmManager& AlarmManager::GetInstance() {
    static AlarmManager instance;
    return instance;
}

void AlarmManager::Initialize() {
    Load();

    if (timer_ == nullptr) {
        esp_timer_create_args_t args = {
            .callback = &AlarmManager::TickCallback,
            .arg = this,
            .dispatch_method = ESP_TIMER_TASK,
            .name = "alarm_tick",
            .skip_unhandled_events = true,
        };
        ESP_ERROR_CHECK(esp_timer_create(&args, &timer_));
        ESP_ERROR_CHECK(esp_timer_start_periodic(timer_, 1000 * 1000));
    }
}

const std::vector<AlarmItem>& AlarmManager::GetAlarms() const {
    return alarms_;
}

AlarmItem AlarmManager::GetAlarm(int id) const {
    for (const auto& alarm : alarms_) {
        if (alarm.id == id) {
            return alarm;
        }
    }
    return {};
}

int AlarmManager::NextAlarmId() {
    return next_id_++;
}

int AlarmManager::AddAlarm(const AlarmItem& alarm) {
    AlarmItem item = alarm;
    item.id = NextAlarmId();
    alarms_.push_back(item);
    Save();
    return item.id;
}

bool AlarmManager::UpdateAlarm(const AlarmItem& alarm) {
    for (auto& item : alarms_) {
        if (item.id == alarm.id) {
            item = alarm;
            Save();
            return true;
        }
    }
    return false;
}

bool AlarmManager::DeleteAlarm(int id) {
    auto old_size = alarms_.size();
    alarms_.erase(std::remove_if(alarms_.begin(), alarms_.end(),
        [id](const AlarmItem& item) { return item.id == id; }), alarms_.end());
    if (alarms_.size() != old_size) {
        Save();
        return true;
    }
    return false;
}

bool AlarmManager::ToggleAlarm(int id, bool enabled) {
    for (auto& item : alarms_) {
        if (item.id == id) {
            item.enabled = enabled;
            Save();
            return true;
        }
    }
    return false;
}

bool AlarmManager::SetRepeatDaily(int id, bool repeat_daily) {
    for (auto& item : alarms_) {
        if (item.id == id) {
            item.repeat_daily = repeat_daily;
            Save();
            return true;
        }
    }
    return false;
}

bool AlarmManager::SnoozeActiveAlarm(int minutes) {
    if (active_alarm_id_ < 0) {
        return false;
    }
    snooze_alarm_id_ = active_alarm_id_;
    SetSnoozeMinutes(minutes);
    active_alarm_id_ = -1;
    UiSystem::GetInstance().SetState(UiSystemState::Home);
    return true;
}

bool AlarmManager::StopActiveAlarm() {
    if (active_alarm_id_ < 0) {
        return false;
    }
    active_alarm_id_ = -1;
    snooze_alarm_id_ = -1;
    snooze_until_epoch_ = -1;
    UiSystem::GetInstance().SetState(UiSystemState::Home);
    return true;
}

bool AlarmManager::IsRinging() const {
    return active_alarm_id_ >= 0;
}

int AlarmManager::GetActiveAlarmId() const {
    return active_alarm_id_;
}

void AlarmManager::SetRingingCallback(std::function<void(const AlarmItem&)>&& callback) {
    ringing_callback_ = std::move(callback);
}

void AlarmManager::Load() {
    Settings settings(kNamespace, false);
    std::string data = settings.GetString(kKeyData);
    if (data.empty()) {
        alarms_.clear();
        next_id_ = 1;
        return;
    }

    auto root = cJSON_Parse(data.c_str());
    if (root == nullptr) {
        alarms_.clear();
        next_id_ = 1;
        return;
    }

    alarms_.clear();
    auto items = cJSON_GetObjectItem(root, "alarms");
    if (cJSON_IsArray(items)) {
        cJSON* item = nullptr;
        cJSON_ArrayForEach(item, items) {
            if (!cJSON_IsObject(item)) {
                continue;
            }
            AlarmItem alarm;
            alarm.id = cJSON_GetObjectItem(item, "id")->valueint;
            alarm.hour = cJSON_GetObjectItem(item, "hour")->valueint;
            alarm.minute = cJSON_GetObjectItem(item, "minute")->valueint;
            auto enabled = cJSON_GetObjectItem(item, "enabled");
            auto repeat_daily = cJSON_GetObjectItem(item, "repeat_daily");
            auto label = cJSON_GetObjectItem(item, "label");
            alarm.enabled = !cJSON_IsFalse(enabled);
            alarm.repeat_daily = !cJSON_IsFalse(repeat_daily);
            if (cJSON_IsString(label) && label->valuestring != nullptr) {
                alarm.label = label->valuestring;
            }
            alarms_.push_back(alarm);
            next_id_ = std::max(next_id_, alarm.id + 1);
        }
    }

    cJSON_Delete(root);
}

void AlarmManager::Save() {
    auto root = cJSON_CreateObject();
    auto arr = cJSON_CreateArray();
    for (const auto& alarm : alarms_) {
        auto item = cJSON_CreateObject();
        cJSON_AddNumberToObject(item, "id", alarm.id);
        cJSON_AddNumberToObject(item, "hour", alarm.hour);
        cJSON_AddNumberToObject(item, "minute", alarm.minute);
        cJSON_AddBoolToObject(item, "enabled", alarm.enabled);
        cJSON_AddBoolToObject(item, "repeat_daily", alarm.repeat_daily);
        cJSON_AddStringToObject(item, "label", alarm.label.c_str());
        cJSON_AddItemToArray(arr, item);
    }
    cJSON_AddItemToObject(root, "alarms", arr);

    char* json = cJSON_PrintUnformatted(root);
    if (json != nullptr) {
        Settings settings(kNamespace, true);
        settings.SetString(kKeyData, json);
        cJSON_free(json);
    }
    cJSON_Delete(root);
}

void AlarmManager::TickCallback(void* arg) {
    auto* self = static_cast<AlarmManager*>(arg);
    if (self != nullptr) {
        self->CheckDue();
    }
}

void AlarmManager::CheckDue() {
    if (active_alarm_id_ >= 0) {
        return;
    }

    time_t now = time(nullptr);
    if (now <= 0) {
        return;
    }
    struct tm now_tm {};
    localtime_r(&now, &now_tm);

    if (snooze_alarm_id_ >= 0 && snooze_until_epoch_ > 0 && now >= snooze_until_epoch_) {
        auto alarm = GetAlarm(snooze_alarm_id_);
        active_alarm_id_ = snooze_alarm_id_;
        snooze_alarm_id_ = -1;
        snooze_until_epoch_ = -1;
        last_triggered_alarm_id_ = alarm.id;
        last_triggered_yday_ = now_tm.tm_yday;
        UiSystem::GetInstance().SetState(UiSystemState::AlarmRinging);
        if (ringing_callback_) {
            ringing_callback_(alarm);
        }
        return;
    }

    for (auto& alarm : alarms_) {
        if (!alarm.enabled) {
            continue;
        }
        if (alarm.hour == now_tm.tm_hour && alarm.minute == now_tm.tm_min) {
            if (last_triggered_alarm_id_ == alarm.id && last_triggered_yday_ == now_tm.tm_yday) {
                continue;
            }
            active_alarm_id_ = alarm.id;
            last_triggered_alarm_id_ = alarm.id;
            last_triggered_yday_ = now_tm.tm_yday;
            UiSystem::GetInstance().SetState(UiSystemState::AlarmRinging);
            if (ringing_callback_) {
                ringing_callback_(alarm);
            }
            ESP_LOGI(TAG, "Alarm ringing: %02d:%02d %s", alarm.hour, alarm.minute, alarm.label.c_str());
            if (!alarm.repeat_daily) {
                alarm.enabled = false;
                Save();
            }
            break;
        }
    }
}

void AlarmManager::SetSnoozeMinutes(int minutes) {
    time_t now = time(nullptr);
    if (now <= 0 || minutes <= 0) {
        snooze_alarm_id_ = -1;
        snooze_until_epoch_ = -1;
        return;
    }
    snooze_until_epoch_ = static_cast<int64_t>(now) + static_cast<int64_t>(minutes) * 60;
}
