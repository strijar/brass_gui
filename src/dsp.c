/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include "dsp.h"
#include "waterfall.h"
#include "util.h"
#include "radio.h"
#include "params.h"
#include "meter.h"
#include "audio.h"
#include "audio_adc.h"
#include "cw.h"
#include "cw_key.h"
#include "rtty.h"
#include "dialog_ft8.h"
#include "dialog_msg_voice.h"
#include "recorder.h"
#include "fpga/fft.h"
#include "fpga/adc.h"
#include "fpga/dac.h"
#include "fpga/control.h"
#include "dsp/firdes.h"
#include "dsp/agc.h"
#include "msgs.h"
#include "generator.h"
#include "mic.h"
#include "main.h"

const uint16_t          fft_over = (FFT_SAMPLES - 800) / 2;

static pthread_mutex_t  spectrum_mux;

static float            *spectrum_psd;
static uint16_t         spectrum_psd_count = 0;
static float            spectrum_beta = 0.7f;
static uint16_t         spectrum_fps_ms = (1000 / 20);
static uint64_t         spectrum_time;
static msgs_auto_t      spectrum_auto_msg;
static msgs_floats_t    spectrum_data_msg;

static float            *waterfall_psd;
static uint16_t         waterfall_psd_count = 0;
static uint16_t         waterfall_fps_ms = (1000 / 10);
static uint64_t         waterfall_time;

static firhilbf         demod_ssb;
static firfilt_rrrf     demod_dc_block;
static agc_t            *rx_agc;

static size_t           filter_len = 0;
static float            *filter_taps = NULL;
static bool             filter_need_update = false;
static firfilt_rrrf     filter = NULL;

static float            *auto_psd;
static uint16_t         auto_psd_count = 0;
static uint16_t         auto_fps_ms = (1000 / 10);
static uint64_t         auto_time;

static uint8_t          meter_count = 0;
static float            meter_db = 0.0f;

static uint8_t          delay;

static bool             ready = false;
static bool             auto_clear = true;

static float            fft_buf[FFT_SAMPLES];

static int16_t          adc_buf[ADC_SAMPLES];
static float            adc_vol = 0;
static bool             adc_mute = false;

static int16_t          rec_buf[ADC_SAMPLES];

static void calc_auto();

/* * */

void dsp_init() {
    pthread_mutex_init(&spectrum_mux, NULL);

    spectrum_data_msg.size = 800;
    spectrum_data_msg.data = (float *) malloc(spectrum_data_msg.size * sizeof(float));

    for (uint16_t i = 0; i < spectrum_data_msg.size; i++)
        spectrum_data_msg.data[i] = S_MIN;

    spectrum_psd = (float *) malloc(spectrum_data_msg.size * sizeof(float));

    waterfall_psd = (float *) malloc(FFT_SAMPLES * sizeof(float));
    auto_psd = (float *) malloc(FFT_SAMPLES * sizeof(float));

    demod_ssb = firhilbf_create(15, 60.0f);
    demod_dc_block = firfilt_rrrf_create_dc_blocker(25, 20.0f);

    rx_agc = agc_create(
        AGC_FAST,   /* mode */
        ADC_RATE,   /* sample rate */
        0.001f,     /* tau_attack */
        0.250f,     /* tau_decay */
        4,          /* n_tau */
        10000.0f,   /* max_gain */
        1.5f,       /* var_gain */
        4.0f,       /* fixed_gain */
        1.0f,       /* max_input */
        1.0f,       /* out_target */
        0.250f,     /* tau_fast_backaverage */
        0.005f,     /* tau_fast_decay */
        5.0f,       /* pop_ratio */
        1,          /* hang_enable */
        0.500f,     /* tau_hang_backmult */
        0.250f,     /* hangtime */
        0.250f,     /* hang_thresh */
        0.100f      /* tau_hang_decay */
    );

    spectrum_time = get_time();
    waterfall_time = get_time();
    auto_time = get_time();
    
    delay = 4;
    
    dsp_set_vol(params.vol);
    ready = true;
}

void dsp_reset() {
    delay = 4;
}

void dsp_set_filter(float low_freq, float high_freq, float transition, float attenuation) {
    size_t len = firdes_compute_taps_len(12800.0f, transition, attenuation);

    if (filter_len != len) {
        filter_taps = realloc(filter_taps, len * sizeof(float));
        filter_len = len;
    }

    firdes_band_pass(1.0f, 12800.0f, low_freq, high_freq, filter_taps, filter_len);
    filter_need_update = true;
}

void dsp_set_rx_agc(uint8_t mode) {
    agc_set_mode(rx_agc, mode);
}

uint8_t dsp_change_rx_agc(int16_t df) {
    if (df == 0) {
        return params_mode.agc;
    }
    
    params_lock();
    params_mode.agc = limit(params_mode.agc + df, AGC_OFF, AGC_CUSTOM);
    params_unlock(&params_mode.durty.agc);

    dsp_set_rx_agc(params_mode.agc);
    
    return params_mode.agc;
}

void update_auto(uint64_t now) {
    auto_psd_count++;

    if (now - auto_time > auto_fps_ms) {
        for (size_t i = 0; i < FFT_SAMPLES; i++) {
            auto_psd[i] /= auto_psd_count;
        }

        calc_auto();
        auto_psd_count = 0;
        auto_time = now;
    }
}

void update_spectrum(uint64_t now) {
    if (now - spectrum_time > spectrum_fps_ms && spectrum_psd_count > 0) {
        for (uint16_t i = 0; i < spectrum_data_msg.size; i++) {
            float x = spectrum_psd[i] / spectrum_psd_count;
            float mag = 20.0f * log10f(x) - 96.0f;
            
            spectrum_psd[i] = mag;
            lpf(&spectrum_data_msg.data[i], mag, spectrum_beta);
        }

        lv_lock();
        lv_msg_send(MSG_SPECTRUM_DATA, &spectrum_data_msg);
        lv_unlock();

        spectrum_psd_count = 0;
        memset(spectrum_psd, 0, spectrum_data_msg.size * sizeof(float));
        spectrum_time = now;
    } else {
        for (size_t i = 0; i < spectrum_data_msg.size; i++)
            spectrum_psd[i] += fft_buf[i + fft_over];

        spectrum_psd_count++;
    }
}

void update_waterfall(uint64_t now) {
    waterfall_psd_count++;

    if (now - waterfall_time > waterfall_fps_ms) {
        for (uint16_t i = 0; i < FFT_SAMPLES; i++) {
            float x = waterfall_psd[i] / waterfall_psd_count;
            float mag = 20.0f * log10f(x) - 96.0f;
                
            waterfall_psd[i] = mag;
        }

        waterfall_data(waterfall_psd, FFT_SAMPLES);
 
        waterfall_psd_count = 0;
        memset(waterfall_psd, 0, FFT_SAMPLES * sizeof(float));
        waterfall_time = now;
    }
}

void dsp_fft(float complex *data) {
    radio_state_t   state = radio_get_state();

    if (state != RADIO_RX) {
        return;
    }

    for (size_t i = 0; i < FFT_SAMPLES; i++) {
        float complex x = data[i];
        float mag = sqrtf(crealf(x) * crealf(x) + cimagf(x) * cimag(x));
        uint16_t index = (i + FFT_SAMPLES / 2) % FFT_SAMPLES;

        fft_buf[index] = mag;
    }

    for (size_t i = 0; i < FFT_SAMPLES; i++) {
        float x = fft_buf[i];
    
        waterfall_psd[i] += x;
        auto_psd[i] += x;
    }

    uint64_t now = get_time();

    update_spectrum(now);
    update_waterfall(now);
    update_auto(now);
}

static float demodulate(float complex in, radio_mode_t mode) {
    static float    last_phase = 0;
    float           phase, dphase;
    float           a, b;
    float           out = 0.0f;

    switch (mode) {
        case RADIO_MODE_LSB:
        case RADIO_MODE_CWR:
            firhilbf_c2r_execute(demod_ssb, in, &a, &b);
            out = a;
            break;

        case RADIO_MODE_USB:
        case RADIO_MODE_CW:
        case RADIO_MODE_RTTY:
            firhilbf_c2r_execute(demod_ssb, in, &a, &b);
            out = b;
            break;
            
        case RADIO_MODE_AM:
            firfilt_rrrf_push(demod_dc_block, cabsf(in));
            firfilt_rrrf_execute(demod_dc_block, &out);
            break;
            
        case RADIO_MODE_NFM:
            phase = atan2f(cimagf(in), crealf(in));
            dphase = phase - last_phase;
            while (dphase < -M_PI) dphase += 2 * M_PI;
            while (dphase > M_PI) dphase -= 2 * M_PI;
            out = dphase / M_PI;
            last_phase = phase;
            break;
    }
    
    return out;
}

void dsp_adc(float complex *data) {
    radio_state_t   state = radio_get_state();

    if (state != RADIO_RX) {
        return;
    }

    radio_mode_t    mode = radio_current_mode();
    float           peak = 0.0f;

    if (filter_need_update) {
        if (filter) {
            filter = firfilt_rrrf_recreate(filter, filter_taps, filter_len);
        } else {
            filter = firfilt_rrrf_create(filter_taps, filter_len);
        }
        filter_need_update = false;
    }

    for (int i = 0; i < ADC_SAMPLES; i++) {
        float x, y;

        x = demodulate(data[i], mode);
        firfilt_rrrf_execute_one(filter, x, &y);

        if (fabs(y) > peak) {
            peak = fabs(y);
        }

        y = agc_apply(rx_agc, y);

        y *= 16384.0f;
        
        if (y > 16384.0f) {
            y = 16384.0f;
        } else if (y < -16384.0f) {
            y = -16384.0f;
        }
                
        rec_buf[i] = (int16_t) y;
        
        y *= adc_vol;

        if (y > 16384.0f) {
            y = 16384.0f;
        } else if (y < -16384.0f) {
            y = -16384.0f;
        }
        
        adc_buf[i] = (int16_t) y;
    }
    
    audio_adc_play(adc_buf, ADC_SAMPLES);

    if (recorder_is_on()) {
        recorder_put_audio_samples(rec_buf);
    }

    meter_count++;

    if (meter_count > 5) {
        if (dialog_msg_voice_get_state() != MSG_VOICE_RECORD) {
            meter_update(meter_db / 5.0f, 0.5f);
        }

        meter_count = 0;
        meter_db = 0;
    } else {
        meter_db += 20.0f * log10f(peak) - 56.0f;
    }

    switch (mode) {
        case RADIO_MODE_CW:
        case RADIO_MODE_CWR:
            cw_put_audio_samples(data, ADC_SAMPLES);
            break;
            
        case RADIO_MODE_RTTY:
            rtty_put_audio_samples(data, ADC_SAMPLES);
            break;
            
        default:
            dialog_audio_samples(data, ADC_SAMPLES);
            break;
    }
}

void dsp_set_spectrum_factor(uint8_t x) {
    control_set_fft_rate(240 * x);
    lv_msg_send(MSG_RATE_FFT_CHANGED, &x);
}

float dsp_get_spectrum_beta() {
    return spectrum_beta;
}

void dsp_set_spectrum_beta(float x) {
    spectrum_beta = x;
}

void dsp_auto_clear() {
    auto_clear = true;
}

static int compare_fft(const void *p1, const void *p2) {
    float *i1 = (float *) p1;
    float *i2 = (float *) p2;

    return (*i1 < *i2) ? -1 : 1;
}

static void calc_auto() {
    float       min = 0;
    float       max = 0;
    size_t      window = 30;

    qsort(auto_psd, FFT_SAMPLES, sizeof(float), compare_fft);
    
    for (size_t i = 0; i < window; i++) {
        min += auto_psd[i + fft_over];
        max += auto_psd[FFT_SAMPLES - i - fft_over - 1];
    }

    min /= window;
    max /= window;

    min = 20.0f * log10f(min) - 96.0f;
    max = 20.0f * log10f(max) - 96.0f;

    if (max > S9_40) {
        max = S9_40;
    } else if (max < S8) {
        max = S8;
    }

    if (min > S7) {
        min = S7;
    } else if (min < S_MIN) {
        min = S_MIN;
    }

    min -= 3.0f;

    if (auto_clear) {
        spectrum_auto_msg.min = min;
        spectrum_auto_msg.max = max;

        waterfall_auto_min = min;
        waterfall_auto_max = max;

        auto_clear = false;
    } else {
        lpf(&spectrum_auto_msg.min, min, 0.8f);
        lpf(&spectrum_auto_msg.max, max, 0.8f);

        lpf(&waterfall_auto_min, min, 0.5f);
        lpf(&waterfall_auto_max, max, 0.5f);
    }

    lv_lock();
    lv_msg_send(MSG_SPECTRUM_AUTO, &spectrum_auto_msg);
    lv_unlock();
}

void dsp_set_vol(uint8_t x) {
    adc_vol = x / 100.0f;
}

uint16_t dsp_change_vol(int16_t df) {
    if (df == 0) {
        return params.vol;
    }
    
    adc_mute = false;
    
    params_lock();
    params.vol = limit(params.vol + df, 0, 100);
    params_unlock(&params.durty.vol);

    dsp_set_vol(params.vol);
    
    return params.vol;
}

size_t dsp_dac(float complex *data, size_t max_size) {
    radio_state_t   state = radio_get_state();
    size_t          size = 0;

    if (state == RADIO_RX) {
        mic_on_air(false);
    } else {
        radio_mode_t mode = radio_current_mode();
    
        switch (mode) {
            case RADIO_MODE_CW:
                mic_on_air(false);
                size = cw_key_generator(data, max_size, false);
                break;

            case RADIO_MODE_CWR:
                mic_on_air(false);
                size = cw_key_generator(data, max_size, true);
                break;
                
            case RADIO_MODE_LSB:
            case RADIO_MODE_USB:
            case RADIO_MODE_AM:
            case RADIO_MODE_NFM:
                mic_on_air(true);
                size = mic_modulate(data, max_size, mode);
                break;
               
            default:
                mic_on_air(false);
                break;
        }
    }

    return size;
}
