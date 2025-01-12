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

#include "lvgl/lvgl.h"
#include "params.h"
#include "util.h"
#include "bands.h"
#include "mfk.h"
#include "vol.h"
#include "dialog_msg_cw.h"
#include "voice.h"
#include "dsp/agc.h"
#include "msgs.h"

#define PARAMS_SAVE_TIMEOUT  (3 * 1000)

params_t params = {
    .brightness_normal      = 9,
    .brightness_idle        = 1,
    .brightness_timeout     = 10,
    .brightness_buttons     = BUTTONS_TEMPORARILY,

    .mag_freq               = { .x = true,  .name = "mag_freq",             .voice = "Magnification of frequency" },
    .mag_info               = { .x = true,  .name = "mag_info",             .voice = "Magnification of info" },
    .mag_alc                = { .x = true,  .name = "mag_alc",              .voice = "Magnification of A L C" },
    .clock_view             = CLOCK_TIME_POWER,
    .clock_time_timeout     = 5,
    .clock_power_timeout    = 3,
    .clock_tx_timeout       = 1,

    .ant                    = 1,
    .pwr                    = 5.0f,
    .moni                   = 59,
    .freq_accel             = { .x = FREQ_ACCEL_NONE,   .name = "freq_accel",       .voice = "Frequency acceleration" },
    .freq_mode              = { .x = FREQ_MODE_SLIDE,   .name = "freq_mode",        .voice = "Frequency mode", .min = FREQ_MODE_JOIN, .max = FREQ_MODE_FFT_ONLY },
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

    .cw_encoder_period      = 10,
    .voice_msg_period       = 10,

    .swrscan_linear         = true,
    .swrscan_span           = 200000,

    /*
    .press_f1               = ACTION_STEP_UP,
    .press_f2               = ACTION_NONE,
    .long_f1                = ACTION_STEP_DOWN,
    .long_f2                = ACTION_NONE,
    */

    .rec_format             = REC_FORMAT_WAV,

    .voice_mode             = { .x = VOICE_LCD,                                 .name = "voice_mode" },
    .voice_lang             = { .x = 0,   .min = 0,  .max = (VOICES_NUM - 1),   .name = "voice_lang" },
    .voice_rate             = { .x = 100, .min = 50, .max = 150,                .name = "voice_rate",     .voice = "Voice rate" },
    .voice_pitch            = { .x = 100, .min = 50, .max = 150,                .name = "voice_pitch",    .voice = "Voice pitch" },
    .voice_volume           = { .x = 100, .min = 50, .max = 150,                .name = "voice_volume",   .voice = "Voice volume" }
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

static bool params_exec(const char *sql);
static bool params_mb_save(uint16_t id);

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

        if (strcmp(name, "sql") == 0) {
            params.sql = i;
        } else if (strcmp(name, "atu") == 0) {
            params.atu = i;
        } else if (strcmp(name, "pwr") == 0) {
            params.pwr = i * 0.1f;
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
        } else if (strcmp(name, "cw_encoder_period") == 0) {
            params.cw_encoder_period = i;
        } else if (strcmp(name, "voice_msg_period") == 0) {
            params.voice_msg_period = i;
        } else if (strcmp(name, "ant") == 0) {
            params.ant = i;
        } else if (strcmp(name, "brightness_normal") == 0) {
            params.brightness_normal = i;
        } else if (strcmp(name, "brightness_idle") == 0) {
            params.brightness_idle = i;
        } else if (strcmp(name, "brightness_timeout") == 0) {
            params.brightness_timeout = i;
        } else if (strcmp(name, "brightness_buttons") == 0) {
            params.brightness_buttons = i;
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
        } else if (strcmp(name, "press_f1") == 0) {
            params.press_f1 = i;
        } else if (strcmp(name, "press_f2") == 0) {
            params.press_f2 = i;
        } else if (strcmp(name, "long_f1") == 0) {
            params.long_f1 = i;
        } else if (strcmp(name, "long_f2") == 0) {
            params.long_f2 = i;
        } 
        
        if (params_load_bool(&params.mag_freq, name, i)) continue;
        if (params_load_bool(&params.mag_info, name, i)) continue;
        if (params_load_bool(&params.mag_alc, name, i)) continue;

        if (params_load_uint8(&params.voice_mode, name, i)) continue;
        if (params_load_uint8(&params.voice_lang, name, i)) continue;
        if (params_load_uint8(&params.voice_rate, name, i)) continue;
        if (params_load_uint8(&params.voice_pitch, name, i)) continue;
        if (params_load_uint8(&params.voice_volume, name, i)) continue;
        if (params_load_uint8(&params.freq_accel, name, i)) continue;
        if (params_load_uint8(&params.freq_mode, name, i)) continue;
        if (params_load_int32(&params.txo_offset, name, i)) continue;
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

    if (params.durty.sql)                   params_write_int("sql", params.sql, &params.durty.sql);
    if (params.durty.atu)                   params_write_int("atu", params.atu, &params.durty.atu);
    if (params.durty.pwr)                   params_write_int("pwr", params.pwr * 10, &params.durty.pwr);

    if (params.durty.key_speed)             params_write_int("key_speed", params.key_speed, &params.durty.key_speed);
    if (params.durty.key_mode)              params_write_int("key_mode", params.key_mode, &params.durty.key_mode);
    if (params.durty.iambic_mode)           params_write_int("iambic_mode", params.iambic_mode, &params.durty.iambic_mode);
    if (params.durty.key_tone)              params_write_int("key_tone", params.key_tone, &params.durty.key_tone);
    if (params.durty.key_vol)               params_write_int("key_vol", params.key_vol, &params.durty.key_vol);
    if (params.durty.key_train)             params_write_int("key_train", params.key_train, &params.durty.key_train);
    if (params.durty.qsk_time)              params_write_int("qsk_time", params.qsk_time, &params.durty.qsk_time);
    if (params.durty.key_ratio)             params_write_int("key_ratio", params.key_ratio, &params.durty.key_ratio);

    if (params.durty.dnf)                   params_write_int("dnf", params.dnf, &params.durty.dnf);
    if (params.durty.dnf_center)            params_write_int("dnf_center", params.dnf_center, &params.durty.dnf_center);
    if (params.durty.dnf_width)             params_write_int("dnf_width", params.dnf_width, &params.durty.dnf_width);
    if (params.durty.nb)                    params_write_int("nb", params.nb, &params.durty.nb);
    if (params.durty.nb_level)              params_write_int("nb_level", params.nb_level, &params.durty.nb_level);
    if (params.durty.nb_width)              params_write_int("nb_width", params.nb_width, &params.durty.nb_width);
    if (params.durty.nr)                    params_write_int("nr", params.nr, &params.durty.nr);
    if (params.durty.nr_level)              params_write_int("nr_level", params.nr_level, &params.durty.nr_level);

    if (params.durty.cw_encoder_period)     params_write_int("cw_encoder_period", params.cw_encoder_period, &params.durty.cw_encoder_period);
    if (params.durty.voice_msg_period)      params_write_int("voice_msg_period", params.voice_msg_period, &params.durty.voice_msg_period);

    if (params.durty.ant)                   params_write_int("ant", params.ant, &params.durty.ant);

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

    if (params.durty.press_f1)              params_write_int("press_f1", params.press_f1, &params.durty.press_f1);
    if (params.durty.press_f2)              params_write_int("press_f2", params.press_f2, &params.durty.press_f2);
    if (params.durty.long_f1)               params_write_int("long_f1", params.long_f1, &params.durty.long_f1);
    if (params.durty.long_f2)               params_write_int("long_f2", params.long_f2, &params.durty.long_f2);

    params_save_uint8(&params.voice_mode);
    params_save_uint8(&params.voice_lang);
    params_save_uint8(&params.voice_rate);
    params_save_uint8(&params.voice_pitch);
    params_save_uint8(&params.voice_volume);
    params_save_uint8(&params.freq_accel);
    params_save_uint8(&params.freq_mode);
    params_save_int32(&params.txo_offset);

    params_save_bool(&params.mag_freq);
    params_save_bool(&params.mag_info);
    params_save_bool(&params.mag_alc);

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
