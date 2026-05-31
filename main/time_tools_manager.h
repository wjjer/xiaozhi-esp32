#ifndef TIME_TOOLS_MANAGER_H_
#define TIME_TOOLS_MANAGER_H_

#include <esp_timer.h>

#include <functional>
#include <mutex>

class TimeToolsManager {
public:
    static TimeToolsManager& GetInstance();

    void Initialize();
    void SetStateChangedCallback(std::function<void()>&& callback);
    void SetEventCallback(std::function<void(const char*)>&& callback);

    void SetTimerPresetMinutes(int minutes);
    void ToggleTimer();
    void ResetTimer();
    int GetTimerRemainingSeconds() const;
    bool IsTimerRunning() const;
    int GetTimerPresetMinutes() const;

    void ToggleStopwatch();
    void ResetStopwatch();
    int GetStopwatchElapsedSeconds() const;
    bool IsStopwatchRunning() const;

    void SetFocusPresetMinutes(int minutes);
    void ToggleFocus();
    void StopFocus();
    int GetFocusRemainingSeconds() const;
    bool IsFocusRunning() const;
    int GetFocusPresetMinutes() const;

private:
    TimeToolsManager() = default;
    static void TickCallback(void* arg);
    void OnTick();
    void NotifyStateChanged();

    mutable std::mutex mutex_;
    esp_timer_handle_t timer_handle_ = nullptr;
    std::function<void()> state_changed_callback_;
    std::function<void(const char*)> event_callback_;

    int timer_preset_minutes_ = 25;
    int timer_remaining_seconds_ = 25 * 60;
    bool timer_running_ = false;
    int64_t timer_target_epoch_ = 0;

    int stopwatch_elapsed_seconds_ = 0;
    bool stopwatch_running_ = false;
    int64_t stopwatch_started_epoch_ = 0;

    int focus_preset_minutes_ = 25;
    int focus_remaining_seconds_ = 25 * 60;
    bool focus_running_ = false;
    int64_t focus_target_epoch_ = 0;
};

#endif // TIME_TOOLS_MANAGER_H_
