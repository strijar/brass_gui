/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#include <stdlib.h>
#include <liquid/liquid.h>
#include <math.h>
#include <pthread.h>

#include "mic.h"
#include "dsp.h"
#include "audio.h"
#include "msgs.h"
#include "util.h"
#include "fpga/dac.h"
#include "dsp/firdes.h"
#include "dsp/agc.h"
#include "dsp/biquad.h"
#include "dialog_msg_voice.h"
#include "settings/options.h"

#define DECIM   441
#define INTER   128

static bool             on_air = false;
static bool             enabled = false;
static firfilt_rrrf     dc_block;
static cbufferf         in_buf;
static rresamp_rrrf     resamp;
static float            resamp_buf[INTER];
static cbufferf         out_buf;
static agc_t            *agc;
static size_t           filter_len = 0;
static float            *filter_taps = NULL;
static bool             filter_need_update = false;
static firfilt_rrrf     filter = NULL;

static uint8_t          meter_count = 0;
static float            meter_sum = 0.0f;
static float            meter_avr = 0.0f;
static lv_timer_t       *meter_timer = NULL;
static pthread_mutex_t  meter_mux;

static bool             mic_equalizer_update = true;
static biquad_t         mic_equalizer[EQUALIZER_NUM];

static void meter_timer_cb(lv_timer_t *t);

void mic_init() {
    dc_block = firfilt_rrrf_create_dc_blocker(25, 30.0f);
    in_buf = cbufferf_create(AUDIO_CAPTURE_RATE / 4);
    resamp = rresamp_rrrf_create_default(INTER, DECIM);     /* DAC_RATE <- AUDIO_CAPTURE_RATE */
    out_buf = cbufferf_create(DAC_RATE / 4);

    agc = agc_create(
        AGC_FAST,               /* mode */
        AUDIO_CAPTURE_RATE,     /* sample rate */
        0.001f,                 /* tau_attack */
        0.250f,                 /* tau_decay */
        4,                      /* n_tau */
        4.0f,                   /* max_gain */
        1.5f,                   /* var_gain */
        4.0f,                   /* fixed_gain */
        1.0f,                   /* max_input */
        1.0f,                   /* out_target */
        0.250f,                 /* tau_fast_backaverage */
        0.005f,                 /* tau_fast_decay */
        5.0f,                   /* pop_ratio */
        1,                      /* hang_enable */
        0.500f,                 /* tau_hang_backmult */
        0.250f,                 /* hangtime */
        0.250f,                 /* hang_thresh */
        0.100f                  /* tau_hang_decay */
    );

    pthread_mutex_init(&meter_mux, NULL);
    meter_timer = lv_timer_create(meter_timer_cb, 1000 / 10, NULL);

    mic_update_filter();
}

void mic_update_filter() {
    size_t len = firdes_compute_taps_len(44100.0f, options->audio.mic.filter.transition, 40.0f);

    if (filter_len != len) {
        filter_taps = realloc(filter_taps, len * sizeof(float));
        filter_len = len;
    }

    firdes_band_pass(1.0f, 44100.0f, options->audio.mic.filter.low, options->audio.mic.filter.high, filter_taps, filter_len);
    filter_need_update = true;
}

void mic_update_equalizer() {
    mic_equalizer_update = true;
}

size_t mic_modulate(float complex *data, size_t max_size, radio_mode_t mode) {
    size_t size = 0;

    uint32_t part = INTER;

    if (cbufferf_size(out_buf) > part) {
        uint32_t n;
        float *buf;

        cbufferf_read(out_buf, part, &buf, &n);

        for (uint32_t i = 0; i < n; i++) {
            data[i] = dsp_modulate(buf[i], mode);
        }

        cbufferf_release(out_buf, n);
        size = n;
    }

    return size;
}

void mic_on_air(bool on) {
    on_air = on;
}

void mic_enabled(bool on) {
    enabled = on;
    lv_msg_send(MSG_MIC, &enabled);
}

static void meter_timer_cb(lv_timer_t *t) {
    pthread_mutex_lock(&meter_mux);

    lpf(&meter_avr, meter_sum / meter_count, 0.2f);
    lv_msg_send(MSG_MIC_METER, &meter_avr);

    meter_count = 0;
    meter_sum = 0;

    pthread_mutex_unlock(&meter_mux);
}

void mic_put_audio_samples(size_t nsamples, int16_t *samples) {
    if (filter_need_update) {
        if (filter) {
            filter = firfilt_rrrf_recreate(filter, filter_taps, filter_len);
        } else {
            filter = firfilt_rrrf_create(filter_taps, filter_len);
        }
        filter_need_update = false;
    }

    if (mic_equalizer_update) {
        for (int i = 0; i < EQUALIZER_NUM; i++) {
            const equalizer_item_t *item = &options->audio.mic.eq[i];

            biquad_peak_eq(&mic_equalizer[i], item->freq, item->q * 0.5f, item->gain, 44100);
        }

        mic_equalizer_update = false;
    }

    float   peak = 0.0f;
    float   a, b;
    bool    rec_msg = (dialog_msg_voice_get_state() == MSG_VOICE_RECORD);

    for (int16_t i = 0; i < nsamples; i++) {
        firfilt_rrrf_push(dc_block, samples[i] / 32768.0f);
        firfilt_rrrf_execute(dc_block, &a);

        if (on_air || rec_msg) {
            for (int n = 0; n < EQUALIZER_NUM; n++) {
                a = biqiad_apply(&mic_equalizer[n], a);
            }

            firfilt_rrrf_execute_one(filter, a, &b);
            b = agc_apply(agc, b);

            cbufferf_push(in_buf, b);

            if (fabs(b) > peak) {
                peak = fabs(b);
            }
        }
    }

    pthread_mutex_lock(&meter_mux);
    meter_sum += peak;
    meter_count++;
    pthread_mutex_unlock(&meter_mux);

    unsigned int n;
    float *buf;

    if (rec_msg) {
        cbufferf_read(in_buf, nsamples, &buf, &n);

        dialog_msg_voice_put_audio_samples(buf, n);
        cbufferf_reset(in_buf);

        return;
    }

    if (!on_air) {
        if (cbufferf_size(in_buf) > 0) {
            cbufferf_reset(in_buf);
        }

        if (cbufferf_size(out_buf) > 0) {
            cbufferf_reset(out_buf);
        }

        return;
    }

    while (cbufferf_size(in_buf) > DECIM) {
        cbufferf_read(in_buf, DECIM, &buf, &n);
        rresamp_rrrf_execute(resamp, buf, resamp_buf);
        cbufferf_release(in_buf, n);

        cbufferf_write(out_buf, resamp_buf, INTER);
    }
}
