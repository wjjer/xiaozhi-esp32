/**
 * Project-specific LVGL configuration overrides.
 *
 * The Kconfig string type wraps values in double quotes (e.g. ""),
 * which are invalid as C attributes. This file pre-defines the
 * attribute macros as empty, preventing lv_conf_internal.h from
 * using the quoted Kconfig string values.
 */

#ifndef LV_CONF_H
#define LV_CONF_H

/* Fix: Kconfig string defaults produce invalid C attributes (e.g. "") */
#define LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_LARGE_CONST
#define LV_ATTRIBUTE_LARGE_RAM_ARRAY
#define LV_ATTRIBUTE_FAST_MEM

#endif /* LV_CONF_H */
