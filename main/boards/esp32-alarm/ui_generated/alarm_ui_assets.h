#ifndef ESP32_ALARM_UI_ASSETS_H
#define ESP32_ALARM_UI_ASSETS_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

void alarm_ui_set_png_src(lv_obj_t* obj, const char* file_name);
void alarm_ui_set_png_fit(lv_obj_t* obj, const char* file_name, lv_coord_t max_w, lv_coord_t max_h);

#ifdef __cplusplus
}
#endif

#endif
