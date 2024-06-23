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
#include "spectrum.h"
#include "waterfall.h"
#include "util.h"
#include "radio.h"
#include "params.h"
#include "meter.h"
#include "audio.h"
#include "audio_adc.h"
#include "cw.h"
#include "rtty.h"
#include "dialog_ft8.h"
#include "dialog_msg_voice.h"
#include "recorder.h"
#include "fpga/fft.h"
#include "fpga/adc.h"

const uint16_t          fft_over = (FFT_SAMPLES - 800) / 2;

static pthread_mutex_t  spectrum_mux;

static float            *spectrum_psd;
static uint16_t         spectrum_psd_count = 0;
static float            *spectrum_psd_filtered;
static float            spectrum_beta = 0.7f;
static uint16_t         spectrum_fps_ms = (1000 / 30);
static uint64_t         spectrum_time;

static float            *waterfall_psd;
static uint16_t         waterfall_psd_count = 0;
static uint16_t         waterfall_fps_ms = (1000 / 10);
static uint64_t         waterfall_time;

static firhilbf         demod_ssb;
static firfilt_rrrf     filter;

static float            *auto_psd;
static uint16_t         auto_psd_count = 0;
static uint16_t         auto_fps_ms = (1000 / 10);
static uint64_t         auto_time;

static uint8_t          meter_count = 0;
static float            meter_db = 0.0f;

static float complex    *buf;

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

    spectrum_psd = (float *) malloc(FFT_SAMPLES * sizeof(float));
    spectrum_psd_filtered = (float *) malloc(FFT_SAMPLES * sizeof(float));

    for (uint16_t i = 0; i < FFT_SAMPLES; i++)
        spectrum_psd_filtered[i] = S_MIN;

    waterfall_psd = (float *) malloc(FFT_SAMPLES * sizeof(float));
    auto_psd = (float *) malloc(FFT_SAMPLES * sizeof(float));

    buf = (float complex*) malloc(RADIO_SAMPLES * sizeof(float complex));

    demod_ssb = firhilbf_create(15, 60.0f);
    
    filter = firfilt_rrrf_create_kaiser(127, 2800.0f / 12800.0f, 30.0f, 0);
    firfilt_rrrf_set_scale(filter, 1.0f);

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
    spectrum_psd_count++;

    if (now - spectrum_time > spectrum_fps_ms) {
        for (uint16_t i = 0; i < FFT_SAMPLES; i++) {
            float x = spectrum_psd[i] / spectrum_psd_count;
            float mag = 20.0f * log10f(x) - 96.0f;
            
            spectrum_psd[i] = mag;
            lpf(&spectrum_psd_filtered[i], mag, spectrum_beta);
        }

        spectrum_data(spectrum_psd_filtered + fft_over, 800);
 
        spectrum_psd_count = 0;
        memset(spectrum_psd, 0, FFT_SAMPLES * sizeof(float));
        spectrum_time = now;
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
    for (size_t i = 0; i < FFT_SAMPLES; i++) {
        float complex x = data[i];
        float mag = sqrtf(crealf(x) * crealf(x) + cimagf(x) * cimag(x));
        uint16_t index = (i + FFT_SAMPLES / 2) % FFT_SAMPLES;

        fft_buf[index] = mag;
    }

    for (size_t i = 0; i < FFT_SAMPLES; i++) {
        float x = fft_buf[i];
    
        spectrum_psd[i] += x;
        waterfall_psd[i] += x;
        auto_psd[i] += x;
    }

    uint64_t now = get_time();

    update_spectrum(now);
    update_waterfall(now);
    update_auto(now);
}

void dsp_adc(float complex *data) {
    radio_mode_t    mode = radio_current_mode();
    float           peak = 0.0f;

    for (int i = 0; i < ADC_SAMPLES; i++) {
        float m_lsb, m_usb;
        float x = 0.0, y;

        switch (mode) {
            case radio_mode_lsb:
            case radio_mode_cwr:
                firhilbf_c2r_execute(demod_ssb, data[i], &m_lsb, &m_usb);
                x = m_lsb;
                break;

            case radio_mode_usb:
            case radio_mode_cw:
                firhilbf_c2r_execute(demod_ssb, data[i], &m_lsb, &m_usb);
                x = m_usb;
                break;
        }
  
        firfilt_rrrf_execute_one(filter, x, &y);

        if (fabs(y) > peak) {
            peak = fabs(y);
        }

        y *= 16384.0f * 2.0f;
        
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

    if (rtty_get_state() == RTTY_RX) {
        rtty_put_audio_samples(data, ADC_SAMPLES);
    } else if (mode == radio_mode_cw || mode == radio_mode_cwr) {
        cw_put_audio_samples(data, ADC_SAMPLES);
    } else {
        dialog_audio_samples(data, ADC_SAMPLES);
    }
}

void dsp_set_spectrum_factor(uint8_t x) {
}

float dsp_get_spectrum_beta() {
    return spectrum_beta;
}

void dsp_set_spectrum_beta(float x) {
    spectrum_beta = x;
}

void dsp_put_audio_samples(size_t nsamples, int16_t *samples) {
    if (!ready) {
        return;
    }

    if (dialog_msg_voice_get_state() == MSG_VOICE_RECORD) {
        dialog_msg_voice_put_audio_samples(nsamples, samples);
        return;
    }
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
        spectrum_auto_min = min;
        spectrum_auto_max = max;

        waterfall_auto_min = min;
        waterfall_auto_max = max;

        auto_clear = false;
    } else {
        lpf(&spectrum_auto_min, min, 0.8f);
        lpf(&spectrum_auto_max, max, 0.8f);

        lpf(&waterfall_auto_min, min, 0.5f);
        lpf(&waterfall_auto_max, max, 0.5f);
    }
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
