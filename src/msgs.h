/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#pragma once

#include <stdint.h>
#include "widgets/lv_finder.h"

typedef struct {
    float   min;
    float   max;
} msgs_auto_t;

typedef struct {
    float   *data;
    size_t  size;
} msgs_floats_t;

typedef struct {
    uint8_t num;
    int16_t cursor[LV_FINDER_CURSORS];
} msg_finder_cursor_t;

typedef enum {
    MSG_MODE_CHANGED = 1,
    MSG_FILTER_CHANGED,
    MSG_BAND_CHANGED,
    MSG_FREQ_RX_PRE_CHANGED,    /* uint64_t */
    MSG_FREQ_RX_CHANGED,        /* uint64_t */
    MSG_FREQ_TX_PRE_CHANGED,    /* uint64_t */
    MSG_FREQ_TX_CHANGED,        /* uint64_t */
    MSG_FREQ_FFT_CHANGED,       /* uint64_t */
    MSG_FREQ_FFT_SHIFT,         /* int32_t */
    MSG_RATE_FFT_CHANGED,       /* uint8_t */
    MSG_SPECTRUM_AUTO,          /* msgs_auto_t */
    MSG_WATERFALL_AUTO,         /* msgs_auto_t */
    MSG_SPECTRUM_DATA,          /* msgs_floats_t */
    MSG_WATERFALL_DATA,         /* msgs_floats_t */
    MSG_PTT,                    /* int32_t */
    MSG_TX,
    MSG_RX,
    MSG_FINDER_CURSOR,
} msgs_t;
