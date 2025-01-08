/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#include <cyaml/cyaml.h>
#include "lvgl/lvgl.h"
#include "options.h"
#include "src/qth.h"
#include "src/dsp.h"
#include "src/vol.h"
#include "src/mfk.h"

static const char  filename[] = "/mnt/settings/options.yaml";

static const cyaml_schema_field_t operator_fields_schema[] = {
    CYAML_FIELD_STRING("qth",           CYAML_FLAG_OPTIONAL, options_operator_t, qth, 0),
    CYAML_FIELD_STRING("callsign",      CYAML_FLAG_OPTIONAL, options_operator_t, callsign, 0),
    CYAML_FIELD_END
};

const cyaml_schema_field_t mic_fields_schema[] = {
    CYAML_FIELD_MAPPING("filter",       CYAML_FLAG_OPTIONAL, options_mic_t, filter, filter_fields_schema),
    CYAML_FIELD_END
};

const cyaml_schema_field_t audio_fields_schema[] = {
    CYAML_FIELD_UINT("vol",             CYAML_FLAG_OPTIONAL, options_audio_t, vol),
    CYAML_FIELD_MAPPING("mic",          CYAML_FLAG_OPTIONAL, options_audio_t, mic, mic_fields_schema),
    CYAML_FIELD_END
};

const cyaml_schema_field_t spectrum_fields_schema[] = {
    CYAML_FIELD_FLOAT("beta",           CYAML_FLAG_OPTIONAL, options_spectrum_t, beta),
    CYAML_FIELD_BOOL("filled",          CYAML_FLAG_OPTIONAL, options_spectrum_t, filled),
    CYAML_FIELD_BOOL("peak",            CYAML_FLAG_OPTIONAL, options_spectrum_t, peak),
    CYAML_FIELD_UINT("peak_hold",       CYAML_FLAG_OPTIONAL, options_spectrum_t, peak_hold),
    CYAML_FIELD_FLOAT("peak_speed",     CYAML_FLAG_OPTIONAL, options_spectrum_t, peak_speed),
    CYAML_FIELD_END
};

static const cyaml_strval_t vol_flags_strings[] = {
    { "vol",                (1 << VOL_VOL) },
    { "pwr",                (1 << VOL_PWR) },
    { "freq_mode",          (1 << VOL_FREQ_MODE) },
    { "split",              (1 << VOL_SPLIT) },
    { "voice_lang",         (1 << VOL_VOICE_LANG) },
    { "voice_rate",         (1 << VOL_VOICE_RATE) },
    { "voice_pitch",        (1 << VOL_VOICE_PITCH) },
    { "voice_volume",       (1 << VOL_VOICE_VOLUME) },
};

static const cyaml_strval_t mfk_flags_strings[] = {
    { "filter_low",         (1 << MFK_FILTER_LOW ) },
    { "filter_high",        (1 << MFK_FILTER_HIGH )},
    { "filter_transition",  (1 << MFK_FILTER_TRANSITION )},
    { "agc",                (1 << MFK_AGC )},
    { "spectrum_factor",    (1 << MFK_SPECTRUM_FACTOR )},
    { "spectrum_beta",      (1 << MFK_SPECTRUM_BETA )},
    { "peak_hold",          (1 << MFK_PEAK_HOLD )},
    { "peak_speed",         (1 << MFK_PEAK_SPEED )},
    { "spectrum_fill",      (1 << MFK_SPECTRUM_FILL )},
    { "spectrum_peak",      (1 << MFK_SPECTRUM_PEAK )},
};

static const cyaml_strval_t action_strings[] = {
    { "none",               ACTION_NONE },
    { "screenshot",         ACTION_SCREENSHOT },
    { "recorder",           ACTION_RECORDER },
    { "mute",               ACTION_MUTE },
    { "step_up",            ACTION_STEP_UP },
    { "step_down",          ACTION_STEP_DOWN },
    { "voice_mode",         ACTION_VOICE_MODE },

    { "app_rtty",           ACTION_APP_RTTY },
    { "app_ft8",            ACTION_APP_FT8 },
    { "app_swrscan",        ACTION_APP_SWRSCAN },
    { "app_gps",            ACTION_APP_GPS },
    { "app_settings",       ACTION_APP_SETTINGS },
    { "app_recorder",       ACTION_APP_RECORDER },
    { "app_qth",            ACTION_APP_QTH },
    { "app_callsign",       ACTION_APP_CALLSIGN }
};

#define CONTROL_FLAGS (CYAML_FLAG_OPTIONAL | CYAML_FLAG_STRICT)

const cyaml_schema_field_t control_fields_schema[] = {
    CYAML_FIELD_FLAGS("vol",            CONTROL_FLAGS, options_control_t, vol, vol_flags_strings, CYAML_ARRAY_LEN(vol_flags_strings)),
    CYAML_FIELD_FLAGS("mfk",            CONTROL_FLAGS, options_control_t, mfk, mfk_flags_strings, CYAML_ARRAY_LEN(mfk_flags_strings)),
    CYAML_FIELD_ENUM("long_vol",        CYAML_FLAG_OPTIONAL, options_control_t, long_vol, action_strings, CYAML_ARRAY_LEN(action_strings)),
    CYAML_FIELD_ENUM("long_mfk",        CYAML_FLAG_OPTIONAL, options_control_t, long_mfk, action_strings, CYAML_ARRAY_LEN(action_strings)),
    CYAML_FIELD_ENUM("long_app",        CYAML_FLAG_OPTIONAL, options_control_t, long_app, action_strings, CYAML_ARRAY_LEN(action_strings)),
    CYAML_FIELD_ENUM("long_band_down",  CYAML_FLAG_OPTIONAL, options_control_t, long_band_down, action_strings, CYAML_ARRAY_LEN(action_strings)),
    CYAML_FIELD_ENUM("long_band_up",    CYAML_FLAG_OPTIONAL, options_control_t, long_band_up, action_strings, CYAML_ARRAY_LEN(action_strings)),
    CYAML_FIELD_END
};

const cyaml_schema_field_t options_fields_schema[] = {
    CYAML_FIELD_MAPPING("operator",     CYAML_FLAG_OPTIONAL, options_t, operator, operator_fields_schema),
    CYAML_FIELD_MAPPING("audio",        CYAML_FLAG_OPTIONAL, options_t, audio, audio_fields_schema),
    CYAML_FIELD_MAPPING("spectrum",     CYAML_FLAG_OPTIONAL, options_t, spectrum, spectrum_fields_schema),
    CYAML_FIELD_MAPPING("control",      CYAML_FLAG_OPTIONAL, options_t, control, control_fields_schema),
    CYAML_FIELD_END
};

static const cyaml_schema_value_t options_schema = {
    CYAML_VALUE_MAPPING(CYAML_FLAG_POINTER, options_t, options_fields_schema)
};

static const cyaml_config_t config = {
    .log_fn = cyaml_log,
    .mem_fn = cyaml_mem,
    .log_level = CYAML_LOG_WARNING,
};

options_t   *options = NULL;

void settings_options_load() {
    cyaml_err_t err;

    err = cyaml_load_file(filename, &config, &options_schema, (void **) &options, NULL);

    if (err != CYAML_OK) {
        LV_LOG_ERROR("%s", cyaml_strerror(err));
        return;
    }

    qth_update(options->operator.qth);
}

void settings_options_save() {
    cyaml_err_t err;

    err = cyaml_save_file(filename, &config, &options_schema, options, 0);

    if (err != CYAML_OK) {
        LV_LOG_ERROR("%s", cyaml_strerror(err));
        return;
    }
}
