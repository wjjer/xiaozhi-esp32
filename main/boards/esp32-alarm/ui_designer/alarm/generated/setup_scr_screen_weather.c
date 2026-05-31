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



void setup_scr_screen_weather(lv_ui *ui)
{
    //Write codes screen_weather
    ui->screen_weather = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_weather, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_weather, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_weather, lv_color_hex(0xF7F9FF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_weather, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_cont_weather_strip
    ui->screen_weather_cont_weather_strip = lv_obj_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_cont_weather_strip, 216, 90);
    lv_obj_set_size(ui->screen_weather_cont_weather_strip, 90, 136);
    lv_obj_set_scrollbar_mode(ui->screen_weather_cont_weather_strip, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_weather_cont_weather_strip, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_cont_weather_strip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_cont_weather_strip, 18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_cont_weather_strip, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_weather_cont_weather_strip, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_weather_cont_weather_strip, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_cont_weather_strip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_cont_weather_strip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_cont_weather_strip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_cont_weather_strip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_cont_weather_strip, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_weather_cont_weather_strip, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_weather_cont_weather_strip, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_weather_cont_weather_strip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_weather_cont_weather_strip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_weather_cont_weather_strip, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_weather_row_2
    ui->screen_weather_weather_row_2 = lv_obj_create(ui->screen_weather_cont_weather_strip);
    lv_obj_set_pos(ui->screen_weather_weather_row_2, 0, 72);
    lv_obj_set_size(ui->screen_weather_weather_row_2, 70, 32);
    lv_obj_set_scrollbar_mode(ui->screen_weather_weather_row_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_weather_weather_row_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_weather_row_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_weather_row_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_weather_row_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_weather_row_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_weather_row_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_weather_row_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_weather_row_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_weather_row_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_weather_row_label_2
    ui->screen_weather_weather_row_label_2 = lv_label_create(ui->screen_weather_weather_row_2);
    lv_obj_set_pos(ui->screen_weather_weather_row_label_2, 26, 8);
    lv_obj_set_size(ui->screen_weather_weather_row_label_2, 42, 14);
    lv_label_set_text(ui->screen_weather_weather_row_label_2, "Weather");
    lv_label_set_long_mode(ui->screen_weather_weather_row_label_2, LV_LABEL_LONG_CLIP);

    //Write style for screen_weather_weather_row_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_weather_row_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_weather_row_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_weather_row_label_2, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_weather_row_label_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_weather_row_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_weather_row_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_weather_row_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_weather_row_label_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_weather_row_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_weather_row_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_weather_row_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_weather_row_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_weather_row_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_weather_row_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_weather_row_img_2
    ui->screen_weather_weather_row_img_2 = lv_image_create(ui->screen_weather_weather_row_2);
    lv_obj_set_pos(ui->screen_weather_weather_row_img_2, 0, 6);
    lv_obj_set_size(ui->screen_weather_weather_row_img_2, 20, 20);
    lv_obj_add_flag(ui->screen_weather_weather_row_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_weather_row_img_2, &_status_weather_RGB565A8_20x20);
    lv_image_set_pivot(ui->screen_weather_weather_row_img_2, 50,50);
    lv_image_set_rotation(ui->screen_weather_weather_row_img_2, 0);

    //Write style for screen_weather_weather_row_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_weather_row_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_weather_row_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_weather_row_1
    ui->screen_weather_weather_row_1 = lv_obj_create(ui->screen_weather_cont_weather_strip);
    lv_obj_set_pos(ui->screen_weather_weather_row_1, 0, 38);
    lv_obj_set_size(ui->screen_weather_weather_row_1, 70, 32);
    lv_obj_set_scrollbar_mode(ui->screen_weather_weather_row_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_weather_weather_row_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_weather_row_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_weather_row_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_weather_row_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_weather_row_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_weather_row_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_weather_row_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_weather_row_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_weather_row_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_weather_row_label_1
    ui->screen_weather_weather_row_label_1 = lv_label_create(ui->screen_weather_weather_row_1);
    lv_obj_set_pos(ui->screen_weather_weather_row_label_1, 26, 8);
    lv_obj_set_size(ui->screen_weather_weather_row_label_1, 42, 14);
    lv_label_set_text(ui->screen_weather_weather_row_label_1, "Battery");
    lv_label_set_long_mode(ui->screen_weather_weather_row_label_1, LV_LABEL_LONG_CLIP);

    //Write style for screen_weather_weather_row_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_weather_row_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_weather_row_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_weather_row_label_1, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_weather_row_label_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_weather_row_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_weather_row_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_weather_row_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_weather_row_label_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_weather_row_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_weather_row_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_weather_row_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_weather_row_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_weather_row_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_weather_row_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_weather_row_img_1
    ui->screen_weather_weather_row_img_1 = lv_image_create(ui->screen_weather_weather_row_1);
    lv_obj_set_pos(ui->screen_weather_weather_row_img_1, 0, 6);
    lv_obj_set_size(ui->screen_weather_weather_row_img_1, 20, 20);
    lv_obj_add_flag(ui->screen_weather_weather_row_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_weather_row_img_1, &_status_battery_RGB565A8_20x20);
    lv_image_set_pivot(ui->screen_weather_weather_row_img_1, 50,50);
    lv_image_set_rotation(ui->screen_weather_weather_row_img_1, 0);

    //Write style for screen_weather_weather_row_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_weather_row_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_weather_row_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_weather_row_0
    ui->screen_weather_weather_row_0 = lv_obj_create(ui->screen_weather_cont_weather_strip);
    lv_obj_set_pos(ui->screen_weather_weather_row_0, 0, 4);
    lv_obj_set_size(ui->screen_weather_weather_row_0, 70, 32);
    lv_obj_set_scrollbar_mode(ui->screen_weather_weather_row_0, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_weather_weather_row_0, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_weather_row_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_weather_row_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_weather_row_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_weather_row_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_weather_row_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_weather_row_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_weather_row_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_weather_row_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_weather_row_label_0
    ui->screen_weather_weather_row_label_0 = lv_label_create(ui->screen_weather_weather_row_0);
    lv_obj_set_pos(ui->screen_weather_weather_row_label_0, 26, 8);
    lv_obj_set_size(ui->screen_weather_weather_row_label_0, 42, 14);
    lv_label_set_text(ui->screen_weather_weather_row_label_0, "WiFi");
    lv_label_set_long_mode(ui->screen_weather_weather_row_label_0, LV_LABEL_LONG_CLIP);

    //Write style for screen_weather_weather_row_label_0, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_weather_row_label_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_weather_row_label_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_weather_row_label_0, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_weather_row_label_0, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_weather_row_label_0, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_weather_row_label_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_weather_row_label_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_weather_row_label_0, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_weather_row_label_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_weather_row_label_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_weather_row_label_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_weather_row_label_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_weather_row_label_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_weather_row_label_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_weather_row_img_0
    ui->screen_weather_weather_row_img_0 = lv_image_create(ui->screen_weather_weather_row_0);
    lv_obj_set_pos(ui->screen_weather_weather_row_img_0, 0, 6);
    lv_obj_set_size(ui->screen_weather_weather_row_img_0, 20, 20);
    lv_obj_add_flag(ui->screen_weather_weather_row_img_0, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_weather_row_img_0, &_status_wifi_RGB565A8_20x20);
    lv_image_set_pivot(ui->screen_weather_weather_row_img_0, 50,50);
    lv_image_set_rotation(ui->screen_weather_weather_row_img_0, 0);

    //Write style for screen_weather_weather_row_img_0, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_weather_row_img_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_weather_row_img_0, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_cont_weather_panel
    ui->screen_weather_cont_weather_panel = lv_obj_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_cont_weather_panel, 14, 90);
    lv_obj_set_size(ui->screen_weather_cont_weather_panel, 188, 136);
    lv_obj_set_scrollbar_mode(ui->screen_weather_cont_weather_panel, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_weather_cont_weather_panel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_cont_weather_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_cont_weather_panel, 18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_cont_weather_panel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_weather_cont_weather_panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_weather_cont_weather_panel, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_cont_weather_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_cont_weather_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_cont_weather_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_cont_weather_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_cont_weather_panel, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_weather_cont_weather_panel, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_weather_cont_weather_panel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_weather_cont_weather_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_weather_cont_weather_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_weather_cont_weather_panel, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_weather_meta
    ui->screen_weather_label_weather_meta = lv_label_create(ui->screen_weather_cont_weather_panel);
    lv_obj_set_pos(ui->screen_weather_label_weather_meta, 0, 112);
    lv_obj_set_size(ui->screen_weather_label_weather_meta, 90, 14);
    lv_label_set_text(ui->screen_weather_label_weather_meta, "Today 09:00");
    lv_label_set_long_mode(ui->screen_weather_label_weather_meta, LV_LABEL_LONG_CLIP);

    //Write style for screen_weather_label_weather_meta, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_weather_meta, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_weather_meta, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_weather_meta, lv_color_hex(0x5C628B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_weather_meta, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_weather_meta, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_weather_meta, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_weather_meta, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_weather_meta, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_weather_meta, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_weather_meta, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_weather_meta, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_weather_meta, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_weather_meta, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_weather_meta, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_weather_desc
    ui->screen_weather_label_weather_desc = lv_label_create(ui->screen_weather_cont_weather_panel);
    lv_obj_set_pos(ui->screen_weather_label_weather_desc, 0, 42);
    lv_obj_set_size(ui->screen_weather_label_weather_desc, 80, 18);
    lv_label_set_text(ui->screen_weather_label_weather_desc, "Sunny");
    lv_label_set_long_mode(ui->screen_weather_label_weather_desc, LV_LABEL_LONG_CLIP);

    //Write style for screen_weather_label_weather_desc, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_weather_desc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_weather_desc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_weather_desc, lv_color_hex(0x5C628B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_weather_desc, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_weather_desc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_weather_desc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_weather_desc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_weather_desc, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_weather_desc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_weather_desc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_weather_desc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_weather_desc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_weather_desc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_weather_desc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_weather_temp
    ui->screen_weather_label_weather_temp = lv_label_create(ui->screen_weather_cont_weather_panel);
    lv_obj_set_pos(ui->screen_weather_label_weather_temp, 0, 0);
    lv_obj_set_size(ui->screen_weather_label_weather_temp, 90, 34);
    lv_label_set_text(ui->screen_weather_label_weather_temp, "24 C");
    lv_label_set_long_mode(ui->screen_weather_label_weather_temp, LV_LABEL_LONG_CLIP);

    //Write style for screen_weather_label_weather_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_weather_temp, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_weather_temp, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_weather_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_weather_temp, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_weather_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_label_weather_title
    ui->screen_weather_label_weather_title = lv_label_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_label_weather_title, 16, 12);
    lv_obj_set_size(ui->screen_weather_label_weather_title, 90, 22);
    lv_label_set_text(ui->screen_weather_label_weather_title, "Weather");
    lv_label_set_long_mode(ui->screen_weather_label_weather_title, LV_LABEL_LONG_CLIP);

    //Write style for screen_weather_label_weather_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_weather_label_weather_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_weather_label_weather_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_weather_label_weather_title, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_weather_label_weather_title, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_weather_label_weather_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_weather_label_weather_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_weather_label_weather_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_weather_label_weather_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_weather_label_weather_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_weather_label_weather_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_weather_label_weather_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_weather_label_weather_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_weather_label_weather_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_weather_label_weather_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_weather_img_weather_icon
    ui->screen_weather_img_weather_icon = lv_image_create(ui->screen_weather);
    lv_obj_set_pos(ui->screen_weather_img_weather_icon, 226, 14);
    lv_obj_set_size(ui->screen_weather_img_weather_icon, 80, 80);
    lv_obj_add_flag(ui->screen_weather_img_weather_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_weather_img_weather_icon, &_weather_sun_RGB565A8_80x80);
    lv_image_set_pivot(ui->screen_weather_img_weather_icon, 50,50);
    lv_image_set_rotation(ui->screen_weather_img_weather_icon, 0);

    //Write style for screen_weather_img_weather_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_weather_img_weather_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_weather_img_weather_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_weather.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_weather);

}
