/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#pragma once

#include <stdbool.h>

#include "lvgl/lvgl.h"

typedef enum {
    RADIO_MODE_LSB = 0,
    RADIO_MODE_USB,
    RADIO_MODE_CW,
    RADIO_MODE_CWR,
    RADIO_MODE_AM,
    RADIO_MODE_NFM,
    RADIO_MODE_RTTY,
    RADIO_MODE_OLIVIA,
} radio_mode_t;

typedef enum {
    RADIO_MODE_NEXT = 0,
    RADIO_MODE_SUBSET
} radio_change_mode_t;

typedef enum {
    radio_att_off = 0,
    radio_att_on = 1
} radio_att_t;

typedef enum {
    radio_pre_off = 0,
    radio_pre_on = 1
} radio_pre_t;

typedef enum {
    RADIO_RX = 0,
    RADIO_TX,
    RADIO_STOP_TX,
    RADIO_ATU_START,
    RADIO_ATU_WAIT,
    RADIO_ATU_RUN,
    RADIO_SWRSCAN,

    RADIO_POWEROFF,
    RADIO_OFF
} radio_state_t;

typedef enum {
    RADIO_CHARGER_OFF = 0,
    RADIO_CHARGER_ON,
    RADIO_CHARGER_SHADOW
} radio_charger_t;

typedef enum {
    SPLIT_NONE = 0,
    SPLIT_RX,
    SPLIT_TX
} split_mode_t;

void radio_init(lv_obj_t *obj);
bool radio_tick();
radio_state_t radio_get_state();

void radio_set_freq_rx(uint64_t freq);
void radio_set_freq_tx(uint64_t freq);
uint64_t radio_set_freqs(uint64_t rx, uint64_t tx);
void radio_set_freq_fft(uint64_t freq);
split_mode_t radio_change_split(int16_t d);

void radio_change_mode(radio_change_mode_t select);

uint16_t radio_change_rfg(int16_t df);
uint16_t radio_change_sql(int16_t df);
uint32_t radio_change_filter_low(int32_t freq);
uint32_t radio_change_filter_high(int32_t freq);
uint32_t radio_change_filter_transition(int32_t freq);
uint16_t radio_change_moni(int16_t df);

bool radio_change_pre();
bool radio_change_att();
void radio_change_atu();
float radio_change_pwr(int16_t d);

bool radio_change_dnf(int16_t d);
uint16_t radio_change_dnf_center(int16_t d);
uint16_t radio_change_dnf_width(int16_t d);
bool radio_change_nb(int16_t d);
uint8_t radio_change_nb_level(int16_t d);
uint8_t radio_change_nb_width(int16_t d);
bool radio_change_nr(int16_t d);

void radio_start_atu();
void radio_load_atu();

bool radio_start_swrscan();
void radio_stop_swrscan();

void radio_freq_update();

void radio_filter_get(int32_t *from_freq, int32_t *to_freq);
void radio_poweroff();

void radio_set_ptt(bool on);
void radio_stop_tx();
void radio_set_morse_key(bool on);
