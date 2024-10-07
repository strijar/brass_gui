/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sqlite3.h>
#include <string.h>

#include "lvgl/lvgl.h"
#include "params.h"
#include "util.h"
#include "bands.h"
#include "mfk.h"
#include "vol.h"
#include "dialog_msg_cw.h"
#include "qth.h"
#include "voice.h"
#include "dsp/agc.h"

#define PARAMS_SAVE_TIMEOUT  (3 * 1000)

params_t params = {
    .vol_modes              = (1 << VOL_VOL) | (1 << VOL_AGC) | (1 << VOL_FILTER_LOW) | (1 << VOL_FILTER_HIGH) | (1 << VOL_PWR) | (1 << VOL_HMIC),
    .mfk_modes              = (1 << MFK_SPECTRUM_FACTOR) | (1 << MFK_SPECTRUM_BETA) | (1 << MFK_PEAK_HOLD) | (1<< MFK_PEAK_SPEED),

    .brightness_normal      = 9,
    .brightness_idle        = 1,
    .brightness_timeout     = 10,
    .brightness_buttons     = BUTTONS_TEMPORARILY,

    .spectrum_beta          = 70,
    .spectrum_filled        = true,
    .spectrum_peak          = true,
    .spectrum_peak_hold     = 5000,
    .spectrum_peak_speed    = 0.5f,
    .mag_freq               = { .x = true,  .name = "mag_freq",             .voice = "Magnification of frequency" },
    .mag_info               = { .x = true,  .name = "mag_info",             .voice = "Magnification of info" },
    .mag_alc                = { .x = true,  .name = "mag_alc",              .voice = "Magnification of A L C" },
    .clock_view             = CLOCK_TIME_POWER,
    .clock_time_timeout     = 5,
    .clock_power_timeout    = 3,
    .clock_tx_timeout       = 1,

    .vol                    = 50,
    .rfg                    = 63,
    .ant                    = 1,
    .pwr                    = 5.0f,
    .mic                    = radio_mic_auto,
    .hmic                   = 20,
    .imic                   = 30,
    .charger                = true,
    .bias_drive             = 450,
    .bias_final             = 650,
    .rit                    = 0,
    .xit                    = 0,
    .line_in                = 10,
    .line_out               = 10,
    .moni                   = 59,
    .freq_accel             = { .x = FREQ_ACCEL_LITE,   .name = "freq_accel",       .voice = "Frequency acceleration" },
    .freq_mode              = { .x = FREQ_MODE_JOIN,    .name = "freq_mode",        .voice = "Frequency mode", .min = FREQ_MODE_JOIN, .max = FREQ_MODE_FFT_ONLY },
    .txo_offset             = { .x = 0,                 .name = "txo_offset",       .voice = "Oscilator offset", .min = -100000, .max = 1000000 },

    .dnf                    = false,
    .dnf_center             = 1000,
    .dnf_width              = 50,
    .nb                     = false,
    .nb_level               = 10,
    .nb_width               = 10,
    .nr                     = false,
    .nr_level               = 0,

    .vox                    = false,
    .vox_ag                 = 0,
    .vox_delay              = 100,
    .vox_gain               = 50,

    .key_speed              = 15,
    .key_mode               = cw_key_manual,
    .iambic_mode            = cw_key_iambic_a,
    .key_tone               = 700,
    .key_vol                = 10,
    .key_train              = false,
    .qsk_time               = 100,
    .key_ratio              = 30,
    
    .cw_decoder             = true,
    .cw_decoder_snr         = 10.0f,
    .cw_decoder_snr_gist    = 3.0f,
    .cw_decoder_peak_beta   = 0.10f,
    .cw_decoder_noise_beta  = 0.80f,

    .cw_encoder_period      = 10,
    .voice_msg_period       = 10,
    
    .rtty_center            = 800,
    .rtty_shift             = 170,
    .rtty_rate              = 4545,
    .rtty_reverse           = false,
    .rtty_bits              = 5,
    .rtty_snr               = 3.0f,

    .swrscan_linear         = true,
    .swrscan_span           = 200000,

    .ft8_show_all           = true,
    .ft8_protocol           = PROTO_FT8,
    .ft8_band               = 5,
    .ft8_tx_freq            = { .x = 1325,      .name = "ft8_tx_freq" },
    .ft8_auto               = { .x = true,      .name = "ft8_auto" },

    .long_gen               = ACTION_SCREENSHOT,
    .long_app               = ACTION_APP_RECORDER,
    .long_key               = ACTION_NONE,
    .long_msg               = ACTION_RECORDER,
    .long_dfn               = ACTION_VOICE_MODE,
    .long_dfl               = ACTION_NONE,
    
    .press_f1               = ACTION_STEP_UP,
    .press_f2               = ACTION_NONE,
    .long_f1                = ACTION_STEP_DOWN,
    .long_f2                = ACTION_NONE,
    
    .play_gain              = 100,
    .rec_gain               = 100,
    .rec_format             = REC_FORMAT_WAV,

    .voice_mode             = { .x = VOICE_LCD,                                 .name = "voice_mode" },
    .voice_lang             = { .x = 0,   .min = 0,  .max = (VOICES_NUM - 1),   .name = "voice_lang" },
    .voice_rate             = { .x = 100, .min = 50, .max = 150,                .name = "voice_rate",     .voice = "Voice rate" },
    .voice_pitch            = { .x = 100, .min = 50, .max = 150,                .name = "voice_pitch",    .voice = "Voice pitch" },
    .voice_volume           = { .x = 100, .min = 50, .max = 150,                .name = "voice_volume",   .voice = "Voice volume" },

    .qth                    = { .x = "",  .max_len = 6, .name = "qth" },
    .callsign               = { .x = "",  .max_len = 12, .name = "callsign" },

    .mic_filter_low         = { .x = 150,   .min = 100,     .max = 300,     .name = "mic_filter_low" },
    .mic_filter_high        = { .x = 2900,  .min = 1000,    .max = 3200,    .name = "mic_filter_high" },
    .mic_filter_transition  = { .x = 100,   .min = 50,      .max = 200,     .name = "mic_filter_transition" },
};

params_band_t params_band = {
    .freq_rx        = 14000000,
    .freq_tx        = 14000000,
    .freq_fft       = 14000000,
    .att            = radio_att_off,
    .pre            = radio_pre_off,
    .mode           = radio_mode_usb,

    .split          = SPLIT_NONE
};

params_mode_t params_mode = {
    .filter_low         = 50,
    .filter_high        = 2950,
    .filter_transition  = 100,
    .agc                = AGC_MED,

    .freq_step          = 500,
    .spectrum_factor    = 1,
};

transverter_t params_transverter[TRANSVERTER_NUM] = {
    { .from = 144000000,    .to = 150000000,    .shift = 116000000 },
    { .from = 432000000,    .to = 438000000,    .shift = 404000000 }
};

static pthread_mutex_t  params_mux;
static uint64_t         durty_time;
static sqlite3          *db = NULL;
static sqlite3_stmt     *write_stmt;
static sqlite3_stmt     *write_mb_stmt;
static sqlite3_stmt     *write_mode_stmt;
static sqlite3_stmt     *save_atu_stmt;
static sqlite3_stmt     *load_atu_stmt;
static sqlite3_stmt     *bands_find_all_stmt;
static sqlite3_stmt     *bands_find_stmt;

static bool params_exec(const char *sql);
static bool params_mb_save(uint16_t id);
static void params_mb_load(sqlite3_stmt *stmt, bool set_freq);

/* Mode params */

void params_mode_load() {
    sqlite3_stmt    *stmt;
    int             rc;

    rc = sqlite3_prepare_v2(db, "SELECT name,val FROM mode_params WHERE mode = ?", -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        LV_LOG_ERROR("Prepare");
        return;
    }

    radio_mode_t    mode = radio_current_mode();

    sqlite3_bind_int(stmt, 1, mode);

    while (sqlite3_step(stmt) != SQLITE_DONE) {
        const char *name = sqlite3_column_text(stmt, 0);

        if (strcmp(name, "filter_low") == 0) {
            params_mode.filter_low = sqlite3_column_int(stmt, 1);
        } else if (strcmp(name, "filter_high") == 0) {
            params_mode.filter_high = sqlite3_column_int(stmt, 1);
        } else if (strcmp(name, "filter_transition") == 0) {
            params_mode.filter_transition = sqlite3_column_int(stmt, 1);
        } else if (strcmp(name, "freq_step") == 0) {
            params_mode.freq_step = sqlite3_column_int(stmt, 1);
        } else if (strcmp(name, "spectrum_factor") == 0) {
            params_mode.spectrum_factor = sqlite3_column_int(stmt, 1);
        } else if (strcmp(name, "agc") == 0) {
            params_mode.agc = sqlite3_column_int(stmt, 1);
        }
    }

    sqlite3_finalize(stmt);
}

static void params_mode_write_int(const char *name, int data, bool *durty) {
    radio_mode_t    mode = radio_current_mode();

    sqlite3_bind_int(write_mode_stmt, 1, mode);
    sqlite3_bind_text(write_mode_stmt, 2, name, strlen(name), 0);
    sqlite3_bind_int(write_mode_stmt, 3, data);
    sqlite3_step(write_mode_stmt);
    sqlite3_reset(write_mode_stmt);
    sqlite3_clear_bindings(write_mode_stmt);
    
    *durty = false;
}

void params_mode_save() {
    if (!params_exec("BEGIN")) {
        return;
    }

    if (params_mode.durty.filter_low)           params_mode_write_int("filter_low", params_mode.filter_low, &params_mode.durty.filter_low);
    if (params_mode.durty.filter_high)          params_mode_write_int("filter_high", params_mode.filter_high, &params_mode.durty.filter_high);
    if (params_mode.durty.filter_transition)    params_mode_write_int("filter_transition", params_mode.filter_transition, &params_mode.durty.filter_transition);
    if (params_mode.durty.freq_step)            params_mode_write_int("freq_step", params_mode.freq_step, &params_mode.durty.freq_step);
    if (params_mode.durty.spectrum_factor)      params_mode_write_int("spectrum_factor", params_mode.spectrum_factor, &params_mode.durty.spectrum_factor);
    if (params_mode.durty.agc)                  params_mode_write_int("agc", params_mode.agc, &params_mode.durty.agc);

    params_exec("COMMIT");
}

/* Memory/Bands params */

void params_memory_load(uint16_t id) {
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, "SELECT name,val FROM memory WHERE id = ?", -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        LV_LOG_ERROR("Prepare");
        return;
    }

    sqlite3_bind_int(stmt, 1, id);
    params_mb_load(stmt, true);
}

void params_band_load(bool set_freq) {
    if (params.band < 0) {
        return;
    }

    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, "SELECT name,val FROM band_params WHERE bands_id = ?", -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        LV_LOG_ERROR("Prepare");
        return;
    }

    sqlite3_bind_int(stmt, 1, params.band);
    params_mb_load(stmt, set_freq);
}

static void params_mb_load(sqlite3_stmt *stmt, bool set_freq) {
    memset(params_band.label, 0, sizeof(params_band.label));
    
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        const char *name = sqlite3_column_text(stmt, 0);

        if (strcmp(name, "freq") == 0) {
            if (set_freq) {
                uint64_t x = sqlite3_column_int64(stmt, 1);
        
                params_band.freq_rx = x;
                params_band.freq_tx = x;
                params_band.freq_fft = x;
            }
        } else if (strcmp(name, "att") == 0) {
            params_band.att = sqlite3_column_int(stmt, 1);
        } else if (strcmp(name, "pre") == 0) {
            params_band.pre = sqlite3_column_int(stmt, 1);
        } else if (strcmp(name, "mode") == 0) {
            params_band.mode = sqlite3_column_int(stmt, 1);
        } else if (strcmp(name, "freq_rx") == 0) {
            if (set_freq) {
                uint64_t x = sqlite3_column_int64(stmt, 1);
        
                params_band.freq_rx = x;
            }
        } else if (strcmp(name, "freq_tx") == 0) {
            if (set_freq) {
                uint64_t x = sqlite3_column_int64(stmt, 1);
        
                params_band.freq_tx = x;
            }
        } else if (strcmp(name, "freq_fft") == 0) {
            if (set_freq) {
                uint64_t x = sqlite3_column_int64(stmt, 1);
        
                params_band.freq_fft = x;
            }
        } else if (strcmp(name, "split") == 0) {
            params_band.split = sqlite3_column_int(stmt, 1);
        } else if (strcmp(name, "label") == 0) {
            strncpy(params_band.label, sqlite3_column_text(stmt, 1), sizeof(params_band.label) - 1);
        }
    }

    sqlite3_finalize(stmt);
    params_mode_load();
}

static void params_mb_write_int(uint16_t id, const char *name, int data, bool *durty) {
    sqlite3_bind_int(write_mb_stmt, 1, id);
    sqlite3_bind_text(write_mb_stmt, 2, name, strlen(name), 0);
    sqlite3_bind_int(write_mb_stmt, 3, data);
    sqlite3_step(write_mb_stmt);
    sqlite3_reset(write_mb_stmt);
    sqlite3_clear_bindings(write_mb_stmt);
    
    *durty = false;
}

static void params_mb_write_int64(uint16_t id, const char *name, uint64_t data, bool *durty) {
    sqlite3_bind_int(write_mb_stmt, 1, id);
    sqlite3_bind_text(write_mb_stmt, 2, name, strlen(name), 0);
    sqlite3_bind_int64(write_mb_stmt, 3, data);
    sqlite3_step(write_mb_stmt);
    sqlite3_reset(write_mb_stmt);
    sqlite3_clear_bindings(write_mb_stmt);
    
    *durty = false;
}

void params_band_save() {
    if (params.band < 0) {
        return;
    }

    if (!params_exec("BEGIN")) {
        return;
    }

    sqlite3_prepare_v2(db, "INSERT INTO band_params(bands_id, name, val) VALUES(?, ?, ?)", -1, &write_mb_stmt, 0);
    
    params_mb_save(params.band);
    sqlite3_finalize(write_mb_stmt);
}

void params_memory_save(uint16_t id) {
    if (!params_exec("BEGIN")) {
        return;
    }

    sqlite3_prepare_v2(db, "INSERT INTO memory(id, name, val) VALUES(?, ?, ?)", -1, &write_mb_stmt, 0);

    params_band.durty.freq_rx = true;
    params_band.durty.freq_tx = true;
    params_band.durty.freq_fft = true;
    params_band.durty.att = true;
    params_band.durty.pre = true;
    params_band.durty.mode = true;
    params_band.durty.split = true;
    
    params_mb_save(id);
    sqlite3_finalize(write_mb_stmt);
}

static bool params_mb_save(uint16_t id) {
    if (params_band.durty.freq_rx)
        params_mb_write_int64(id, "freq_rx", params_band.freq_rx, &params_band.durty.freq_rx);

    if (params_band.durty.freq_tx)
        params_mb_write_int64(id, "freq_tx", params_band.freq_tx, &params_band.durty.freq_tx);

    if (params_band.durty.freq_fft)
        params_mb_write_int64(id, "freq_fft", params_band.freq_fft, &params_band.durty.freq_fft);
        
    if (params_band.durty.att)
        params_mb_write_int(id, "att", params_band.att, &params_band.durty.att);
        
    if (params_band.durty.pre)
        params_mb_write_int(id, "pre", params_band.pre, &params_band.durty.pre);
        
    if (params_band.durty.mode)
        params_mb_write_int(id, "mode", params_band.mode, &params_band.durty.mode);

    if (params_band.durty.split)
        params_mb_write_int(id, "split", params_band.split, &params_band.durty.split);
        
    if (!params_exec("COMMIT")) {
        return false;
    }

    params_mode_save();

    return true;
}

/* System params */

static bool params_load_bool(params_bool_t *var, const char *name, const int32_t x) {
    if (strcmp(name, var->name) == 0) {
        var->x = x;
        return true;
    }
    
    return false;
}

static bool params_load_uint8(params_uint8_t *var, const char *name, const int32_t x) {
    if (strcmp(name, var->name) == 0) {
        var->x = x;
        return true;
    }
    
    return false;
}

static bool params_load_uint16(params_uint16_t *var, const char *name, const int32_t x) {
    if (strcmp(name, var->name) == 0) {
        var->x = x;
        return true;
    }
    
    return false;
}

static bool params_load_int32(params_int32_t *var, const char *name, const int32_t x) {
    if (strcmp(name, var->name) == 0) {
        var->x = x;
        return true;
    }
    
    return false;
}

static bool params_load_uint64(params_uint64_t *var, const char *name, const uint64_t x) {
    if (strcmp(name, var->name) == 0) {
        var->x = x;
        return true;
    }
    
    return false;
}

static bool params_load_str(params_str_t *var, const char *name, const char *x) {
    if (strcmp(name, var->name) == 0) {
        strncpy(var->x, x, sizeof(var->x) - 1);
        return true;
    }
    
    return false;
}

static bool params_load() {
    sqlite3_stmt    *stmt;
    int             rc;
    
    rc = sqlite3_prepare_v2(db, "SELECT * FROM params", -1, &stmt, 0);
    
    if (rc != SQLITE_OK) {
        return false;
    }
    
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        const char      *name = sqlite3_column_text(stmt, 0);
        const int32_t   i = sqlite3_column_int(stmt, 1);
        const int64_t   l = sqlite3_column_int64(stmt, 1);
        const char      *t = sqlite3_column_text(stmt, 1);

        if (strcmp(name, "band") == 0) {
            params.band = i;
            params_band_load(true);
        } else if (strcmp(name, "vol") == 0) {
            params.vol = i;
        } else if (strcmp(name, "rfg") == 0) {
            params.rfg = i;
        } else if (strcmp(name, "sql") == 0) {
            params.sql = i;
        } else if (strcmp(name, "atu") == 0) {
            params.atu = i;
        } else if (strcmp(name, "pwr") == 0) {
            params.pwr = i * 0.1f;
        } else if (strcmp(name, "spectrum_beta") == 0) {
            params.spectrum_beta = i;
        } else if (strcmp(name, "spectrum_filled") == 0) {
            params.spectrum_filled = i;
        } else if (strcmp(name, "spectrum_peak") == 0) {
            params.spectrum_peak = i;
        } else if (strcmp(name, "spectrum_peak_hold") == 0) {
            params.spectrum_peak_hold = i;
        } else if (strcmp(name, "spectrum_peak_speed") == 0) {
            params.spectrum_peak_speed = i * 0.1f;
        } else if (strcmp(name, "key_speed") == 0) {
            params.key_speed = i;
        } else if (strcmp(name, "key_mode") == 0) {
            params.key_mode = i;
        } else if (strcmp(name, "iambic_mode") == 0) {
            params.iambic_mode = i;
        } else if (strcmp(name, "key_tone") == 0) {
            params.key_tone = i;
        } else if (strcmp(name, "key_vol") == 0) {
            params.key_vol = i;
        } else if (strcmp(name, "key_train") == 0) {
            params.key_train = i;
        } else if (strcmp(name, "qsk_time") == 0) {
            params.qsk_time = i;
        } else if (strcmp(name, "key_ratio") == 0) {
            params.key_ratio = i;
        } else if (strcmp(name, "mic") == 0) {
            params.mic = i;
        } else if (strcmp(name, "hmic") == 0) {
            params.hmic = i;
        } else if (strcmp(name, "imic") == 0) {
            params.imic = i;
        } else if (strcmp(name, "charger") == 0) {
            params.charger = i;
        } else if (strcmp(name, "dnf") == 0) {
            params.dnf = i;
        } else if (strcmp(name, "dnf_center") == 0) {
            params.dnf_center = i;
        } else if (strcmp(name, "dnf_width") == 0) {
            params.dnf_width = i;
        } else if (strcmp(name, "nb") == 0) {
            params.nb = i;
        } else if (strcmp(name, "nb_level") == 0) {
            params.nb_level = i;
        } else if (strcmp(name, "nb_width") == 0) {
            params.nb_width = i;
        } else if (strcmp(name, "nr") == 0) {
            params.nr = i;
        } else if (strcmp(name, "nr_level") == 0) {
            params.nr_level = i;
        } else if (strcmp(name, "cw_decoder") == 0) {
            params.cw_decoder = i;
        } else if (strcmp(name, "cw_decoder_snr") == 0) {
            params.cw_decoder_snr = i * 0.1f;
        } else if (strcmp(name, "cw_decoder_peak_beta") == 0) {
            params.cw_decoder_peak_beta = i * 0.01f;
        } else if (strcmp(name, "cw_decoder_noise_beta") == 0) {
            params.cw_decoder_noise_beta = i * 0.01f;
        } else if (strcmp(name, "cw_encoder_period") == 0) {
            params.cw_encoder_period = i;
        } else if (strcmp(name, "voice_msg_period") == 0) {
            params.voice_msg_period = i;
        } else if (strcmp(name, "vol_modes") == 0) {
            params.vol_modes = l;
        } else if (strcmp(name, "mfk_modes") == 0) {
            params.mfk_modes = l;
        } else if (strcmp(name, "rtty_rate") == 0) {
            params.rtty_rate = i;
        } else if (strcmp(name, "rtty_shift") == 0) {
            params.rtty_shift = i;
        } else if (strcmp(name, "rtty_center") == 0) {
            params.rtty_center = i;
        } else if (strcmp(name, "rtty_reverse") == 0) {
            params.rtty_reverse = i;
        } else if (strcmp(name, "ant") == 0) {
            params.ant = i;
        } else if (strcmp(name, "rit") == 0) {
            params.rit = i;
        } else if (strcmp(name, "xit") == 0) {
            params.xit = i;
        } else if (strcmp(name, "brightness_normal") == 0) {
            params.brightness_normal = i;
        } else if (strcmp(name, "brightness_idle") == 0) {
            params.brightness_idle = i;
        } else if (strcmp(name, "brightness_timeout") == 0) {
            params.brightness_timeout = i;
        } else if (strcmp(name, "brightness_buttons") == 0) {
            params.brightness_buttons = i;
        } else if (strcmp(name, "line_in") == 0) {
            params.line_in = i;
        } else if (strcmp(name, "line_out") == 0) {
            params.line_out = i;
        } else if (strcmp(name, "moni") == 0) {
            params.moni = i;
        } else if (strcmp(name, "clock_view") == 0) {
            params.clock_view = i;
        } else if (strcmp(name, "clock_time_timeout") == 0) {
            params.clock_time_timeout = i;
        } else if (strcmp(name, "clock_power_timeout") == 0) {
            params.clock_power_timeout = i;
        } else if (strcmp(name, "clock_tx_timeout") == 0) {
            params.clock_tx_timeout = i;
        } else if (strcmp(name, "swrscan_linear") == 0) {
            params.swrscan_linear = i;
        } else if (strcmp(name, "swrscan_span") == 0) {
            params.swrscan_span = i;
        } else if (strcmp(name, "ft8_show_all") == 0) {
            params.ft8_show_all = i;
        } else if (strcmp(name, "ft8_band") == 0) {
            params.ft8_band = i;
        } else if (strcmp(name, "ft8_protocol") == 0) {
            params.ft8_protocol = i;
        } else if (strcmp(name, "long_gen") == 0) {
            params.long_gen = i;
        } else if (strcmp(name, "long_app") == 0) {
            params.long_app = i;
        } else if (strcmp(name, "long_key") == 0) {
            params.long_key = i;
        } else if (strcmp(name, "long_msg") == 0) {
            params.long_msg = i;
        } else if (strcmp(name, "long_dfn") == 0) {
            params.long_dfn = i;
        } else if (strcmp(name, "long_dfl") == 0) {
            params.long_dfl = i;
        } else if (strcmp(name, "press_f1") == 0) {
            params.press_f1 = i;
        } else if (strcmp(name, "press_f2") == 0) {
            params.press_f2 = i;
        } else if (strcmp(name, "long_f1") == 0) {
            params.long_f1 = i;
        } else if (strcmp(name, "long_f2") == 0) {
            params.long_f2 = i;
        } else if (strcmp(name, "play_gain") == 0) {
            params.play_gain = i;
        } else if (strcmp(name, "rec_gain") == 0) {
            params.rec_gain = i;
        } 
        
        if (params_load_bool(&params.mag_freq, name, i)) continue;
        if (params_load_bool(&params.mag_info, name, i)) continue;
        if (params_load_bool(&params.mag_alc, name, i)) continue;
        if (params_load_bool(&params.ft8_auto, name, i)) continue;

        if (params_load_uint8(&params.voice_mode, name, i)) continue;
        if (params_load_uint8(&params.voice_lang, name, i)) continue;
        if (params_load_uint8(&params.voice_rate, name, i)) continue;
        if (params_load_uint8(&params.voice_pitch, name, i)) continue;
        if (params_load_uint8(&params.voice_volume, name, i)) continue;
        if (params_load_uint8(&params.freq_accel, name, i)) continue;
        if (params_load_uint8(&params.freq_mode, name, i)) continue;
        if (params_load_int32(&params.txo_offset, name, i)) continue;

        if (params_load_uint16(&params.ft8_tx_freq, name, i)) continue;

        if (params_load_str(&params.qth, name, t)) { 
            qth_update(t);
            continue;
        }

        if (params_load_str(&params.callsign, name, t)) continue;
    }
    
    sqlite3_finalize(stmt);
    return true;
}

static bool params_exec(const char *sql) {
    char    *err = 0;
    int     rc;
    
    rc = sqlite3_exec(db, sql, NULL, NULL, &err);
    
    if (rc != SQLITE_OK) {
        LV_LOG_ERROR(err);
        return false;
    }
    
    return true;
}

static void params_write_int(const char *name, int data, bool *durty) {
    sqlite3_bind_text(write_stmt, 1, name, strlen(name), 0);
    sqlite3_bind_int(write_stmt, 2, data);
    sqlite3_step(write_stmt);
    sqlite3_reset(write_stmt);
    sqlite3_clear_bindings(write_stmt);
    
    *durty = false;
}

static void params_write_int64(const char *name, uint64_t data, bool *durty) {
    sqlite3_bind_text(write_stmt, 1, name, strlen(name), 0);
    sqlite3_bind_int64(write_stmt, 2, data);
    sqlite3_step(write_stmt);
    sqlite3_reset(write_stmt);
    sqlite3_clear_bindings(write_stmt);
    
    *durty = false;
}

static void params_write_text(const char *name, const char *data, bool *durty) {
    sqlite3_bind_text(write_stmt, 1, name, strlen(name), 0);
    sqlite3_bind_text(write_stmt, 2, data, strlen(data), 0);
    sqlite3_step(write_stmt);
    sqlite3_reset(write_stmt);
    sqlite3_clear_bindings(write_stmt);
    
    *durty = false;
}

static void params_save_bool(params_bool_t *var) {
    if (var->durty) {
        params_write_int(var->name, var->x, &var->durty);
    }
}

static void params_save_uint8(params_uint8_t *var) {
    if (var->durty) {
        params_write_int(var->name, var->x, &var->durty);
    }
}

static void params_save_uint16(params_uint16_t *var) {
    if (var->durty) {
        params_write_int(var->name, var->x, &var->durty);
    }
}

static void params_save_int32(params_int32_t *var) {
    if (var->durty) {
        params_write_int(var->name, var->x, &var->durty);
    }
}

static void params_save_uint64(params_uint64_t *var) {
    if (var->durty) {
        params_write_int64(var->name, var->x, &var->durty);
    }
}

static void params_save_str(params_str_t *var) {
    if (var->durty) {
        params_write_text(var->name, var->x, &var->durty);
    }
}

static void params_save() {
    if (!params_exec("BEGIN")) {
        return;
    }

    if (params.durty.band)                  params_write_int("band", params.band, &params.durty.band);
    if (params.durty.vol)                   params_write_int("vol", params.vol, &params.durty.vol);
    if (params.durty.rfg)                   params_write_int("rfg", params.rfg, &params.durty.rfg);
    if (params.durty.sql)                   params_write_int("sql", params.sql, &params.durty.sql);
    if (params.durty.atu)                   params_write_int("atu", params.atu, &params.durty.atu);
    if (params.durty.pwr)                   params_write_int("pwr", params.pwr * 10, &params.durty.pwr);

    if (params.durty.spectrum_beta)         params_write_int("spectrum_beta", params.spectrum_beta, &params.durty.spectrum_beta);
    if (params.durty.spectrum_filled)       params_write_int("spectrum_filled", params.spectrum_filled, &params.durty.spectrum_filled);
    if (params.durty.spectrum_peak)         params_write_int("spectrum_peak", params.spectrum_peak, &params.durty.spectrum_peak);
    if (params.durty.spectrum_peak_hold)    params_write_int("spectrum_peak_hold", params.spectrum_peak_hold, &params.durty.spectrum_peak_hold);
    if (params.durty.spectrum_peak_speed)   params_write_int("spectrum_peak_speed", params.spectrum_peak_speed * 10, &params.durty.spectrum_peak_speed);

    if (params.durty.key_speed)             params_write_int("key_speed", params.key_speed, &params.durty.key_speed);
    if (params.durty.key_mode)              params_write_int("key_mode", params.key_mode, &params.durty.key_mode);
    if (params.durty.iambic_mode)           params_write_int("iambic_mode", params.iambic_mode, &params.durty.iambic_mode);
    if (params.durty.key_tone)              params_write_int("key_tone", params.key_tone, &params.durty.key_tone);
    if (params.durty.key_vol)               params_write_int("key_vol", params.key_vol, &params.durty.key_vol);
    if (params.durty.key_train)             params_write_int("key_train", params.key_train, &params.durty.key_train);
    if (params.durty.qsk_time)              params_write_int("qsk_time", params.qsk_time, &params.durty.qsk_time);
    if (params.durty.key_ratio)             params_write_int("key_ratio", params.key_ratio, &params.durty.key_ratio);

    if (params.durty.mic)                   params_write_int("mic", params.mic, &params.durty.mic);
    if (params.durty.hmic)                  params_write_int("hmic", params.hmic, &params.durty.hmic);
    if (params.durty.imic)                  params_write_int("imic", params.imic, &params.durty.imic);

    if (params.durty.charger)               params_write_int("charger", params.charger, &params.durty.charger);

    if (params.durty.dnf)                   params_write_int("dnf", params.dnf, &params.durty.dnf);
    if (params.durty.dnf_center)            params_write_int("dnf_center", params.dnf_center, &params.durty.dnf_center);
    if (params.durty.dnf_width)             params_write_int("dnf_width", params.dnf_width, &params.durty.dnf_width);
    if (params.durty.nb)                    params_write_int("nb", params.nb, &params.durty.nb);
    if (params.durty.nb_level)              params_write_int("nb_level", params.nb_level, &params.durty.nb_level);
    if (params.durty.nb_width)              params_write_int("nb_width", params.nb_width, &params.durty.nb_width);
    if (params.durty.nr)                    params_write_int("nr", params.nr, &params.durty.nr);
    if (params.durty.nr_level)              params_write_int("nr_level", params.nr_level, &params.durty.nr_level);

    if (params.durty.cw_decoder)            params_write_int("cw_decoder", params.cw_decoder, &params.durty.cw_decoder);
    if (params.durty.cw_decoder_snr)        params_write_int("cw_decoder_snr", params.cw_decoder_snr * 10, &params.durty.cw_decoder_snr);
    if (params.durty.cw_decoder_peak_beta)  params_write_int("cw_decoder_peak_beta", params.cw_decoder_peak_beta * 100, &params.durty.cw_decoder_peak_beta);
    if (params.durty.cw_decoder_noise_beta) params_write_int("cw_decoder_noise_beta", params.cw_decoder_noise_beta * 100, &params.durty.cw_decoder_noise_beta);

    if (params.durty.cw_encoder_period)     params_write_int("cw_encoder_period", params.cw_encoder_period, &params.durty.cw_encoder_period);
    if (params.durty.voice_msg_period)      params_write_int("voice_msg_period", params.voice_msg_period, &params.durty.voice_msg_period);

    if (params.durty.vol_modes)             params_write_int64("vol_modes", params.vol_modes, &params.durty.vol_modes);
    if (params.durty.mfk_modes)             params_write_int64("mfk_modes", params.mfk_modes, &params.durty.mfk_modes);

    if (params.durty.rtty_rate)             params_write_int("rtty_rate", params.rtty_rate, &params.durty.rtty_rate);
    if (params.durty.rtty_shift)            params_write_int("rtty_shift", params.rtty_shift, &params.durty.rtty_shift);
    if (params.durty.rtty_center)           params_write_int("rtty_center", params.rtty_center, &params.durty.rtty_center);
    if (params.durty.rtty_reverse)          params_write_int("rtty_reverse", params.rtty_reverse, &params.durty.rtty_reverse);

    if (params.durty.ant)                   params_write_int("ant", params.ant, &params.durty.ant);
    if (params.durty.rit)                   params_write_int("rit", params.rit, &params.durty.rit);
    if (params.durty.xit)                   params_write_int("xit", params.xit, &params.durty.xit);

    if (params.durty.line_in)               params_write_int("line_in", params.line_in, &params.durty.line_in);
    if (params.durty.line_out)              params_write_int("line_out", params.line_out, &params.durty.line_out);

    if (params.durty.moni)                  params_write_int("moni", params.moni, &params.durty.moni);

    if (params.durty.brightness_normal)     params_write_int("brightness_normal", params.brightness_normal, &params.durty.brightness_normal);
    if (params.durty.brightness_idle)       params_write_int("brightness_idle", params.brightness_idle, &params.durty.brightness_idle);
    if (params.durty.brightness_timeout)    params_write_int("brightness_timeout", params.brightness_timeout, &params.durty.brightness_timeout);
    if (params.durty.brightness_buttons)    params_write_int("brightness_buttons", params.brightness_buttons, &params.durty.brightness_buttons);

    if (params.durty.clock_view)            params_write_int("clock_view", params.clock_view, &params.durty.clock_view);
    if (params.durty.clock_time_timeout)    params_write_int("clock_time_timeout", params.clock_time_timeout, &params.durty.clock_time_timeout);
    if (params.durty.clock_power_timeout)   params_write_int("clock_power_timeout", params.clock_power_timeout, &params.durty.clock_power_timeout);
    if (params.durty.clock_tx_timeout)      params_write_int("clock_tx_timeout", params.clock_tx_timeout, &params.durty.clock_tx_timeout);

    if (params.durty.swrscan_linear)        params_write_int("swrscan_linear", params.swrscan_linear, &params.durty.swrscan_linear);
    if (params.durty.swrscan_span)          params_write_int("swrscan_span", params.swrscan_span, &params.durty.swrscan_span);

    if (params.durty.ft8_show_all)          params_write_int("ft8_show_all", params.ft8_show_all, &params.durty.ft8_show_all);
    if (params.durty.ft8_band)              params_write_int("ft8_band", params.ft8_band, &params.durty.ft8_band);
    if (params.durty.ft8_protocol)          params_write_int("ft8_protocol", params.ft8_protocol, &params.durty.ft8_protocol);

    if (params.durty.long_gen)              params_write_int("long_gen", params.long_gen, &params.durty.long_gen);
    if (params.durty.long_app)              params_write_int("long_app", params.long_app, &params.durty.long_app);
    if (params.durty.long_key)              params_write_int("long_key", params.long_key, &params.durty.long_key);
    if (params.durty.long_msg)              params_write_int("long_msg", params.long_msg, &params.durty.long_msg);
    if (params.durty.long_dfn)              params_write_int("long_dfn", params.long_dfn, &params.durty.long_dfn);
    if (params.durty.long_dfl)              params_write_int("long_dfl", params.long_dfl, &params.durty.long_dfl);

    if (params.durty.press_f1)              params_write_int("press_f1", params.press_f1, &params.durty.press_f1);
    if (params.durty.press_f2)              params_write_int("press_f2", params.press_f2, &params.durty.press_f2);
    if (params.durty.long_f1)               params_write_int("long_f1", params.long_f1, &params.durty.long_f1);
    if (params.durty.long_f2)               params_write_int("long_f2", params.long_f2, &params.durty.long_f2);

    if (params.durty.play_gain)             params_write_int("play_gain", params.play_gain, &params.durty.play_gain);
    if (params.durty.rec_gain)              params_write_int("rec_gain", params.rec_gain, &params.durty.rec_gain);

    params_save_uint8(&params.voice_mode);
    params_save_uint8(&params.voice_lang);
    params_save_uint8(&params.voice_rate);
    params_save_uint8(&params.voice_pitch);
    params_save_uint8(&params.voice_volume);
    params_save_uint8(&params.freq_accel);
    params_save_uint8(&params.freq_mode);
    params_save_int32(&params.txo_offset);

    params_save_uint16(&params.ft8_tx_freq);

    params_save_bool(&params.mag_freq);
    params_save_bool(&params.mag_info);
    params_save_bool(&params.mag_alc);
    params_save_bool(&params.ft8_auto);

    params_save_str(&params.qth);
    params_save_str(&params.callsign);

    params_exec("COMMIT");
}

/* Transverter */

bool transverter_load() {
    sqlite3_stmt    *stmt;
    int             rc;
    
    rc = sqlite3_prepare_v2(db, "SELECT * FROM transverter", -1, &stmt, 0);
    
    if (rc != SQLITE_OK) {
        return false;
    }
    
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        const int       id = sqlite3_column_int(stmt, 0);
        const char      *name = sqlite3_column_text(stmt, 1);
        const uint64_t  val = sqlite3_column_int64(stmt, 2);

        if (strcmp(name, "from") == 0) {
            params_transverter[id].from = val;
        } else if (strcmp(name, "to") == 0) {
            params_transverter[id].to = val;
        } else if (strcmp(name, "shift") == 0) {
            params_transverter[id].shift = val;
        }
    }

    sqlite3_finalize(stmt);
    return true;
}

static void transverter_write(sqlite3_stmt *stmt, uint8_t id, const char *name, uint64_t data, bool *durty) {
    sqlite3_bind_int64(stmt, 1, id);
    sqlite3_bind_text(stmt, 2, name, strlen(name), 0);
    sqlite3_bind_int64(stmt, 3, data);
    sqlite3_step(stmt);
    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);
    
    *durty = false;
}

void transverter_save() {
    sqlite3_stmt    *stmt;
    int             rc;

    rc = sqlite3_prepare_v2(db, "INSERT INTO transverter(id, name, val) VALUES(?, ?, ?)", -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        return;
    }

    if (!params_exec("BEGIN")) {
        return;
    }
    
    for (uint8_t i = 0; i < TRANSVERTER_NUM; i++) {
        transverter_t *transverter = &params_transverter[i];
        
        if (transverter->durty.from)    transverter_write(stmt, i, "from", transverter->from, &transverter->durty.from);
        if (transverter->durty.to)      transverter_write(stmt, i, "to", transverter->to, &transverter->durty.to);
        if (transverter->durty.shift)   transverter_write(stmt, i, "shift", transverter->shift, &transverter->durty.shift);
    }

    params_exec("COMMIT");
}

/* * */

static void * params_thread(void *arg) {
    while (true) {
        pthread_mutex_lock(&params_mux);

        if (durty_time) {
            uint64_t    now = get_time();
            int32_t     d = now - durty_time;
    
            if (d > PARAMS_SAVE_TIMEOUT) {
                durty_time = 0;

                params_save();
                params_band_save();
                params_mode_save();
                transverter_save();
            }
        }
        
        pthread_mutex_unlock(&params_mux);
        usleep(100000);
    }
}

void params_init() {
    int rc = sqlite3_open("/mnt/params.db", &db);
    
    if (rc == SQLITE_OK) {
        if (!params_load()) {
            LV_LOG_ERROR("Load params");
            sqlite3_close(db);
            db = NULL;
        }

        rc = sqlite3_prepare_v2(db, "INSERT INTO params(name, val) VALUES(?, ?)", -1, &write_stmt, 0);

        if (rc != SQLITE_OK) {
            LV_LOG_ERROR("Prepare write");
        }

        rc = sqlite3_prepare_v2(db, "INSERT INTO mode_params(mode, name, val) VALUES(?, ?, ?)", -1, &write_mode_stmt, 0);

        if (rc != SQLITE_OK) {
            LV_LOG_ERROR("Prepare mode write");
        }

        rc = sqlite3_prepare_v2(db, "INSERT INTO atu(ant, freq, val) VALUES(?, ?, ?)", -1, &save_atu_stmt, 0);

        if (rc != SQLITE_OK) {
            LV_LOG_ERROR("Prepare atu save");
        }

        rc = sqlite3_prepare_v2(db, "SELECT val FROM atu WHERE ant = ? AND freq = ?", -1, &load_atu_stmt, 0);

        if (rc != SQLITE_OK) {
            LV_LOG_ERROR("Prepare atu load");
        }

        rc = sqlite3_prepare_v2(db, 
            "SELECT id,name,start_freq,stop_freq,type FROM bands "
                "WHERE (stop_freq BETWEEN ? AND ?) OR (start_freq BETWEEN ? AND ?) OR (start_freq <= ? AND stop_freq >= ?) "
                "ORDER BY start_freq ASC", 
                -1, &bands_find_all_stmt, 0
        );

        if (rc != SQLITE_OK) {
            LV_LOG_ERROR("Prepare bands all find");
        }

        rc = sqlite3_prepare_v2(db,  "SELECT id,name,start_freq,stop_freq,type FROM bands WHERE (? BETWEEN start_freq AND stop_freq)", -1, &bands_find_stmt, 0);

        if (rc != SQLITE_OK) {
            LV_LOG_ERROR("Prepare bands find");
        }
        
        if (!transverter_load()) {
            LV_LOG_ERROR("Load transverter");
        }
    } else {
        LV_LOG_ERROR("Open params.db");
    }
    
    pthread_mutex_init(&params_mux, NULL);

    durty_time = 0;

    pthread_t thread;

    pthread_create(&thread, NULL, params_thread, NULL);
    pthread_detach(thread);
}

void params_lock() {
    pthread_mutex_lock(&params_mux);
}

void params_unlock(bool *durty) {
    if (durty != NULL) {
        *durty = true;
    }

    durty_time = get_time();
    pthread_mutex_unlock(&params_mux);
}

void params_band_freq_rx_set(uint64_t freq) {
    params_lock();

    params_band.freq_rx = freq;
    params_unlock(&params_band.durty.freq_rx);
}

void params_band_freq_fft_set(uint64_t freq) {
    params_lock();

    params_band.freq_fft = freq;
    params_unlock(&params_band.durty.freq_fft);
}

void params_atu_save(uint32_t val) {
    uint64_t freq = params_band.freq_rx;

    params_lock();

    sqlite3_bind_int(save_atu_stmt, 1, params.ant);
    sqlite3_bind_int(save_atu_stmt, 2, freq / 50000);
    sqlite3_bind_int(save_atu_stmt, 3, val);
    
    sqlite3_step(save_atu_stmt);
    sqlite3_reset(save_atu_stmt);
    sqlite3_clear_bindings(save_atu_stmt);
    
    params_unlock(NULL);
}

uint32_t params_atu_load(bool *loaded) {
    uint32_t    res = 0;
    uint64_t    freq = params_band.freq_rx;
    
    *loaded = false;

    params_lock();

    sqlite3_bind_int(load_atu_stmt, 1, params.ant);
    sqlite3_bind_int(load_atu_stmt, 2, freq / 50000);

    if (sqlite3_step(load_atu_stmt) != SQLITE_DONE) {
        res = sqlite3_column_int64(load_atu_stmt, 0);
        *loaded = true;
    }

    sqlite3_reset(load_atu_stmt);
    sqlite3_clear_bindings(load_atu_stmt);

    params_unlock(NULL);
    
    return res;
}

void params_msg_cw_load() {
    sqlite3_stmt    *stmt;
    int             rc;
    
    rc = sqlite3_prepare_v2(db, "SELECT id,val FROM msg_cw", -1, &stmt, 0);
    
    if (rc != SQLITE_OK) {
        return;
    }
    
    while (sqlite3_step(stmt) != SQLITE_DONE) {
        int         id = sqlite3_column_int(stmt, 0);
        const char  *val = sqlite3_column_text(stmt, 1);
        
        dialog_msg_cw_append(id, val);
    }
    
    sqlite3_finalize(stmt);
}

void params_msg_cw_new(const char *val) {
    sqlite3_stmt    *stmt;
    int             rc;
    
    rc = sqlite3_prepare_v2(db, "INSERT INTO msg_cw (val) VALUES(?)", -1, &stmt, 0);
    
    if (rc != SQLITE_OK) {
        return;
    }

    sqlite3_bind_text(stmt, 1, val, strlen(val), 0);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    dialog_msg_cw_append(sqlite3_last_insert_rowid(db), val);
}

void params_msg_cw_edit(uint32_t id, const char *val) {
    sqlite3_stmt    *stmt;
    int             rc;
    
    rc = sqlite3_prepare_v2(db, "UPDATE msg_cw SET val = ? WHERE id = ?", -1, &stmt, 0);
    
    if (rc != SQLITE_OK) {
        return;
    }

    sqlite3_bind_text(stmt, 1, val, strlen(val), 0);
    sqlite3_bind_int(stmt, 2, id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void params_msg_cw_delete(uint32_t id) {
    sqlite3_stmt    *stmt;
    int             rc;
    
    rc = sqlite3_prepare_v2(db, "DELETE FROM msg_cw WHERE id = ?", -1, &stmt, 0);
    
    if (rc != SQLITE_OK) {
        return;
    }

    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

band_t * params_bands_find_all(uint64_t freq, int32_t half_width, uint16_t *count) {
    uint64_t    left = freq - half_width;
    uint64_t    right = freq + half_width;
    band_t      *res = NULL;
    uint16_t    n = 0;

    sqlite3_bind_int64(bands_find_all_stmt, 1, left);
    sqlite3_bind_int64(bands_find_all_stmt, 2, right);
    sqlite3_bind_int64(bands_find_all_stmt, 3, left);
    sqlite3_bind_int64(bands_find_all_stmt, 4, right);
    sqlite3_bind_int64(bands_find_all_stmt, 5, left);
    sqlite3_bind_int64(bands_find_all_stmt, 6, right);
    
    while (sqlite3_step(bands_find_all_stmt) != SQLITE_DONE) {
        n++;
        res = realloc(res, sizeof(band_t) * n);
        
        band_t *current = &res[n - 1];

        current->id = sqlite3_column_int(bands_find_all_stmt, 0);
        current->name = strdup(sqlite3_column_text(bands_find_all_stmt, 1));
        current->start_freq = sqlite3_column_int64(bands_find_all_stmt, 2);
        current->stop_freq = sqlite3_column_int64(bands_find_all_stmt, 3);
        current->type = sqlite3_column_int(bands_find_all_stmt, 4);
    }

    sqlite3_reset(bands_find_all_stmt);
    sqlite3_clear_bindings(bands_find_all_stmt);
    
    *count = n;
    return res;
}

bool params_bands_find(uint64_t freq, band_t *band) {
    bool res = false;

    sqlite3_bind_int64(bands_find_stmt, 1, freq);

    if (sqlite3_step(bands_find_stmt) == SQLITE_ROW) {
        if (band->name)
            free(band->name);
    
        band->id = sqlite3_column_int(bands_find_stmt, 0);
        band->name = strdup(sqlite3_column_text(bands_find_stmt, 1));
        band->start_freq = sqlite3_column_int64(bands_find_stmt, 2);
        band->stop_freq = sqlite3_column_int64(bands_find_stmt, 3);
        band->type = sqlite3_column_int(bands_find_stmt, 4);
        
        res = true;
    }

    sqlite3_reset(bands_find_stmt);
    sqlite3_clear_bindings(bands_find_stmt);
    
    return res;
}

bool params_bands_find_next(uint64_t freq, bool up, band_t *band) {
    bool            res = false;
    sqlite3_stmt    *stmt;
    int             rc;
    
    if (up) {
        rc = sqlite3_prepare_v2(db, "SELECT id,name,start_freq,stop_freq,type FROM bands WHERE (? < start_freq AND type != 0) ORDER BY start_freq ASC", -1, &stmt, 0);
    } else {
        rc = sqlite3_prepare_v2(db, "SELECT id,name,start_freq,stop_freq,type FROM bands WHERE (? > stop_freq AND type != 0) ORDER BY start_freq DESC", -1, &stmt, 0);
    }
    
    if (rc != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_int64(stmt, 1, freq);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        if (band->name)
            free(band->name);
    
        band->id = sqlite3_column_int(stmt, 0);
        band->name = strdup(sqlite3_column_text(stmt, 1));
        band->start_freq = sqlite3_column_int64(stmt, 2);
        band->stop_freq = sqlite3_column_int64(stmt, 3);
        band->type = sqlite3_column_int(stmt, 4);

        res = true;
    }

    sqlite3_finalize(stmt);

    return res;
}

void params_bool_set(params_bool_t *var, bool x) {
    params_lock();
    var->x = x;
    params_unlock(&var->durty);
    
    if (var->voice) {
        voice_say_bool(var->voice, var->x);
    }
}

void params_uint8_set(params_uint8_t *var, uint8_t x) {
    params_lock();
    var->x = x;
    params_unlock(&var->durty);
    
    if (var->voice) {
        voice_say_int(var->voice, var->x);
    }
}

void params_uint16_set(params_uint16_t *var, uint16_t x) {
    params_lock();
    var->x = x;
    params_unlock(&var->durty);
    
    if (var->voice) {
        voice_say_int(var->voice, var->x);
    }
}

void params_int32_set(params_int32_t *var, int32_t x) {
    params_lock();
    var->x = x;
    params_unlock(&var->durty);
    
    if (var->voice) {
        voice_say_int(var->voice, var->x);
    }
}

void params_uint64_set(params_uint64_t *var, uint64_t x) {
    params_lock();
    var->x = x;
    params_unlock(&var->durty);
    
    if (var->voice) {
        voice_say_freq(var->x);
    }
}

void params_str_set(params_str_t *var, const char *x) {
    params_lock();
    strncpy(var->x, x, sizeof(var->x) - 1);
    params_unlock(&var->durty);
}

uint8_t params_uint8_change(params_uint8_t *var, int16_t df) {
    if (df == 0) {
        return var->x;
    }
    
    int32_t x = var->x + df;
    
    if (x > var->max) x = var->max;
    if (x < var->min) x = var->min;
    
    params_uint8_set(var, x);
    
    return var->x;
}
