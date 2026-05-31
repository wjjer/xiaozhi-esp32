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



void setup_scr_screen_stopwatch(lv_ui *ui)
{
    //Write codes screen_stopwatch
    ui->screen_stopwatch = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_stopwatch, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_stopwatch, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_stopwatch, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_stopwatch, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_stopwatch, lv_color_hex(0xF2FFF7), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_stopwatch, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_stopwatch_cont_stopwatch_panel
    ui->screen_stopwatch_cont_stopwatch_panel = lv_obj_create(ui->screen_stopwatch);
    lv_obj_set_pos(ui->screen_stopwatch_cont_stopwatch_panel, 14, 58);
    lv_obj_set_size(ui->screen_stopwatch_cont_stopwatch_panel, 172, 158);
    lv_obj_set_scrollbar_mode(ui->screen_stopwatch_cont_stopwatch_panel, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_stopwatch_cont_stopwatch_panel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_stopwatch_cont_stopwatch_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_stopwatch_cont_stopwatch_panel, 18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_stopwatch_cont_stopwatch_panel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_stopwatch_cont_stopwatch_panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_stopwatch_cont_stopwatch_panel, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_stopwatch_cont_stopwatch_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_stopwatch_cont_stopwatch_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_stopwatch_cont_stopwatch_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_stopwatch_cont_stopwatch_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_stopwatch_cont_stopwatch_panel, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_stopwatch_cont_stopwatch_panel, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_stopwatch_cont_stopwatch_panel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_stopwatch_cont_stopwatch_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_stopwatch_cont_stopwatch_panel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_stopwatch_cont_stopwatch_panel, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_stopwatch_label_stopwatch_lap
    ui->screen_stopwatch_label_stopwatch_lap = lv_label_create(ui->screen_stopwatch_cont_stopwatch_panel);
    lv_obj_set_pos(ui->screen_stopwatch_label_stopwatch_lap, 20, 54);
    lv_obj_set_size(ui->screen_stopwatch_label_stopwatch_lap, 80, 14);
    lv_label_set_text(ui->screen_stopwatch_label_stopwatch_lap, "Lap 01");
    lv_label_set_long_mode(ui->screen_stopwatch_label_stopwatch_lap, LV_LABEL_LONG_CLIP);

    //Write style for screen_stopwatch_label_stopwatch_lap, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_stopwatch_label_stopwatch_lap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_stopwatch_label_stopwatch_lap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_stopwatch_label_stopwatch_lap, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_stopwatch_label_stopwatch_lap, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_stopwatch_label_stopwatch_lap, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_stopwatch_label_stopwatch_lap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_stopwatch_label_stopwatch_lap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_stopwatch_label_stopwatch_lap, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_stopwatch_label_stopwatch_lap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_stopwatch_label_stopwatch_lap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_stopwatch_label_stopwatch_lap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_stopwatch_label_stopwatch_lap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_stopwatch_label_stopwatch_lap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_stopwatch_label_stopwatch_lap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_stopwatch_img_stopwatch_lap
    ui->screen_stopwatch_img_stopwatch_lap = lv_image_create(ui->screen_stopwatch_cont_stopwatch_panel);
    lv_obj_set_pos(ui->screen_stopwatch_img_stopwatch_lap, 0, 48);
    lv_obj_set_size(ui->screen_stopwatch_img_stopwatch_lap, 120, 28);
    lv_obj_add_flag(ui->screen_stopwatch_img_stopwatch_lap, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_stopwatch_img_stopwatch_lap, &_lap_item_bg_RGB565A8_120x28);
    lv_image_set_pivot(ui->screen_stopwatch_img_stopwatch_lap, 50,50);
    lv_image_set_rotation(ui->screen_stopwatch_img_stopwatch_lap, 0);

    //Write style for screen_stopwatch_img_stopwatch_lap, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_stopwatch_img_stopwatch_lap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_stopwatch_img_stopwatch_lap, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_stopwatch_label_stopwatch_time
    ui->screen_stopwatch_label_stopwatch_time = lv_label_create(ui->screen_stopwatch_cont_stopwatch_panel);
    lv_obj_set_pos(ui->screen_stopwatch_label_stopwatch_time, 0, 0);
    lv_obj_set_size(ui->screen_stopwatch_label_stopwatch_time, 120, 30);
    lv_label_set_text(ui->screen_stopwatch_label_stopwatch_time, "00:12.45");
    lv_label_set_long_mode(ui->screen_stopwatch_label_stopwatch_time, LV_LABEL_LONG_CLIP);

    //Write style for screen_stopwatch_label_stopwatch_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_stopwatch_label_stopwatch_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_stopwatch_label_stopwatch_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_stopwatch_label_stopwatch_time, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_stopwatch_label_stopwatch_time, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_stopwatch_label_stopwatch_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_stopwatch_label_stopwatch_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_stopwatch_label_stopwatch_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_stopwatch_label_stopwatch_time, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_stopwatch_label_stopwatch_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_stopwatch_label_stopwatch_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_stopwatch_label_stopwatch_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_stopwatch_label_stopwatch_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_stopwatch_label_stopwatch_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_stopwatch_label_stopwatch_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_stopwatch_label_stopwatch_title
    ui->screen_stopwatch_label_stopwatch_title = lv_label_create(ui->screen_stopwatch);
    lv_obj_set_pos(ui->screen_stopwatch_label_stopwatch_title, 16, 12);
    lv_obj_set_size(ui->screen_stopwatch_label_stopwatch_title, 110, 22);
    lv_label_set_text(ui->screen_stopwatch_label_stopwatch_title, "Stopwatch");
    lv_label_set_long_mode(ui->screen_stopwatch_label_stopwatch_title, LV_LABEL_LONG_CLIP);

    //Write style for screen_stopwatch_label_stopwatch_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_stopwatch_label_stopwatch_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_stopwatch_label_stopwatch_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_stopwatch_label_stopwatch_title, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_stopwatch_label_stopwatch_title, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_stopwatch_label_stopwatch_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_stopwatch_label_stopwatch_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_stopwatch_label_stopwatch_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_stopwatch_label_stopwatch_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_stopwatch_label_stopwatch_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_stopwatch_label_stopwatch_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_stopwatch_label_stopwatch_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_stopwatch_label_stopwatch_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_stopwatch_label_stopwatch_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_stopwatch_label_stopwatch_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_stopwatch_img_stopwatch_bg
    ui->screen_stopwatch_img_stopwatch_bg = lv_image_create(ui->screen_stopwatch);
    lv_obj_set_pos(ui->screen_stopwatch_img_stopwatch_bg, 174, 54);
    lv_obj_set_size(ui->screen_stopwatch_img_stopwatch_bg, 136, 132);
    lv_obj_add_flag(ui->screen_stopwatch_img_stopwatch_bg, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_stopwatch_img_stopwatch_bg, &_stopwatch_bg_RGB565A8_136x132);
    lv_image_set_pivot(ui->screen_stopwatch_img_stopwatch_bg, 50,50);
    lv_image_set_rotation(ui->screen_stopwatch_img_stopwatch_bg, 0);

    //Write style for screen_stopwatch_img_stopwatch_bg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_stopwatch_img_stopwatch_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_stopwatch_img_stopwatch_bg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_stopwatch.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_stopwatch);

}
