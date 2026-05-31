#include "time_tools_manager.h"

#include <ctime>

namespace {
int64_t NowEpochSeconds() {
    return static_cast<int64_t>(time(nullptr));
}
}

TimeToolsManager& TimeToolsManager::GetInstance() {
    static TimeToolsManager instance;
    return instance;
}

void TimeToolsManager::Initialize() {
    if (timer_handle_ != nullptr) {
        return;
    }

    esp_timer_create_args_t args = {
        .callback = &TimeToolsManager::TickCallback,
        .arg = this,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "time_tools_tick",
        .skip_unhandled_events = true,
    };
    ESP_ERROR_CHECK(esp_timer_create(&args, &timer_handle_));
    ESP_ERROR_CHECK(esp_timer_start_periodic(timer_handle_, 1000 * 1000));
}

void TimeToolsManager::SetStateChangedCallback(std::function<void()>&& callback) {
    state_changed_callback_ = std::move(callback);
}

void TimeToolsManager::SetEventCallback(std::function<void(const char*)>&& callback) {
    event_callback_ = std::move(callback);
}

void TimeToolsManager::SetTimerPresetMinutes(int minutes) {
    std::lock_guard<std::mutex> lock(mutex_);
    timer_preset_minutes_ = minutes;
    timer_remaining_seconds_ = minutes * 60;
    timer_running_ = false;
    timer_target_epoch_ = 0;
    NotifyStateChanged();
}

void TimeToolsManager::ToggleTimer() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (timer_running_) {
        int64_t remaining = timer_target_epoch_ - NowEpochSeconds();
        timer_remaining_seconds_ = remaining > 0 ? static_cast<int>(remaining) : 0;
        timer_running_ = false;
        timer_target_epoch_ = 0;
    } else {
        if (timer_remaining_seconds_ <= 0) {
            timer_remaining_seconds_ = timer_preset_minutes_ * 60;
        }
        timer_running_ = true;
        timer_target_epoch_ = NowEpochSeconds() + timer_remaining_seconds_;
    }
    NotifyStateChanged();
}

void TimeToolsManager::ResetTimer() {
    std::lock_guard<std::mutex> lock(mutex_);
    timer_running_ = false;
    timer_target_epoch_ = 0;
    timer_remaining_seconds_ = timer_preset_minutes_ * 60;
    NotifyStateChanged();
}

int TimeToolsManager::GetTimerRemainingSeconds() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return timer_remaining_seconds_;
}

bool TimeToolsManager::IsTimerRunning() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return timer_running_;
}

int TimeToolsManager::GetTimerPresetMinutes() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return timer_preset_minutes_;
}

void TimeToolsManager::ToggleStopwatch() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (stopwatch_running_) {
        stopwatch_elapsed_seconds_ += static_cast<int>(NowEpochSeconds() - stopwatch_started_epoch_);
        stopwatch_running_ = false;
        stopwatch_started_epoch_ = 0;
    } else {
        stopwatch_running_ = true;
        stopwatch_started_epoch_ = NowEpochSeconds();
    }
    NotifyStateChanged();
}

void TimeToolsManager::ResetStopwatch() {
    std::lock_guard<std::mutex> lock(mutex_);
    stopwatch_elapsed_seconds_ = 0;
    stopwatch_running_ = false;
    stopwatch_started_epoch_ = 0;
    NotifyStateChanged();
}

int TimeToolsManager::GetStopwatchElapsedSeconds() const {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!stopwatch_running_) {
        return stopwatch_elapsed_seconds_;
    }
    return stopwatch_elapsed_seconds_ + static_cast<int>(NowEpochSeconds() - stopwatch_started_epoch_);
}

bool TimeToolsManager::IsStopwatchRunning() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return stopwatch_running_;
}

void TimeToolsManager::SetFocusPresetMinutes(int minutes) {
    std::lock_guard<std::mutex> lock(mutex_);
    focus_preset_minutes_ = minutes;
    focus_remaining_seconds_ = minutes * 60;
    focus_running_ = false;
    focus_target_epoch_ = 0;
    NotifyStateChanged();
}

void TimeToolsManager::ToggleFocus() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (focus_running_) {
        int64_t remaining = focus_target_epoch_ - NowEpochSeconds();
        focus_remaining_seconds_ = remaining > 0 ? static_cast<int>(remaining) : 0;
        focus_running_ = false;
        focus_target_epoch_ = 0;
    } else {
        if (focus_remaining_seconds_ <= 0) {
            focus_remaining_seconds_ = focus_preset_minutes_ * 60;
        }
        focus_running_ = true;
        focus_target_epoch_ = NowEpochSeconds() + focus_remaining_seconds_;
    }
    NotifyStateChanged();
}

void TimeToolsManager::StopFocus() {
    std::lock_guard<std::mutex> lock(mutex_);
    focus_running_ = false;
    focus_target_epoch_ = 0;
    focus_remaining_seconds_ = focus_preset_minutes_ * 60;
    NotifyStateChanged();
}

int TimeToolsManager::GetFocusRemainingSeconds() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return focus_remaining_seconds_;
}

bool TimeToolsManager::IsFocusRunning() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return focus_running_;
}

int TimeToolsManager::GetFocusPresetMinutes() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return focus_preset_minutes_;
}

void TimeToolsManager::TickCallback(void* arg) {
    auto* self = static_cast<TimeToolsManager*>(arg);
    if (self != nullptr) {
        self->OnTick();
    }
}

void TimeToolsManager::OnTick() {
    std::lock_guard<std::mutex> lock(mutex_);
    int64_t now = NowEpochSeconds();
    bool changed = false;

    if (timer_running_) {
        int remaining = static_cast<int>(timer_target_epoch_ - now);
        if (remaining <= 0) {
            timer_running_ = false;
            timer_target_epoch_ = 0;
            timer_remaining_seconds_ = 0;
            if (event_callback_) {
                event_callback_("Timer finished");
            }
            changed = true;
        } else if (remaining != timer_remaining_seconds_) {
            timer_remaining_seconds_ = remaining;
            changed = true;
        }
    }

    if (focus_running_) {
        int remaining = static_cast<int>(focus_target_epoch_ - now);
        if (remaining <= 0) {
            focus_running_ = false;
            focus_target_epoch_ = 0;
            focus_remaining_seconds_ = 0;
            if (event_callback_) {
                event_callback_("Focus finished");
            }
            changed = true;
        } else if (remaining != focus_remaining_seconds_) {
            focus_remaining_seconds_ = remaining;
            changed = true;
        }
    }

    if (stopwatch_running_) {
        changed = true;
    }

    if (changed) {
        NotifyStateChanged();
    }
}

void TimeToolsManager::NotifyStateChanged() {
    if (state_changed_callback_) {
        state_changed_callback_();
    }
}
