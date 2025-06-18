/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#include "audio.h"

static const cyaml_schema_field_t equalizer_fields_schema[] = {
    CYAML_FIELD_INT("freq",     CYAML_FLAG_OPTIONAL, equalizer_item_t, freq),
    CYAML_FIELD_INT("q",        CYAML_FLAG_OPTIONAL, equalizer_item_t, q),
    CYAML_FIELD_INT("gain",     CYAML_FLAG_OPTIONAL, equalizer_item_t, gain),
    CYAML_FIELD_END
};

static const cyaml_schema_value_t equalizer_schema = {
    CYAML_VALUE_MAPPING(CYAML_FLAG_FLOW, equalizer_item_t, equalizer_fields_schema)
};

static const cyaml_schema_field_t mic_fields_schema[] = {
    CYAML_FIELD_SEQUENCE_FIXED("eq",    CYAML_FLAG_POINTER, options_mic_t, eq, &equalizer_schema, EQUALIZER_NUM),
    CYAML_FIELD_MAPPING("filter",       CYAML_FLAG_FLOW, options_mic_t, filter, filter_fields_schema),
    CYAML_FIELD_END
};

static const cyaml_schema_field_t speaker_fields_schema[] = {
    CYAML_FIELD_UINT("vol",             CYAML_FLAG_OPTIONAL, options_speaker_t, vol),
    CYAML_FIELD_SEQUENCE_FIXED("eq",    CYAML_FLAG_POINTER, options_speaker_t, eq, &equalizer_schema, 3),
    CYAML_FIELD_END
};

static const cyaml_strval_t rec_format_strings[] = {
    { "wav",                REC_FORMAT_WAV },
    { "mp3",                REC_FORMAT_MP3 }
};

static const cyaml_strval_t denoise_mode_strings[] = {
    { "off",                DENOISE_OFF },
    { "nr",                 DENOISE_NR },
    { "emnr",               DENOISE_EMNR },
};

static const cyaml_schema_field_t options_nr_schema[] = {
    CYAML_FIELD_INT("frame_size",               CYAML_FLAG_OPTIONAL, options_nr_t, frame_size),
    CYAML_FIELD_INT("reduction_amount",         CYAML_FLAG_OPTIONAL, options_nr_t, reduction_amount),
    CYAML_FIELD_INT("smoothing_factor",         CYAML_FLAG_OPTIONAL, options_nr_t, smoothing_factor),
    CYAML_FIELD_INT("whitening_factor",         CYAML_FLAG_OPTIONAL, options_nr_t, whitening_factor),
    CYAML_FIELD_INT("noise_scaling_type",       CYAML_FLAG_OPTIONAL, options_nr_t, noise_scaling_type),
    CYAML_FIELD_INT("noise_rescale",            CYAML_FLAG_OPTIONAL, options_nr_t, noise_rescale),
    CYAML_FIELD_INT("post_filter_threshold",    CYAML_FLAG_OPTIONAL, options_nr_t, post_filter_threshold),
    CYAML_FIELD_END
};

static const cyaml_schema_field_t options_emnr_schema[] = {
    CYAML_FIELD_UINT("fft",                     CYAML_FLAG_OPTIONAL, options_emnr_t, fft),
    CYAML_FIELD_UINT("over",                    CYAML_FLAG_OPTIONAL, options_emnr_t, over),
    CYAML_FIELD_UINT("gain_method",             CYAML_FLAG_OPTIONAL, options_emnr_t, gain_method),
    CYAML_FIELD_UINT("npe_method",              CYAML_FLAG_OPTIONAL, options_emnr_t, npe_method),
    CYAML_FIELD_FLOAT("trained_thresh",         CYAML_FLAG_OPTIONAL, options_emnr_t, trained_thresh),
    CYAML_FIELD_FLOAT("trained_t2",             CYAML_FLAG_OPTIONAL, options_emnr_t, trained_t2),
    CYAML_FIELD_END
};

static const cyaml_schema_field_t denoise_fields_schema[] = {
    CYAML_FIELD_ENUM("mode",                    CYAML_FLAG_OPTIONAL, denoise_t, mode, denoise_mode_strings, CYAML_ARRAY_LEN(denoise_mode_strings)),
    CYAML_FIELD_BOOL("before_agc",              CYAML_FLAG_OPTIONAL, denoise_t, before_agc),
    CYAML_FIELD_MAPPING("nr",                   CYAML_FLAG_OPTIONAL, denoise_t, nr, options_nr_schema),
    CYAML_FIELD_MAPPING("emnr",                 CYAML_FLAG_OPTIONAL, denoise_t, emnr, options_emnr_schema),
    CYAML_FIELD_END
};

const cyaml_schema_field_t audio_fields_schema[] = {
    CYAML_FIELD_MAPPING("speaker",      CYAML_FLAG_OPTIONAL, options_audio_t, speaker, speaker_fields_schema),
    CYAML_FIELD_MAPPING("mic",          CYAML_FLAG_OPTIONAL, options_audio_t, mic, mic_fields_schema),
    CYAML_FIELD_ENUM("rec_format",      CYAML_FLAG_OPTIONAL, options_audio_t, rec_format, rec_format_strings, CYAML_ARRAY_LEN(rec_format_strings)),
    CYAML_FIELD_MAPPING("denoise",      CYAML_FLAG_OPTIONAL, options_audio_t, denoise, denoise_fields_schema),
    CYAML_FIELD_END
};
