/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "bands/bands.h"
#include "radio.h"
#include "clock.h"
#include "voice.h"
#include "cw_key.h"

/* Params items */

typedef struct {
    char        *name;
    char        *voice;
    bool        x;
    bool        durty;
} params_bool_t;

typedef struct {
    char        *name;
    char        *voice;
    float       x;
    bool        durty;
} params_float_t;

typedef struct {
    char        *name;
    char        *voice;
    uint8_t     x;
    uint8_t     min;
    uint8_t     max;
    bool        durty;
} params_uint8_t;

typedef struct {
    char        *name;
    char        *voice;
    int8_t      x;
    int8_t      min;
    int8_t      max;
    bool        durty;
} params_int8_t;

typedef struct {
    char        *name;
    char        *voice;
    uint16_t    x;
    uint16_t    min;
    uint16_t    max;
    bool        durty;
} params_uint16_t;

typedef struct {
    char        *name;
    char        *voice;
    int16_t     x;
    int16_t     min;
    int16_t     max;
    bool        durty;
} params_int16_t;

typedef struct {
    char        *name;
    char        *voice;
    int32_t     x;
    int32_t     min;
    int32_t     max;
    bool        durty;
} params_int32_t;

typedef struct {
    char        *name;
    char        *voice;
    uint64_t    x;
    uint64_t    min;
    uint64_t    max;
    bool        durty;
} params_uint64_t;

typedef struct {
    char        *name;
    char        *voice;
    char        x[16];
    uint8_t     max_len;
    bool        durty;
} params_str_t;

/* * */

typedef enum {
    BUTTONS_DARK = 0,
    BUTTONS_LIGHT,
    BUTTONS_TEMPORARILY
} buttons_light_t;

typedef enum {
    FREQ_ACCEL_NONE = 0,
    FREQ_ACCEL_LITE,
    FREQ_ACCEL_STRONG,
} freq_accel_t;

typedef enum {
    FREQ_MODE_JOIN = 0,
    FREQ_MODE_SLIDE,
    FREQ_MODE_RX_ONLY,
    FREQ_MODE_FFT_ONLY
} rx_freq_mode_t;

/* Params */

typedef struct {
    /* LCD */
    
    int16_t             brightness_normal;
    int16_t             brightness_idle;
    uint16_t            brightness_timeout; /* seconds */
    buttons_light_t     brightness_buttons;

    /* radio */
    
    uint8_t             sql;
    bool                atu;
    bool                atu_loaded;
    uint8_t             ant;
    float               pwr;
    int16_t             moni;
    params_uint8_t      freq_accel;
    params_uint8_t      freq_mode;
    params_int32_t      txo_offset;
    
    /* DSP */
    
    bool                dnf;
    uint16_t            dnf_center;
    uint16_t            dnf_width;
    
    bool                nb;
    uint8_t             nb_level;
    uint8_t             nb_width;
    
    bool                nr;
    uint8_t             nr_level;
    
    /* VOX */
    
    bool                vox;
    uint8_t             vox_ag;
    uint16_t            vox_delay;
    uint8_t             vox_gain;
    
    /* main screen */
    
    params_bool_t       mag_freq;
    params_bool_t       mag_info;
    params_bool_t       mag_alc;
    clock_view_t        clock_view;
    uint8_t             clock_time_timeout;     /* seconds */
    uint8_t             clock_power_timeout;    /* seconds */
    uint8_t             clock_tx_timeout;       /* seconds */
    
    /* CW key */
    
    uint8_t             key_speed;
    cw_key_mode_t       key_mode;
    cw_key_iambic_mode_t iambic_mode;
    uint16_t            key_tone;
    uint16_t            key_vol;
    bool                key_train;
    uint16_t            qsk_time;
    uint8_t             key_ratio;

    /* Msg */
    
    uint16_t            cw_encoder_period;  /* seconds */

    /* SWR Scan */

    bool                swrscan_linear;
    uint32_t            swrscan_span;

    /* HMic F1, F2 actions */
    
    uint8_t             press_f1;
    uint8_t             press_f2;
    uint8_t             long_f1;
    uint8_t             long_f2;
    
    /* Voice */

    params_uint8_t      voice_mode;
    params_uint8_t      voice_lang;
    params_uint8_t      voice_rate;
    params_uint8_t      voice_pitch;
    params_uint8_t      voice_volume;

    /* durty flags */
    
    struct {
        bool    vol_modes;
        bool    mfk_modes;

        bool    brightness_normal;
        bool    brightness_idle;
        bool    brightness_timeout;
        bool    brightness_buttons;
        
        bool    sql;
        bool    atu;
        bool    ant;
        bool    pwr;
        bool    moni;
        
        bool    dnf;
        bool    dnf_center;
        bool    dnf_width;
        bool    nb;
        bool    nb_level;
        bool    nb_width;
        bool    nr;
        bool    nr_level;

        bool    vox;
        bool    vox_ag;
        bool    vox_delay;
        bool    vox_gain;

        bool    clock_view;
        bool    clock_time_timeout;
        bool    clock_power_timeout;
        bool    clock_tx_timeout;
        
        bool    key_speed;
        bool    key_mode;
        bool    iambic_mode;
        bool    key_tone;
        bool    key_vol;
        bool    key_train;
        bool    qsk_time;
        bool    key_ratio;

        bool    cw_encoder_period;

        bool    swrscan_linear;
        bool    swrscan_span;

        bool    press_f1;
        bool    press_f2;
        bool    long_f1;
        bool    long_f2;
    } durty;
} params_t;

extern params_t params;

void params_init();
void params_lock();
void params_unlock(bool *durty);

void params_bool_set(params_bool_t *var, bool x);
void params_uint8_set(params_uint8_t *var, uint8_t x);
void params_uint16_set(params_uint16_t *var, uint16_t x);
void params_int32_set(params_int32_t *var, int32_t x);
void params_uint64_set(params_uint64_t *var, uint64_t x);
void params_str_set(params_str_t *var, const char *x);

uint8_t params_uint8_change(params_uint8_t *var, int16_t df);

void params_msg_cw_load();
void params_msg_cw_new(const char *val);
void params_msg_cw_edit(uint32_t id, const char *val);
void params_msg_cw_delete(uint32_t id);
