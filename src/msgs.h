/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#pragma once

#include <stdint.h>

typedef enum {
    MSG_MODE_CHANGED = 1,
    MSG_FILTER_CHANGED,
    MSG_FREQ_RX_CHANGED,
    MSG_FREQ_FFT_CHANGED
} msgs_t;
