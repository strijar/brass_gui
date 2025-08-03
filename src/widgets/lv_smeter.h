/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#ifndef LV_SMETER_H
#define LV_SMETER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/

#define S_MIN   (-134)
#define S1      (-121)
#define S2      (-115)
#define S3      (-109)
#define S4      (-103)
#define S5      (-97)
#define S6      (-91)
#define S7      (-85)
#define S8      (-79)
#define S9      (-73)
#define S9_20   (S9 + 20)
#define S9_40   (S9 + 40)

/**********************
 *      TYPEDEFS
 **********************/

enum {
    LV_PART_METER_1     = LV_PART_CUSTOM_FIRST,
    LV_PART_METER_2     = LV_PART_CUSTOM_FIRST + 0x10000,
    LV_PART_METER_3     = LV_PART_CUSTOM_FIRST + 0x20000,
    LV_PART_METER_4     = LV_PART_CUSTOM_FIRST + 0x30000
};

typedef struct {
    lv_obj_t            obj;

    float               min;
    float               max;
    float               value;
    int16_t             slice_db;
    int16_t             slice_width;
    int16_t             slice_pad;
    int16_t             part[3];
} lv_smeter_t;

extern const lv_obj_class_t lv_smeter_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t * lv_smeter_create(lv_obj_t * parent);

/*=====================
 * Setter functions
 *====================*/

void lv_smeter_set_value(lv_obj_t * obj, int16_t db);
void lv_smeter_set_part(lv_obj_t * obj, uint8_t index, int16_t db);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
