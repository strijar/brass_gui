/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>

void audio_adc_init();
int audio_adc_play(int16_t *buf, size_t samples);

void audio_adc_set_vol(uint8_t x);
