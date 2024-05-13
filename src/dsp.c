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
#include "cw.h"
#include "rtty.h"
#include "dialog_ft8.h"
#include "dialog_msg_voice.h"
#include "recorder.h"
#include "fpga/fft.h"

static int32_t          nfft = 800;

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

static float            *auto_psd;
static uint16_t         auto_psd_count = 0;
static uint16_t         auto_fps_ms = (1000 / 10);
static uint64_t         auto_time;

static float complex    *buf;

static uint8_t          delay;

static firhilbf         audio_hilb;
static float complex    *audio;

static bool             ready = false;
static bool             auto_clear = true;

static float            fft_buf[FFT_SAMPLES];

static void calc_auto();

/* * */

void dsp_init() {
    pthread_mutex_init(&spectrum_mux, NULL);

    spectrum_psd = (float *) malloc(nfft * sizeof(float));
    spectrum_psd_filtered = (float *) malloc(nfft * sizeof(float));

    for (uint16_t i = 0; i < nfft; i++)
        spectrum_psd_filtered[i] = S_MIN;

    waterfall_psd = (float *) malloc(nfft * sizeof(float));
    auto_psd = (float *) malloc(nfft * sizeof(float));

    buf = (float complex*) malloc(RADIO_SAMPLES * sizeof(float complex));

    spectrum_time = get_time();
    waterfall_time = get_time();
    auto_time = get_time();
    
    delay = 4;
    
    audio = (float complex *) malloc(AUDIO_CAPTURE_RATE * sizeof(float complex));
    audio_hilb = firhilbf_create(7, 60.0f);
    
    ready = true;
}

void dsp_reset() {
    delay = 4;
}

static void update_smeter() {
    if (dialog_msg_voice_get_state() != MSG_VOICE_RECORD) {
        int32_t filter_from, filter_to;
        int32_t from, to;
    
        radio_filter_get(&filter_from, &filter_to);
    
        from = nfft / 2;
        from -= filter_to * nfft / 100000;
    
        to = nfft / 2;
        to -= filter_from * nfft / 100000;
    
        int16_t peak_db = -121;
 
        for (int32_t i = from; i <= to; i++) {
            float x = spectrum_psd[i];
            
            if (x > peak_db)
                peak_db = x;
        }

        meter_update(peak_db, 0.8f);
    }
}

void update_auto(uint64_t now) {
    auto_psd_count++;

    if (now - auto_time > auto_fps_ms) {
        for (uint16_t i = 0; i < nfft; i++) {
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
        for (uint16_t i = 0; i < nfft; i++) {
            float x = spectrum_psd[i] / spectrum_psd_count;
            float mag = 20.0f * log10f(x) - 96.0f;
            
            spectrum_psd[i] = mag;
            lpf(&spectrum_psd_filtered[i], mag, spectrum_beta);
        }

        spectrum_data(spectrum_psd_filtered, nfft);
        update_smeter();
 
        spectrum_psd_count = 0;
        memset(spectrum_psd, 0, nfft * sizeof(float));
        spectrum_time = now;
    }
}

void update_waterfall(uint64_t now) {
    waterfall_psd_count++;

    if (now - waterfall_time > waterfall_fps_ms) {
        for (uint16_t i = 0; i < nfft; i++) {
            float x = waterfall_psd[i] / waterfall_psd_count;
            float mag = 20.0f * log10f(x) - 96.0f;
                
            waterfall_psd[i] = mag;
        }

        waterfall_data(waterfall_psd, nfft);
 
        waterfall_psd_count = 0;
        memset(waterfall_psd, 0, nfft * sizeof(float));
        waterfall_time = now;
    }
}

void dsp_fft(float complex *data) {
    for (uint16_t i = 0; i < FFT_SAMPLES; i++) {
        float complex x = data[i];
        float mag = sqrtf(crealf(x) * crealf(x) + cimagf(x) * cimag(x));
        uint16_t index = (i + FFT_SAMPLES / 2) % FFT_SAMPLES;

        fft_buf[index] = mag;
    }

    const uint16_t over = (FFT_SAMPLES - nfft) / 2;

    for (uint16_t i = 0; i < nfft; i++) {
        float x = fft_buf[i + over];
    
        spectrum_psd[i] += x;
        waterfall_psd[i] += x;
        auto_psd[i] += x;
    }

    uint64_t now = get_time();

    update_spectrum(now);
    update_waterfall(now);
    update_auto(now);
}

void dsp_samples(float complex *buf_samples, uint16_t size) {
#if 0
    int res;

    if (delay)
        delay--;

    uint64_t now = get_time();

    /* Spectrum */

    pthread_mutex_lock(&spectrum_mux);

    if (spectrum_factor > 1) {
        firdecim_crcf_execute_block(spectrum_decim, buf_samples, size / spectrum_factor, spectrum_dec_buf);
        spgramcf_write(spectrum_sg, spectrum_dec_buf, size / spectrum_factor);
    
        memset(spectrum_dec_buf, 0, sizeof(float complex) * size / spectrum_factor);

        for (uint8_t i = 0; i < spectrum_factor - 1; i++) {
            spgramcf_write(spectrum_sg, spectrum_dec_buf, size / spectrum_factor);
        }
    } else {
        spgramcf_write(spectrum_sg, buf_samples, size);
    }

    spgramcf_get_psd(spectrum_sg, spectrum_psd);

    for (uint16_t i = 0; i < nfft; i++)
        spectrum_psd[i] -= 12.0f;

    pthread_mutex_unlock(&spectrum_mux);
    
    if (now - spectrum_time > spectrum_fps_ms) {
        if (!delay) {
            for (uint16_t i = 0; i < nfft; i++) {
                float psd = spectrum_psd[i];
                
                lpf(&spectrum_psd_filtered[i], psd, spectrum_beta);
            }
        
            spectrum_data(spectrum_psd_filtered, nfft);
        }

        spgramcf_reset(spectrum_sg);
        spectrum_time = now;
    }

    /* Waterfall */

    spgramcf_write(waterfall_sg, buf_samples, size);
    spgramcf_get_psd(waterfall_sg, waterfall_psd);

    for (uint16_t i = 0; i < nfft; i++)
        waterfall_psd[i] -= 12.0f;

    if (now - waterfall_time > waterfall_fps_ms) {
        if (!delay) {
            waterfall_data(waterfall_psd, nfft);
        }

        spgramcf_reset(waterfall_sg);
        waterfall_time = now;
    }
#endif
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

    if (recorder_is_on()) {
        recorder_put_audio_samples(nsamples, samples);
    }

    for (uint16_t i = 0; i < nsamples; i++)
        firhilbf_r2c_execute(audio_hilb, samples[i] / 32768.0f, &audio[i]);

    radio_mode_t    mode = radio_current_mode();
    
    if (rtty_get_state() == RTTY_RX) {
        rtty_put_audio_samples(nsamples, audio);
    } else if (mode == radio_mode_cw || mode == radio_mode_cwr) {
        cw_put_audio_samples(nsamples, audio);
    } else {
        dialog_audio_samples(nsamples, audio);
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
    uint16_t    window = 30;

    qsort(auto_psd, nfft, sizeof(float), compare_fft);
    
    for (uint16_t i = 0; i < window; i++) {
        min += auto_psd[i];
        max += auto_psd[nfft - i - 1];
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
