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



void setup_scr_screen_timer(lv_ui *ui)
{
    //Write codes screen_timer
    ui->screen_timer = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_timer, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_timer, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_timer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_timer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_timer, lv_color_hex(0xF2F6FF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_timer, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_timer_cont_timer_panel
    ui->screen_timer_cont_timer_panel = lv_obj_create(ui->screen_timer);
    lv_obj_set_pos(ui->screen_timer_cont_timer_panel, 14, 60);
    lv_obj_set_size(ui->screen_timer_cont_timer_panel, 162, 156);
    lv_obj_set_scrollbar_mode(ui->screen_timer_cont_timer_panel, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_timer_cont_timer_panel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_timer_cont_timer_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_timer_cont_timer_panel, 18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_timer_cont_timer_panel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_timer_cont_timer_panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_timer_cont_timer_panel, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_timer_cont_timer_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_timer_cont_timer_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_timer_cont_timer_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_timer_cont_timer_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_timer_cont_timer_panel, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_timer_cont_timer_panel, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_timer_cont_timer_panel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_timer_cont_timer_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_timer_cont_timer_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_timer_cont_timer_panel, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_timer_img_timer_btn
    ui->screen_timer_img_timer_btn = lv_image_create(ui->screen_timer_cont_timer_panel);
    lv_obj_set_pos(ui->screen_timer_img_timer_btn, 0, 100);
    lv_obj_set_size(ui->screen_timer_img_timer_btn, 72, 40);
    lv_obj_add_flag(ui->screen_timer_img_timer_btn, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_timer_img_timer_btn, &_button_timer_RGB565A8_72x40);
    lv_image_set_pivot(ui->screen_timer_img_timer_btn, 50,50);
    lv_image_set_rotation(ui->screen_timer_img_timer_btn, 0);

    //Write style for screen_timer_img_timer_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_timer_img_timer_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_timer_img_timer_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_timer_label_timer_sub
    ui->screen_timer_label_timer_sub = lv_label_create(ui->screen_timer_cont_timer_panel);
    lv_obj_set_pos(ui->screen_timer_label_timer_sub, 0, 42);
    lv_obj_set_size(ui->screen_timer_label_timer_sub, 100, 18);
    lv_label_set_text(ui->screen_timer_label_timer_sub, "Focus timer");
    lv_label_set_long_mode(ui->screen_timer_label_timer_sub, LV_LABEL_LONG_CLIP);

    //Write style for screen_timer_label_timer_sub, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_timer_label_timer_sub, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_timer_label_timer_sub, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_timer_label_timer_sub, lv_color_hex(0x5C628B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_timer_label_timer_sub, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_timer_label_timer_sub, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_timer_label_timer_sub, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_timer_label_timer_sub, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_timer_label_timer_sub, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_timer_label_timer_sub, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_timer_label_timer_sub, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_timer_label_timer_sub, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_timer_label_timer_sub, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_timer_label_timer_sub, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_timer_label_timer_sub, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_timer_label_timer_time
    ui->screen_timer_label_timer_time = lv_label_create(ui->screen_timer_cont_timer_panel);
    lv_obj_set_pos(ui->screen_timer_label_timer_time, 0, 0);
    lv_obj_set_size(ui->screen_timer_label_timer_time, 100, 34);
    lv_label_set_text(ui->screen_timer_label_timer_time, "25:00");
    lv_label_set_long_mode(ui->screen_timer_label_timer_time, LV_LABEL_LONG_CLIP);

    //Write style for screen_timer_label_timer_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_timer_label_timer_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_timer_label_timer_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_timer_label_timer_time, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_timer_label_timer_time, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_timer_label_timer_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_timer_label_timer_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_timer_label_timer_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_timer_label_timer_time, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_timer_label_timer_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_timer_label_timer_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_timer_label_timer_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_timer_label_timer_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_timer_label_timer_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_timer_label_timer_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_timer_label_timer_title
    ui->screen_timer_label_timer_title = lv_label_create(ui->screen_timer);
    lv_obj_set_pos(ui->screen_timer_label_timer_title, 16, 12);
    lv_obj_set_size(ui->screen_timer_label_timer_title, 80, 22);
    lv_label_set_text(ui->screen_timer_label_timer_title, "Timer");
    lv_label_set_long_mode(ui->screen_timer_label_timer_title, LV_LABEL_LONG_CLIP);

    //Write style for screen_timer_label_timer_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_timer_label_timer_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_timer_label_timer_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_timer_label_timer_title, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_timer_label_timer_title, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_timer_label_timer_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_timer_label_timer_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_timer_label_timer_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_timer_label_timer_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_timer_label_timer_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_timer_label_timer_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_timer_label_timer_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_timer_label_timer_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_timer_label_timer_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_timer_label_timer_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_timer_img_timer_clock
    ui->screen_timer_img_timer_clock = lv_image_create(ui->screen_timer);
    lv_obj_set_pos(ui->screen_timer_img_timer_clock, 178, 52);
    lv_obj_set_size(ui->screen_timer_img_timer_clock, 132, 132);
    lv_obj_add_flag(ui->screen_timer_img_timer_clock, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_timer_img_timer_clock, &_clock_bg_RGB565A8_132x132);
    lv_image_set_pivot(ui->screen_timer_img_timer_clock, 50,50);
    lv_image_set_rotation(ui->screen_timer_img_timer_clock, 0);

    //Write style for screen_timer_img_timer_clock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_timer_img_timer_clock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_timer_img_timer_clock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_timer.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_timer);

}
