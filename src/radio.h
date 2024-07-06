/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#pragma once

#include <stdbool.h>

#include "lvgl/lvgl.h"

#define RADIO_SAMPLES   (256)
#define RADIO_FFT       (1024)

typedef enum {
    RADIO_VFO_A = 0,
    RADIO_VFO_B
} radio_vfo_t;

typedef enum {
    radio_mode_lsb = 0,
    radio_mode_lsb_dig = 1,
    radio_mode_usb = 2,
    radio_mode_usb_dig = 3,
    radio_mode_cw = 4,
    radio_mode_cwr = 5,
    radio_mode_am = 6,
    radio_mode_nfm = 7,

    /* Loop by keys */

    RADIO_MODE_AM,
    RADIO_MODE_CW,
    RADIO_MODE_SSB,

    /* Direct set */

    RADIO_MODE_USB,
    RADIO_MODE_LSB
} radio_mode_t;

typedef enum {
    radio_key_manual = 0,
    radio_key_auto_left = 1,
    radio_key_auto_right = 2
} radio_key_mode_t;

typedef enum {
    radio_iambic_a = 0,
    radio_iambic_b = 1
} radio_iambic_mode_t;

typedef enum {
    radio_mic_builtin = 0,
    radio_mic_handle,
    radio_mic_auto
} radio_mic_sel_t;

typedef enum {
    radio_agc_off = 0,
    radio_agc_slow = 1,
    radio_agc_fast = 2,
    radio_agc_auto = 3
} radio_agc_t;

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

void radio_init(lv_obj_t *obj);
bool radio_tick();
radio_state_t radio_get_state();

void radio_set_freq_rx(uint64_t freq);
void radio_set_freq_fft(uint64_t freq);
bool radio_check_freq(uint64_t freq, uint64_t *shift);

void radio_set_mode(radio_vfo_t vfo,  radio_mode_t mode);
void radio_change_mode(radio_mode_t select);
void radio_restore_mode(radio_mode_t mode);
radio_mode_t radio_current_mode();

radio_vfo_t radio_set_vfo(radio_vfo_t vfo);
radio_vfo_t radio_change_vfo();

uint16_t radio_change_rfg(int16_t df);
uint16_t radio_change_sql(int16_t df);
uint32_t radio_change_filter_low(int32_t freq);
uint32_t radio_change_filter_high(int32_t freq);
uint32_t radio_change_filter_transition(int32_t freq);
uint16_t radio_change_moni(int16_t df);

void radio_change_mute();

bool radio_change_pre();
bool radio_change_att();
void radio_change_agc();
void radio_change_atu();
void radio_change_split();
float radio_change_pwr(int16_t d);

uint16_t radio_change_key_speed(int16_t d);
radio_key_mode_t radio_change_key_mode(int16_t d);
radio_iambic_mode_t radio_change_iambic_mode(int16_t d);
uint16_t radio_change_key_tone(int16_t d);
uint16_t radio_change_key_vol(int16_t d);
bool radio_change_key_train(int16_t d);
uint16_t radio_change_qsk_time(int16_t d);
uint8_t radio_change_key_ratio(int16_t d);
radio_charger_t radio_change_charger(int16_t d);

radio_mic_sel_t radio_change_mic(int16_t d);
uint8_t radio_change_hmic(int16_t d);
uint8_t radio_change_imic(int16_t d);

bool radio_change_dnf(int16_t d);
uint16_t radio_change_dnf_center(int16_t d);
uint16_t radio_change_dnf_width(int16_t d);
bool radio_change_nb(int16_t d);
uint8_t radio_change_nb_level(int16_t d);
uint8_t radio_change_nb_width(int16_t d);
bool radio_change_nr(int16_t d);
uint8_t radio_change_nr_level(int16_t d);

bool radio_change_agc_hang(int16_t d);
int8_t radio_change_agc_knee(int16_t d);
uint8_t radio_change_agc_slope(int16_t d);

void radio_start_atu();
void radio_load_atu();

bool radio_start_swrscan();
void radio_stop_swrscan();

void radio_vfo_set();
void radio_mode_set();

void radio_filter_get(int32_t *from_freq, int32_t *to_freq);
void radio_poweroff();
void radio_set_ptt(bool tx);

int16_t radio_change_xit(int16_t d);
int16_t radio_change_rit(int16_t d);

void radio_set_line_in(uint8_t d);
void radio_set_line_out(uint8_t d);

void radio_set_morse_key(bool on);
