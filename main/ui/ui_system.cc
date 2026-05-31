#include "ui_system.h"

UiSystem& UiSystem::GetInstance() {
    static UiSystem instance;
    return instance;
}

void UiSystem::Initialize() {
    state_ = UiSystemState::Boot;
}

void UiSystem::SetState(UiSystemState state) {
    state_ = state;
}

UiSystemState UiSystem::GetState() const {
    return state_;
}

void UiSystem::SetHomeStatus(const std::string& status) {
    home_status_ = status;
}

const std::string& UiSystem::GetHomeStatus() const {
    return home_status_;
}
