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
    { "denoise_enable",     (1 << MFK_DENOISE_ENABLE )},
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

const cyaml_schema_field_t rtty_fields_schema[] = {
    CYAML_FIELD_UINT("center",          CYAML_FLAG_OPTIONAL, options_rtty_t, center),
    CYAML_FIELD_UINT("shift",           CYAML_FLAG_OPTIONAL, options_rtty_t, shift),
    CYAML_FIELD_FLOAT("rate",           CYAML_FLAG_OPTIONAL, options_rtty_t, rate),
    CYAML_FIELD_BOOL("reverse",         CYAML_FLAG_OPTIONAL, options_rtty_t, reverse),
    CYAML_FIELD_UINT("bits",            CYAML_FLAG_OPTIONAL, options_rtty_t, bits),
    CYAML_FIELD_FLOAT("snr",            CYAML_FLAG_OPTIONAL, options_rtty_t, snr),
    CYAML_FIELD_END
};

const cyaml_schema_field_t cw_fields_schema[] = {
    CYAML_FIELD_BOOL("decoder",             CYAML_FLAG_OPTIONAL, options_cw_t, decoder),
    CYAML_FIELD_FLOAT("decoder_snr",        CYAML_FLAG_OPTIONAL, options_cw_t, decoder_snr),
    CYAML_FIELD_FLOAT("decoder_snr_gist",   CYAML_FLAG_OPTIONAL, options_cw_t, decoder_snr_gist),
    CYAML_FIELD_FLOAT("decoder_peak_beta",  CYAML_FLAG_OPTIONAL, options_cw_t, decoder_peak_beta),
    CYAML_FIELD_FLOAT("decoder_noise_beta", CYAML_FLAG_OPTIONAL, options_cw_t, decoder_noise_beta),
    CYAML_FIELD_END
};

const cyaml_schema_field_t olivia_fields_schema[] = {
    CYAML_FIELD_UINT("tones",               CYAML_FLAG_OPTIONAL, options_olivia_t, tones),
    CYAML_FIELD_UINT("band_width",          CYAML_FLAG_OPTIONAL, options_olivia_t, band_width),
    CYAML_FIELD_UINT("band_lower",          CYAML_FLAG_OPTIONAL, options_olivia_t, band_lower),
    CYAML_FIELD_UINT("sync_margin",         CYAML_FLAG_OPTIONAL, options_olivia_t, sync_margin),
    CYAML_FIELD_UINT("sync_integ",          CYAML_FLAG_OPTIONAL, options_olivia_t, sync_integ),
    CYAML_FIELD_FLOAT("sync_threshold",     CYAML_FLAG_OPTIONAL, options_olivia_t, sync_threshold),
    CYAML_FIELD_END
};

const cyaml_schema_field_t msg_fields_schema[] = {
    CYAML_FIELD_UINT("voice_period",        CYAML_FLAG_OPTIONAL, options_msg_t, voice_period),
    CYAML_FIELD_END
};

const cyaml_schema_field_t options_fields_schema[] = {
    CYAML_FIELD_MAPPING("operator",     CYAML_FLAG_OPTIONAL, options_t, op, operator_fields_schema),
    CYAML_FIELD_MAPPING("audio",        CYAML_FLAG_OPTIONAL, options_t, audio, audio_fields_schema),
    CYAML_FIELD_MAPPING("spectrum",     CYAML_FLAG_OPTIONAL, options_t, spectrum, spectrum_fields_schema),
    CYAML_FIELD_MAPPING("control",      CYAML_FLAG_OPTIONAL, options_t, control, control_fields_schema),
    CYAML_FIELD_MAPPING("rtty",         CYAML_FLAG_OPTIONAL, options_t, rtty, rtty_fields_schema),
    CYAML_FIELD_MAPPING("cw",           CYAML_FLAG_OPTIONAL, options_t, cw, cw_fields_schema),
    CYAML_FIELD_MAPPING("olivia",       CYAML_FLAG_OPTIONAL, options_t, olivia, olivia_fields_schema),
    CYAML_FIELD_MAPPING("msg",          CYAML_FLAG_OPTIONAL, options_t, msg, msg_fields_schema),
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

    qth_update(options->op.qth);
}

void settings_options_save() {
    cyaml_err_t err;

    err = cyaml_save_file(filename, &config, &options_schema, options, 0);

    if (err != CYAML_OK) {
        LV_LOG_ERROR("%s", cyaml_strerror(err));
        return;
    }
}
