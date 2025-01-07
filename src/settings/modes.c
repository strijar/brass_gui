/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#include <stdio.h>
#include <cyaml/cyaml.h>
#include "lvgl/lvgl.h"
#include "src/dsp.h"
#include "modes.h"

static const char filename[] = "/mnt/settings/modes.yaml";

static const cyaml_strval_t agc_mode_strings[] = {
    { "Off",        AGC_OFF },
    { "Long",       AGC_LONG },
    { "Slow",       AGC_SLOW },
    { "Med",        AGC_MED },
    { "Fast",       AGC_FAST },
    { "Custom",     AGC_CUSTOM },
};

static const cyaml_schema_field_t mode_fields_schema[] = {
    CYAML_FIELD_MAPPING("filter",       CYAML_FLAG_FLOW, op_mode_t, filter, filter_fields_schema),
    CYAML_FIELD_ENUM("agc",             CYAML_FLAG_DEFAULT, op_mode_t, agc, agc_mode_strings, CYAML_ARRAY_LEN(agc_mode_strings)),
    CYAML_FIELD_UINT("freq_step",       CYAML_FLAG_DEFAULT, op_mode_t, freq_step),
    CYAML_FIELD_UINT("spectrum_factor", CYAML_FLAG_DEFAULT, op_mode_t, spectrum_factor),
    CYAML_FIELD_BOOL("is_used",         CYAML_FLAG_DEFAULT, op_mode_t, is_used),
    CYAML_FIELD_END
};

static const cyaml_schema_field_t modes_fields_schema[] = {
    CYAML_FIELD_MAPPING("lsb",      CYAML_FLAG_DEFAULT, op_modes_t, lsb, mode_fields_schema),
    CYAML_FIELD_MAPPING("usb",      CYAML_FLAG_DEFAULT, op_modes_t, usb, mode_fields_schema),
    CYAML_FIELD_MAPPING("cw",       CYAML_FLAG_DEFAULT, op_modes_t, cw, mode_fields_schema),
    CYAML_FIELD_MAPPING("cwr",      CYAML_FLAG_DEFAULT, op_modes_t, cwr, mode_fields_schema),
    CYAML_FIELD_MAPPING("am",       CYAML_FLAG_DEFAULT, op_modes_t, am, mode_fields_schema),
    CYAML_FIELD_MAPPING("nfm",      CYAML_FLAG_DEFAULT, op_modes_t, nfm, mode_fields_schema),
    CYAML_FIELD_MAPPING("rtty",     CYAML_FLAG_DEFAULT, op_modes_t, rtty, mode_fields_schema),
    CYAML_FIELD_END
};

static const cyaml_schema_value_t modes_schema = {
    CYAML_VALUE_MAPPING(CYAML_FLAG_POINTER, op_modes_t, modes_fields_schema),
};

static const cyaml_config_t config = {
    .log_fn = cyaml_log,
    .mem_fn = cyaml_mem,
    .log_level = CYAML_LOG_WARNING,
};

op_modes_t  *op_modes = NULL;
op_mode_t   *op_mode = NULL;

void settings_modes_load() {
    cyaml_err_t err;

    err = cyaml_load_file(filename, &config, &modes_schema, (void **) &op_modes, NULL);

    if (err != CYAML_OK) {
        LV_LOG_ERROR("%s", cyaml_strerror(err));
        return;
    }

    op_mode = &op_modes->lsb;
}

void settings_modes_save() {
    cyaml_err_t err;

    err = cyaml_save_file(filename, &config, &modes_schema, op_modes, 0);

    if (err != CYAML_OK) {
        LV_LOG_ERROR("%s", cyaml_strerror(err));
        return;
    }
}

void settings_mode_update(radio_mode_t mode) {
    op_mode_t *prev = op_mode;

    switch (mode) {
        case RADIO_MODE_LSB:
            op_mode = &op_modes->lsb;
            break;

        case RADIO_MODE_USB:
            op_mode = &op_modes->usb;
            break;

        case RADIO_MODE_CW:
            op_mode = &op_modes->cw;
            break;

        case RADIO_MODE_CWR:
            op_mode = &op_modes->cwr;
            break;

        case RADIO_MODE_AM:
            op_mode = &op_modes->am;
            break;

        case RADIO_MODE_NFM:
            op_mode = &op_modes->nfm;
            break;

        case RADIO_MODE_RTTY:
            op_mode = &op_modes->rtty;
            break;
    }

    dsp_set_filter(&op_mode->filter);
    dsp_set_rx_agc(op_mode->agc);

    if (prev->spectrum_factor != op_mode->spectrum_factor) {
        dsp_set_spectrum_factor(op_mode->spectrum_factor);
    }
}
