/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#pragma once

#include <stdbool.h>

typedef struct {
    char    *morse;
    char    *character;
} cw_characters_t;

extern cw_characters_t cw_characters[];

void cw_decoder_init();

/* From thread */

void cw_decoder_signal(bool on, float ms);
