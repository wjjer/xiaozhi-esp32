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



void setup_scr_screen_ai(lv_ui *ui)
{
    //Write codes screen_ai
    ui->screen_ai = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_ai, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_ai, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_ai, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_ai, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_ai, lv_color_hex(0xEFF6FF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_ai, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_ai_label_ai_quick
    ui->screen_ai_label_ai_quick = lv_label_create(ui->screen_ai);
    lv_obj_set_pos(ui->screen_ai_label_ai_quick, 188, 188);
    lv_obj_set_size(ui->screen_ai_label_ai_quick, 102, 14);
    lv_label_set_text(ui->screen_ai_label_ai_quick, "Quick questions");
    lv_label_set_long_mode(ui->screen_ai_label_ai_quick, LV_LABEL_LONG_CLIP);

    //Write style for screen_ai_label_ai_quick, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_ai_label_ai_quick, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ai_label_ai_quick, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_ai_label_ai_quick, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_ai_label_ai_quick, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_ai_label_ai_quick, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_ai_label_ai_quick, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_ai_label_ai_quick, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_ai_label_ai_quick, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_ai_label_ai_quick, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_ai_label_ai_quick, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_ai_label_ai_quick, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_ai_label_ai_quick, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_ai_label_ai_quick, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_ai_label_ai_quick, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_ai_ai_quick_question_bg
    ui->screen_ai_ai_quick_question_bg = lv_image_create(ui->screen_ai);
    lv_obj_set_pos(ui->screen_ai_ai_quick_question_bg, 174, 174);
    lv_obj_set_size(ui->screen_ai_ai_quick_question_bg, 132, 44);
    lv_obj_add_flag(ui->screen_ai_ai_quick_question_bg, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_ai_ai_quick_question_bg, &_quick_question_bg_RGB565A8_132x44);
    lv_image_set_pivot(ui->screen_ai_ai_quick_question_bg, 50,50);
    lv_image_set_rotation(ui->screen_ai_ai_quick_question_bg, 0);

    //Write style for screen_ai_ai_quick_question_bg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_ai_ai_quick_question_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_ai_ai_quick_question_bg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_ai_ai_message_label
    ui->screen_ai_ai_message_label = lv_label_create(ui->screen_ai);
    lv_obj_set_pos(ui->screen_ai_ai_message_label, 128, 42);
    lv_obj_set_size(ui->screen_ai_ai_message_label, 150, 56);
    lv_label_set_text(ui->screen_ai_ai_message_label, "Ask me anything.");
    lv_label_set_long_mode(ui->screen_ai_ai_message_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_ai_ai_message_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_ai_ai_message_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ai_ai_message_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_ai_ai_message_label, lv_color_hex(0x5C628B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_ai_ai_message_label, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_ai_ai_message_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_ai_ai_message_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_ai_ai_message_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_ai_ai_message_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_ai_ai_message_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_ai_ai_message_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_ai_ai_message_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_ai_ai_message_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_ai_ai_message_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_ai_ai_message_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_ai_ai_state_label
    ui->screen_ai_ai_state_label = lv_label_create(ui->screen_ai);
    lv_obj_set_pos(ui->screen_ai_ai_state_label, 128, 16);
    lv_obj_set_size(ui->screen_ai_ai_state_label, 120, 20);
    lv_label_set_text(ui->screen_ai_ai_state_label, "Waiting");
    lv_label_set_long_mode(ui->screen_ai_ai_state_label, LV_LABEL_LONG_CLIP);

    //Write style for screen_ai_ai_state_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_ai_ai_state_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_ai_ai_state_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_ai_ai_state_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_ai_ai_state_label, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_ai_ai_state_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_ai_ai_state_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_ai_ai_state_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_ai_ai_state_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_ai_ai_state_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_ai_ai_state_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_ai_ai_state_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_ai_ai_state_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_ai_ai_state_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_ai_ai_state_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_ai_ai_state_icon
    ui->screen_ai_ai_state_icon = lv_image_create(ui->screen_ai);
    lv_obj_set_pos(ui->screen_ai_ai_state_icon, 28, 176);
    lv_obj_set_size(ui->screen_ai_ai_state_icon, 46, 46);
    lv_obj_add_flag(ui->screen_ai_ai_state_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_ai_ai_state_icon, &_mic_button_idle_RGB565A8_46x46);
    lv_image_set_pivot(ui->screen_ai_ai_state_icon, 50,50);
    lv_image_set_rotation(ui->screen_ai_ai_state_icon, 0);

    //Write style for screen_ai_ai_state_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_ai_ai_state_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_ai_ai_state_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_ai_ai_character_image
    ui->screen_ai_ai_character_image = lv_image_create(ui->screen_ai);
    lv_obj_set_pos(ui->screen_ai_ai_character_image, 18, 78);
    lv_obj_set_size(ui->screen_ai_ai_character_image, 110, 110);
    lv_obj_add_flag(ui->screen_ai_ai_character_image, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_ai_ai_character_image, &_ai_character_idle_RGB565A8_110x110);
    lv_image_set_pivot(ui->screen_ai_ai_character_image, 50,50);
    lv_image_set_rotation(ui->screen_ai_ai_character_image, 0);

    //Write style for screen_ai_ai_character_image, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_ai_ai_character_image, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_ai_ai_character_image, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_ai_img_ai_bubble
    ui->screen_ai_img_ai_bubble = lv_image_create(ui->screen_ai);
    lv_obj_set_pos(ui->screen_ai_img_ai_bubble, 8, 56);
    lv_obj_set_size(ui->screen_ai_img_ai_bubble, 304, 176);
    lv_obj_add_flag(ui->screen_ai_img_ai_bubble, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_ai_img_ai_bubble, &_speech_bubble_RGB565A8_304x176);
    lv_image_set_pivot(ui->screen_ai_img_ai_bubble, 50,50);
    lv_image_set_rotation(ui->screen_ai_img_ai_bubble, 0);

    //Write style for screen_ai_img_ai_bubble, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_ai_img_ai_bubble, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_ai_img_ai_bubble, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_ai.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_ai);

}
