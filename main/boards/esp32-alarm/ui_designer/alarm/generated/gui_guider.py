# Copyright 2026 NXP
# NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
# accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
# activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
# comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
# terms, then you may not retain, install, activate or otherwise use the software.

import utime as time
import usys as sys
import lvgl as lv
import ustruct
import fs_driver

lv.init()

# Register display driver.
disp_drv = lv.sdl_window_create(320, 240)
lv.sdl_window_set_resizeable(disp_drv, False)
lv.sdl_window_set_title(disp_drv, "Simulator (MicroPython)")

# Regsiter input driver
mouse = lv.sdl_mouse_create()

# Add default theme for bottom layer
bottom_layer = lv.layer_bottom()
lv.theme_apply(bottom_layer)

fs_drv = lv.fs_drv_t()
fs_driver.fs_register(fs_drv, 'Z')

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def anim_width_cb(obj, v):
    obj.set_width(v)

def anim_height_cb(obj, v):
    obj.set_height(v)

def anim_img_zoom_cb(obj, v):
    obj.set_scale(v)

def anim_img_rotate_cb(obj, v):
    obj.set_rotation(v)

global_font_cache = {}
def test_font(font_family, font_size):
    global global_font_cache
    if font_family + str(font_size) in global_font_cache:
        return global_font_cache[font_family + str(font_size)]
    if font_size % 2:
        candidates = [
            (font_family, font_size),
            (font_family, font_size-font_size%2),
            (font_family, font_size+font_size%2),
            ("montserrat", font_size-font_size%2),
            ("montserrat", font_size+font_size%2),
            ("montserrat", 16)
        ]
    else:
        candidates = [
            (font_family, font_size),
            ("montserrat", font_size),
            ("montserrat", 16)
        ]
    for (family, size) in candidates:
        try:
            if eval(f'lv.font_{family}_{size}'):
                global_font_cache[font_family + str(font_size)] = eval(f'lv.font_{family}_{size}')
                if family != font_family or size != font_size:
                    print(f'WARNING: lv.font_{family}_{size} is used!')
                return eval(f'lv.font_{family}_{size}')
        except AttributeError:
            try:
                load_font = lv.binfont_create(f"Z:MicroPython/lv_font_{family}_{size}.fnt")
                global_font_cache[font_family + str(font_size)] = load_font
                return load_font
            except:
                if family == font_family and size == font_size:
                    print(f'WARNING: lv.font_{family}_{size} is NOT supported!')

global_image_cache = {}
def load_image(file):
    global global_image_cache
    if file in global_image_cache:
        return global_image_cache[file]
    try:
        with open(file,'rb') as f:
            data = f.read()
    except:
        print(f'Could not open {file}')
        sys.exit()

    img = lv.image_dsc_t({
        'data_size': len(data),
        'data': data
    })
    global_image_cache[file] = img
    return img

def calendar_event_handler(e,obj):
    code = e.get_code()

    if code == lv.EVENT.VALUE_CHANGED:
        source = lv.calendar.__cast__(e.get_current_target())
        date = lv.calendar_date_t()
        if source.get_pressed_date(date) == lv.RESULT.OK:
            source.set_highlighted_dates([date], 1)

def spinbox_increment_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.increment()
def spinbox_decrement_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.decrement()

def digital_clock_cb(timer, obj, current_time, show_second, use_ampm):
    hour = int(current_time[0])
    minute = int(current_time[1])
    second = int(current_time[2])
    ampm = current_time[3]
    second = second + 1
    if second == 60:
        second = 0
        minute = minute + 1
        if minute == 60:
            minute = 0
            hour = hour + 1
            if use_ampm:
                if hour == 12:
                    if ampm == 'AM':
                        ampm = 'PM'
                    elif ampm == 'PM':
                        ampm = 'AM'
                if hour > 12:
                    hour = hour % 12
    hour = hour % 24
    if use_ampm:
        if show_second:
            obj.set_text("%d:%02d:%02d %s" %(hour, minute, second, ampm))
        else:
            obj.set_text("%d:%02d %s" %(hour, minute, ampm))
    else:
        if show_second:
            obj.set_text("%d:%02d:%02d" %(hour, minute, second))
        else:
            obj.set_text("%d:%02d" %(hour, minute))
    current_time[0] = hour
    current_time[1] = minute
    current_time[2] = second
    current_time[3] = ampm

def analog_clock_cb(timer, obj):
    datetime = time.localtime()
    hour = datetime[3]
    if hour >= 12: hour = hour - 12
    obj.set_time(hour, datetime[4], datetime[5])

def datetext_event_handler(e, obj):
    code = e.get_code()
    datetext = lv.label.__cast__(e.get_target())
    if code == lv.EVENT.FOCUSED:
        if obj is None:
            bg = lv.layer_top()
            bg.add_flag(lv.obj.FLAG.CLICKABLE)
            obj = lv.calendar(bg)
            scr = lv.screen_active()
            scr_height = scr.get_height()
            scr_width = scr.get_width()
            obj.set_size(int(scr_width * 0.8), int(scr_height * 0.8))
            datestring = datetext.get_text()
            year = int(datestring.split('/')[0])
            month = int(datestring.split('/')[1])
            day = int(datestring.split('/')[2])
            obj.set_showed_date(year, month)
            highlighted_days=[lv.calendar_date_t({'year':year, 'month':month, 'day':day})]
            obj.set_highlighted_dates(highlighted_days, 1)
            obj.align(lv.ALIGN.CENTER, 0, 0)
            lv.calendar_header_arrow(obj)
            obj.add_event_cb(lambda e: datetext_calendar_event_handler(e, datetext), lv.EVENT.ALL, None)
            scr.update_layout()

def datetext_calendar_event_handler(e, obj):
    code = e.get_code()
    calendar = lv.calendar.__cast__(e.get_current_target())
    if code == lv.EVENT.VALUE_CHANGED:
        date = lv.calendar_date_t()
        if calendar.get_pressed_date(date) == lv.RESULT.OK:
            obj.set_text(f"{date.year}/{date.month}/{date.day}")
            bg = lv.layer_top()
            bg.remove_flag(lv.obj.FLAG.CLICKABLE)
            bg.set_style_bg_opa(lv.OPA.TRANSP, 0)
            calendar.delete()

# Create screen_boot
screen_boot = lv.obj()
screen_boot.set_size(320, 240)
screen_boot.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_boot, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_boot.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_boot.set_style_bg_color(lv.color_hex(0x10131A), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_boot.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_boot_boot_hint_label
screen_boot_boot_hint_label = lv.label(screen_boot)
screen_boot_boot_hint_label.set_text("AI Alarm")
screen_boot_boot_hint_label.set_long_mode(lv.label.LONG.CLIP)
screen_boot_boot_hint_label.set_width(lv.pct(100))
screen_boot_boot_hint_label.set_pos(118, 206)
screen_boot_boot_hint_label.set_size(84, 18)
# Set style for screen_boot_boot_hint_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_boot_boot_hint_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_boot_boot_hint_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_boot_boot_hint_label.set_style_text_color(lv.color_hex(0xE8ECFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_boot_boot_hint_label.set_style_text_font(test_font("montserratMedium", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_boot_boot_hint_label.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_boot_boot_hint_label.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_boot_boot_hint_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_boot_boot_hint_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_boot_boot_hint_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_boot_boot_hint_label.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_boot_boot_hint_label.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_boot_boot_hint_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_boot_boot_hint_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_boot_boot_hint_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_boot_boot_spinner_image
screen_boot_boot_spinner_image = lv.image(screen_boot)
screen_boot_boot_spinner_image.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\loading_spinner_1_24_24.png"))
screen_boot_boot_spinner_image.add_flag(lv.obj.FLAG.CLICKABLE)
screen_boot_boot_spinner_image.set_pivot(50,50)
screen_boot_boot_spinner_image.set_rotation(0)
screen_boot_boot_spinner_image.set_pos(148, 178)
screen_boot_boot_spinner_image.set_size(24, 24)
# Set style for screen_boot_boot_spinner_image, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_boot_boot_spinner_image.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_boot_boot_logo_image
screen_boot_boot_logo_image = lv.image(screen_boot)
screen_boot_boot_logo_image.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\launch_logo_100_100.png"))
screen_boot_boot_logo_image.add_flag(lv.obj.FLAG.CLICKABLE)
screen_boot_boot_logo_image.set_pivot(50,50)
screen_boot_boot_logo_image.set_rotation(0)
screen_boot_boot_logo_image.set_pos(110, 54)
screen_boot_boot_logo_image.set_size(100, 100)
# Set style for screen_boot_boot_logo_image, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_boot_boot_logo_image.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_boot.update_layout()
# Create screen_home
screen_home = lv.obj()
screen_home.set_size(320, 240)
screen_home.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_home, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home.set_style_bg_color(lv.color_hex(0xF3F7FF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_home_cards_container
screen_home_home_cards_container = lv.obj(screen_home)
screen_home_home_cards_container.set_pos(14, 120)
screen_home_home_cards_container.set_size(292, 108)
screen_home_home_cards_container.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_home_home_cards_container, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_home_cards_container.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_cards_container.set_style_radius(18, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_cards_container.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_cards_container.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_cards_container.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_cards_container.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_cards_container.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_cards_container.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_home_card_tools
screen_home_card_tools = lv.obj(screen_home_home_cards_container)
screen_home_card_tools.set_pos(222, 8)
screen_home_card_tools.set_size(64, 92)
screen_home_card_tools.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_home_card_tools, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_card_tools.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools.set_style_radius(16, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools.set_style_bg_color(lv.color_hex(0xFFFFFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools.set_style_shadow_width(4, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools.set_style_shadow_color(lv.color_hex(0xA0B4D6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools.set_style_shadow_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools.set_style_shadow_spread(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools.set_style_shadow_offset_x(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools.set_style_shadow_offset_y(2, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_home_card_tools_label
screen_home_card_tools_label = lv.label(screen_home_card_tools)
screen_home_card_tools_label.set_text("Tools")
screen_home_card_tools_label.set_long_mode(lv.label.LONG.WRAP)
screen_home_card_tools_label.set_width(lv.pct(100))
screen_home_card_tools_label.set_pos(8, 62)
screen_home_card_tools_label.set_size(48, 16)
# Set style for screen_home_card_tools_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_card_tools_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools_label.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools_label.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools_label.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools_label.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools_label.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools_label.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_tools_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_card_tools_img
screen_home_card_tools_img = lv.image(screen_home_card_tools)
screen_home_card_tools_img.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\icon_tools_36_36.png"))
screen_home_card_tools_img.add_flag(lv.obj.FLAG.CLICKABLE)
screen_home_card_tools_img.set_pivot(50,50)
screen_home_card_tools_img.set_rotation(0)
screen_home_card_tools_img.set_pos(14, 12)
screen_home_card_tools_img.set_size(36, 36)
# Set style for screen_home_card_tools_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_card_tools_img.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_card_alarm
screen_home_card_alarm = lv.obj(screen_home_home_cards_container)
screen_home_card_alarm.set_pos(148, 8)
screen_home_card_alarm.set_size(64, 92)
screen_home_card_alarm.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_home_card_alarm, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_card_alarm.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm.set_style_radius(16, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm.set_style_bg_color(lv.color_hex(0xFFFFFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm.set_style_shadow_width(4, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm.set_style_shadow_color(lv.color_hex(0xA0B4D6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm.set_style_shadow_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm.set_style_shadow_spread(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm.set_style_shadow_offset_x(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm.set_style_shadow_offset_y(2, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_home_card_alarm_label
screen_home_card_alarm_label = lv.label(screen_home_card_alarm)
screen_home_card_alarm_label.set_text("Alarm")
screen_home_card_alarm_label.set_long_mode(lv.label.LONG.WRAP)
screen_home_card_alarm_label.set_width(lv.pct(100))
screen_home_card_alarm_label.set_pos(8, 62)
screen_home_card_alarm_label.set_size(48, 16)
# Set style for screen_home_card_alarm_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_card_alarm_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm_label.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm_label.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm_label.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm_label.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm_label.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm_label.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_alarm_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_card_alarm_img
screen_home_card_alarm_img = lv.image(screen_home_card_alarm)
screen_home_card_alarm_img.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\icon_alarm_36_36.png"))
screen_home_card_alarm_img.add_flag(lv.obj.FLAG.CLICKABLE)
screen_home_card_alarm_img.set_pivot(50,50)
screen_home_card_alarm_img.set_rotation(0)
screen_home_card_alarm_img.set_pos(14, 12)
screen_home_card_alarm_img.set_size(36, 36)
# Set style for screen_home_card_alarm_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_card_alarm_img.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_card_study
screen_home_card_study = lv.obj(screen_home_home_cards_container)
screen_home_card_study.set_pos(74, 8)
screen_home_card_study.set_size(64, 92)
screen_home_card_study.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_home_card_study, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_card_study.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study.set_style_radius(16, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study.set_style_bg_color(lv.color_hex(0xFFFFFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study.set_style_shadow_width(4, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study.set_style_shadow_color(lv.color_hex(0xA0B4D6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study.set_style_shadow_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study.set_style_shadow_spread(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study.set_style_shadow_offset_x(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study.set_style_shadow_offset_y(2, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_home_card_study_label
screen_home_card_study_label = lv.label(screen_home_card_study)
screen_home_card_study_label.set_text("Study")
screen_home_card_study_label.set_long_mode(lv.label.LONG.WRAP)
screen_home_card_study_label.set_width(lv.pct(100))
screen_home_card_study_label.set_pos(8, 62)
screen_home_card_study_label.set_size(48, 16)
# Set style for screen_home_card_study_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_card_study_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study_label.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study_label.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study_label.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study_label.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study_label.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study_label.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_study_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_card_study_img
screen_home_card_study_img = lv.image(screen_home_card_study)
screen_home_card_study_img.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\icon_study_36_36.png"))
screen_home_card_study_img.add_flag(lv.obj.FLAG.CLICKABLE)
screen_home_card_study_img.set_pivot(50,50)
screen_home_card_study_img.set_rotation(0)
screen_home_card_study_img.set_pos(14, 12)
screen_home_card_study_img.set_size(36, 36)
# Set style for screen_home_card_study_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_card_study_img.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_card_ai
screen_home_card_ai = lv.obj(screen_home_home_cards_container)
screen_home_card_ai.set_pos(0, 8)
screen_home_card_ai.set_size(64, 92)
screen_home_card_ai.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_home_card_ai, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_card_ai.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai.set_style_radius(16, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai.set_style_bg_color(lv.color_hex(0xFFFFFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai.set_style_shadow_width(4, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai.set_style_shadow_color(lv.color_hex(0xA0B4D6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai.set_style_shadow_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai.set_style_shadow_spread(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai.set_style_shadow_offset_x(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai.set_style_shadow_offset_y(2, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_home_card_ai_label
screen_home_card_ai_label = lv.label(screen_home_card_ai)
screen_home_card_ai_label.set_text("AI")
screen_home_card_ai_label.set_long_mode(lv.label.LONG.WRAP)
screen_home_card_ai_label.set_width(lv.pct(100))
screen_home_card_ai_label.set_pos(8, 62)
screen_home_card_ai_label.set_size(48, 16)
# Set style for screen_home_card_ai_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_card_ai_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai_label.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai_label.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai_label.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai_label.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai_label.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai_label.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_card_ai_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_card_ai_img
screen_home_card_ai_img = lv.image(screen_home_card_ai)
screen_home_card_ai_img.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\icon_ai_36_36.png"))
screen_home_card_ai_img.add_flag(lv.obj.FLAG.CLICKABLE)
screen_home_card_ai_img.set_pivot(50,50)
screen_home_card_ai_img.set_rotation(0)
screen_home_card_ai_img.set_pos(14, 12)
screen_home_card_ai_img.set_size(36, 36)
# Set style for screen_home_card_ai_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_card_ai_img.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_home_status_card
screen_home_home_status_card = lv.obj(screen_home)
screen_home_home_status_card.set_pos(176, 14)
screen_home_home_status_card.set_size(130, 86)
screen_home_home_status_card.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_home_home_status_card, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_home_status_card.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_card.set_style_radius(18, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_card.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_card.set_style_bg_color(lv.color_hex(0xF7FAFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_card.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_card.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_card.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_card.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_card.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_card.set_style_shadow_width(4, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_card.set_style_shadow_color(lv.color_hex(0xA0B4D6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_card.set_style_shadow_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_card.set_style_shadow_spread(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_card.set_style_shadow_offset_x(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_card.set_style_shadow_offset_y(2, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_home_home_status_label
screen_home_home_status_label = lv.label(screen_home_home_status_card)
screen_home_home_status_label.set_text("Ready")
screen_home_home_status_label.set_long_mode(lv.label.LONG.WRAP)
screen_home_home_status_label.set_width(lv.pct(100))
screen_home_home_status_label.set_pos(10, 30)
screen_home_home_status_label.set_size(110, 24)
# Set style for screen_home_home_status_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_home_status_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_label.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_label.set_style_text_font(test_font("montserratMedium", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_label.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_label.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_label.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_label.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_label.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_status_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_home_time_card
screen_home_home_time_card = lv.obj(screen_home)
screen_home_home_time_card.set_pos(14, 14)
screen_home_home_time_card.set_size(150, 86)
screen_home_home_time_card.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_home_home_time_card, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_home_time_card.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_card.set_style_radius(18, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_card.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_card.set_style_bg_color(lv.color_hex(0xFFFFFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_card.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_card.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_card.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_card.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_card.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_card.set_style_shadow_width(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_card.set_style_shadow_color(lv.color_hex(0xA0B4D6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_card.set_style_shadow_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_card.set_style_shadow_spread(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_card.set_style_shadow_offset_x(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_card.set_style_shadow_offset_y(2, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_home_home_date_label
screen_home_home_date_label = lv.label(screen_home_home_time_card)
screen_home_home_date_label.set_text("Wed 05/13")
screen_home_home_date_label.set_long_mode(lv.label.LONG.CLIP)
screen_home_home_date_label.set_width(lv.pct(100))
screen_home_home_date_label.set_pos(12, 56)
screen_home_home_date_label.set_size(100, 16)
# Set style for screen_home_home_date_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_home_date_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_date_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_date_label.set_style_text_color(lv.color_hex(0x5C628B), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_date_label.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_date_label.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_date_label.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_date_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_date_label.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_date_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_date_label.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_date_label.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_date_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_date_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_date_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_home_time_label
screen_home_home_time_label = lv.label(screen_home_home_time_card)
screen_home_home_time_label.set_text("--:--")
screen_home_home_time_label.set_long_mode(lv.label.LONG.CLIP)
screen_home_home_time_label.set_width(lv.pct(100))
screen_home_home_time_label.set_pos(12, 10)
screen_home_home_time_label.set_size(110, 34)
# Set style for screen_home_home_time_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_home_time_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_label.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_label.set_style_text_font(test_font("montserratMedium", 28), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_label.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_label.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_label.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_label.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_label.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_home_time_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_home_bg_image
screen_home_home_bg_image = lv.image(screen_home)
screen_home_home_bg_image.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\home_bg_320_240.png"))
screen_home_home_bg_image.add_flag(lv.obj.FLAG.CLICKABLE)
screen_home_home_bg_image.set_pivot(50,50)
screen_home_home_bg_image.set_rotation(0)
screen_home_home_bg_image.set_pos(0, 0)
screen_home_home_bg_image.set_size(320, 240)
# Set style for screen_home_home_bg_image, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_home_bg_image.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_home.update_layout()
# Create screen_app_grid
screen_app_grid = lv.obj()
screen_app_grid.set_size(320, 240)
screen_app_grid.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_app_grid, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_app_grid.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid.set_style_bg_color(lv.color_hex(0xEEF4FF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_app_grid_cont_app_grid
screen_app_grid_cont_app_grid = lv.obj(screen_app_grid)
screen_app_grid_cont_app_grid.set_pos(16, 48)
screen_app_grid_cont_app_grid.set_size(288, 168)
screen_app_grid_cont_app_grid.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_app_grid_cont_app_grid, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_app_grid_cont_app_grid.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_cont_app_grid.set_style_radius(18, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_cont_app_grid.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_cont_app_grid.set_style_bg_color(lv.color_hex(0xFFFFFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_cont_app_grid.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_cont_app_grid.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_cont_app_grid.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_cont_app_grid.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_cont_app_grid.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_cont_app_grid.set_style_shadow_width(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_cont_app_grid.set_style_shadow_color(lv.color_hex(0xA0B4D6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_cont_app_grid.set_style_shadow_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_cont_app_grid.set_style_shadow_spread(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_cont_app_grid.set_style_shadow_offset_x(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_cont_app_grid.set_style_shadow_offset_y(2, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_app_grid_app_tools
screen_app_grid_app_tools = lv.obj(screen_app_grid_cont_app_grid)
screen_app_grid_app_tools.set_pos(150, 88)
screen_app_grid_app_tools.set_size(128, 64)
screen_app_grid_app_tools.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_app_grid_app_tools, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_app_grid_app_tools.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools.set_style_radius(14, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools.set_style_bg_color(lv.color_hex(0xF7FAFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_app_grid_app_tools_label
screen_app_grid_app_tools_label = lv.label(screen_app_grid_app_tools)
screen_app_grid_app_tools_label.set_text("Tools")
screen_app_grid_app_tools_label.set_long_mode(lv.label.LONG.WRAP)
screen_app_grid_app_tools_label.set_width(lv.pct(100))
screen_app_grid_app_tools_label.set_pos(46, 22)
screen_app_grid_app_tools_label.set_size(64, 18)
# Set style for screen_app_grid_app_tools_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_app_grid_app_tools_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools_label.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools_label.set_style_text_font(test_font("montserratMedium", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools_label.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools_label.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools_label.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools_label.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools_label.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_tools_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_app_grid_app_tools_img
screen_app_grid_app_tools_img = lv.image(screen_app_grid_app_tools)
screen_app_grid_app_tools_img.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\icon_tools_28_28.png"))
screen_app_grid_app_tools_img.add_flag(lv.obj.FLAG.CLICKABLE)
screen_app_grid_app_tools_img.set_pivot(50,50)
screen_app_grid_app_tools_img.set_rotation(0)
screen_app_grid_app_tools_img.set_pos(8, 18)
screen_app_grid_app_tools_img.set_size(28, 28)
# Set style for screen_app_grid_app_tools_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_app_grid_app_tools_img.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_app_grid_app_alarm
screen_app_grid_app_alarm = lv.obj(screen_app_grid_cont_app_grid)
screen_app_grid_app_alarm.set_pos(10, 88)
screen_app_grid_app_alarm.set_size(128, 64)
screen_app_grid_app_alarm.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_app_grid_app_alarm, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_app_grid_app_alarm.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm.set_style_radius(14, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm.set_style_bg_color(lv.color_hex(0xF7FAFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_app_grid_app_alarm_label
screen_app_grid_app_alarm_label = lv.label(screen_app_grid_app_alarm)
screen_app_grid_app_alarm_label.set_text("Alarm")
screen_app_grid_app_alarm_label.set_long_mode(lv.label.LONG.WRAP)
screen_app_grid_app_alarm_label.set_width(lv.pct(100))
screen_app_grid_app_alarm_label.set_pos(46, 22)
screen_app_grid_app_alarm_label.set_size(64, 18)
# Set style for screen_app_grid_app_alarm_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_app_grid_app_alarm_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm_label.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm_label.set_style_text_font(test_font("montserratMedium", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm_label.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm_label.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm_label.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm_label.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm_label.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_alarm_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_app_grid_app_alarm_img
screen_app_grid_app_alarm_img = lv.image(screen_app_grid_app_alarm)
screen_app_grid_app_alarm_img.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\icon_alarm_28_28.png"))
screen_app_grid_app_alarm_img.add_flag(lv.obj.FLAG.CLICKABLE)
screen_app_grid_app_alarm_img.set_pivot(50,50)
screen_app_grid_app_alarm_img.set_rotation(0)
screen_app_grid_app_alarm_img.set_pos(8, 18)
screen_app_grid_app_alarm_img.set_size(28, 28)
# Set style for screen_app_grid_app_alarm_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_app_grid_app_alarm_img.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_app_grid_app_study
screen_app_grid_app_study = lv.obj(screen_app_grid_cont_app_grid)
screen_app_grid_app_study.set_pos(150, 12)
screen_app_grid_app_study.set_size(128, 64)
screen_app_grid_app_study.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_app_grid_app_study, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_app_grid_app_study.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study.set_style_radius(14, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study.set_style_bg_color(lv.color_hex(0xF7FAFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_app_grid_app_study_label
screen_app_grid_app_study_label = lv.label(screen_app_grid_app_study)
screen_app_grid_app_study_label.set_text("Study")
screen_app_grid_app_study_label.set_long_mode(lv.label.LONG.WRAP)
screen_app_grid_app_study_label.set_width(lv.pct(100))
screen_app_grid_app_study_label.set_pos(46, 22)
screen_app_grid_app_study_label.set_size(64, 18)
# Set style for screen_app_grid_app_study_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_app_grid_app_study_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study_label.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study_label.set_style_text_font(test_font("montserratMedium", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study_label.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study_label.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study_label.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study_label.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study_label.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_study_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_app_grid_app_study_img
screen_app_grid_app_study_img = lv.image(screen_app_grid_app_study)
screen_app_grid_app_study_img.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\icon_study_28_28.png"))
screen_app_grid_app_study_img.add_flag(lv.obj.FLAG.CLICKABLE)
screen_app_grid_app_study_img.set_pivot(50,50)
screen_app_grid_app_study_img.set_rotation(0)
screen_app_grid_app_study_img.set_pos(8, 18)
screen_app_grid_app_study_img.set_size(28, 28)
# Set style for screen_app_grid_app_study_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_app_grid_app_study_img.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_app_grid_app_ai
screen_app_grid_app_ai = lv.obj(screen_app_grid_cont_app_grid)
screen_app_grid_app_ai.set_pos(10, 12)
screen_app_grid_app_ai.set_size(128, 64)
screen_app_grid_app_ai.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_app_grid_app_ai, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_app_grid_app_ai.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai.set_style_radius(14, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai.set_style_bg_color(lv.color_hex(0xF7FAFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_app_grid_app_ai_label
screen_app_grid_app_ai_label = lv.label(screen_app_grid_app_ai)
screen_app_grid_app_ai_label.set_text("AI")
screen_app_grid_app_ai_label.set_long_mode(lv.label.LONG.WRAP)
screen_app_grid_app_ai_label.set_width(lv.pct(100))
screen_app_grid_app_ai_label.set_pos(46, 22)
screen_app_grid_app_ai_label.set_size(64, 18)
# Set style for screen_app_grid_app_ai_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_app_grid_app_ai_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai_label.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai_label.set_style_text_font(test_font("montserratMedium", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai_label.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai_label.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai_label.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai_label.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai_label.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_app_ai_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_app_grid_app_ai_img
screen_app_grid_app_ai_img = lv.image(screen_app_grid_app_ai)
screen_app_grid_app_ai_img.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\icon_ai_28_28.png"))
screen_app_grid_app_ai_img.add_flag(lv.obj.FLAG.CLICKABLE)
screen_app_grid_app_ai_img.set_pivot(50,50)
screen_app_grid_app_ai_img.set_rotation(0)
screen_app_grid_app_ai_img.set_pos(8, 18)
screen_app_grid_app_ai_img.set_size(28, 28)
# Set style for screen_app_grid_app_ai_img, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_app_grid_app_ai_img.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_app_grid_label_apps_title
screen_app_grid_label_apps_title = lv.label(screen_app_grid)
screen_app_grid_label_apps_title.set_text("Apps")
screen_app_grid_label_apps_title.set_long_mode(lv.label.LONG.CLIP)
screen_app_grid_label_apps_title.set_width(lv.pct(100))
screen_app_grid_label_apps_title.set_pos(16, 12)
screen_app_grid_label_apps_title.set_size(80, 22)
# Set style for screen_app_grid_label_apps_title, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_app_grid_label_apps_title.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_label_apps_title.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_label_apps_title.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_label_apps_title.set_style_text_font(test_font("montserratMedium", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_label_apps_title.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_label_apps_title.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_label_apps_title.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_label_apps_title.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_label_apps_title.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_label_apps_title.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_label_apps_title.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_label_apps_title.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_label_apps_title.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_app_grid_label_apps_title.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_app_grid.update_layout()
# Create screen_ai
screen_ai = lv.obj()
screen_ai.set_size(320, 240)
screen_ai.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_ai, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_ai.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai.set_style_bg_color(lv.color_hex(0xEFF6FF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_ai_label_ai_quick
screen_ai_label_ai_quick = lv.label(screen_ai)
screen_ai_label_ai_quick.set_text("Quick questions")
screen_ai_label_ai_quick.set_long_mode(lv.label.LONG.CLIP)
screen_ai_label_ai_quick.set_width(lv.pct(100))
screen_ai_label_ai_quick.set_pos(188, 188)
screen_ai_label_ai_quick.set_size(102, 14)
# Set style for screen_ai_label_ai_quick, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_ai_label_ai_quick.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_label_ai_quick.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_label_ai_quick.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_label_ai_quick.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_label_ai_quick.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_label_ai_quick.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_label_ai_quick.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_label_ai_quick.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_label_ai_quick.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_label_ai_quick.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_label_ai_quick.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_label_ai_quick.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_label_ai_quick.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_label_ai_quick.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_ai_ai_quick_question_bg
screen_ai_ai_quick_question_bg = lv.image(screen_ai)
screen_ai_ai_quick_question_bg.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\quick_question_bg_132_44.png"))
screen_ai_ai_quick_question_bg.add_flag(lv.obj.FLAG.CLICKABLE)
screen_ai_ai_quick_question_bg.set_pivot(50,50)
screen_ai_ai_quick_question_bg.set_rotation(0)
screen_ai_ai_quick_question_bg.set_pos(174, 174)
screen_ai_ai_quick_question_bg.set_size(132, 44)
# Set style for screen_ai_ai_quick_question_bg, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_ai_ai_quick_question_bg.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_ai_ai_message_label
screen_ai_ai_message_label = lv.label(screen_ai)
screen_ai_ai_message_label.set_text("Ask me anything.")
screen_ai_ai_message_label.set_long_mode(lv.label.LONG.WRAP)
screen_ai_ai_message_label.set_width(lv.pct(100))
screen_ai_ai_message_label.set_pos(128, 42)
screen_ai_ai_message_label.set_size(150, 56)
# Set style for screen_ai_ai_message_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_ai_ai_message_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_message_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_message_label.set_style_text_color(lv.color_hex(0x5C628B), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_message_label.set_style_text_font(test_font("montserratMedium", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_message_label.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_message_label.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_message_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_message_label.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_message_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_message_label.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_message_label.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_message_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_message_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_message_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_ai_ai_state_label
screen_ai_ai_state_label = lv.label(screen_ai)
screen_ai_ai_state_label.set_text("Waiting")
screen_ai_ai_state_label.set_long_mode(lv.label.LONG.CLIP)
screen_ai_ai_state_label.set_width(lv.pct(100))
screen_ai_ai_state_label.set_pos(128, 16)
screen_ai_ai_state_label.set_size(120, 20)
# Set style for screen_ai_ai_state_label, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_ai_ai_state_label.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_state_label.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_state_label.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_state_label.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_state_label.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_state_label.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_state_label.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_state_label.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_state_label.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_state_label.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_state_label.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_state_label.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_state_label.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_ai_ai_state_label.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_ai_ai_state_icon
screen_ai_ai_state_icon = lv.image(screen_ai)
screen_ai_ai_state_icon.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\mic_button_idle_46_46.png"))
screen_ai_ai_state_icon.add_flag(lv.obj.FLAG.CLICKABLE)
screen_ai_ai_state_icon.set_pivot(50,50)
screen_ai_ai_state_icon.set_rotation(0)
screen_ai_ai_state_icon.set_pos(28, 176)
screen_ai_ai_state_icon.set_size(46, 46)
# Set style for screen_ai_ai_state_icon, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_ai_ai_state_icon.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_ai_ai_character_image
screen_ai_ai_character_image = lv.image(screen_ai)
screen_ai_ai_character_image.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\ai_character_idle_110_110.png"))
screen_ai_ai_character_image.add_flag(lv.obj.FLAG.CLICKABLE)
screen_ai_ai_character_image.set_pivot(50,50)
screen_ai_ai_character_image.set_rotation(0)
screen_ai_ai_character_image.set_pos(18, 78)
screen_ai_ai_character_image.set_size(110, 110)
# Set style for screen_ai_ai_character_image, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_ai_ai_character_image.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_ai_img_ai_bubble
screen_ai_img_ai_bubble = lv.image(screen_ai)
screen_ai_img_ai_bubble.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\speech_bubble_304_176.png"))
screen_ai_img_ai_bubble.add_flag(lv.obj.FLAG.CLICKABLE)
screen_ai_img_ai_bubble.set_pivot(50,50)
screen_ai_img_ai_bubble.set_rotation(0)
screen_ai_img_ai_bubble.set_pos(8, 56)
screen_ai_img_ai_bubble.set_size(304, 176)
# Set style for screen_ai_img_ai_bubble, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_ai_img_ai_bubble.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_ai.update_layout()
# Create screen_study
screen_study = lv.obj()
screen_study.set_size(320, 240)
screen_study.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_study, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_study.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study.set_style_bg_color(lv.color_hex(0xF4FFF6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_study_label_study_note
screen_study_label_study_note = lv.label(screen_study)
screen_study_label_study_note.set_text("Vocabulary / history / wordbook / K12 pending")
screen_study_label_study_note.set_long_mode(lv.label.LONG.CLIP)
screen_study_label_study_note.set_width(lv.pct(100))
screen_study_label_study_note.set_pos(20, 216)
screen_study_label_study_note.set_size(280, 16)
# Set style for screen_study_label_study_note, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_study_label_study_note.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_study_note.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_study_note.set_style_text_color(lv.color_hex(0x5C628B), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_study_note.set_style_text_font(test_font("montserratMedium", 11), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_study_note.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_study_note.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_study_note.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_study_note.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_study_note.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_study_note.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_study_note.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_study_note.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_study_note.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_study_note.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_study_cont_study_main
screen_study_cont_study_main = lv.obj(screen_study)
screen_study_cont_study_main.set_pos(16, 36)
screen_study_cont_study_main.set_size(288, 176)
screen_study_cont_study_main.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_study_cont_study_main, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_study_cont_study_main.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_cont_study_main.set_style_radius(18, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_cont_study_main.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_cont_study_main.set_style_bg_color(lv.color_hex(0xFFFFFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_cont_study_main.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_cont_study_main.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_cont_study_main.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_cont_study_main.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_cont_study_main.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_cont_study_main.set_style_shadow_width(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_cont_study_main.set_style_shadow_color(lv.color_hex(0xA0B4D6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_cont_study_main.set_style_shadow_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_cont_study_main.set_style_shadow_spread(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_cont_study_main.set_style_shadow_offset_x(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_cont_study_main.set_style_shadow_offset_y(2, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_study_study_k12
screen_study_study_k12 = lv.obj(screen_study_cont_study_main)
screen_study_study_k12.set_pos(150, 92)
screen_study_study_k12.set_size(126, 72)
screen_study_study_k12.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_study_study_k12, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_study_study_k12.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_k12.set_style_radius(16, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_k12.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_k12.set_style_bg_color(lv.color_hex(0xF9FBFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_k12.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_k12.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_k12.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_k12.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_k12.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_k12.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_study_label_k12
screen_study_label_k12 = lv.label(screen_study_study_k12)
screen_study_label_k12.set_text("K12")
screen_study_label_k12.set_long_mode(lv.label.LONG.CLIP)
screen_study_label_k12.set_width(lv.pct(100))
screen_study_label_k12.set_pos(52, 12)
screen_study_label_k12.set_size(60, 18)
# Set style for screen_study_label_k12, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_study_label_k12.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_k12.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_k12.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_k12.set_style_text_font(test_font("montserratMedium", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_k12.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_k12.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_k12.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_k12.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_k12.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_k12.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_k12.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_k12.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_k12.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_k12.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_study_img_k12
screen_study_img_k12 = lv.image(screen_study_study_k12)
screen_study_img_k12.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\placeholder_icon_k12_32_32.png"))
screen_study_img_k12.add_flag(lv.obj.FLAG.CLICKABLE)
screen_study_img_k12.set_pivot(50,50)
screen_study_img_k12.set_rotation(0)
screen_study_img_k12.set_pos(12, 10)
screen_study_img_k12.set_size(32, 32)
# Set style for screen_study_img_k12, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_study_img_k12.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_study_study_vocab
screen_study_study_vocab = lv.obj(screen_study_cont_study_main)
screen_study_study_vocab.set_pos(12, 92)
screen_study_study_vocab.set_size(126, 72)
screen_study_study_vocab.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_study_study_vocab, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_study_study_vocab.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_vocab.set_style_radius(16, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_vocab.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_vocab.set_style_bg_color(lv.color_hex(0xF9FBFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_vocab.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_vocab.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_vocab.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_vocab.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_vocab.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_vocab.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_study_label_vocab
screen_study_label_vocab = lv.label(screen_study_study_vocab)
screen_study_label_vocab.set_text("Vocabulary")
screen_study_label_vocab.set_long_mode(lv.label.LONG.CLIP)
screen_study_label_vocab.set_width(lv.pct(100))
screen_study_label_vocab.set_pos(52, 12)
screen_study_label_vocab.set_size(60, 18)
# Set style for screen_study_label_vocab, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_study_label_vocab.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_vocab.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_vocab.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_vocab.set_style_text_font(test_font("montserratMedium", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_vocab.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_vocab.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_vocab.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_vocab.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_vocab.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_vocab.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_vocab.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_vocab.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_vocab.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_vocab.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_study_img_vocab
screen_study_img_vocab = lv.image(screen_study_study_vocab)
screen_study_img_vocab.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\placeholder_icon_vocabulary_32_32.png"))
screen_study_img_vocab.add_flag(lv.obj.FLAG.CLICKABLE)
screen_study_img_vocab.set_pivot(50,50)
screen_study_img_vocab.set_rotation(0)
screen_study_img_vocab.set_pos(12, 10)
screen_study_img_vocab.set_size(32, 32)
# Set style for screen_study_img_vocab, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_study_img_vocab.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_study_study_wordbook
screen_study_study_wordbook = lv.obj(screen_study_cont_study_main)
screen_study_study_wordbook.set_pos(150, 12)
screen_study_study_wordbook.set_size(126, 72)
screen_study_study_wordbook.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_study_study_wordbook, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_study_study_wordbook.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_wordbook.set_style_radius(16, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_wordbook.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_wordbook.set_style_bg_color(lv.color_hex(0xF9FBFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_wordbook.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_wordbook.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_wordbook.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_wordbook.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_wordbook.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_wordbook.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_study_label_wordbook
screen_study_label_wordbook = lv.label(screen_study_study_wordbook)
screen_study_label_wordbook.set_text("Wordbook")
screen_study_label_wordbook.set_long_mode(lv.label.LONG.CLIP)
screen_study_label_wordbook.set_width(lv.pct(100))
screen_study_label_wordbook.set_pos(52, 12)
screen_study_label_wordbook.set_size(60, 18)
# Set style for screen_study_label_wordbook, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_study_label_wordbook.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_wordbook.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_wordbook.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_wordbook.set_style_text_font(test_font("montserratMedium", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_wordbook.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_wordbook.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_wordbook.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_wordbook.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_wordbook.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_wordbook.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_wordbook.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_wordbook.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_wordbook.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_wordbook.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_study_img_wordbook
screen_study_img_wordbook = lv.image(screen_study_study_wordbook)
screen_study_img_wordbook.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\placeholder_icon_word_study_32_32.png"))
screen_study_img_wordbook.add_flag(lv.obj.FLAG.CLICKABLE)
screen_study_img_wordbook.set_pivot(50,50)
screen_study_img_wordbook.set_rotation(0)
screen_study_img_wordbook.set_pos(12, 10)
screen_study_img_wordbook.set_size(32, 32)
# Set style for screen_study_img_wordbook, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_study_img_wordbook.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_study_study_dictionary
screen_study_study_dictionary = lv.obj(screen_study_cont_study_main)
screen_study_study_dictionary.set_pos(12, 12)
screen_study_study_dictionary.set_size(126, 72)
screen_study_study_dictionary.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_study_study_dictionary, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_study_study_dictionary.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_dictionary.set_style_radius(16, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_dictionary.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_dictionary.set_style_bg_color(lv.color_hex(0xF9FBFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_dictionary.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_dictionary.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_dictionary.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_dictionary.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_dictionary.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_study_dictionary.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_study_label_dictionary
screen_study_label_dictionary = lv.label(screen_study_study_dictionary)
screen_study_label_dictionary.set_text("Translate")
screen_study_label_dictionary.set_long_mode(lv.label.LONG.CLIP)
screen_study_label_dictionary.set_width(lv.pct(100))
screen_study_label_dictionary.set_pos(52, 12)
screen_study_label_dictionary.set_size(60, 18)
# Set style for screen_study_label_dictionary, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_study_label_dictionary.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_dictionary.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_dictionary.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_dictionary.set_style_text_font(test_font("montserratMedium", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_dictionary.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_dictionary.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_dictionary.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_dictionary.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_dictionary.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_dictionary.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_dictionary.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_dictionary.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_dictionary.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_study_label_dictionary.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_study_img_dictionary
screen_study_img_dictionary = lv.image(screen_study_study_dictionary)
screen_study_img_dictionary.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\placeholder_icon_dictionary_32_32.png"))
screen_study_img_dictionary.add_flag(lv.obj.FLAG.CLICKABLE)
screen_study_img_dictionary.set_pivot(50,50)
screen_study_img_dictionary.set_rotation(0)
screen_study_img_dictionary.set_pos(12, 10)
screen_study_img_dictionary.set_size(32, 32)
# Set style for screen_study_img_dictionary, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_study_img_dictionary.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_study_img_study_bg
screen_study_img_study_bg = lv.image(screen_study)
screen_study_img_study_bg.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\placeholder_msg_bg_320_240.png"))
screen_study_img_study_bg.add_flag(lv.obj.FLAG.CLICKABLE)
screen_study_img_study_bg.set_pivot(50,50)
screen_study_img_study_bg.set_rotation(0)
screen_study_img_study_bg.set_pos(0, 0)
screen_study_img_study_bg.set_size(320, 240)
# Set style for screen_study_img_study_bg, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_study_img_study_bg.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_study.update_layout()
# Create screen_alarm
screen_alarm = lv.obj()
screen_alarm.set_size(320, 240)
screen_alarm.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_alarm, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_alarm.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm.set_style_bg_color(lv.color_hex(0xFFF6EA), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_alarm_cont_alarm_card
screen_alarm_cont_alarm_card = lv.obj(screen_alarm)
screen_alarm_cont_alarm_card.set_pos(16, 52)
screen_alarm_cont_alarm_card.set_size(288, 176)
screen_alarm_cont_alarm_card.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_alarm_cont_alarm_card, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_alarm_cont_alarm_card.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_cont_alarm_card.set_style_radius(18, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_cont_alarm_card.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_cont_alarm_card.set_style_bg_color(lv.color_hex(0xFFFFFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_cont_alarm_card.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_cont_alarm_card.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_cont_alarm_card.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_cont_alarm_card.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_cont_alarm_card.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_cont_alarm_card.set_style_shadow_width(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_cont_alarm_card.set_style_shadow_color(lv.color_hex(0xA0B4D6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_cont_alarm_card.set_style_shadow_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_cont_alarm_card.set_style_shadow_spread(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_cont_alarm_card.set_style_shadow_offset_x(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_cont_alarm_card.set_style_shadow_offset_y(2, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_alarm_label_alarm_hint
screen_alarm_label_alarm_hint = lv.label(screen_alarm_cont_alarm_card)
screen_alarm_label_alarm_hint.set_text("Alarm center")
screen_alarm_label_alarm_hint.set_long_mode(lv.label.LONG.WRAP)
screen_alarm_label_alarm_hint.set_width(lv.pct(100))
screen_alarm_label_alarm_hint.set_pos(126, 78)
screen_alarm_label_alarm_hint.set_size(140, 22)
# Set style for screen_alarm_label_alarm_hint, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_alarm_label_alarm_hint.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_hint.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_hint.set_style_text_color(lv.color_hex(0x5C628B), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_hint.set_style_text_font(test_font("montserratMedium", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_hint.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_hint.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_hint.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_hint.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_hint.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_hint.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_hint.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_hint.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_hint.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_hint.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_alarm_img_alarm_clock
screen_alarm_img_alarm_clock = lv.image(screen_alarm_cont_alarm_card)
screen_alarm_img_alarm_clock.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\clock_bg_92_92.png"))
screen_alarm_img_alarm_clock.add_flag(lv.obj.FLAG.CLICKABLE)
screen_alarm_img_alarm_clock.set_pivot(50,50)
screen_alarm_img_alarm_clock.set_rotation(0)
screen_alarm_img_alarm_clock.set_pos(12, 42)
screen_alarm_img_alarm_clock.set_size(92, 92)
# Set style for screen_alarm_img_alarm_clock, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_alarm_img_alarm_clock.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_alarm_label_alarm_title
screen_alarm_label_alarm_title = lv.label(screen_alarm)
screen_alarm_label_alarm_title.set_text("Alarm")
screen_alarm_label_alarm_title.set_long_mode(lv.label.LONG.CLIP)
screen_alarm_label_alarm_title.set_width(lv.pct(100))
screen_alarm_label_alarm_title.set_pos(16, 12)
screen_alarm_label_alarm_title.set_size(80, 22)
# Set style for screen_alarm_label_alarm_title, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_alarm_label_alarm_title.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_title.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_title.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_title.set_style_text_font(test_font("montserratMedium", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_title.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_title.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_title.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_title.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_title.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_title.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_title.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_title.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_title.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_alarm_label_alarm_title.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_alarm_img_alarm_bg
screen_alarm_img_alarm_bg = lv.image(screen_alarm)
screen_alarm_img_alarm_bg.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\alarm_bg_320_240.png"))
screen_alarm_img_alarm_bg.add_flag(lv.obj.FLAG.CLICKABLE)
screen_alarm_img_alarm_bg.set_pivot(50,50)
screen_alarm_img_alarm_bg.set_rotation(0)
screen_alarm_img_alarm_bg.set_pos(0, 0)
screen_alarm_img_alarm_bg.set_size(320, 240)
# Set style for screen_alarm_img_alarm_bg, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_alarm_img_alarm_bg.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_alarm.update_layout()
# Create screen_weather
screen_weather = lv.obj()
screen_weather.set_size(320, 240)
screen_weather.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_weather, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_weather.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather.set_style_bg_color(lv.color_hex(0xF7F9FF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_weather_cont_weather_strip
screen_weather_cont_weather_strip = lv.obj(screen_weather)
screen_weather_cont_weather_strip.set_pos(216, 90)
screen_weather_cont_weather_strip.set_size(90, 136)
screen_weather_cont_weather_strip.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_weather_cont_weather_strip, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_weather_cont_weather_strip.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_strip.set_style_radius(18, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_strip.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_strip.set_style_bg_color(lv.color_hex(0xFFFFFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_strip.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_strip.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_strip.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_strip.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_strip.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_strip.set_style_shadow_width(4, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_strip.set_style_shadow_color(lv.color_hex(0xA0B4D6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_strip.set_style_shadow_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_strip.set_style_shadow_spread(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_strip.set_style_shadow_offset_x(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_strip.set_style_shadow_offset_y(2, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_weather_weather_row_2
screen_weather_weather_row_2 = lv.obj(screen_weather_cont_weather_strip)
screen_weather_weather_row_2.set_pos(0, 72)
screen_weather_weather_row_2.set_size(70, 32)
screen_weather_weather_row_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_weather_weather_row_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_weather_weather_row_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_weather_weather_row_label_2
screen_weather_weather_row_label_2 = lv.label(screen_weather_weather_row_2)
screen_weather_weather_row_label_2.set_text("Weather")
screen_weather_weather_row_label_2.set_long_mode(lv.label.LONG.CLIP)
screen_weather_weather_row_label_2.set_width(lv.pct(100))
screen_weather_weather_row_label_2.set_pos(26, 8)
screen_weather_weather_row_label_2.set_size(42, 14)
# Set style for screen_weather_weather_row_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_weather_weather_row_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_2.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_2.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_2.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_weather_weather_row_img_2
screen_weather_weather_row_img_2 = lv.image(screen_weather_weather_row_2)
screen_weather_weather_row_img_2.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\status_weather_20_20.png"))
screen_weather_weather_row_img_2.add_flag(lv.obj.FLAG.CLICKABLE)
screen_weather_weather_row_img_2.set_pivot(50,50)
screen_weather_weather_row_img_2.set_rotation(0)
screen_weather_weather_row_img_2.set_pos(0, 6)
screen_weather_weather_row_img_2.set_size(20, 20)
# Set style for screen_weather_weather_row_img_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_weather_weather_row_img_2.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_weather_weather_row_1
screen_weather_weather_row_1 = lv.obj(screen_weather_cont_weather_strip)
screen_weather_weather_row_1.set_pos(0, 38)
screen_weather_weather_row_1.set_size(70, 32)
screen_weather_weather_row_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_weather_weather_row_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_weather_weather_row_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_weather_weather_row_label_1
screen_weather_weather_row_label_1 = lv.label(screen_weather_weather_row_1)
screen_weather_weather_row_label_1.set_text("Battery")
screen_weather_weather_row_label_1.set_long_mode(lv.label.LONG.CLIP)
screen_weather_weather_row_label_1.set_width(lv.pct(100))
screen_weather_weather_row_label_1.set_pos(26, 8)
screen_weather_weather_row_label_1.set_size(42, 14)
# Set style for screen_weather_weather_row_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_weather_weather_row_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_1.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_1.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_weather_weather_row_img_1
screen_weather_weather_row_img_1 = lv.image(screen_weather_weather_row_1)
screen_weather_weather_row_img_1.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\status_battery_20_20.png"))
screen_weather_weather_row_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
screen_weather_weather_row_img_1.set_pivot(50,50)
screen_weather_weather_row_img_1.set_rotation(0)
screen_weather_weather_row_img_1.set_pos(0, 6)
screen_weather_weather_row_img_1.set_size(20, 20)
# Set style for screen_weather_weather_row_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_weather_weather_row_img_1.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_weather_weather_row_0
screen_weather_weather_row_0 = lv.obj(screen_weather_cont_weather_strip)
screen_weather_weather_row_0.set_pos(0, 4)
screen_weather_weather_row_0.set_size(70, 32)
screen_weather_weather_row_0.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_weather_weather_row_0, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_weather_weather_row_0.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_0.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_0.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_0.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_0.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_0.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_0.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_0.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_weather_weather_row_label_0
screen_weather_weather_row_label_0 = lv.label(screen_weather_weather_row_0)
screen_weather_weather_row_label_0.set_text("WiFi")
screen_weather_weather_row_label_0.set_long_mode(lv.label.LONG.CLIP)
screen_weather_weather_row_label_0.set_width(lv.pct(100))
screen_weather_weather_row_label_0.set_pos(26, 8)
screen_weather_weather_row_label_0.set_size(42, 14)
# Set style for screen_weather_weather_row_label_0, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_weather_weather_row_label_0.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_0.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_0.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_0.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_0.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_0.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_0.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_0.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_0.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_0.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_0.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_0.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_0.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_weather_row_label_0.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_weather_weather_row_img_0
screen_weather_weather_row_img_0 = lv.image(screen_weather_weather_row_0)
screen_weather_weather_row_img_0.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\status_wifi_20_20.png"))
screen_weather_weather_row_img_0.add_flag(lv.obj.FLAG.CLICKABLE)
screen_weather_weather_row_img_0.set_pivot(50,50)
screen_weather_weather_row_img_0.set_rotation(0)
screen_weather_weather_row_img_0.set_pos(0, 6)
screen_weather_weather_row_img_0.set_size(20, 20)
# Set style for screen_weather_weather_row_img_0, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_weather_weather_row_img_0.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_weather_cont_weather_panel
screen_weather_cont_weather_panel = lv.obj(screen_weather)
screen_weather_cont_weather_panel.set_pos(14, 90)
screen_weather_cont_weather_panel.set_size(188, 136)
screen_weather_cont_weather_panel.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_weather_cont_weather_panel, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_weather_cont_weather_panel.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_panel.set_style_radius(18, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_panel.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_panel.set_style_bg_color(lv.color_hex(0xFFFFFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_panel.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_panel.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_panel.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_panel.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_panel.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_panel.set_style_shadow_width(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_panel.set_style_shadow_color(lv.color_hex(0xA0B4D6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_panel.set_style_shadow_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_panel.set_style_shadow_spread(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_panel.set_style_shadow_offset_x(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_cont_weather_panel.set_style_shadow_offset_y(2, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_weather_label_weather_meta
screen_weather_label_weather_meta = lv.label(screen_weather_cont_weather_panel)
screen_weather_label_weather_meta.set_text("Today 09:00")
screen_weather_label_weather_meta.set_long_mode(lv.label.LONG.CLIP)
screen_weather_label_weather_meta.set_width(lv.pct(100))
screen_weather_label_weather_meta.set_pos(0, 112)
screen_weather_label_weather_meta.set_size(90, 14)
# Set style for screen_weather_label_weather_meta, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_weather_label_weather_meta.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_meta.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_meta.set_style_text_color(lv.color_hex(0x5C628B), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_meta.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_meta.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_meta.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_meta.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_meta.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_meta.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_meta.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_meta.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_meta.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_meta.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_meta.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_weather_label_weather_desc
screen_weather_label_weather_desc = lv.label(screen_weather_cont_weather_panel)
screen_weather_label_weather_desc.set_text("Sunny")
screen_weather_label_weather_desc.set_long_mode(lv.label.LONG.CLIP)
screen_weather_label_weather_desc.set_width(lv.pct(100))
screen_weather_label_weather_desc.set_pos(0, 42)
screen_weather_label_weather_desc.set_size(80, 18)
# Set style for screen_weather_label_weather_desc, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_weather_label_weather_desc.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_desc.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_desc.set_style_text_color(lv.color_hex(0x5C628B), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_desc.set_style_text_font(test_font("montserratMedium", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_desc.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_desc.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_desc.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_desc.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_desc.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_desc.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_desc.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_desc.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_desc.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_desc.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_weather_label_weather_temp
screen_weather_label_weather_temp = lv.label(screen_weather_cont_weather_panel)
screen_weather_label_weather_temp.set_text("24 C")
screen_weather_label_weather_temp.set_long_mode(lv.label.LONG.CLIP)
screen_weather_label_weather_temp.set_width(lv.pct(100))
screen_weather_label_weather_temp.set_pos(0, 0)
screen_weather_label_weather_temp.set_size(90, 34)
# Set style for screen_weather_label_weather_temp, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_weather_label_weather_temp.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_temp.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_temp.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_temp.set_style_text_font(test_font("montserratMedium", 28), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_temp.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_temp.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_temp.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_temp.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_temp.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_temp.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_temp.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_temp.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_temp.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_temp.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_weather_label_weather_title
screen_weather_label_weather_title = lv.label(screen_weather)
screen_weather_label_weather_title.set_text("Weather")
screen_weather_label_weather_title.set_long_mode(lv.label.LONG.CLIP)
screen_weather_label_weather_title.set_width(lv.pct(100))
screen_weather_label_weather_title.set_pos(16, 12)
screen_weather_label_weather_title.set_size(90, 22)
# Set style for screen_weather_label_weather_title, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_weather_label_weather_title.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_title.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_title.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_title.set_style_text_font(test_font("montserratMedium", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_title.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_title.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_title.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_title.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_title.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_title.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_title.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_title.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_title.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_weather_label_weather_title.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_weather_img_weather_icon
screen_weather_img_weather_icon = lv.image(screen_weather)
screen_weather_img_weather_icon.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\weather_sun_80_80.png"))
screen_weather_img_weather_icon.add_flag(lv.obj.FLAG.CLICKABLE)
screen_weather_img_weather_icon.set_pivot(50,50)
screen_weather_img_weather_icon.set_rotation(0)
screen_weather_img_weather_icon.set_pos(226, 14)
screen_weather_img_weather_icon.set_size(80, 80)
# Set style for screen_weather_img_weather_icon, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_weather_img_weather_icon.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_weather.update_layout()
# Create screen_timer
screen_timer = lv.obj()
screen_timer.set_size(320, 240)
screen_timer.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_timer, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_timer.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer.set_style_bg_color(lv.color_hex(0xF2F6FF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_timer_cont_timer_panel
screen_timer_cont_timer_panel = lv.obj(screen_timer)
screen_timer_cont_timer_panel.set_pos(14, 60)
screen_timer_cont_timer_panel.set_size(162, 156)
screen_timer_cont_timer_panel.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_timer_cont_timer_panel, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_timer_cont_timer_panel.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_cont_timer_panel.set_style_radius(18, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_cont_timer_panel.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_cont_timer_panel.set_style_bg_color(lv.color_hex(0xFFFFFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_cont_timer_panel.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_cont_timer_panel.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_cont_timer_panel.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_cont_timer_panel.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_cont_timer_panel.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_cont_timer_panel.set_style_shadow_width(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_cont_timer_panel.set_style_shadow_color(lv.color_hex(0xA0B4D6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_cont_timer_panel.set_style_shadow_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_cont_timer_panel.set_style_shadow_spread(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_cont_timer_panel.set_style_shadow_offset_x(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_cont_timer_panel.set_style_shadow_offset_y(2, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_timer_img_timer_btn
screen_timer_img_timer_btn = lv.image(screen_timer_cont_timer_panel)
screen_timer_img_timer_btn.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\button_timer_72_40.png"))
screen_timer_img_timer_btn.add_flag(lv.obj.FLAG.CLICKABLE)
screen_timer_img_timer_btn.set_pivot(50,50)
screen_timer_img_timer_btn.set_rotation(0)
screen_timer_img_timer_btn.set_pos(0, 100)
screen_timer_img_timer_btn.set_size(72, 40)
# Set style for screen_timer_img_timer_btn, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_timer_img_timer_btn.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_timer_label_timer_sub
screen_timer_label_timer_sub = lv.label(screen_timer_cont_timer_panel)
screen_timer_label_timer_sub.set_text("Focus timer")
screen_timer_label_timer_sub.set_long_mode(lv.label.LONG.CLIP)
screen_timer_label_timer_sub.set_width(lv.pct(100))
screen_timer_label_timer_sub.set_pos(0, 42)
screen_timer_label_timer_sub.set_size(100, 18)
# Set style for screen_timer_label_timer_sub, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_timer_label_timer_sub.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_sub.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_sub.set_style_text_color(lv.color_hex(0x5C628B), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_sub.set_style_text_font(test_font("montserratMedium", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_sub.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_sub.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_sub.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_sub.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_sub.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_sub.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_sub.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_sub.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_sub.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_sub.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_timer_label_timer_time
screen_timer_label_timer_time = lv.label(screen_timer_cont_timer_panel)
screen_timer_label_timer_time.set_text("25:00")
screen_timer_label_timer_time.set_long_mode(lv.label.LONG.CLIP)
screen_timer_label_timer_time.set_width(lv.pct(100))
screen_timer_label_timer_time.set_pos(0, 0)
screen_timer_label_timer_time.set_size(100, 34)
# Set style for screen_timer_label_timer_time, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_timer_label_timer_time.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_time.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_time.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_time.set_style_text_font(test_font("montserratMedium", 28), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_time.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_time.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_time.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_time.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_time.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_time.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_time.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_time.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_time.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_time.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_timer_label_timer_title
screen_timer_label_timer_title = lv.label(screen_timer)
screen_timer_label_timer_title.set_text("Timer")
screen_timer_label_timer_title.set_long_mode(lv.label.LONG.CLIP)
screen_timer_label_timer_title.set_width(lv.pct(100))
screen_timer_label_timer_title.set_pos(16, 12)
screen_timer_label_timer_title.set_size(80, 22)
# Set style for screen_timer_label_timer_title, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_timer_label_timer_title.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_title.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_title.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_title.set_style_text_font(test_font("montserratMedium", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_title.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_title.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_title.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_title.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_title.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_title.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_title.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_title.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_title.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_timer_label_timer_title.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_timer_img_timer_clock
screen_timer_img_timer_clock = lv.image(screen_timer)
screen_timer_img_timer_clock.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\clock_bg_132_132.png"))
screen_timer_img_timer_clock.add_flag(lv.obj.FLAG.CLICKABLE)
screen_timer_img_timer_clock.set_pivot(50,50)
screen_timer_img_timer_clock.set_rotation(0)
screen_timer_img_timer_clock.set_pos(178, 52)
screen_timer_img_timer_clock.set_size(132, 132)
# Set style for screen_timer_img_timer_clock, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_timer_img_timer_clock.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_timer.update_layout()
# Create screen_stopwatch
screen_stopwatch = lv.obj()
screen_stopwatch.set_size(320, 240)
screen_stopwatch.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_stopwatch, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_stopwatch.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch.set_style_bg_color(lv.color_hex(0xF2FFF7), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_stopwatch_cont_stopwatch_panel
screen_stopwatch_cont_stopwatch_panel = lv.obj(screen_stopwatch)
screen_stopwatch_cont_stopwatch_panel.set_pos(14, 58)
screen_stopwatch_cont_stopwatch_panel.set_size(172, 158)
screen_stopwatch_cont_stopwatch_panel.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_stopwatch_cont_stopwatch_panel, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_stopwatch_cont_stopwatch_panel.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_cont_stopwatch_panel.set_style_radius(18, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_cont_stopwatch_panel.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_cont_stopwatch_panel.set_style_bg_color(lv.color_hex(0xFFFFFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_cont_stopwatch_panel.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_cont_stopwatch_panel.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_cont_stopwatch_panel.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_cont_stopwatch_panel.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_cont_stopwatch_panel.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_cont_stopwatch_panel.set_style_shadow_width(6, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_cont_stopwatch_panel.set_style_shadow_color(lv.color_hex(0xA0B4D6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_cont_stopwatch_panel.set_style_shadow_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_cont_stopwatch_panel.set_style_shadow_spread(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_cont_stopwatch_panel.set_style_shadow_offset_x(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_cont_stopwatch_panel.set_style_shadow_offset_y(2, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_stopwatch_label_stopwatch_lap
screen_stopwatch_label_stopwatch_lap = lv.label(screen_stopwatch_cont_stopwatch_panel)
screen_stopwatch_label_stopwatch_lap.set_text("Lap 01")
screen_stopwatch_label_stopwatch_lap.set_long_mode(lv.label.LONG.CLIP)
screen_stopwatch_label_stopwatch_lap.set_width(lv.pct(100))
screen_stopwatch_label_stopwatch_lap.set_pos(20, 54)
screen_stopwatch_label_stopwatch_lap.set_size(80, 14)
# Set style for screen_stopwatch_label_stopwatch_lap, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_stopwatch_label_stopwatch_lap.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_lap.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_lap.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_lap.set_style_text_font(test_font("montserratMedium", 12), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_lap.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_lap.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_lap.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_lap.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_lap.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_lap.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_lap.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_lap.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_lap.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_lap.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_stopwatch_img_stopwatch_lap
screen_stopwatch_img_stopwatch_lap = lv.image(screen_stopwatch_cont_stopwatch_panel)
screen_stopwatch_img_stopwatch_lap.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\lap_item_bg_120_28.png"))
screen_stopwatch_img_stopwatch_lap.add_flag(lv.obj.FLAG.CLICKABLE)
screen_stopwatch_img_stopwatch_lap.set_pivot(50,50)
screen_stopwatch_img_stopwatch_lap.set_rotation(0)
screen_stopwatch_img_stopwatch_lap.set_pos(0, 48)
screen_stopwatch_img_stopwatch_lap.set_size(120, 28)
# Set style for screen_stopwatch_img_stopwatch_lap, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_stopwatch_img_stopwatch_lap.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_stopwatch_label_stopwatch_time
screen_stopwatch_label_stopwatch_time = lv.label(screen_stopwatch_cont_stopwatch_panel)
screen_stopwatch_label_stopwatch_time.set_text("00:12.45")
screen_stopwatch_label_stopwatch_time.set_long_mode(lv.label.LONG.CLIP)
screen_stopwatch_label_stopwatch_time.set_width(lv.pct(100))
screen_stopwatch_label_stopwatch_time.set_pos(0, 0)
screen_stopwatch_label_stopwatch_time.set_size(120, 30)
# Set style for screen_stopwatch_label_stopwatch_time, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_stopwatch_label_stopwatch_time.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_time.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_time.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_time.set_style_text_font(test_font("montserratMedium", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_time.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_time.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_time.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_time.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_time.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_time.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_time.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_time.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_time.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_time.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_stopwatch_label_stopwatch_title
screen_stopwatch_label_stopwatch_title = lv.label(screen_stopwatch)
screen_stopwatch_label_stopwatch_title.set_text("Stopwatch")
screen_stopwatch_label_stopwatch_title.set_long_mode(lv.label.LONG.CLIP)
screen_stopwatch_label_stopwatch_title.set_width(lv.pct(100))
screen_stopwatch_label_stopwatch_title.set_pos(16, 12)
screen_stopwatch_label_stopwatch_title.set_size(110, 22)
# Set style for screen_stopwatch_label_stopwatch_title, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_stopwatch_label_stopwatch_title.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_title.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_title.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_title.set_style_text_font(test_font("montserratMedium", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_title.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_title.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_title.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_title.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_title.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_title.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_title.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_title.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_title.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_stopwatch_label_stopwatch_title.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_stopwatch_img_stopwatch_bg
screen_stopwatch_img_stopwatch_bg = lv.image(screen_stopwatch)
screen_stopwatch_img_stopwatch_bg.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\stopwatch_bg_136_132.png"))
screen_stopwatch_img_stopwatch_bg.add_flag(lv.obj.FLAG.CLICKABLE)
screen_stopwatch_img_stopwatch_bg.set_pivot(50,50)
screen_stopwatch_img_stopwatch_bg.set_rotation(0)
screen_stopwatch_img_stopwatch_bg.set_pos(174, 54)
screen_stopwatch_img_stopwatch_bg.set_size(136, 132)
# Set style for screen_stopwatch_img_stopwatch_bg, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_stopwatch_img_stopwatch_bg.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_stopwatch.update_layout()
# Create screen_focus
screen_focus = lv.obj()
screen_focus.set_size(320, 240)
screen_focus.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_focus, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_focus.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus.set_style_bg_color(lv.color_hex(0xFFF4EC), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_focus_img_focus_start
screen_focus_img_focus_start = lv.image(screen_focus)
screen_focus_img_focus_start.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\button_focus_start_84_40.png"))
screen_focus_img_focus_start.add_flag(lv.obj.FLAG.CLICKABLE)
screen_focus_img_focus_start.set_pivot(50,50)
screen_focus_img_focus_start.set_rotation(0)
screen_focus_img_focus_start.set_pos(220, 184)
screen_focus_img_focus_start.set_size(84, 40)
# Set style for screen_focus_img_focus_start, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_focus_img_focus_start.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_focus_cont_focus_stats
screen_focus_cont_focus_stats = lv.obj(screen_focus)
screen_focus_cont_focus_stats.set_pos(14, 118)
screen_focus_cont_focus_stats.set_size(144, 96)
screen_focus_cont_focus_stats.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_focus_cont_focus_stats, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_focus_cont_focus_stats.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_cont_focus_stats.set_style_radius(18, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_cont_focus_stats.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_cont_focus_stats.set_style_bg_color(lv.color_hex(0xFFFFFF), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_cont_focus_stats.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_cont_focus_stats.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_cont_focus_stats.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_cont_focus_stats.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_cont_focus_stats.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_cont_focus_stats.set_style_shadow_width(4, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_cont_focus_stats.set_style_shadow_color(lv.color_hex(0xA0B4D6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_cont_focus_stats.set_style_shadow_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_cont_focus_stats.set_style_shadow_spread(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_cont_focus_stats.set_style_shadow_offset_x(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_cont_focus_stats.set_style_shadow_offset_y(2, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_focus_img_focus_stats
screen_focus_img_focus_stats = lv.image(screen_focus_cont_focus_stats)
screen_focus_img_focus_stats.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\focus_stats_bg_124_76.png"))
screen_focus_img_focus_stats.add_flag(lv.obj.FLAG.CLICKABLE)
screen_focus_img_focus_stats.set_pivot(50,50)
screen_focus_img_focus_stats.set_rotation(0)
screen_focus_img_focus_stats.set_pos(0, 0)
screen_focus_img_focus_stats.set_size(124, 76)
# Set style for screen_focus_img_focus_stats, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_focus_img_focus_stats.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_focus_img_focus_tomato
screen_focus_img_focus_tomato = lv.image(screen_focus)
screen_focus_img_focus_tomato.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\focus_tomato_38_38.png"))
screen_focus_img_focus_tomato.add_flag(lv.obj.FLAG.CLICKABLE)
screen_focus_img_focus_tomato.set_pivot(50,50)
screen_focus_img_focus_tomato.set_rotation(0)
screen_focus_img_focus_tomato.set_pos(252, 12)
screen_focus_img_focus_tomato.set_size(38, 38)
# Set style for screen_focus_img_focus_tomato, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_focus_img_focus_tomato.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_focus_img_focus_fill
screen_focus_img_focus_fill = lv.image(screen_focus)
screen_focus_img_focus_fill.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\focus_progress_fill_140_16.png"))
screen_focus_img_focus_fill.add_flag(lv.obj.FLAG.CLICKABLE)
screen_focus_img_focus_fill.set_pivot(50,50)
screen_focus_img_focus_fill.set_rotation(0)
screen_focus_img_focus_fill.set_pos(20, 190)
screen_focus_img_focus_fill.set_size(140, 16)
# Set style for screen_focus_img_focus_fill, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_focus_img_focus_fill.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_focus_img_focus_bg
screen_focus_img_focus_bg = lv.image(screen_focus)
screen_focus_img_focus_bg.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\focus_progress_bg_150_120.png"))
screen_focus_img_focus_bg.add_flag(lv.obj.FLAG.CLICKABLE)
screen_focus_img_focus_bg.set_pivot(50,50)
screen_focus_img_focus_bg.set_rotation(0)
screen_focus_img_focus_bg.set_pos(160, 60)
screen_focus_img_focus_bg.set_size(150, 120)
# Set style for screen_focus_img_focus_bg, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_focus_img_focus_bg.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_focus_label_focus_title
screen_focus_label_focus_title = lv.label(screen_focus)
screen_focus_label_focus_title.set_text("Focus")
screen_focus_label_focus_title.set_long_mode(lv.label.LONG.CLIP)
screen_focus_label_focus_title.set_width(lv.pct(100))
screen_focus_label_focus_title.set_pos(16, 12)
screen_focus_label_focus_title.set_size(80, 22)
# Set style for screen_focus_label_focus_title, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_focus_label_focus_title.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_label_focus_title.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_label_focus_title.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_label_focus_title.set_style_text_font(test_font("montserratMedium", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_label_focus_title.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_label_focus_title.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_label_focus_title.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_label_focus_title.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_label_focus_title.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_label_focus_title.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_label_focus_title.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_label_focus_title.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_label_focus_title.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_focus_label_focus_title.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_focus.update_layout()
# Create screen_night_light
screen_night_light = lv.obj()
screen_night_light.set_size(320, 240)
screen_night_light.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_night_light, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_night_light.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_night_light.set_style_bg_color(lv.color_hex(0xFFF7D6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_night_light.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_night_light_img_night_thumb
screen_night_light_img_night_thumb = lv.image(screen_night_light)
screen_night_light_img_night_thumb.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\slider_thumb_24_24.png"))
screen_night_light_img_night_thumb.add_flag(lv.obj.FLAG.CLICKABLE)
screen_night_light_img_night_thumb.set_pivot(50,50)
screen_night_light_img_night_thumb.set_rotation(0)
screen_night_light_img_night_thumb.set_pos(164, 134)
screen_night_light_img_night_thumb.set_size(24, 24)
# Set style for screen_night_light_img_night_thumb, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_night_light_img_night_thumb.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_night_light_img_night_slider
screen_night_light_img_night_slider = lv.image(screen_night_light)
screen_night_light_img_night_slider.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\slider_bg_148_16.png"))
screen_night_light_img_night_slider.add_flag(lv.obj.FLAG.CLICKABLE)
screen_night_light_img_night_slider.set_pivot(50,50)
screen_night_light_img_night_slider.set_rotation(0)
screen_night_light_img_night_slider.set_pos(86, 146)
screen_night_light_img_night_slider.set_size(148, 16)
# Set style for screen_night_light_img_night_slider, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_night_light_img_night_slider.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_night_light_img_night_toggle
screen_night_light_img_night_toggle = lv.image(screen_night_light)
screen_night_light_img_night_toggle.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\button_toggle_light_92_36.png"))
screen_night_light_img_night_toggle.add_flag(lv.obj.FLAG.CLICKABLE)
screen_night_light_img_night_toggle.set_pivot(50,50)
screen_night_light_img_night_toggle.set_rotation(0)
screen_night_light_img_night_toggle.set_pos(20, 178)
screen_night_light_img_night_toggle.set_size(92, 36)
# Set style for screen_night_light_img_night_toggle, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_night_light_img_night_toggle.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_night_light_img_night_bg
screen_night_light_img_night_bg = lv.image(screen_night_light)
screen_night_light_img_night_bg.set_src(load_image(r"D:\work\wifi\manul\xiaozhi\xiaozhi-esp32_main\main\boards\esp32-alarm\ui_designer\alarm\generated\MicroPython\night_light_off_110_130.png"))
screen_night_light_img_night_bg.add_flag(lv.obj.FLAG.CLICKABLE)
screen_night_light_img_night_bg.set_pivot(50,50)
screen_night_light_img_night_bg.set_rotation(0)
screen_night_light_img_night_bg.set_pos(180, 50)
screen_night_light_img_night_bg.set_size(110, 130)
# Set style for screen_night_light_img_night_bg, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_night_light_img_night_bg.set_style_image_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_night_light_label_night_title
screen_night_light_label_night_title = lv.label(screen_night_light)
screen_night_light_label_night_title.set_text("Night Light")
screen_night_light_label_night_title.set_long_mode(lv.label.LONG.CLIP)
screen_night_light_label_night_title.set_width(lv.pct(100))
screen_night_light_label_night_title.set_pos(16, 12)
screen_night_light_label_night_title.set_size(120, 22)
# Set style for screen_night_light_label_night_title, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_night_light_label_night_title.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_night_light_label_night_title.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_night_light_label_night_title.set_style_text_color(lv.color_hex(0x1F2450), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_night_light_label_night_title.set_style_text_font(test_font("montserratMedium", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_night_light_label_night_title.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_night_light_label_night_title.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_night_light_label_night_title.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_night_light_label_night_title.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_night_light_label_night_title.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_night_light_label_night_title.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_night_light_label_night_title.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_night_light_label_night_title.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_night_light_label_night_title.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_night_light_label_night_title.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_night_light.update_layout()

# content from custom.py

# Load the default screen
lv.screen_load(screen_weather)

if __name__ == '__main__':
    while True:
        lv.task_handler()
        time.sleep_ms(5)
