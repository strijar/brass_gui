/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
    cw_key_manual = 0,
    cw_key_auto_left = 1,
    cw_key_auto_right = 2
} cw_key_mode_t;

typedef enum {
    cw_key_iambic_a = 0,
    cw_key_iambic_b = 1
} cw_key_iambic_mode_t;

void cw_key_init();

uint16_t cw_key_change_speed(int16_t d);
cw_key_mode_t cw_key_change_mode(int16_t d);
cw_key_iambic_mode_t cw_key_change_iambic_mode(int16_t d);
uint16_t cw_key_change_tone(int16_t d);
uint16_t cw_key_change_vol(int16_t d);
bool cw_key_change_train(int16_t d);
uint16_t cw_key_change_qsk_time(int16_t d);
uint8_t cw_key_change_ratio(int16_t d);

#ifndef __cplusplus
#include <complex.h>

size_t cw_key_generator(float complex *data, size_t max_size, bool reverse);

#endif
