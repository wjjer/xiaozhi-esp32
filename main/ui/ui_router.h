#ifndef UI_ROUTER_H_
#define UI_ROUTER_H_

#include <string>
#include <functional>
#include <vector>

/**
 * @brief UI Router
 * 
 * Manages page navigation and route state.
 * Provides callbacks for display layer to receive navigation events.
 */
class UiRouter {
public:
    enum class RoutePage {
        Home,
        AppGrid,
        AI,
        Study,
        Alarm,
        Weather,
        Timer,
        Stopwatch,
        Focus,
        NightLight,
        Translate,
        Wordbook,
        Vocab,
        K12,
        Placeholder,
    };

    static UiRouter& GetInstance();

    // Navigation
    void NavigateTo(const std::string& route);
    bool GoBack();
    const std::string& CurrentRoute() const;

    // Route checking helpers
    bool IsHomeRoute() const;
    bool IsAppGridRoute() const;
    static RoutePage ResolveRoutePage(const std::string& route);

    // Navigation callback for display layer
    using NavigateCallback = std::function<void(const std::string& from_route, const std::string& to_route)>;
    void SetNavigateCallback(NavigateCallback callback);

    // Get all registered routes
    static constexpr const char* RouteHome = "home";
    static constexpr const char* RouteAppGrid = "app_grid";
    static constexpr const char* RouteTools = "tools";
    static constexpr const char* RouteAlarm = "alarm";
    static constexpr const char* RouteAlarmEditor = "alarm_editor";
    static constexpr const char* RouteStudy = "study";
    static constexpr const char* RouteStory = "story";
    static constexpr const char* RouteAI = "ai";
    static constexpr const char* RouteMicroChat = "micro_chat";
    static constexpr const char* RouteWeather = "weather";
    static constexpr const char* RouteTimer = "timer";
    static constexpr const char* RouteStopwatch = "stopwatch";
    static constexpr const char* RouteFocus = "focus";
    static constexpr const char* RouteNightLight = "night_light";
    static constexpr const char* RouteTranslate = "translate";
    static constexpr const char* RouteEnglishQuery = "english_query";
    static constexpr const char* RouteWordbook = "wordbook";
    static constexpr const char* RouteWordStudy = "word_study";
    static constexpr const char* RouteVocab = "vocab";
    static constexpr const char* RouteK12 = "k12";
    static constexpr const char* RouteStudyHub = "study_hub";
    static constexpr const char* RouteAllSubjectStudy = "all_subject_study";
    static constexpr const char* RouteSyncTextbook = "sync_textbook";
    static constexpr const char* RouteBaiduNetdisk = "baidu_netdisk";
    static constexpr const char* RouteDictionary = "dictionary";
    static constexpr const char* RouteSettings = "settings";
    static constexpr const char* RouteMusic = "music";
    static constexpr const char* RouteLocalContent = "local_content";
    static constexpr const char* RouteVoiceTranslate = "voice_translate";
    static constexpr const char* RoutePlaceholder = "placeholder";

private:
    UiRouter() = default;
    void NavigateToInternal(const std::string& route, bool record_history);
    std::string current_route_ = "boot";
    std::vector<std::string> history_;
    NavigateCallback navigate_callback_;
};

#endif // UI_ROUTER_H_
