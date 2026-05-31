#ifndef UI_SYSTEM_H_
#define UI_SYSTEM_H_

#include <string>

enum class UiSystemState {
    Boot,
    Standby,
    Home,
    AppGrid,
    VoiceListening,
    VoiceThinking,
    VoiceSpeaking,
    AlarmRinging,
};

class UiSystem {
public:
    static UiSystem& GetInstance();

    void Initialize();
    void SetState(UiSystemState state);
    UiSystemState GetState() const;
    void SetHomeStatus(const std::string& status);
    const std::string& GetHomeStatus() const;

private:
    UiSystem() = default;
    UiSystemState state_ = UiSystemState::Boot;
    std::string home_status_ = "ready";
};

#endif // UI_SYSTEM_H_
