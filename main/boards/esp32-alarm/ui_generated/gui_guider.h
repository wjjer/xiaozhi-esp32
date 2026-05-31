/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"


typedef struct
{
  
	lv_obj_t *screen_boot;
	bool screen_boot_del;
	lv_obj_t *screen_boot_boot_hint_label;
	lv_obj_t *screen_boot_boot_spinner_image;
	lv_obj_t *screen_boot_boot_logo_image;
	lv_obj_t *screen_home;
	bool screen_home_del;
	lv_obj_t *screen_home_home_cards_container;
	lv_obj_t *screen_home_card_tools;
	lv_obj_t *screen_home_card_tools_label;
	lv_obj_t *screen_home_card_tools_img;
	lv_obj_t *screen_home_card_focus;
	lv_obj_t *screen_home_card_focus_label;
	lv_obj_t *screen_home_card_focus_img;
	lv_obj_t *screen_home_card_stopwatch;
	lv_obj_t *screen_home_card_stopwatch_label;
	lv_obj_t *screen_home_card_stopwatch_img;
	lv_obj_t *screen_home_card_timer;
	lv_obj_t *screen_home_card_timer_label;
	lv_obj_t *screen_home_card_timer_img;
	lv_obj_t *screen_home_card_all_subject_study;
	lv_obj_t *screen_home_card_all_subject_study_label;
	lv_obj_t *screen_home_card_all_subject_study_img;
	lv_obj_t *screen_home_card_sync_textbook;
	lv_obj_t *screen_home_card_sync_textbook_label;
	lv_obj_t *screen_home_card_sync_textbook_img;
	lv_obj_t *screen_home_card_micro_chat;
	lv_obj_t *screen_home_card_micro_chat_label;
	lv_obj_t *screen_home_card_micro_chat_img;
	lv_obj_t *screen_home_card_baidu_netdisk;
	lv_obj_t *screen_home_card_baidu_netdisk_label;
	lv_obj_t *screen_home_card_baidu_netdisk_img;
	lv_obj_t *screen_home_card_word_study;
	lv_obj_t *screen_home_card_word_study_label;
	lv_obj_t *screen_home_card_word_study_img;
	lv_obj_t *screen_home_card_dictionary;
	lv_obj_t *screen_home_card_dictionary_label;
	lv_obj_t *screen_home_card_dictionary_img;
	lv_obj_t *screen_home_card_settings;
	lv_obj_t *screen_home_card_settings_label;
	lv_obj_t *screen_home_card_settings_img;
	lv_obj_t *screen_home_card_story;
	lv_obj_t *screen_home_card_story_label;
	lv_obj_t *screen_home_card_story_img;
	lv_obj_t *screen_home_card_music;
	lv_obj_t *screen_home_card_music_label;
	lv_obj_t *screen_home_card_music_img;
	lv_obj_t *screen_home_card_local_content;
	lv_obj_t *screen_home_card_local_content_label;
	lv_obj_t *screen_home_card_local_content_img;
	lv_obj_t *screen_home_card_k12;
	lv_obj_t *screen_home_card_k12_label;
	lv_obj_t *screen_home_card_k12_img;
	lv_obj_t *screen_home_card_vocabulary;
	lv_obj_t *screen_home_card_vocabulary_label;
	lv_obj_t *screen_home_card_vocabulary_img;
	lv_obj_t *screen_home_card_english_query;
	lv_obj_t *screen_home_card_english_query_label;
	lv_obj_t *screen_home_card_english_query_img;
	lv_obj_t *screen_home_card_weather;
	lv_obj_t *screen_home_card_weather_label;
	lv_obj_t *screen_home_card_weather_img;
	lv_obj_t *screen_home_card_alarm;
	lv_obj_t *screen_home_card_alarm_label;
	lv_obj_t *screen_home_card_alarm_img;
	lv_obj_t *screen_home_card_voice_translate;
	lv_obj_t *screen_home_card_voice_translate_label;
	lv_obj_t *screen_home_card_voice_translate_img;
	lv_obj_t *screen_home_card_ai;
	lv_obj_t *screen_home_card_ai_label;
	lv_obj_t *screen_home_card_ai_img;
	lv_obj_t *screen_home_home_status_card;
	lv_obj_t *screen_home_home_status_label;
	lv_obj_t *screen_home_home_time_card;
	lv_obj_t *screen_home_home_time_label;
	lv_obj_t *screen_home_home_date_label;
	lv_obj_t *screen_home_home_bg_image;
	lv_obj_t *screen_app_grid;
	bool screen_app_grid_del;
	lv_obj_t *screen_app_grid_cont_app_grid;
	lv_obj_t *screen_app_grid_app_tools;
	lv_obj_t *screen_app_grid_app_tools_label;
	lv_obj_t *screen_app_grid_app_tools_img;
	lv_obj_t *screen_app_grid_app_alarm;
	lv_obj_t *screen_app_grid_app_alarm_label;
	lv_obj_t *screen_app_grid_app_alarm_img;
	lv_obj_t *screen_app_grid_app_study;
	lv_obj_t *screen_app_grid_app_study_label;
	lv_obj_t *screen_app_grid_app_study_img;
	lv_obj_t *screen_app_grid_app_ai;
	lv_obj_t *screen_app_grid_app_ai_label;
	lv_obj_t *screen_app_grid_app_ai_img;
	lv_obj_t *screen_app_grid_label_apps_title;
	lv_obj_t *screen_ai;
	bool screen_ai_del;
	lv_obj_t *screen_ai_label_ai_quick;
	lv_obj_t *screen_ai_ai_quick_question_bg;
	lv_obj_t *screen_ai_ai_message_label;
	lv_obj_t *screen_ai_ai_state_label;
	lv_obj_t *screen_ai_ai_state_icon;
	lv_obj_t *screen_ai_ai_character_image;
	lv_obj_t *screen_ai_img_ai_bubble;
	lv_obj_t *screen_study;
	bool screen_study_del;
	lv_obj_t *screen_study_label_study_note;
	lv_obj_t *screen_study_cont_study_main;
	lv_obj_t *screen_study_study_k12;
	lv_obj_t *screen_study_label_k12;
	lv_obj_t *screen_study_img_k12;
	lv_obj_t *screen_study_study_vocab;
	lv_obj_t *screen_study_label_vocab;
	lv_obj_t *screen_study_img_vocab;
	lv_obj_t *screen_study_study_wordbook;
	lv_obj_t *screen_study_label_wordbook;
	lv_obj_t *screen_study_img_wordbook;
	lv_obj_t *screen_study_study_dictionary;
	lv_obj_t *screen_study_label_dictionary;
	lv_obj_t *screen_study_img_dictionary;
	lv_obj_t *screen_study_img_study_bg;
	lv_obj_t *screen_alarm;
	bool screen_alarm_del;
	lv_obj_t *screen_alarm_cont_alarm_card;
	lv_obj_t *screen_alarm_label_alarm_hint;
	lv_obj_t *screen_alarm_img_alarm_clock;
	lv_obj_t *screen_alarm_label_alarm_title;
	lv_obj_t *screen_alarm_img_alarm_bg;
	lv_obj_t *screen_weather;
	bool screen_weather_del;
	lv_obj_t *screen_weather_cont_weather_strip;
	lv_obj_t *screen_weather_weather_row_2;
	lv_obj_t *screen_weather_weather_row_label_2;
	lv_obj_t *screen_weather_weather_row_img_2;
	lv_obj_t *screen_weather_weather_row_1;
	lv_obj_t *screen_weather_weather_row_label_1;
	lv_obj_t *screen_weather_weather_row_img_1;
	lv_obj_t *screen_weather_weather_row_0;
	lv_obj_t *screen_weather_weather_row_label_0;
	lv_obj_t *screen_weather_weather_row_img_0;
	lv_obj_t *screen_weather_cont_weather_panel;
	lv_obj_t *screen_weather_label_weather_meta;
	lv_obj_t *screen_weather_label_weather_desc;
	lv_obj_t *screen_weather_label_weather_temp;
	lv_obj_t *screen_weather_label_weather_title;
	lv_obj_t *screen_weather_img_weather_icon;
	lv_obj_t *screen_timer;
	bool screen_timer_del;
	lv_obj_t *screen_timer_cont_timer_panel;
	lv_obj_t *screen_timer_img_timer_btn;
	lv_obj_t *screen_timer_label_timer_sub;
	lv_obj_t *screen_timer_label_timer_time;
	lv_obj_t *screen_timer_label_timer_title;
	lv_obj_t *screen_timer_img_timer_clock;
	lv_obj_t *screen_stopwatch;
	bool screen_stopwatch_del;
	lv_obj_t *screen_stopwatch_cont_stopwatch_panel;
	lv_obj_t *screen_stopwatch_label_stopwatch_lap;
	lv_obj_t *screen_stopwatch_img_stopwatch_lap;
	lv_obj_t *screen_stopwatch_label_stopwatch_time;
	lv_obj_t *screen_stopwatch_label_stopwatch_title;
	lv_obj_t *screen_stopwatch_img_stopwatch_bg;
	lv_obj_t *screen_focus;
	bool screen_focus_del;
	lv_obj_t *screen_focus_img_focus_start;
	lv_obj_t *screen_focus_cont_focus_stats;
	lv_obj_t *screen_focus_img_focus_stats;
	lv_obj_t *screen_focus_img_focus_tomato;
	lv_obj_t *screen_focus_img_focus_fill;
	lv_obj_t *screen_focus_img_focus_bg;
	lv_obj_t *screen_focus_label_focus_title;
	lv_obj_t *screen_night_light;
	bool screen_night_light_del;
	lv_obj_t *screen_night_light_img_night_thumb;
	lv_obj_t *screen_night_light_img_night_slider;
	lv_obj_t *screen_night_light_img_night_toggle;
	lv_obj_t *screen_night_light_img_night_bg;
	lv_obj_t *screen_night_light_label_night_title;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_screen_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, uint32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                  uint32_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                  lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_completed_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_bottom_layer(void);

void setup_ui(lv_ui *ui);

void video_play(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_screen_boot(lv_ui *ui);
void setup_scr_screen_home(lv_ui *ui);
void setup_scr_screen_app_grid(lv_ui *ui);
void setup_scr_screen_ai(lv_ui *ui);
void setup_scr_screen_study(lv_ui *ui);
void setup_scr_screen_alarm(lv_ui *ui);
void setup_scr_screen_weather(lv_ui *ui);
void setup_scr_screen_timer(lv_ui *ui);
void setup_scr_screen_stopwatch(lv_ui *ui);
void setup_scr_screen_focus(lv_ui *ui);
void setup_scr_screen_night_light(lv_ui *ui);
LV_IMAGE_DECLARE(_loading_spinner_1_RGB565A8_24x24);
LV_IMAGE_DECLARE(_launch_logo_RGB565A8_100x100);
LV_IMAGE_DECLARE(_icon_tools_RGB565A8_36x36);
LV_IMAGE_DECLARE(_focus_home_RGB565A8_36x36);
LV_IMAGE_DECLARE(_stopwatch_home_RGB565A8_36x36);
LV_IMAGE_DECLARE(_button_timer_home_RGB565A8_36x36);
LV_IMAGE_DECLARE(_icon_all_subject_study_RGB565A8_36x36);
LV_IMAGE_DECLARE(_icon_sync_textbook_RGB565A8_36x36);
LV_IMAGE_DECLARE(_icon_micro_chat_RGB565A8_36x36);
LV_IMAGE_DECLARE(_icon_baidu_netdisk_RGB565A8_36x36);
LV_IMAGE_DECLARE(_placeholder_icon_word_study_RGB565A8_36x36);
LV_IMAGE_DECLARE(_placeholder_icon_dictionary_RGB565A8_36x36);
LV_IMAGE_DECLARE(_icon_settings_home_RGB565A8_36x36);
LV_IMAGE_DECLARE(_icon_classic_story_RGB565A8_36x36);
LV_IMAGE_DECLARE(_icon_netease_music_RGB565A8_36x36);
LV_IMAGE_DECLARE(_icon_local_content_RGB565A8_36x36);
LV_IMAGE_DECLARE(_placeholder_icon_k12_RGB565A8_36x36);
LV_IMAGE_DECLARE(_placeholder_icon_vocabulary_RGB565A8_36x36);
LV_IMAGE_DECLARE(_icon_english_query_RGB565A8_36x36);
LV_IMAGE_DECLARE(_weather_home_RGB565A8_36x36);
LV_IMAGE_DECLARE(_icon_alarm_RGB565A8_36x36);
LV_IMAGE_DECLARE(_icon_translate_RGB565A8_36x36);
LV_IMAGE_DECLARE(_icon_ai_RGB565A8_36x36);
LV_IMAGE_DECLARE(_home_bg_RGB565A8_320x240);
LV_IMAGE_DECLARE(_icon_tools_RGB565A8_28x28);
LV_IMAGE_DECLARE(_icon_alarm_RGB565A8_28x28);
LV_IMAGE_DECLARE(_icon_study_RGB565A8_28x28);
LV_IMAGE_DECLARE(_icon_ai_RGB565A8_28x28);
LV_IMAGE_DECLARE(_quick_question_bg_RGB565A8_132x44);
LV_IMAGE_DECLARE(_mic_button_idle_RGB565A8_46x46);
LV_IMAGE_DECLARE(_ai_character_idle_RGB565A8_110x110);
LV_IMAGE_DECLARE(_speech_bubble_RGB565A8_304x176);
LV_IMAGE_DECLARE(_placeholder_icon_k12_RGB565A8_32x32);
LV_IMAGE_DECLARE(_placeholder_icon_vocabulary_RGB565A8_32x32);
LV_IMAGE_DECLARE(_placeholder_icon_word_study_RGB565A8_32x32);
LV_IMAGE_DECLARE(_placeholder_icon_dictionary_RGB565A8_32x32);
LV_IMAGE_DECLARE(_placeholder_msg_bg_RGB565A8_320x240);
LV_IMAGE_DECLARE(_clock_bg_RGB565A8_92x92);
LV_IMAGE_DECLARE(_alarm_bg_RGB565A8_320x240);
LV_IMAGE_DECLARE(_status_weather_RGB565A8_20x20);
LV_IMAGE_DECLARE(_status_battery_RGB565A8_20x20);
LV_IMAGE_DECLARE(_status_wifi_RGB565A8_20x20);
LV_IMAGE_DECLARE(_weather_sun_RGB565A8_80x80);
LV_IMAGE_DECLARE(_button_timer_RGB565A8_72x40);
LV_IMAGE_DECLARE(_clock_bg_RGB565A8_132x132);
LV_IMAGE_DECLARE(_lap_item_bg_RGB565A8_120x28);
LV_IMAGE_DECLARE(_stopwatch_bg_RGB565A8_136x132);
LV_IMAGE_DECLARE(_button_focus_start_RGB565A8_84x40);
LV_IMAGE_DECLARE(_focus_stats_bg_RGB565A8_124x76);
LV_IMAGE_DECLARE(_focus_tomato_RGB565A8_38x38);
LV_IMAGE_DECLARE(_focus_progress_fill_RGB565A8_140x16);
LV_IMAGE_DECLARE(_focus_progress_bg_RGB565A8_150x120);
LV_IMAGE_DECLARE(_slider_thumb_RGB565A8_24x24);
LV_IMAGE_DECLARE(_slider_bg_RGB565A8_148x16);
LV_IMAGE_DECLARE(_button_toggle_light_RGB565A8_92x36);
LV_IMAGE_DECLARE(_night_light_off_RGB565A8_110x130);

LV_FONT_DECLARE(lv_font_montserratMedium_14)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_montserratMedium_28)
LV_FONT_DECLARE(lv_font_montserratMedium_18)
LV_FONT_DECLARE(lv_font_montserratMedium_11)
LV_FONT_DECLARE(lv_font_montserratMedium_24)


#ifdef __cplusplus
}
#endif
#endif
