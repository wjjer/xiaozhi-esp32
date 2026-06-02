# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

# Add this line to disable the specific warning
add_compile_options(-Wno-missing-field-initializers)

# Fix: LVGL Kconfig string type wraps values in double quotes (e.g. ""),
# which are invalid as C attributes (e.g. static "" const uint8_t ...).
# Pre-define these macros as empty so lv_conf_internal.h's #ifndef guards skip them.
add_compile_definitions(
    LV_ATTRIBUTE_MEM_ALIGN=
    LV_ATTRIBUTE_LARGE_CONST=
    LV_ATTRIBUTE_LARGE_RAM_ARRAY=
    LV_ATTRIBUTE_FAST_MEM=
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
# "Trim" the build. Include the minimal set of components, main, and anything it depends on.
idf_build_set_property(MINIMAL_BUILD ON)

set(PROJECT_VER "2.2.4")
project(xiaozhi)
