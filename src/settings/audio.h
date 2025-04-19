/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <cyaml/cyaml.h>

#include "filter.h"

#define EQUALIZER_NUM   3

typedef struct {
    int16_t     freq;
    int16_t     q;      /* 1 .. 10 */
    int16_t     gain;   /* -20 .. 10 */
} equalizer_item_t;

typedef struct {
    filter_t            filter;
    equalizer_item_t    *eq;
} options_mic_t;

typedef struct {
    uint8_t             vol;
    equalizer_item_t    *eq;
} options_speaker_t;

typedef enum {
    REC_FORMAT_WAV = 0,
    REC_FORMAT_MP3
} rec_format_t;

typedef struct {
    bool                enable;
    bool                before_agc;
    uint16_t            frame_size;
    int16_t             reduction_amount;
    int16_t             smoothing_factor;
    int16_t             whitening_factor;
    int16_t             noise_scaling_type;
    int16_t             noise_rescale;
    int16_t             post_filter_threshold;
} denoise_t;

typedef struct {
    options_speaker_t   speaker;
    options_mic_t       mic;
    rec_format_t        rec_format;
    denoise_t           denoise;
} options_audio_t;

extern const cyaml_schema_field_t audio_fields_schema[];
