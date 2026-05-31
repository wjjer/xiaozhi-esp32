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



void setup_scr_screen_home(lv_ui *ui)
{
    //Write codes screen_home
    ui->screen_home = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_home, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_home, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home, lv_color_hex(0xF3F7FF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_home_cards_container
    ui->screen_home_home_cards_container = lv_obj_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_home_cards_container, 12, 120);
    lv_obj_set_size(ui->screen_home_home_cards_container, 296, 104);
    lv_obj_set_scrollbar_mode(ui->screen_home_home_cards_container, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_home_cards_container, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_home_cards_container, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_home_cards_container, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_home_cards_container, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_home_cards_container, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_home_cards_container, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_home_cards_container, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_home_cards_container, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_home_cards_container, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_tools
    ui->screen_home_card_tools = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_tools, 1440, 8);
    lv_obj_set_size(ui->screen_home_card_tools, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_tools, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_tools, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_tools, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_tools, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_tools, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_tools, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_tools, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_tools, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_tools, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_tools, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_tools, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_tools, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_tools, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_tools, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_tools, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_tools, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_tools, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_tools_label
    ui->screen_home_card_tools_label = lv_label_create(ui->screen_home_card_tools);
    lv_obj_set_pos(ui->screen_home_card_tools_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_tools_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_tools_label, "工具");
    lv_label_set_long_mode(ui->screen_home_card_tools_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_tools_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_tools_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_tools_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_tools_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_tools_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_tools_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_tools_img
    ui->screen_home_card_tools_img = lv_image_create(ui->screen_home_card_tools);
    lv_obj_set_pos(ui->screen_home_card_tools_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_tools_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_tools_img, &_icon_tools_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_tools_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_tools_img, 0);

    //Write style for screen_home_card_tools_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_tools_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_tools_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_focus
    ui->screen_home_card_focus = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_focus, 1368, 8);
    lv_obj_set_size(ui->screen_home_card_focus, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_focus, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_focus, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_focus, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_focus, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_focus, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_focus, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_focus, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_focus, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_focus, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_focus, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_focus, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_focus, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_focus, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_focus, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_focus, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_focus, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_focus, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_focus_label
    ui->screen_home_card_focus_label = lv_label_create(ui->screen_home_card_focus);
    lv_obj_set_pos(ui->screen_home_card_focus_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_focus_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_focus_label, "专注时间");
    lv_label_set_long_mode(ui->screen_home_card_focus_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_focus_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_focus_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_focus_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_focus_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_focus_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_focus_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_focus_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_focus_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_focus_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_focus_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_focus_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_focus_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_focus_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_focus_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_focus_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_focus_img
    ui->screen_home_card_focus_img = lv_image_create(ui->screen_home_card_focus);
    lv_obj_set_pos(ui->screen_home_card_focus_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_focus_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_focus_img, &_focus_home_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_focus_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_focus_img, 0);

    //Write style for screen_home_card_focus_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_focus_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_focus_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_stopwatch
    ui->screen_home_card_stopwatch = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_stopwatch, 1296, 8);
    lv_obj_set_size(ui->screen_home_card_stopwatch, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_stopwatch, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_stopwatch, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_stopwatch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_stopwatch, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_stopwatch, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_stopwatch, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_stopwatch, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_stopwatch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_stopwatch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_stopwatch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_stopwatch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_stopwatch, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_stopwatch, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_stopwatch, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_stopwatch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_stopwatch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_stopwatch, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_stopwatch_label
    ui->screen_home_card_stopwatch_label = lv_label_create(ui->screen_home_card_stopwatch);
    lv_obj_set_pos(ui->screen_home_card_stopwatch_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_stopwatch_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_stopwatch_label, "秒表");
    lv_label_set_long_mode(ui->screen_home_card_stopwatch_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_stopwatch_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_stopwatch_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_stopwatch_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_stopwatch_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_stopwatch_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_stopwatch_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_stopwatch_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_stopwatch_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_stopwatch_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_stopwatch_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_stopwatch_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_stopwatch_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_stopwatch_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_stopwatch_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_stopwatch_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_stopwatch_img
    ui->screen_home_card_stopwatch_img = lv_image_create(ui->screen_home_card_stopwatch);
    lv_obj_set_pos(ui->screen_home_card_stopwatch_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_stopwatch_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_stopwatch_img, &_stopwatch_home_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_stopwatch_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_stopwatch_img, 0);

    //Write style for screen_home_card_stopwatch_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_stopwatch_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_stopwatch_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_timer
    ui->screen_home_card_timer = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_timer, 1224, 8);
    lv_obj_set_size(ui->screen_home_card_timer, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_timer, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_timer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_timer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_timer, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_timer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_timer, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_timer, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_timer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_timer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_timer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_timer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_timer, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_timer, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_timer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_timer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_timer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_timer, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_timer_label
    ui->screen_home_card_timer_label = lv_label_create(ui->screen_home_card_timer);
    lv_obj_set_pos(ui->screen_home_card_timer_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_timer_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_timer_label, "倒计时");
    lv_label_set_long_mode(ui->screen_home_card_timer_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_timer_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_timer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_timer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_timer_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_timer_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_timer_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_timer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_timer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_timer_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_timer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_timer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_timer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_timer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_timer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_timer_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_timer_img
    ui->screen_home_card_timer_img = lv_image_create(ui->screen_home_card_timer);
    lv_obj_set_pos(ui->screen_home_card_timer_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_timer_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_timer_img, &_button_timer_home_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_timer_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_timer_img, 0);

    //Write style for screen_home_card_timer_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_timer_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_timer_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_all_subject_study
    ui->screen_home_card_all_subject_study = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_all_subject_study, 1152, 8);
    lv_obj_set_size(ui->screen_home_card_all_subject_study, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_all_subject_study, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_all_subject_study, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_all_subject_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_all_subject_study, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_all_subject_study, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_all_subject_study, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_all_subject_study, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_all_subject_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_all_subject_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_all_subject_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_all_subject_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_all_subject_study, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_all_subject_study, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_all_subject_study, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_all_subject_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_all_subject_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_all_subject_study, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_all_subject_study_label
    ui->screen_home_card_all_subject_study_label = lv_label_create(ui->screen_home_card_all_subject_study);
    lv_obj_set_pos(ui->screen_home_card_all_subject_study_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_all_subject_study_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_all_subject_study_label, "全科学习");
    lv_label_set_long_mode(ui->screen_home_card_all_subject_study_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_all_subject_study_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_all_subject_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_all_subject_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_all_subject_study_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_all_subject_study_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_all_subject_study_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_all_subject_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_all_subject_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_all_subject_study_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_all_subject_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_all_subject_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_all_subject_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_all_subject_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_all_subject_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_all_subject_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_all_subject_study_img
    ui->screen_home_card_all_subject_study_img = lv_image_create(ui->screen_home_card_all_subject_study);
    lv_obj_set_pos(ui->screen_home_card_all_subject_study_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_all_subject_study_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_all_subject_study_img, &_icon_all_subject_study_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_all_subject_study_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_all_subject_study_img, 0);

    //Write style for screen_home_card_all_subject_study_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_all_subject_study_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_all_subject_study_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_sync_textbook
    ui->screen_home_card_sync_textbook = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_sync_textbook, 1080, 8);
    lv_obj_set_size(ui->screen_home_card_sync_textbook, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_sync_textbook, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_sync_textbook, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_sync_textbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_sync_textbook, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_sync_textbook, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_sync_textbook, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_sync_textbook, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_sync_textbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_sync_textbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_sync_textbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_sync_textbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_sync_textbook, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_sync_textbook, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_sync_textbook, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_sync_textbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_sync_textbook, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_sync_textbook, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_sync_textbook_label
    ui->screen_home_card_sync_textbook_label = lv_label_create(ui->screen_home_card_sync_textbook);
    lv_obj_set_pos(ui->screen_home_card_sync_textbook_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_sync_textbook_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_sync_textbook_label, "同步教材");
    lv_label_set_long_mode(ui->screen_home_card_sync_textbook_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_sync_textbook_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_sync_textbook_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_sync_textbook_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_sync_textbook_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_sync_textbook_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_sync_textbook_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_sync_textbook_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_sync_textbook_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_sync_textbook_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_sync_textbook_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_sync_textbook_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_sync_textbook_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_sync_textbook_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_sync_textbook_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_sync_textbook_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_sync_textbook_img
    ui->screen_home_card_sync_textbook_img = lv_image_create(ui->screen_home_card_sync_textbook);
    lv_obj_set_pos(ui->screen_home_card_sync_textbook_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_sync_textbook_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_sync_textbook_img, &_icon_sync_textbook_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_sync_textbook_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_sync_textbook_img, 0);

    //Write style for screen_home_card_sync_textbook_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_sync_textbook_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_sync_textbook_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_micro_chat
    ui->screen_home_card_micro_chat = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_micro_chat, 1008, 8);
    lv_obj_set_size(ui->screen_home_card_micro_chat, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_micro_chat, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_micro_chat, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_micro_chat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_micro_chat, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_micro_chat, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_micro_chat, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_micro_chat, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_micro_chat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_micro_chat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_micro_chat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_micro_chat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_micro_chat, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_micro_chat, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_micro_chat, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_micro_chat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_micro_chat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_micro_chat, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_micro_chat_label
    ui->screen_home_card_micro_chat_label = lv_label_create(ui->screen_home_card_micro_chat);
    lv_obj_set_pos(ui->screen_home_card_micro_chat_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_micro_chat_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_micro_chat_label, "微聊");
    lv_label_set_long_mode(ui->screen_home_card_micro_chat_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_micro_chat_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_micro_chat_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_micro_chat_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_micro_chat_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_micro_chat_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_micro_chat_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_micro_chat_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_micro_chat_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_micro_chat_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_micro_chat_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_micro_chat_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_micro_chat_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_micro_chat_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_micro_chat_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_micro_chat_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_micro_chat_img
    ui->screen_home_card_micro_chat_img = lv_image_create(ui->screen_home_card_micro_chat);
    lv_obj_set_pos(ui->screen_home_card_micro_chat_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_micro_chat_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_micro_chat_img, &_icon_micro_chat_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_micro_chat_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_micro_chat_img, 0);

    //Write style for screen_home_card_micro_chat_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_micro_chat_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_micro_chat_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_baidu_netdisk
    ui->screen_home_card_baidu_netdisk = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_baidu_netdisk, 936, 8);
    lv_obj_set_size(ui->screen_home_card_baidu_netdisk, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_baidu_netdisk, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_baidu_netdisk, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_baidu_netdisk, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_baidu_netdisk, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_baidu_netdisk, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_baidu_netdisk, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_baidu_netdisk, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_baidu_netdisk, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_baidu_netdisk, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_baidu_netdisk, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_baidu_netdisk, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_baidu_netdisk, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_baidu_netdisk, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_baidu_netdisk, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_baidu_netdisk, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_baidu_netdisk, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_baidu_netdisk, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_baidu_netdisk_label
    ui->screen_home_card_baidu_netdisk_label = lv_label_create(ui->screen_home_card_baidu_netdisk);
    lv_obj_set_pos(ui->screen_home_card_baidu_netdisk_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_baidu_netdisk_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_baidu_netdisk_label, "百度网盘");
    lv_label_set_long_mode(ui->screen_home_card_baidu_netdisk_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_baidu_netdisk_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_baidu_netdisk_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_baidu_netdisk_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_baidu_netdisk_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_baidu_netdisk_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_baidu_netdisk_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_baidu_netdisk_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_baidu_netdisk_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_baidu_netdisk_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_baidu_netdisk_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_baidu_netdisk_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_baidu_netdisk_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_baidu_netdisk_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_baidu_netdisk_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_baidu_netdisk_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_baidu_netdisk_img
    ui->screen_home_card_baidu_netdisk_img = lv_image_create(ui->screen_home_card_baidu_netdisk);
    lv_obj_set_pos(ui->screen_home_card_baidu_netdisk_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_baidu_netdisk_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_baidu_netdisk_img, &_icon_baidu_netdisk_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_baidu_netdisk_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_baidu_netdisk_img, 0);

    //Write style for screen_home_card_baidu_netdisk_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_baidu_netdisk_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_baidu_netdisk_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_word_study
    ui->screen_home_card_word_study = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_word_study, 864, 8);
    lv_obj_set_size(ui->screen_home_card_word_study, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_word_study, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_word_study, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_word_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_word_study, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_word_study, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_word_study, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_word_study, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_word_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_word_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_word_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_word_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_word_study, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_word_study, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_word_study, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_word_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_word_study, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_word_study, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_word_study_label
    ui->screen_home_card_word_study_label = lv_label_create(ui->screen_home_card_word_study);
    lv_obj_set_pos(ui->screen_home_card_word_study_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_word_study_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_word_study_label, "背单词");
    lv_label_set_long_mode(ui->screen_home_card_word_study_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_word_study_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_word_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_word_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_word_study_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_word_study_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_word_study_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_word_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_word_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_word_study_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_word_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_word_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_word_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_word_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_word_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_word_study_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_word_study_img
    ui->screen_home_card_word_study_img = lv_image_create(ui->screen_home_card_word_study);
    lv_obj_set_pos(ui->screen_home_card_word_study_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_word_study_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_word_study_img, &_placeholder_icon_word_study_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_word_study_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_word_study_img, 0);

    //Write style for screen_home_card_word_study_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_word_study_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_word_study_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_dictionary
    ui->screen_home_card_dictionary = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_dictionary, 792, 8);
    lv_obj_set_size(ui->screen_home_card_dictionary, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_dictionary, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_dictionary, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_dictionary, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_dictionary, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_dictionary, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_dictionary, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_dictionary, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_dictionary, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_dictionary, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_dictionary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_dictionary, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_dictionary_label
    ui->screen_home_card_dictionary_label = lv_label_create(ui->screen_home_card_dictionary);
    lv_obj_set_pos(ui->screen_home_card_dictionary_label, 2, 61);
    lv_obj_set_size(ui->screen_home_card_dictionary_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_dictionary_label, "生词本");
    lv_label_set_long_mode(ui->screen_home_card_dictionary_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_dictionary_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_dictionary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_dictionary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_dictionary_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_dictionary_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_dictionary_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_dictionary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_dictionary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_dictionary_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_dictionary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_dictionary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_dictionary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_dictionary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_dictionary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_dictionary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_dictionary_img
    ui->screen_home_card_dictionary_img = lv_image_create(ui->screen_home_card_dictionary);
    lv_obj_set_pos(ui->screen_home_card_dictionary_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_dictionary_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_dictionary_img, &_placeholder_icon_dictionary_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_dictionary_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_dictionary_img, 0);

    //Write style for screen_home_card_dictionary_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_dictionary_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_dictionary_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_settings
    ui->screen_home_card_settings = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_settings, 720, 8);
    lv_obj_set_size(ui->screen_home_card_settings, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_settings, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_settings, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_settings, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_settings, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_settings, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_settings, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_settings, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_settings, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_settings, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_settings, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_settings, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_settings, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_settings, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_settings, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_settings, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_settings, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_settings, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_settings_label
    ui->screen_home_card_settings_label = lv_label_create(ui->screen_home_card_settings);
    lv_obj_set_pos(ui->screen_home_card_settings_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_settings_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_settings_label, "设置");
    lv_label_set_long_mode(ui->screen_home_card_settings_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_settings_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_settings_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_settings_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_settings_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_settings_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_settings_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_settings_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_settings_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_settings_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_settings_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_settings_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_settings_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_settings_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_settings_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_settings_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_settings_img
    ui->screen_home_card_settings_img = lv_image_create(ui->screen_home_card_settings);
    lv_obj_set_pos(ui->screen_home_card_settings_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_settings_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_settings_img, &_icon_settings_home_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_settings_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_settings_img, 0);

    //Write style for screen_home_card_settings_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_settings_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_settings_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_story
    ui->screen_home_card_story = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_story, 648, 8);
    lv_obj_set_size(ui->screen_home_card_story, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_story, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_story, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_story, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_story, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_story, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_story, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_story, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_story, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_story, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_story, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_story, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_story, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_story, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_story, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_story, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_story, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_story, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_story_label
    ui->screen_home_card_story_label = lv_label_create(ui->screen_home_card_story);
    lv_obj_set_pos(ui->screen_home_card_story_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_story_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_story_label, "国学故事");
    lv_label_set_long_mode(ui->screen_home_card_story_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_story_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_story_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_story_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_story_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_story_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_story_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_story_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_story_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_story_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_story_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_story_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_story_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_story_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_story_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_story_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_story_img
    ui->screen_home_card_story_img = lv_image_create(ui->screen_home_card_story);
    lv_obj_set_pos(ui->screen_home_card_story_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_story_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_story_img, &_icon_classic_story_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_story_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_story_img, 0);

    //Write style for screen_home_card_story_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_story_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_story_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_music
    ui->screen_home_card_music = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_music, 576, 8);
    lv_obj_set_size(ui->screen_home_card_music, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_music, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_music, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_music, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_music, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_music, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_music, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_music, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_music, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_music, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_music, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_music_label
    ui->screen_home_card_music_label = lv_label_create(ui->screen_home_card_music);
    lv_obj_set_pos(ui->screen_home_card_music_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_music_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_music_label, "网易云音乐");
    lv_label_set_long_mode(ui->screen_home_card_music_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_music_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_music_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_music_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_music_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_music_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_music_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_music_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_music_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_music_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_music_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_music_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_music_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_music_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_music_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_music_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_music_img
    ui->screen_home_card_music_img = lv_image_create(ui->screen_home_card_music);
    lv_obj_set_pos(ui->screen_home_card_music_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_music_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_music_img, &_icon_netease_music_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_music_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_music_img, 0);

    //Write style for screen_home_card_music_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_music_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_music_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_local_content
    ui->screen_home_card_local_content = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_local_content, 504, 8);
    lv_obj_set_size(ui->screen_home_card_local_content, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_local_content, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_local_content, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_local_content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_local_content, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_local_content, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_local_content, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_local_content, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_local_content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_local_content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_local_content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_local_content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_local_content, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_local_content, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_local_content, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_local_content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_local_content, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_local_content, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_local_content_label
    ui->screen_home_card_local_content_label = lv_label_create(ui->screen_home_card_local_content);
    lv_obj_set_pos(ui->screen_home_card_local_content_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_local_content_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_local_content_label, "本地内容");
    lv_label_set_long_mode(ui->screen_home_card_local_content_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_local_content_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_local_content_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_local_content_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_local_content_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_local_content_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_local_content_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_local_content_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_local_content_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_local_content_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_local_content_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_local_content_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_local_content_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_local_content_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_local_content_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_local_content_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_local_content_img
    ui->screen_home_card_local_content_img = lv_image_create(ui->screen_home_card_local_content);
    lv_obj_set_pos(ui->screen_home_card_local_content_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_local_content_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_local_content_img, &_icon_local_content_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_local_content_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_local_content_img, 0);

    //Write style for screen_home_card_local_content_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_local_content_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_local_content_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_k12
    ui->screen_home_card_k12 = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_k12, 432, 8);
    lv_obj_set_size(ui->screen_home_card_k12, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_k12, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_k12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_k12, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_k12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_k12, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_k12, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_k12, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_k12, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_k12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_k12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_k12, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_k12_label
    ui->screen_home_card_k12_label = lv_label_create(ui->screen_home_card_k12);
    lv_obj_set_pos(ui->screen_home_card_k12_label, -1, 62);
    lv_obj_set_size(ui->screen_home_card_k12_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_k12_label, "K12乐园");
    lv_label_set_long_mode(ui->screen_home_card_k12_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_k12_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_k12_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_k12_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_k12_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_k12_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_k12_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_k12_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_k12_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_k12_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_k12_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_k12_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_k12_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_k12_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_k12_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_k12_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_k12_img
    ui->screen_home_card_k12_img = lv_image_create(ui->screen_home_card_k12);
    lv_obj_set_pos(ui->screen_home_card_k12_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_k12_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_k12_img, &_placeholder_icon_k12_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_k12_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_k12_img, 0);

    //Write style for screen_home_card_k12_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_k12_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_k12_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_vocabulary
    ui->screen_home_card_vocabulary = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_vocabulary, 360, 8);
    lv_obj_set_size(ui->screen_home_card_vocabulary, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_vocabulary, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_vocabulary, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_vocabulary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_vocabulary, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_vocabulary, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_vocabulary, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_vocabulary, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_vocabulary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_vocabulary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_vocabulary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_vocabulary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_vocabulary, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_vocabulary, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_vocabulary, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_vocabulary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_vocabulary, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_vocabulary, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_vocabulary_label
    ui->screen_home_card_vocabulary_label = lv_label_create(ui->screen_home_card_vocabulary);
    lv_obj_set_pos(ui->screen_home_card_vocabulary_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_vocabulary_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_vocabulary_label, "生词本");
    lv_label_set_long_mode(ui->screen_home_card_vocabulary_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_vocabulary_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_vocabulary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_vocabulary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_vocabulary_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_vocabulary_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_vocabulary_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_vocabulary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_vocabulary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_vocabulary_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_vocabulary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_vocabulary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_vocabulary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_vocabulary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_vocabulary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_vocabulary_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_vocabulary_img
    ui->screen_home_card_vocabulary_img = lv_image_create(ui->screen_home_card_vocabulary);
    lv_obj_set_pos(ui->screen_home_card_vocabulary_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_vocabulary_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_vocabulary_img, &_placeholder_icon_vocabulary_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_vocabulary_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_vocabulary_img, 0);

    //Write style for screen_home_card_vocabulary_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_vocabulary_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_vocabulary_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_english_query
    ui->screen_home_card_english_query = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_english_query, 288, 8);
    lv_obj_set_size(ui->screen_home_card_english_query, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_english_query, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_english_query, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_english_query, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_english_query, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_english_query, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_english_query, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_english_query, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_english_query, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_english_query, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_english_query, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_english_query, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_english_query, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_english_query, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_english_query, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_english_query, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_english_query, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_english_query, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_english_query_label
    ui->screen_home_card_english_query_label = lv_label_create(ui->screen_home_card_english_query);
    lv_obj_set_pos(ui->screen_home_card_english_query_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_english_query_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_english_query_label, "英文查词");
    lv_label_set_long_mode(ui->screen_home_card_english_query_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_english_query_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_english_query_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_english_query_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_english_query_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_english_query_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_english_query_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_english_query_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_english_query_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_english_query_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_english_query_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_english_query_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_english_query_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_english_query_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_english_query_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_english_query_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_english_query_img
    ui->screen_home_card_english_query_img = lv_image_create(ui->screen_home_card_english_query);
    lv_obj_set_pos(ui->screen_home_card_english_query_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_english_query_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_english_query_img, &_icon_english_query_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_english_query_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_english_query_img, 0);

    //Write style for screen_home_card_english_query_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_english_query_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_english_query_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_weather
    ui->screen_home_card_weather = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_weather, 216, 8);
    lv_obj_set_size(ui->screen_home_card_weather, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_weather, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_weather, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_weather, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_weather, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_weather, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_weather, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_weather, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_weather_label
    ui->screen_home_card_weather_label = lv_label_create(ui->screen_home_card_weather);
    lv_obj_set_pos(ui->screen_home_card_weather_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_weather_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_weather_label, "天气");
    lv_label_set_long_mode(ui->screen_home_card_weather_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_weather_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_weather_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_weather_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_weather_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_weather_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_weather_img
    ui->screen_home_card_weather_img = lv_image_create(ui->screen_home_card_weather);
    lv_obj_set_pos(ui->screen_home_card_weather_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_weather_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_weather_img, &_weather_home_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_weather_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_weather_img, 0);

    //Write style for screen_home_card_weather_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_weather_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_weather_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_alarm
    ui->screen_home_card_alarm = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_alarm, 144, 8);
    lv_obj_set_size(ui->screen_home_card_alarm, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_alarm, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_alarm, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_alarm, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_alarm, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_alarm, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_alarm, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_alarm, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_alarm, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_alarm, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_alarm, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_alarm_label
    ui->screen_home_card_alarm_label = lv_label_create(ui->screen_home_card_alarm);
    lv_obj_set_pos(ui->screen_home_card_alarm_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_alarm_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_alarm_label, "闹钟");
    lv_label_set_long_mode(ui->screen_home_card_alarm_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_alarm_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_alarm_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_alarm_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_alarm_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_alarm_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_alarm_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_alarm_img
    ui->screen_home_card_alarm_img = lv_image_create(ui->screen_home_card_alarm);
    lv_obj_set_pos(ui->screen_home_card_alarm_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_alarm_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_alarm_img, &_icon_alarm_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_alarm_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_alarm_img, 0);

    //Write style for screen_home_card_alarm_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_alarm_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_alarm_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_voice_translate
    ui->screen_home_card_voice_translate = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_voice_translate, 72, 8);
    lv_obj_set_size(ui->screen_home_card_voice_translate, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_voice_translate, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_voice_translate, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_voice_translate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_voice_translate, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_voice_translate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_voice_translate, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_voice_translate, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_voice_translate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_voice_translate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_voice_translate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_voice_translate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_voice_translate, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_voice_translate, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_voice_translate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_voice_translate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_voice_translate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_voice_translate, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_voice_translate_label
    ui->screen_home_card_voice_translate_label = lv_label_create(ui->screen_home_card_voice_translate);
    lv_obj_set_pos(ui->screen_home_card_voice_translate_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_voice_translate_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_voice_translate_label, "语音翻译");
    lv_label_set_long_mode(ui->screen_home_card_voice_translate_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_voice_translate_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_voice_translate_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_voice_translate_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_voice_translate_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_voice_translate_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_voice_translate_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_voice_translate_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_voice_translate_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_voice_translate_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_voice_translate_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_voice_translate_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_voice_translate_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_voice_translate_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_voice_translate_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_voice_translate_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_voice_translate_img
    ui->screen_home_card_voice_translate_img = lv_image_create(ui->screen_home_card_voice_translate);
    lv_obj_set_pos(ui->screen_home_card_voice_translate_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_voice_translate_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_voice_translate_img, &_icon_translate_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_voice_translate_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_voice_translate_img, 0);

    //Write style for screen_home_card_voice_translate_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_voice_translate_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_voice_translate_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_ai
    ui->screen_home_card_ai = lv_button_create(ui->screen_home_home_cards_container);
    lv_obj_set_pos(ui->screen_home_card_ai, 0, 8);
    lv_obj_set_size(ui->screen_home_card_ai, 64, 92);
    lv_obj_set_scrollbar_mode(ui->screen_home_card_ai, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_card_ai, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_ai, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_ai, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_ai, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_card_ai, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_card_ai, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_ai, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_ai, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_ai, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_ai, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_ai, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_card_ai, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_card_ai, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_card_ai, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_card_ai, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_card_ai, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_ai_label
    ui->screen_home_card_ai_label = lv_label_create(ui->screen_home_card_ai);
    lv_obj_set_pos(ui->screen_home_card_ai_label, 0, 62);
    lv_obj_set_size(ui->screen_home_card_ai_label, 64, 16);
    lv_label_set_text(ui->screen_home_card_ai_label, "AI伙伴");
    lv_label_set_long_mode(ui->screen_home_card_ai_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_card_ai_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_card_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_card_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_card_ai_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_card_ai_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_card_ai_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_card_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_card_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_card_ai_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_card_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_card_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_card_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_card_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_card_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_card_ai_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_card_ai_img
    ui->screen_home_card_ai_img = lv_image_create(ui->screen_home_card_ai);
    lv_obj_set_pos(ui->screen_home_card_ai_img, 14, 12);
    lv_obj_set_size(ui->screen_home_card_ai_img, 36, 36);
    lv_image_set_src(ui->screen_home_card_ai_img, &_icon_ai_RGB565A8_36x36);
    lv_image_set_pivot(ui->screen_home_card_ai_img, 50,50);
    lv_image_set_rotation(ui->screen_home_card_ai_img, 0);

    //Write style for screen_home_card_ai_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_card_ai_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_card_ai_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_home_status_card
    ui->screen_home_home_status_card = lv_obj_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_home_status_card, 176, 14);
    lv_obj_set_size(ui->screen_home_home_status_card, 130, 86);
    lv_obj_set_scrollbar_mode(ui->screen_home_home_status_card, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_home_status_card, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_home_status_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_home_status_card, 18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_home_status_card, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_home_status_card, lv_color_hex(0xF7FAFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_home_status_card, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_home_status_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_home_status_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_home_status_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_home_status_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_home_status_card, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_home_status_card, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_home_status_card, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_home_status_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_home_status_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_home_status_card, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_home_status_label
    ui->screen_home_home_status_label = lv_label_create(ui->screen_home_home_status_card);
    lv_obj_set_pos(ui->screen_home_home_status_label, 10, 30);
    lv_obj_set_size(ui->screen_home_home_status_label, 110, 24);
    lv_label_set_text(ui->screen_home_home_status_label, "Ready");
    lv_label_set_long_mode(ui->screen_home_home_status_label, LV_LABEL_LONG_WRAP);

    //Write style for screen_home_home_status_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_home_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_home_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_home_status_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_home_status_label, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_home_status_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_home_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_home_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_home_status_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_home_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_home_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_home_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_home_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_home_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_home_status_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_home_time_card
    ui->screen_home_home_time_card = lv_obj_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_home_time_card, 14, 14);
    lv_obj_set_size(ui->screen_home_home_time_card, 150, 86);
    lv_obj_set_scrollbar_mode(ui->screen_home_home_time_card, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_home_home_time_card, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_home_time_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_home_time_card, 18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_home_time_card, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_home_home_time_card, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_home_home_time_card, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_home_time_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_home_time_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_home_time_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_home_time_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_home_time_card, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_home_home_time_card, lv_color_hex(0xA0B4D6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_home_home_time_card, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_home_home_time_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_x(ui->screen_home_home_time_card, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_offset_y(ui->screen_home_home_time_card, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_home_time_label
    ui->screen_home_home_time_label = lv_label_create(ui->screen_home_home_time_card);
    lv_obj_set_pos(ui->screen_home_home_time_label, 12, 10);
    lv_obj_set_size(ui->screen_home_home_time_label, 110, 34);
    lv_label_set_text(ui->screen_home_home_time_label, "--:--");
    lv_label_set_long_mode(ui->screen_home_home_time_label, LV_LABEL_LONG_CLIP);

    //Write style for screen_home_home_time_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_home_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_home_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_home_time_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_home_time_label, &lv_font_montserratMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_home_time_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_home_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_home_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_home_time_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_home_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_home_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_home_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_home_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_home_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_home_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_home_date_label
    ui->screen_home_home_date_label = lv_label_create(ui->screen_home_home_time_card);
    lv_obj_set_pos(ui->screen_home_home_date_label, 12, 56);
    lv_obj_set_size(ui->screen_home_home_date_label, 100, 16);
    lv_label_set_text(ui->screen_home_home_date_label, "Wed 05/13");
    lv_label_set_long_mode(ui->screen_home_home_date_label, LV_LABEL_LONG_CLIP);

    //Write style for screen_home_home_date_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_home_home_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_home_home_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_home_home_date_label, lv_color_hex(0x1F2450), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_home_home_date_label, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_home_home_date_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_home_home_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_home_home_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_home_home_date_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_home_home_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_home_home_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_home_home_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_home_home_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_home_home_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_home_home_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_home_home_bg_image
    ui->screen_home_home_bg_image = lv_image_create(ui->screen_home);
    lv_obj_set_pos(ui->screen_home_home_bg_image, 0, 0);
    lv_obj_set_size(ui->screen_home_home_bg_image, 320, 240);
    lv_obj_add_flag(ui->screen_home_home_bg_image, LV_OBJ_FLAG_HIDDEN);
    lv_image_set_src(ui->screen_home_home_bg_image, &_home_bg_RGB565A8_320x240);
    lv_image_set_pivot(ui->screen_home_home_bg_image, 0,0);
    lv_image_set_rotation(ui->screen_home_home_bg_image, 0);

    //Write style for screen_home_home_bg_image, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_home_home_bg_image, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_home_home_bg_image, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_home.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_home);

}
