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



void setup_scr_screen_study(lv_ui *ui)
{
    //Write codes screen_study
    ui->screen_study = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_study, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_study, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_study, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_study, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_study, lv_color_hex(0xF4FFF6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_study, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_study_label_study_note
    ui->screen_study_label_study_note = lv_label_create(ui->screen_study);
    lv_obj_set_pos(ui->screen_study_label_study_note, 20, 216);
    lv_obj_set_size(ui->screen_study_label_study_note, 280, 16);
    lv_label_set_text(ui->screen_study_label_study_note, "Vocabulary / history / wordbook / K12 pending");
    lv_label_set_long_mode(ui->screen_study_label_study_note, LV_LABEL_LONG_CLIP);

    //Write style for screen_study_label_study_note, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_study_label_study_note, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_study_label_study_note, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_study_label_study_note, lv_color_hex(0x5C628B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_study_label_study_note, &lv_font_montserratMedium_11, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_study_label_study_note, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_study_label_study_note, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_study_label_study_note, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_study_label_study_note, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_study_label_study_note, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_study_label_study_note, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_study_label_study_note, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_study_label_study_note, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_study_label_study_note, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_study_label_study_note, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_study_cont_study_main
    ui->screen_study_cont_study_main = lv_obj_create(ui->screen_study);
    lv_obj_set_pos(ui->screen_study_cont_study_main, 16, 36);
    lv_obj_set_size(ui->screen_study_cont_study_main, 288, 176);
    lv_obj_set_scrollbar_mode(ui->screen_study_cont_study_main, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_study_cont_study_main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_study_cont_study_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_study_cont_study_main, 18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_study_cont_study_main, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_study_cont_study_main, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_study_cont_study_main, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_study_cont_study_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_study_cont_study_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_study_cont_study_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_study_cont_study_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_study_cont_study_main, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_study_cont_study_main, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_study_cont_study_main, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_study_cont_study_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_study_cont_study_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_study_cont_study_main, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_study_study_k12
    ui->screen_study_study_k12 = lv_obj_create(ui->screen_study_cont_study_main);
    lv_obj_set_pos(ui->screen_study_study_k12, 150, 92);
    lv_obj_set_size(ui->screen_study_study_k12, 126, 72);
    lv_obj_set_scrollbar_mode(ui->screen_study_study_k12, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_study_study_k12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_study_study_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_study_study_k12, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_study_study_k12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_study_study_k12, lv_color_hex(0xF9FBFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_study_study_k12, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_study_study_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_study_study_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_study_study_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_study_study_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_study_study_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_study_label_k12
    ui->screen_study_label_k12 = lv_label_create(ui->screen_study_study_k12);
    lv_obj_set_pos(ui->screen_study_label_k12, 52, 12);
    lv_obj_set_size(ui->screen_study_label_k12, 60, 18);
    lv_label_set_text(ui->screen_study_label_k12, "K12");
    lv_label_set_long_mode(ui->screen_study_label_k12, LV_LABEL_LONG_CLIP);

    //Write style for screen_study_label_k12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_study_label_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_study_label_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_study_label_k12, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_study_label_k12, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_study_label_k12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_study_label_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_study_label_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_study_label_k12, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_study_label_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_study_label_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_study_label_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_study_label_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_study_label_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_study_label_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_study_img_k12
    ui->screen_study_img_k12 = lv_image_create(ui->screen_study_study_k12);
    lv_obj_set_pos(ui->screen_study_img_k12, 12, 10);
    lv_obj_set_size(ui->screen_study_img_k12, 32, 32);
    lv_obj_add_flag(ui->screen_study_img_k12, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_study_img_k12, &_placeholder_icon_k12_RGB565A8_32x32);
    lv_image_set_pivot(ui->screen_study_img_k12, 50,50);
    lv_image_set_rotation(ui->screen_study_img_k12, 0);

    //Write style for screen_study_img_k12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_study_img_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_study_img_k12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_study_study_vocab
    ui->screen_study_study_vocab = lv_obj_create(ui->screen_study_cont_study_main);
    lv_obj_set_pos(ui->screen_study_study_vocab, 12, 92);
    lv_obj_set_size(ui->screen_study_study_vocab, 126, 72);
    lv_obj_set_scrollbar_mode(ui->screen_study_study_vocab, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_study_study_vocab, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_study_study_vocab, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_study_study_vocab, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_study_study_vocab, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_study_study_vocab, lv_color_hex(0xF9FBFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_study_study_vocab, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_study_study_vocab, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_study_study_vocab, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_study_study_vocab, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_study_study_vocab, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_study_study_vocab, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_study_label_vocab
    ui->screen_study_label_vocab = lv_label_create(ui->screen_study_study_vocab);
    lv_obj_set_pos(ui->screen_study_label_vocab, 52, 12);
    lv_obj_set_size(ui->screen_study_label_vocab, 60, 18);
    lv_label_set_text(ui->screen_study_label_vocab, "Vocabulary");
    lv_label_set_long_mode(ui->screen_study_label_vocab, LV_LABEL_LONG_CLIP);

    //Write style for screen_study_label_vocab, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_study_label_vocab, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_study_label_vocab, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_study_label_vocab, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_study_label_vocab, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_study_label_vocab, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_study_label_vocab, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_study_label_vocab, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_study_label_vocab, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_study_label_vocab, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_study_label_vocab, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_study_label_vocab, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_study_label_vocab, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_study_label_vocab, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_study_label_vocab, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_study_img_vocab
    ui->screen_study_img_vocab = lv_image_create(ui->screen_study_study_vocab);
    lv_obj_set_pos(ui->screen_study_img_vocab, 12, 10);
    lv_obj_set_size(ui->screen_study_img_vocab, 32, 32);
    lv_obj_add_flag(ui->screen_study_img_vocab, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_study_img_vocab, &_placeholder_icon_vocabulary_RGB565A8_32x32);
    lv_image_set_pivot(ui->screen_study_img_vocab, 50,50);
    lv_image_set_rotation(ui->screen_study_img_vocab, 0);

    //Write style for screen_study_img_vocab, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_study_img_vocab, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_study_img_vocab, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_study_study_wordbook
    ui->screen_study_study_wordbook = lv_obj_create(ui->screen_study_cont_study_main);
    lv_obj_set_pos(ui->screen_study_study_wordbook, 150, 12);
    lv_obj_set_size(ui->screen_study_study_wordbook, 126, 72);
    lv_obj_set_scrollbar_mode(ui->screen_study_study_wordbook, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_study_study_wordbook, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_study_study_wordbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_study_study_wordbook, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_study_study_wordbook, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_study_study_wordbook, lv_color_hex(0xF9FBFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_study_study_wordbook, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_study_study_wordbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_study_study_wordbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_study_study_wordbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_study_study_wordbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_study_study_wordbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_study_label_wordbook
    ui->screen_study_label_wordbook = lv_label_create(ui->screen_study_study_wordbook);
    lv_obj_set_pos(ui->screen_study_label_wordbook, 52, 12);
    lv_obj_set_size(ui->screen_study_label_wordbook, 60, 18);
    lv_label_set_text(ui->screen_study_label_wordbook, "Wordbook");
    lv_label_set_long_mode(ui->screen_study_label_wordbook, LV_LABEL_LONG_CLIP);

    //Write style for screen_study_label_wordbook, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_study_label_wordbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_study_label_wordbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_study_label_wordbook, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_study_label_wordbook, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_study_label_wordbook, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_study_label_wordbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_study_label_wordbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_study_label_wordbook, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_study_label_wordbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_study_label_wordbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_study_label_wordbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_study_label_wordbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_study_label_wordbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_study_label_wordbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_study_img_wordbook
    ui->screen_study_img_wordbook = lv_image_create(ui->screen_study_study_wordbook);
    lv_obj_set_pos(ui->screen_study_img_wordbook, 12, 10);
    lv_obj_set_size(ui->screen_study_img_wordbook, 32, 32);
    lv_obj_add_flag(ui->screen_study_img_wordbook, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_study_img_wordbook, &_placeholder_icon_word_study_RGB565A8_32x32);
    lv_image_set_pivot(ui->screen_study_img_wordbook, 50,50);
    lv_image_set_rotation(ui->screen_study_img_wordbook, 0);

    //Write style for screen_study_img_wordbook, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_study_img_wordbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_study_img_wordbook, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_study_study_dictionary
    ui->screen_study_study_dictionary = lv_obj_create(ui->screen_study_cont_study_main);
    lv_obj_set_pos(ui->screen_study_study_dictionary, 12, 12);
    lv_obj_set_size(ui->screen_study_study_dictionary, 126, 72);
    lv_obj_set_scrollbar_mode(ui->screen_study_study_dictionary, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_study_study_dictionary, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_study_study_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_study_study_dictionary, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_study_study_dictionary, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_study_study_dictionary, lv_color_hex(0xF9FBFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_study_study_dictionary, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_study_study_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_study_study_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_study_study_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_study_study_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_study_study_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_study_label_dictionary
    ui->screen_study_label_dictionary = lv_label_create(ui->screen_study_study_dictionary);
    lv_obj_set_pos(ui->screen_study_label_dictionary, 52, 12);
    lv_obj_set_size(ui->screen_study_label_dictionary, 60, 18);
    lv_label_set_text(ui->screen_study_label_dictionary, "Translate");
    lv_label_set_long_mode(ui->screen_study_label_dictionary, LV_LABEL_LONG_CLIP);

    //Write style for screen_study_label_dictionary, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_study_label_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_study_label_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_study_label_dictionary, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_study_label_dictionary, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_study_label_dictionary, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_study_label_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_study_label_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_study_label_dictionary, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_study_label_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_study_label_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_study_label_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_study_label_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_study_label_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_study_label_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_study_img_dictionary
    ui->screen_study_img_dictionary = lv_image_create(ui->screen_study_study_dictionary);
    lv_obj_set_pos(ui->screen_study_img_dictionary, 12, 10);
    lv_obj_set_size(ui->screen_study_img_dictionary, 32, 32);
    lv_obj_add_flag(ui->screen_study_img_dictionary, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_study_img_dictionary, &_placeholder_icon_dictionary_RGB565A8_32x32);
    lv_image_set_pivot(ui->screen_study_img_dictionary, 50,50);
    lv_image_set_rotation(ui->screen_study_img_dictionary, 0);

    //Write style for screen_study_img_dictionary, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_study_img_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_study_img_dictionary, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_study_img_study_bg
    ui->screen_study_img_study_bg = lv_image_create(ui->screen_study);
    lv_obj_set_pos(ui->screen_study_img_study_bg, 0, 0);
    lv_obj_set_size(ui->screen_study_img_study_bg, 320, 240);
    lv_obj_add_flag(ui->screen_study_img_study_bg, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_study_img_study_bg, &_placeholder_msg_bg_RGB565A8_320x240);
    lv_image_set_pivot(ui->screen_study_img_study_bg, 50,50);
    lv_image_set_rotation(ui->screen_study_img_study_bg, 0);

    //Write style for screen_study_img_study_bg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_study_img_study_bg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_study_img_study_bg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_study.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_study);

}
