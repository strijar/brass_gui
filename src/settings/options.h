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
    float               beta;
    bool                filled;
    bool                peak;
    uint16_t            peak_hold;
    float               peak_speed;
} options_spectrum_t;

typedef enum {
    ACTION_NONE = 0,
    ACTION_SCREENSHOT,
    ACTION_RECORDER,
    ACTION_MUTE,
    ACTION_STEP_UP,
    ACTION_STEP_DOWN,
    ACTION_VOICE_MODE,

    ACTION_APP_RTTY = 100,
    ACTION_APP_FT8,
    ACTION_APP_SWRSCAN,
    ACTION_APP_GPS,
    ACTION_APP_SETTINGS,
    ACTION_APP_RECORDER,
    ACTION_APP_QTH,
    ACTION_APP_CALLSIGN
} options_action_t;

typedef struct {
    uint64_t            vol;
    uint64_t            mfk;
    options_action_t    long_vol;
    options_action_t    long_mfk;
    options_action_t    long_app;
    options_action_t    long_band_down;
    options_action_t    long_band_up;
} options_control_t;

typedef struct {
    uint16_t            center;
    uint16_t            shift;
    float               rate;
    bool                reverse;
    uint8_t             bits;
    float               snr;
} options_rtty_t;

typedef struct {
    bool                decoder;
    float               decoder_snr;
    float               decoder_snr_gist;
    float               decoder_peak_beta;
    float               decoder_noise_beta;
} options_cw_t;

typedef struct {
    uint16_t            tones;
    uint16_t            band_width;
    uint16_t            band_lower;
    uint16_t            sync_margin;
    uint16_t            sync_integ;
    float               sync_threshold;
} options_olivia_t;

typedef struct {
    options_operator_t  op;
    options_audio_t     audio;
    options_spectrum_t  spectrum;
    options_control_t   control;
    options_rtty_t      rtty;
    options_cw_t        cw;
    options_olivia_t    olivia;
} options_t;

extern options_t   *options;

void settings_options_load();
void settings_options_save();
