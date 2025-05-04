/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#include "rf_filter.h"

static const cyaml_schema_field_t rf_filter_item_schema[] = {
    CYAML_FIELD_UINT("start",           CYAML_FLAG_DEFAULT, rf_filter_t, start),
    CYAML_FIELD_UINT("stop",            CYAML_FLAG_DEFAULT, rf_filter_t, stop),
    CYAML_FIELD_END
};

const cyaml_schema_value_t rf_filter_schema = {
    CYAML_VALUE_MAPPING(CYAML_FLAG_FLOW, rf_filter_t, rf_filter_item_schema)
};
