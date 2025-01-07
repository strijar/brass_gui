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

const cyaml_schema_field_t options_fields_schema[] = {
    CYAML_FIELD_MAPPING("operator",     CYAML_FLAG_OPTIONAL, options_t, operator, operator_fields_schema),
    CYAML_FIELD_MAPPING("audio",        CYAML_FLAG_OPTIONAL, options_t, audio, audio_fields_schema),
    CYAML_FIELD_MAPPING("spectrum",     CYAML_FLAG_OPTIONAL, options_t, spectrum, spectrum_fields_schema),
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
