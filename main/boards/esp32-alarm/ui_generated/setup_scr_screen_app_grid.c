/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen_app_grid(lv_ui *ui)
{
    //Write codes screen_app_grid
    ui->screen_app_grid = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_app_grid, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_app_grid, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_app_grid, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_app_grid, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_app_grid, lv_color_hex(0xEEF4FF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_app_grid, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_app_grid_cont_app_grid
    ui->screen_app_grid_cont_app_grid = lv_obj_create(ui->screen_app_grid);
    lv_obj_set_pos(ui->screen_app_grid_cont_app_grid, 16, 48);
    lv_obj_set_size(ui->screen_app_grid_cont_app_grid, 288, 168);
    lv_obj_set_scrollbar_mode(ui->screen_app_grid_cont_app_grid, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_app_grid_cont_app_grid, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_app_grid_cont_app_grid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_app_grid_cont_app_grid, 18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_app_grid_cont_app_grid, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_app_grid_cont_app_grid, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_app_grid_cont_app_grid, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_app_grid_cont_app_grid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_app_grid_cont_app_grid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_app_grid_cont_app_grid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_app_grid_cont_app_grid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_app_grid_cont_app_grid, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_app_grid_cont_app_grid, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_app_grid_cont_app_grid, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_app_grid_cont_app_grid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_app_grid_cont_app_grid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_app_grid_cont_app_grid, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_app_grid_app_tools
    ui->screen_app_grid_app_tools = lv_obj_create(ui->screen_app_grid_cont_app_grid);
    lv_obj_set_pos(ui->screen_app_grid_app_tools, 150, 88);
    lv_obj_set_size(ui->screen_app_grid_app_tools, 128, 64);
    lv_obj_set_scrollbar_mode(ui->screen_app_grid_app_tools, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_app_grid_app_tools, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_app_grid_app_tools, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_app_grid_app_tools, 14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_app_grid_app_tools, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_app_grid_app_tools, lv_color_hex(0xF7FAFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_app_grid_app_tools, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_app_grid_app_tools, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_app_grid_app_tools, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_app_grid_app_tools, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_app_grid_app_tools, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_app_grid_app_tools, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_app_grid_app_tools_label
    ui->screen_app_grid_app_tools_label = lv_label_create(ui->screen_app_grid_app_tools);
    lv_obj_set_pos(ui->screen_app_grid_app_tools_label, 46, 22);
    lv_obj_set_size(ui->screen_app_grid_app_tools_label, 64, 18);
    lv_label_set_text(ui->screen_app_grid_app_tools_label, "Tools");
    lv_label_set_long_mode(ui->screen_app_grid_app_tools_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_app_grid_app_tools_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_app_grid_app_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_app_grid_app_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_app_grid_app_tools_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_app_grid_app_tools_label, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_app_grid_app_tools_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_app_grid_app_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_app_grid_app_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_app_grid_app_tools_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_app_grid_app_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_app_grid_app_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_app_grid_app_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_app_grid_app_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_app_grid_app_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_app_grid_app_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_app_grid_app_tools_img
    ui->screen_app_grid_app_tools_img = lv_image_create(ui->screen_app_grid_app_tools);
    lv_obj_set_pos(ui->screen_app_grid_app_tools_img, 8, 18);
    lv_obj_set_size(ui->screen_app_grid_app_tools_img, 28, 28);
    lv_obj_add_flag(ui->screen_app_grid_app_tools_img, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_app_grid_app_tools_img, &_icon_tools_RGB565A8_28x28);
    lv_image_set_pivot(ui->screen_app_grid_app_tools_img, 50,50);
    lv_image_set_rotation(ui->screen_app_grid_app_tools_img, 0);

    //Write style for screen_app_grid_app_tools_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_app_grid_app_tools_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_app_grid_app_tools_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_app_grid_app_alarm
    ui->screen_app_grid_app_alarm = lv_obj_create(ui->screen_app_grid_cont_app_grid);
    lv_obj_set_pos(ui->screen_app_grid_app_alarm, 10, 88);
    lv_obj_set_size(ui->screen_app_grid_app_alarm, 128, 64);
    lv_obj_set_scrollbar_mode(ui->screen_app_grid_app_alarm, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_app_grid_app_alarm, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_app_grid_app_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_app_grid_app_alarm, 14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_app_grid_app_alarm, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_app_grid_app_alarm, lv_color_hex(0xF7FAFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_app_grid_app_alarm, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_app_grid_app_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_app_grid_app_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_app_grid_app_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_app_grid_app_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_app_grid_app_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_app_grid_app_alarm_label
    ui->screen_app_grid_app_alarm_label = lv_label_create(ui->screen_app_grid_app_alarm);
    lv_obj_set_pos(ui->screen_app_grid_app_alarm_label, 46, 22);
    lv_obj_set_size(ui->screen_app_grid_app_alarm_label, 64, 18);
    lv_label_set_text(ui->screen_app_grid_app_alarm_label, "Alarm");
    lv_label_set_long_mode(ui->screen_app_grid_app_alarm_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_app_grid_app_alarm_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_app_grid_app_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_app_grid_app_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_app_grid_app_alarm_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_app_grid_app_alarm_label, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_app_grid_app_alarm_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_app_grid_app_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_app_grid_app_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_app_grid_app_alarm_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_app_grid_app_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_app_grid_app_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_app_grid_app_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_app_grid_app_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_app_grid_app_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_app_grid_app_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_app_grid_app_alarm_img
    ui->screen_app_grid_app_alarm_img = lv_image_create(ui->screen_app_grid_app_alarm);
    lv_obj_set_pos(ui->screen_app_grid_app_alarm_img, 8, 18);
    lv_obj_set_size(ui->screen_app_grid_app_alarm_img, 28, 28);
    lv_obj_add_flag(ui->screen_app_grid_app_alarm_img, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_app_grid_app_alarm_img, &_icon_alarm_RGB565A8_28x28);
    lv_image_set_pivot(ui->screen_app_grid_app_alarm_img, 50,50);
    lv_image_set_rotation(ui->screen_app_grid_app_alarm_img, 0);

    //Write style for screen_app_grid_app_alarm_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_app_grid_app_alarm_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_app_grid_app_alarm_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_app_grid_app_study
    ui->screen_app_grid_app_study = lv_obj_create(ui->screen_app_grid_cont_app_grid);
    lv_obj_set_pos(ui->screen_app_grid_app_study, 150, 12);
    lv_obj_set_size(ui->screen_app_grid_app_study, 128, 64);
    lv_obj_set_scrollbar_mode(ui->screen_app_grid_app_study, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_app_grid_app_study, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_app_grid_app_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_app_grid_app_study, 14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_app_grid_app_study, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_app_grid_app_study, lv_color_hex(0xF7FAFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_app_grid_app_study, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_app_grid_app_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_app_grid_app_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_app_grid_app_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_app_grid_app_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_app_grid_app_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_app_grid_app_study_label
    ui->screen_app_grid_app_study_label = lv_label_create(ui->screen_app_grid_app_study);
    lv_obj_set_pos(ui->screen_app_grid_app_study_label, 46, 22);
    lv_obj_set_size(ui->screen_app_grid_app_study_label, 64, 18);
    lv_label_set_text(ui->screen_app_grid_app_study_label, "Study");
    lv_label_set_long_mode(ui->screen_app_grid_app_study_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_app_grid_app_study_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_app_grid_app_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_app_grid_app_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_app_grid_app_study_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_app_grid_app_study_label, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_app_grid_app_study_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_app_grid_app_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_app_grid_app_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_app_grid_app_study_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_app_grid_app_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_app_grid_app_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_app_grid_app_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_app_grid_app_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_app_grid_app_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_app_grid_app_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_app_grid_app_study_img
    ui->screen_app_grid_app_study_img = lv_image_create(ui->screen_app_grid_app_study);
    lv_obj_set_pos(ui->screen_app_grid_app_study_img, 8, 18);
    lv_obj_set_size(ui->screen_app_grid_app_study_img, 28, 28);
    lv_obj_add_flag(ui->screen_app_grid_app_study_img, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_app_grid_app_study_img, &_icon_study_RGB565A8_28x28);
    lv_image_set_pivot(ui->screen_app_grid_app_study_img, 50,50);
    lv_image_set_rotation(ui->screen_app_grid_app_study_img, 0);

    //Write style for screen_app_grid_app_study_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_app_grid_app_study_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_app_grid_app_study_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_app_grid_app_ai
    ui->screen_app_grid_app_ai = lv_obj_create(ui->screen_app_grid_cont_app_grid);
    lv_obj_set_pos(ui->screen_app_grid_app_ai, 10, 12);
    lv_obj_set_size(ui->screen_app_grid_app_ai, 128, 64);
    lv_obj_set_scrollbar_mode(ui->screen_app_grid_app_ai, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_app_grid_app_ai, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_app_grid_app_ai, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_app_grid_app_ai, 14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_app_grid_app_ai, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_app_grid_app_ai, lv_color_hex(0xF7FAFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_app_grid_app_ai, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_app_grid_app_ai, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_app_grid_app_ai, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_app_grid_app_ai, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_app_grid_app_ai, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_app_grid_app_ai, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_app_grid_app_ai_label
    ui->screen_app_grid_app_ai_label = lv_label_create(ui->screen_app_grid_app_ai);
    lv_obj_set_pos(ui->screen_app_grid_app_ai_label, 46, 22);
    lv_obj_set_size(ui->screen_app_grid_app_ai_label, 64, 18);
    lv_label_set_text(ui->screen_app_grid_app_ai_label, "AI");
    lv_label_set_long_mode(ui->screen_app_grid_app_ai_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_app_grid_app_ai_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_app_grid_app_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_app_grid_app_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_app_grid_app_ai_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_app_grid_app_ai_label, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_app_grid_app_ai_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_app_grid_app_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_app_grid_app_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_app_grid_app_ai_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_app_grid_app_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_app_grid_app_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_app_grid_app_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_app_grid_app_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_app_grid_app_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_app_grid_app_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_app_grid_app_ai_img
    ui->screen_app_grid_app_ai_img = lv_image_create(ui->screen_app_grid_app_ai);
    lv_obj_set_pos(ui->screen_app_grid_app_ai_img, 8, 18);
    lv_obj_set_size(ui->screen_app_grid_app_ai_img, 28, 28);
    lv_obj_add_flag(ui->screen_app_grid_app_ai_img, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_app_grid_app_ai_img, &_icon_ai_RGB565A8_28x28);
    lv_image_set_pivot(ui->screen_app_grid_app_ai_img, 50,50);
    lv_image_set_rotation(ui->screen_app_grid_app_ai_img, 0);

    //Write style for screen_app_grid_app_ai_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_app_grid_app_ai_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_app_grid_app_ai_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_app_grid_label_apps_title
    ui->screen_app_grid_label_apps_title = lv_label_create(ui->screen_app_grid);
    lv_obj_set_pos(ui->screen_app_grid_label_apps_title, 16, 12);
    lv_obj_set_size(ui->screen_app_grid_label_apps_title, 80, 22);
    lv_label_set_text(ui->screen_app_grid_label_apps_title, "Apps");
    lv_label_set_long_mode(ui->screen_app_grid_label_apps_title, LV_LABEL_LONG_CLIP);

    //Write style for screen_app_grid_label_apps_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_app_grid_label_apps_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_app_grid_label_apps_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_app_grid_label_apps_title, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_app_grid_label_apps_title, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_app_grid_label_apps_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_app_grid_label_apps_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_app_grid_label_apps_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_app_grid_label_apps_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_app_grid_label_apps_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_app_grid_label_apps_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_app_grid_label_apps_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_app_grid_label_apps_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_app_grid_label_apps_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_app_grid_label_apps_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_app_grid.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_app_grid);

}
