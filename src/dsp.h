/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <liquid/liquid.h>

void dsp_init();
void dsp_adc(float complex *data);
void dsp_fft(float complex *data);
void dsp_reset();

void dsp_set_spectrum_factor(uint8_t x);

float dsp_get_spectrum_beta();
void dsp_set_spectrum_beta(float x);

void dsp_put_audio_samples(size_t nsamples, int16_t *samples);
void dsp_auto_clear();

void dsp_set_vol(uint8_t x);
uint16_t dsp_change_vol(int16_t df);
