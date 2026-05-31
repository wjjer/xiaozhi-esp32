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



void setup_scr_screen_alarm(lv_ui *ui)
{
    //Write codes screen_alarm
    ui->screen_alarm = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_alarm, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_alarm, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_alarm, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_alarm, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_alarm, lv_color_hex(0xFFF6EA), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_alarm, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_alarm_cont_alarm_card
    ui->screen_alarm_cont_alarm_card = lv_obj_create(ui->screen_alarm);
    lv_obj_set_pos(ui->screen_alarm_cont_alarm_card, 16, 52);
    lv_obj_set_size(ui->screen_alarm_cont_alarm_card, 288, 176);
    lv_obj_set_scrollbar_mode(ui->screen_alarm_cont_alarm_card, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_alarm_cont_alarm_card, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_alarm_cont_alarm_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_alarm_cont_alarm_card, 18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_alarm_cont_alarm_card, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_alarm_cont_alarm_card, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_alarm_cont_alarm_card, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_alarm_cont_alarm_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_alarm_cont_alarm_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_alarm_cont_alarm_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_alarm_cont_alarm_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_alarm_cont_alarm_card, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_alarm_cont_alarm_card, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_alarm_cont_alarm_card, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_alarm_cont_alarm_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_alarm_cont_alarm_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_alarm_cont_alarm_card, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_alarm_label_alarm_hint
    ui->screen_alarm_label_alarm_hint = lv_label_create(ui->screen_alarm_cont_alarm_card);
    lv_obj_set_pos(ui->screen_alarm_label_alarm_hint, 126, 78);
    lv_obj_set_size(ui->screen_alarm_label_alarm_hint, 140, 22);
    lv_label_set_text(ui->screen_alarm_label_alarm_hint, "Alarm center");
    lv_label_set_long_mode(ui->screen_alarm_label_alarm_hint, LV_LABEL_LONG_WRAP);

    //Write style for screen_alarm_label_alarm_hint, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_alarm_label_alarm_hint, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_alarm_label_alarm_hint, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_alarm_label_alarm_hint, lv_color_hex(0x5C628B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_alarm_label_alarm_hint, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_alarm_label_alarm_hint, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_alarm_label_alarm_hint, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_alarm_label_alarm_hint, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_alarm_label_alarm_hint, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_alarm_label_alarm_hint, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_alarm_label_alarm_hint, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_alarm_label_alarm_hint, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_alarm_label_alarm_hint, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_alarm_label_alarm_hint, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_alarm_label_alarm_hint, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_alarm_img_alarm_clock
    ui->screen_alarm_img_alarm_clock = lv_image_create(ui->screen_alarm_cont_alarm_card);
    lv_obj_set_pos(ui->screen_alarm_img_alarm_clock, 12, 42);
    lv_obj_set_size(ui->screen_alarm_img_alarm_clock, 92, 92);
    lv_obj_add_flag(ui->screen_alarm_img_alarm_clock, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_alarm_img_alarm_clock, &_clock_bg_RGB565A8_92x92);
    lv_image_set_pivot(ui->screen_alarm_img_alarm_clock, 50,50);
    lv_image_set_rotation(ui->screen_alarm_img_alarm_clock, 0);

    //Write style for screen_alarm_img_alarm_clock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_alarm_img_alarm_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_alarm_img_alarm_clock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_alarm_label_alarm_title
    ui->screen_alarm_label_alarm_title = lv_label_create(ui->screen_alarm);
    lv_obj_set_pos(ui->screen_alarm_label_alarm_title, 16, 12);
    lv_obj_set_size(ui->screen_alarm_label_alarm_title, 80, 22);
    lv_label_set_text(ui->screen_alarm_label_alarm_title, "Alarm");
    lv_label_set_long_mode(ui->screen_alarm_label_alarm_title, LV_LABEL_LONG_CLIP);

    //Write style for screen_alarm_label_alarm_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_alarm_label_alarm_title, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_alarm_label_alarm_title, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_alarm_label_alarm_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_alarm_label_alarm_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_alarm_img_alarm_bg
    ui->screen_alarm_img_alarm_bg = lv_image_create(ui->screen_alarm);
    lv_obj_set_pos(ui->screen_alarm_img_alarm_bg, 0, 0);
    lv_obj_set_size(ui->screen_alarm_img_alarm_bg, 320, 240);
    lv_obj_add_flag(ui->screen_alarm_img_alarm_bg, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_alarm_img_alarm_bg, &_alarm_bg_RGB565A8_320x240);
    lv_image_set_pivot(ui->screen_alarm_img_alarm_bg, 50,50);
    lv_image_set_rotation(ui->screen_alarm_img_alarm_bg, 0);

    //Write style for screen_alarm_img_alarm_bg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_alarm_img_alarm_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_alarm_img_alarm_bg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_alarm.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_alarm);

}
