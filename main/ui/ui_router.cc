#include "ui_router.h"
#include <esp_log.h>

static const char* TAG = "UiRouter";

UiRouter& UiRouter::GetInstance() {
    static UiRouter instance;
    return instance;
}

void UiRouter::NavigateToInternal(const std::string& route, bool record_history) {
    if (current_route_ == route) {
        return;  // No change
    }

    std::string from_route = current_route_;
    if (record_history && from_route != "boot") {
        history_.push_back(from_route);
    }
    current_route_ = route;

    ESP_LOGI(TAG, "Navigation: %s -> %s", from_route.c_str(), route.c_str());

    // Notify callback if registered
    if (navigate_callback_) {
        navigate_callback_(from_route, route);
    }
}

void UiRouter::NavigateTo(const std::string& route) {
    NavigateToInternal(route, true);
}

bool UiRouter::GoBack() {
    if (history_.empty()) {
        return false;
    }

    std::string target = history_.back();
    history_.pop_back();
    NavigateToInternal(target, false);
    return true;
}

const std::string& UiRouter::CurrentRoute() const {
    return current_route_;
}

bool UiRouter::IsHomeRoute() const {
    return current_route_ == RouteHome;
}

bool UiRouter::IsAppGridRoute() const {
    return current_route_ == RouteAppGrid;
}

UiRouter::RoutePage UiRouter::ResolveRoutePage(const std::string& route) {
    if (route == RouteHome) return RoutePage::Home;
    if (route == RouteAppGrid || route == RouteTools) return RoutePage::AppGrid;
    if (route == RouteAI || route == RouteMicroChat) return RoutePage::AI;
    if (route == RouteStudy || route == RouteStory || route == RouteStudyHub ||
        route == RouteAllSubjectStudy || route == RouteSyncTextbook ||
        route == RouteBaiduNetdisk || route == RouteLocalContent) {
        return RoutePage::Study;
    }
    if (route == RouteAlarm || route == RouteAlarmEditor) return RoutePage::Alarm;
    if (route == RouteWeather) return RoutePage::Weather;
    if (route == RouteTimer) return RoutePage::Timer;
    if (route == RouteStopwatch) return RoutePage::Stopwatch;
    if (route == RouteFocus) return RoutePage::Focus;
    if (route == RouteNightLight) return RoutePage::NightLight;
    if (route == RouteTranslate || route == RouteEnglishQuery || route == RouteVoiceTranslate) {
        return RoutePage::Translate;
    }
    if (route == RouteWordbook || route == RouteWordStudy || route == RouteDictionary) {
        return RoutePage::Wordbook;
    }
    if (route == RouteVocab) return RoutePage::Vocab;
    if (route == RouteK12) return RoutePage::K12;
    if (route == RouteSettings || route == RouteMusic || route == RoutePlaceholder) {
        return RoutePage::Placeholder;
    }
    return RoutePage::Placeholder;
}

void UiRouter::SetNavigateCallback(NavigateCallback callback) {
    navigate_callback_ = std::move(callback);
}
