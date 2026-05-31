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



void setup_scr_screen_focus(lv_ui *ui)
{
    //Write codes screen_focus
    ui->screen_focus = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_focus, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_focus, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_focus, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_focus, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_focus, lv_color_hex(0xFFF4EC), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_focus, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_focus_img_focus_start
    ui->screen_focus_img_focus_start = lv_image_create(ui->screen_focus);
    lv_obj_set_pos(ui->screen_focus_img_focus_start, 220, 184);
    lv_obj_set_size(ui->screen_focus_img_focus_start, 84, 40);
    lv_obj_add_flag(ui->screen_focus_img_focus_start, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_focus_img_focus_start, &_button_focus_start_RGB565A8_84x40);
    lv_image_set_pivot(ui->screen_focus_img_focus_start, 50,50);
    lv_image_set_rotation(ui->screen_focus_img_focus_start, 0);

    //Write style for screen_focus_img_focus_start, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_focus_img_focus_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_focus_img_focus_start, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_focus_cont_focus_stats
    ui->screen_focus_cont_focus_stats = lv_obj_create(ui->screen_focus);
    lv_obj_set_pos(ui->screen_focus_cont_focus_stats, 14, 118);
    lv_obj_set_size(ui->screen_focus_cont_focus_stats, 144, 96);
    lv_obj_set_scrollbar_mode(ui->screen_focus_cont_focus_stats, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_focus_cont_focus_stats, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_focus_cont_focus_stats, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_focus_cont_focus_stats, 18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_focus_cont_focus_stats, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_focus_cont_focus_stats, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_focus_cont_focus_stats, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_focus_cont_focus_stats, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_focus_cont_focus_stats, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_focus_cont_focus_stats, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_focus_cont_focus_stats, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_focus_cont_focus_stats, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_focus_cont_focus_stats, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_focus_cont_focus_stats, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_focus_cont_focus_stats, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_focus_cont_focus_stats, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_focus_cont_focus_stats, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_focus_img_focus_stats
    ui->screen_focus_img_focus_stats = lv_image_create(ui->screen_focus_cont_focus_stats);
    lv_obj_set_pos(ui->screen_focus_img_focus_stats, 0, 0);
    lv_obj_set_size(ui->screen_focus_img_focus_stats, 124, 76);
    lv_obj_add_flag(ui->screen_focus_img_focus_stats, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_focus_img_focus_stats, &_focus_stats_bg_RGB565A8_124x76);
    lv_image_set_pivot(ui->screen_focus_img_focus_stats, 50,50);
    lv_image_set_rotation(ui->screen_focus_img_focus_stats, 0);

    //Write style for screen_focus_img_focus_stats, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_focus_img_focus_stats, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_focus_img_focus_stats, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_focus_img_focus_tomato
    ui->screen_focus_img_focus_tomato = lv_image_create(ui->screen_focus);
    lv_obj_set_pos(ui->screen_focus_img_focus_tomato, 252, 12);
    lv_obj_set_size(ui->screen_focus_img_focus_tomato, 38, 38);
    lv_obj_add_flag(ui->screen_focus_img_focus_tomato, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_focus_img_focus_tomato, &_focus_tomato_RGB565A8_38x38);
    lv_image_set_pivot(ui->screen_focus_img_focus_tomato, 50,50);
    lv_image_set_rotation(ui->screen_focus_img_focus_tomato, 0);

    //Write style for screen_focus_img_focus_tomato, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_focus_img_focus_tomato, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_focus_img_focus_tomato, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_focus_img_focus_fill
    ui->screen_focus_img_focus_fill = lv_image_create(ui->screen_focus);
    lv_obj_set_pos(ui->screen_focus_img_focus_fill, 20, 190);
    lv_obj_set_size(ui->screen_focus_img_focus_fill, 140, 16);
    lv_obj_add_flag(ui->screen_focus_img_focus_fill, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_focus_img_focus_fill, &_focus_progress_fill_RGB565A8_140x16);
    lv_image_set_pivot(ui->screen_focus_img_focus_fill, 50,50);
    lv_image_set_rotation(ui->screen_focus_img_focus_fill, 0);

    //Write style for screen_focus_img_focus_fill, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_focus_img_focus_fill, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_focus_img_focus_fill, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_focus_img_focus_bg
    ui->screen_focus_img_focus_bg = lv_image_create(ui->screen_focus);
    lv_obj_set_pos(ui->screen_focus_img_focus_bg, 160, 60);
    lv_obj_set_size(ui->screen_focus_img_focus_bg, 150, 120);
    lv_obj_add_flag(ui->screen_focus_img_focus_bg, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_focus_img_focus_bg, &_focus_progress_bg_RGB565A8_150x120);
    lv_image_set_pivot(ui->screen_focus_img_focus_bg, 50,50);
    lv_image_set_rotation(ui->screen_focus_img_focus_bg, 0);

    //Write style for screen_focus_img_focus_bg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_focus_img_focus_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_focus_img_focus_bg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_focus_label_focus_title
    ui->screen_focus_label_focus_title = lv_label_create(ui->screen_focus);
    lv_obj_set_pos(ui->screen_focus_label_focus_title, 16, 12);
    lv_obj_set_size(ui->screen_focus_label_focus_title, 80, 22);
    lv_label_set_text(ui->screen_focus_label_focus_title, "Focus");
    lv_label_set_long_mode(ui->screen_focus_label_focus_title, LV_LABEL_LONG_CLIP);

    //Write style for screen_focus_label_focus_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_focus_label_focus_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_focus_label_focus_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_focus_label_focus_title, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_focus_label_focus_title, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_focus_label_focus_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_focus_label_focus_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_focus_label_focus_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_focus_label_focus_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_focus_label_focus_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_focus_label_focus_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_focus_label_focus_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_focus_label_focus_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_focus_label_focus_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_focus_label_focus_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_focus.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_focus);

}
