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



void setup_scr_screen_boot(lv_ui *ui)
{
    //Write codes screen_boot
    ui->screen_boot = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_boot, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_boot, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_boot, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_boot, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_boot, lv_color_hex(0x10131A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_boot, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_boot_boot_hint_label
    ui->screen_boot_boot_hint_label = lv_label_create(ui->screen_boot);
    lv_obj_set_pos(ui->screen_boot_boot_hint_label, 118, 206);
    lv_obj_set_size(ui->screen_boot_boot_hint_label, 84, 18);
    lv_label_set_text(ui->screen_boot_boot_hint_label, "AI Alarm");
    lv_label_set_long_mode(ui->screen_boot_boot_hint_label, LV_LABEL_LONG_CLIP);

    //Write style for screen_boot_boot_hint_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_boot_boot_hint_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_boot_boot_hint_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_boot_boot_hint_label, lv_color_hex(0xE8ECFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_boot_boot_hint_label, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_boot_boot_hint_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_boot_boot_hint_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_boot_boot_hint_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_boot_boot_hint_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_boot_boot_hint_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_boot_boot_hint_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_boot_boot_hint_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_boot_boot_hint_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_boot_boot_hint_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_boot_boot_hint_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_boot_boot_spinner_image
    ui->screen_boot_boot_spinner_image = lv_image_create(ui->screen_boot);
    lv_obj_set_pos(ui->screen_boot_boot_spinner_image, 148, 178);
    lv_obj_set_size(ui->screen_boot_boot_spinner_image, 24, 24);
    lv_obj_add_flag(ui->screen_boot_boot_spinner_image, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_boot_boot_spinner_image, &_loading_spinner_1_RGB565A8_24x24);
    lv_image_set_pivot(ui->screen_boot_boot_spinner_image, 50,50);
    lv_image_set_rotation(ui->screen_boot_boot_spinner_image, 0);

    //Write style for screen_boot_boot_spinner_image, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_boot_boot_spinner_image, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_boot_boot_spinner_image, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_boot_boot_logo_image
    ui->screen_boot_boot_logo_image = lv_image_create(ui->screen_boot);
    lv_obj_set_pos(ui->screen_boot_boot_logo_image, 110, 54);
    lv_obj_set_size(ui->screen_boot_boot_logo_image, 100, 100);
    lv_obj_add_flag(ui->screen_boot_boot_logo_image, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_boot_boot_logo_image, &_launch_logo_RGB565A8_100x100);
    lv_image_set_pivot(ui->screen_boot_boot_logo_image, 50,50);
    lv_image_set_rotation(ui->screen_boot_boot_logo_image, 0);

    //Write style for screen_boot_boot_logo_image, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_boot_boot_logo_image, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_boot_boot_logo_image, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_boot.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_boot);

}
