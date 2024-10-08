/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#pragma once

#include <stdint.h>

typedef struct {
    float   min;
    float   max;
} msgs_auto_t;

typedef struct {
    float   *data;
    size_t  size;
} msgs_floats_t;

typedef enum {
    MSG_MODE_CHANGED = 1,
    MSG_FILTER_CHANGED,
    MSG_FREQ_RX_CHANGED,
    MSG_FREQ_TX_CHANGED,
    MSG_FREQ_FFT_CHANGED,
    MSG_FREQ_FFT_SHIFT,
    MSG_RATE_FFT_CHANGED,   /* uint8_t */
    MSG_SPECTRUM_AUTO,      /* msgs_auto_t */
    MSG_WATERFALL_AUTO,     /* msgs_auto_t */
    MSG_SPECTRUM_DATA,      /* msgs_floats_t */
    MSG_PTT,                /* int32_t */
} msgs_t;
