#ifndef ALARM_MANAGER_H_
#define ALARM_MANAGER_H_

#include <esp_timer.h>

#include <functional>
#include <string>
#include <vector>

struct AlarmItem {
    int id = 0;
    int hour = 7;
    int minute = 0;
    bool enabled = true;
    bool repeat_daily = true;
    std::string label = "Alarm";
};

class AlarmManager {
public:
    static AlarmManager& GetInstance();

    void Initialize();
    const std::vector<AlarmItem>& GetAlarms() const;
    AlarmItem GetAlarm(int id) const;
    int AddAlarm(const AlarmItem& alarm);
    bool UpdateAlarm(const AlarmItem& alarm);
    bool DeleteAlarm(int id);
    bool ToggleAlarm(int id, bool enabled);
    bool SetRepeatDaily(int id, bool repeat_daily);
    bool SnoozeActiveAlarm(int minutes);
    bool StopActiveAlarm();
    bool IsRinging() const;
    int GetActiveAlarmId() const;
    void SetRingingCallback(std::function<void(const AlarmItem&)>&& callback);

private:
    AlarmManager() = default;
    void Load();
    void Save();
    void CheckDue();
    static void TickCallback(void* arg);
    int NextAlarmId();
    void SetSnoozeMinutes(int minutes);

    std::vector<AlarmItem> alarms_;
    int next_id_ = 1;
    int active_alarm_id_ = -1;
    int snooze_alarm_id_ = -1;
    int64_t snooze_until_epoch_ = -1;
    int last_triggered_alarm_id_ = -1;
    int last_triggered_yday_ = -1;
    esp_timer_handle_t timer_ = nullptr;
    std::function<void(const AlarmItem&)> ringing_callback_;
};

#endif // ALARM_MANAGER_H_
