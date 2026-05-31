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



void setup_scr_screen_night_light(lv_ui *ui)
{
    //Write codes screen_night_light
    ui->screen_night_light = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_night_light, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_night_light, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_night_light, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_night_light, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_night_light, lv_color_hex(0xFFF7D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_night_light, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_night_light_img_night_thumb
    ui->screen_night_light_img_night_thumb = lv_image_create(ui->screen_night_light);
    lv_obj_set_pos(ui->screen_night_light_img_night_thumb, 164, 134);
    lv_obj_set_size(ui->screen_night_light_img_night_thumb, 24, 24);
    lv_obj_add_flag(ui->screen_night_light_img_night_thumb, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_night_light_img_night_thumb, &_slider_thumb_RGB565A8_24x24);
    lv_image_set_pivot(ui->screen_night_light_img_night_thumb, 50,50);
    lv_image_set_rotation(ui->screen_night_light_img_night_thumb, 0);

    //Write style for screen_night_light_img_night_thumb, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_night_light_img_night_thumb, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_night_light_img_night_thumb, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_night_light_img_night_slider
    ui->screen_night_light_img_night_slider = lv_image_create(ui->screen_night_light);
    lv_obj_set_pos(ui->screen_night_light_img_night_slider, 86, 146);
    lv_obj_set_size(ui->screen_night_light_img_night_slider, 148, 16);
    lv_obj_add_flag(ui->screen_night_light_img_night_slider, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_night_light_img_night_slider, &_slider_bg_RGB565A8_148x16);
    lv_image_set_pivot(ui->screen_night_light_img_night_slider, 50,50);
    lv_image_set_rotation(ui->screen_night_light_img_night_slider, 0);

    //Write style for screen_night_light_img_night_slider, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_night_light_img_night_slider, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_night_light_img_night_slider, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_night_light_img_night_toggle
    ui->screen_night_light_img_night_toggle = lv_image_create(ui->screen_night_light);
    lv_obj_set_pos(ui->screen_night_light_img_night_toggle, 20, 178);
    lv_obj_set_size(ui->screen_night_light_img_night_toggle, 92, 36);
    lv_obj_add_flag(ui->screen_night_light_img_night_toggle, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_night_light_img_night_toggle, &_button_toggle_light_RGB565A8_92x36);
    lv_image_set_pivot(ui->screen_night_light_img_night_toggle, 50,50);
    lv_image_set_rotation(ui->screen_night_light_img_night_toggle, 0);

    //Write style for screen_night_light_img_night_toggle, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_night_light_img_night_toggle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_night_light_img_night_toggle, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_night_light_img_night_bg
    ui->screen_night_light_img_night_bg = lv_image_create(ui->screen_night_light);
    lv_obj_set_pos(ui->screen_night_light_img_night_bg, 180, 50);
    lv_obj_set_size(ui->screen_night_light_img_night_bg, 110, 130);
    lv_obj_add_flag(ui->screen_night_light_img_night_bg, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_night_light_img_night_bg, &_night_light_off_RGB565A8_110x130);
    lv_image_set_pivot(ui->screen_night_light_img_night_bg, 50,50);
    lv_image_set_rotation(ui->screen_night_light_img_night_bg, 0);

    //Write style for screen_night_light_img_night_bg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_night_light_img_night_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_night_light_img_night_bg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_night_light_label_night_title
    ui->screen_night_light_label_night_title = lv_label_create(ui->screen_night_light);
    lv_obj_set_pos(ui->screen_night_light_label_night_title, 16, 12);
    lv_obj_set_size(ui->screen_night_light_label_night_title, 120, 22);
    lv_label_set_text(ui->screen_night_light_label_night_title, "Night Light");
    lv_label_set_long_mode(ui->screen_night_light_label_night_title, LV_LABEL_LONG_CLIP);

    //Write style for screen_night_light_label_night_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_night_light_label_night_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_night_light_label_night_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_night_light_label_night_title, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_night_light_label_night_title, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_night_light_label_night_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_night_light_label_night_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_night_light_label_night_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_night_light_label_night_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_night_light_label_night_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_night_light_label_night_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_night_light_label_night_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_night_light_label_night_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_night_light_label_night_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_night_light_label_night_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_night_light.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_night_light);

}
