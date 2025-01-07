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
#include "filter.h"

typedef struct {
    char                qth[16];
    char                callsign[16];
} options_operator_t;

typedef struct {
    filter_t            filter;
} options_mic_t;

typedef struct {
    uint8_t             vol;
    options_mic_t       mic;
} options_audio_t;

typedef struct {
    options_operator_t  operator;
    options_audio_t     audio;
} options_t;

extern options_t   *options;

void settings_options_load();
void settings_options_save();
