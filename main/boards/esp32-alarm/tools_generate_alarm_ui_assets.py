from __future__ import annotations

from pathlib import Path


ROOT = Path(__file__).resolve().parent
OUT_CPP = ROOT / "ui_generated" / "alarm_ui_assets.cpp"
OUT_H = ROOT / "ui_generated" / "alarm_ui_assets.h"


ENTRIES = [
    ("ai_character_idle.png", "_ai_character_idle_RGB565A8_110x110"),
    ("ai_character_listening.png", "_ai_character_listening_RGB565A8_120x120"),
    ("ai_character_thinking.png", "_ai_character_thinking_RGB565A8_120x120"),
    ("ai_character_speaking.png", "_ai_character_speaking_RGB565A8_120x120"),
    ("mic_button_idle.png", "_mic_button_idle_RGB565A8_46x46"),
    ("mic_button_listening.png", "_mic_button_listening_RGB565A8_80x80"),
    ("mic_button_thinking.png", "_mic_button_thinking_RGB565A8_80x80"),
    ("mic_button_speaking.png", "_mic_button_speaking_RGB565A8_80x80"),
]


def main() -> None:
    OUT_CPP.parent.mkdir(parents=True, exist_ok=True)

    cpp = "\n".join(
        [
            '#include "alarm_ui_assets.h"',
            "",
            '#include "gui_guider.h"',
            "",
            "#include <cstring>",
            "",
            "LV_IMAGE_DECLARE(_ai_character_listening_RGB565A8_120x120);",
            "LV_IMAGE_DECLARE(_ai_character_thinking_RGB565A8_120x120);",
            "LV_IMAGE_DECLARE(_ai_character_speaking_RGB565A8_120x120);",
            "LV_IMAGE_DECLARE(_mic_button_listening_RGB565A8_80x80);",
            "LV_IMAGE_DECLARE(_mic_button_thinking_RGB565A8_80x80);",
            "LV_IMAGE_DECLARE(_mic_button_speaking_RGB565A8_80x80);",
            "",
            "namespace {",
            "struct AlarmImageEntry {",
            "    const char* file_name;",
            "    const lv_image_dsc_t* image;",
            "};",
            "",
            "static const AlarmImageEntry kAlarmImages[] = {",
        ]
        + [f'    {{"{file_name}", &{symbol}}},' for file_name, symbol in ENTRIES]
        + [
            "};",
            "",
            "const lv_image_dsc_t* FindAlarmImage(const char* file_name) {",
            "    if (file_name == nullptr) {",
            "        return nullptr;",
            "    }",
            "    for (const auto& entry : kAlarmImages) {",
            "        if (std::strcmp(entry.file_name, file_name) == 0) {",
            "            return entry.image;",
            "        }",
            "    }",
            "    return nullptr;",
            "}",
            "",
            "}  // namespace",
            "",
            "void alarm_ui_set_png_src(lv_obj_t* obj, const char* file_name) {",
            "    const lv_image_dsc_t* image = FindAlarmImage(file_name);",
            "    if (obj == nullptr || image == nullptr) {",
            "        return;",
            "    }",
            "    lv_image_set_src(obj, image);",
            "}",
            "",
            "void alarm_ui_set_png_fit(lv_obj_t* obj, const char* file_name, lv_coord_t max_w, lv_coord_t max_h) {",
            "    const lv_image_dsc_t* image = FindAlarmImage(file_name);",
            "    if (obj == nullptr || image == nullptr) {",
            "        return;",
            "    }",
            "",
            "    lv_image_set_src(obj, image);",
            "    if (image->header.w <= 0 || image->header.h <= 0) {",
            "        return;",
            "    }",
            "",
            "    const uint32_t scale_w = (static_cast<uint32_t>(max_w) * 256U) / image->header.w;",
            "    const uint32_t scale_h = (static_cast<uint32_t>(max_h) * 256U) / image->header.h;",
            "    const uint32_t scale = scale_w < scale_h ? scale_w : scale_h;",
            "    lv_image_set_scale(obj, scale > 0 ? scale : 256U);",
            "}",
            "",
        ]
    )

    h = "\n".join(
        [
            "#ifndef ESP32_ALARM_UI_ASSETS_H",
            "#define ESP32_ALARM_UI_ASSETS_H",
            "",
            '#include "lvgl.h"',
            "",
            "#ifdef __cplusplus",
            'extern "C" {',
            "#endif",
            "",
            "void alarm_ui_set_png_src(lv_obj_t* obj, const char* file_name);",
            "void alarm_ui_set_png_fit(lv_obj_t* obj, const char* file_name, lv_coord_t max_w, lv_coord_t max_h);",
            "",
            "#ifdef __cplusplus",
            "}",
            "#endif",
            "",
            "#endif",
            "",
        ]
    )

    OUT_CPP.write_text(cpp, encoding="utf-8")
    OUT_H.write_text(h, encoding="utf-8")


if __name__ == "__main__":
    main()
