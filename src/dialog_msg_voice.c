/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sndfile.h>
#include <dirent.h>
#include <pthread.h>

#include "lvgl/lvgl.h"
#include "main.h"
#include "audio.h"
#include "dialog_msg_voice.h"
#include "styles.h"
#include "settings/options.h"
#include "util.h"
#include "keyboard.h"
#include "textarea_window.h"
#include "msg.h"
#include "msgs.h"
#include "meter.h"
#include "buttons.h"
#include "dsp.h"
#include "fpga/dac.h"

#define DECIM       441
#define INTER       128

#define BUF_SIZE    1024

typedef enum {
    VOICE_BEACON_OFF = 0,
    VOICE_BEACON_PLAY,
    VOICE_BEACON_IDLE,
} voice_beacon_t;

static msg_voice_state_t    state = MSG_VOICE_OFF;
static voice_beacon_t       beacon = VOICE_BEACON_OFF;
static lv_timer_t           *beacon_timer = NULL;
static char                 *path = "/mnt/msg";

static lv_obj_t             *table;
static int16_t              table_rows = 0;
static SNDFILE              *file = NULL;

static char                 *prev_filename;
static pthread_t            thread;
static int16_t              samples_buf[BUF_SIZE];

static uint8_t              buttons_page = 0;

/* For send */

static cbufferf             out_buf;
static rresamp_rrrf         resamp;
static float                resamp_buf[INTER];
static pthread_mutex_t      mux;
static pthread_cond_t       cond;

static void construct_cb(lv_obj_t *parent);
static void destruct_cb();
static void key_cb(lv_event_t * e);
static bool keypad_cb(event_keypad_t *keypad);
static bool modulate_state_cb();
static size_t modulate_cb(float complex *data, size_t max_size, radio_mode_t mode);

static void send_cb(lv_event_t * e);
static void beacon_cb(lv_event_t * e);
static void rec_cb(lv_event_t * e);
static void play_cb(lv_event_t * e);
static void rename_cb(lv_event_t * e);
static void delete_cb(lv_event_t * e);
static void beacon_period_cb(lv_event_t * e);

static void send_stop_cb(lv_event_t * e);
static void beacon_stop_cb(lv_event_t * e);
static void rec_stop_cb(lv_event_t * e);
static void play_stop_cb(lv_event_t * e);

static bool send_file();

static button_item_t button_send            = { .label = "Send",            .press = send_cb };
static button_item_t button_becon           = { .label = "Beacon",          .press = beacon_cb };
static button_item_t button_rec             = { .label = "Rec",             .press = rec_cb };
static button_item_t button_play            = { .label = "Play",            .press = play_cb };
static button_item_t button_rename          = { .label = "Rename",          .press = rename_cb };
static button_item_t button_delete          = { .label = "Delete",          .press = delete_cb };

static button_item_t button_becon_period    = { .label = "Beacon\nPeriod",  .press = beacon_period_cb };

static button_item_t button_send_stop       = { .label = "Send\nStop",      .press = send_stop_cb };
static button_item_t button_beacon_stop     = { .label = "Beacon\nStop",    .press = beacon_stop_cb };
static button_item_t button_rec_stop        = { .label = "Rec\nStop",       .press = rec_stop_cb };
static button_item_t button_play_stop       = { .label = "Play\nStop",      .press = play_stop_cb };

static dialog_t             dialog = {
    .run = false,
    .construct_cb = construct_cb,
    .destruct_cb = destruct_cb,
    .keypad_cb = keypad_cb,
    .modulate_state_cb = modulate_state_cb,
    .modulate_cb = modulate_cb,
    .audio_cb = NULL,
    .buttons = true,
    .key_cb = NULL
};

dialog_t *dialog_msg_voice = &dialog;

static void load_page(uint8_t i) {
    switch (i) {
        case 0:
            buttons_load(0, &button_send);
            buttons_load(1, &button_becon);
            buttons_load(2, &button_rec);
            buttons_load(3, &button_play);
            buttons_load(4, &button_rename);
            buttons_load(5, &button_delete);
            break;

        default:
            buttons_load(0, &button_becon_period);
            break;
    }

    buttons_page = i;
}

static void load_table() {
    lv_table_set_row_cnt(table, 1);
    lv_table_set_cell_value(table, 0, 0, "");

    table_rows = 0;

    DIR             *dp;
    struct dirent   *ep;

    dp = opendir(path);

    if (dp != NULL) {
        while ((ep = readdir(dp)) != NULL) {
            if (strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0) {
                continue;
            }

            lv_table_set_cell_value(table, table_rows++, 0, ep->d_name);
        }

        closedir(dp);
    }
}

static const char* get_item() {
    if (table_rows == 0) {
        return NULL;
    }

    int16_t     row = 0;
    int16_t     col = 0;

    lv_table_get_selected_cell(table, &row, &col);

    if (row == LV_TABLE_CELL_NONE) {
        return NULL;
    }

    return lv_table_get_cell_value(table, row, col);
}

static bool create_file() {
    SF_INFO sfinfo;

    memset(&sfinfo, 0, sizeof(sfinfo));

    sfinfo.samplerate = AUDIO_CAPTURE_RATE;
    sfinfo.channels = 1;
    sfinfo.format = SF_FORMAT_MPEG | SF_FORMAT_MPEG_LAYER_III;

    char        filename[64];
    time_t      now = time(NULL);
    struct tm   *t = localtime(&now);

    snprintf(filename, sizeof(filename),
        "%s/MSG_%04i%02i%02i_%02i%02i%02i.mp3", 
        path, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec
    );

    file = sf_open(filename, SFM_WRITE, &sfinfo);

    if (file == NULL) {
        LV_LOG_ERROR("Problem with create file - %s", sf_strerror(NULL));
        return false;
    }

    return true;
}

static void open_file() {
    const char *item = get_item();

    if (!item) {
        return;
    }

    char filename[64];

    strcpy(filename, path);
    strcat(filename, "/");
    strcat(filename, item);

    SF_INFO sfinfo;

    memset(&sfinfo, 0, sizeof(sfinfo));

    file = sf_open(filename, SFM_READ, &sfinfo);
}

static void close_file() {
    sf_close(file);
}

static void * play_thread(void *arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    open_file();

    if (file == NULL) {
        return NULL;
    }

    dsp_set_mute(true);
    state = MSG_VOICE_PLAY;

    while (state == MSG_VOICE_PLAY) {
        int res = sf_read_short(file, samples_buf, BUF_SIZE);

        if (res > 0) {
            audio_play(samples_buf, res);
        } else {
            state = MSG_VOICE_OFF;
        }
    }

    close_file();
    audio_play_wait();
    dsp_set_mute(false);

    if (dialog.run) {
        buttons_unload_page();
        load_page(0);
    }

    return NULL;
}

static void beacon_timer_cb(lv_timer_t *t) {
    beacon_timer = NULL;
    beacon = VOICE_BEACON_PLAY;
    send_file();
}

static void * send_thread(void *arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    dsp_set_mute(true);
    radio_set_ptt(true);
    cbufferf_reset(out_buf);

    state = MSG_VOICE_SEND;

    float *buf = (float *) malloc(sizeof(float) * DECIM);

    while (true) {
        while (cbufferf_space_available(out_buf) > INTER) {
            int res = sf_read_float(file, buf, DECIM);

            if (res < DECIM) {
                state = MSG_VOICE_OFF;
                break;
            } else {
                rresamp_rrrf_execute(resamp, buf, resamp_buf);
                cbufferf_write(out_buf, resamp_buf, INTER);
            }
        }

        if (state == MSG_VOICE_SEND) {
            pthread_mutex_lock(&mux);
            pthread_cond_wait(&cond, &mux);
            pthread_mutex_unlock(&mux);
        } else {
            break;
        }
    }

    free(buf);
    close_file();

    if (!dialog.run) {
        radio_set_ptt(false);
        dsp_set_mute(false);
        return NULL;
    }

    if (state == MSG_VOICE_SEND_CANCEL) {
        state = MSG_VOICE_OFF;
    } else {
        radio_set_ptt(false);
        dsp_set_mute(false);
    }

    if (beacon == VOICE_BEACON_PLAY) {
        beacon = VOICE_BEACON_IDLE;

        beacon_timer = lv_timer_create(beacon_timer_cb, options->msg.voice_period * 1000, NULL);
        lv_timer_set_repeat_count(beacon_timer, 1);
        msg_set_text_fmt("Beacon pause: %i s", options->msg.voice_period);
    } else {
        lv_lock();
        buttons_unload_page();
        load_page(0);
        lv_unlock();
    }
}

static bool send_file() {
    open_file();

    if (file == NULL) {
        msg_set_text_fmt("File problem");
        return false;
    }

    msg_set_text_fmt("Sending message");
    pthread_create(&thread, NULL, send_thread, NULL);

    return true;
}

static void textarea_window_close_cb() {
    lv_group_add_obj(keyboard_group, table);
    lv_group_set_editing(keyboard_group, true);

    free(prev_filename);
    prev_filename = NULL;
}

static void textarea_window_edit_ok_cb() {
    const char *new_filename = textarea_window_get();

    if (strcmp(prev_filename, new_filename) != 0) {
        char prev[64];
        char new[64];

        snprintf(prev, sizeof(prev), "%s/%s", path, prev_filename);
        snprintf(new, sizeof(new), "%s/%s", path, new_filename);

        if (rename(prev, new) == 0) {
            load_table();
            textarea_window_close_cb();
        }
    } else {
        free(prev_filename);
        prev_filename = NULL;
    }
}

static void msg_cb(lv_event_t * e) {
    lv_msg_t *m = lv_event_get_msg(e);

    switch (lv_msg_get_id(m)) {
        case MSG_PTT: {
            const int *on = lv_msg_get_payload(m);

            if (*on) {
                if (beacon == VOICE_BEACON_IDLE) {
                    if (beacon_timer) {
                        lv_timer_del(beacon_timer);
                        beacon_timer = NULL;
                    }
                    buttons_unload_page();
                    load_page(0);
                }

                beacon = VOICE_BEACON_OFF;

                if (state == MSG_VOICE_SEND) {
                    state = MSG_VOICE_SEND_CANCEL;

                    pthread_mutex_lock(&mux);
                    pthread_cond_signal(&cond);
                    pthread_mutex_unlock(&mux);
                }
            } else {
                dsp_set_mute(false);
            }
        } break;

        default:
            break;
    }
}

static void construct_cb(lv_obj_t *parent) {
    dialog_init(parent, &dialog);

    table = lv_table_create(dialog.obj);

    lv_obj_remove_style(table, NULL, LV_STATE_ANY | LV_PART_MAIN);

    lv_obj_set_size(table, 775, 325);

    lv_table_set_col_cnt(table, 1);
    lv_table_set_col_width(table, 0, 770);

    lv_obj_set_style_border_width(table, 0, LV_PART_ITEMS);

    lv_obj_set_style_bg_opa(table, LV_OPA_TRANSP, LV_PART_ITEMS);
    lv_obj_set_style_text_color(table, lv_color_white(), LV_PART_ITEMS);
    lv_obj_set_style_pad_top(table, 5, LV_PART_ITEMS);
    lv_obj_set_style_pad_bottom(table, 5, LV_PART_ITEMS);
    lv_obj_set_style_pad_left(table, 0, LV_PART_ITEMS);
    lv_obj_set_style_pad_right(table, 0, LV_PART_ITEMS);

    lv_obj_set_style_text_color(table, lv_color_black(), LV_PART_ITEMS | LV_STATE_EDITED);
    lv_obj_set_style_bg_color(table, lv_color_white(), LV_PART_ITEMS | LV_STATE_EDITED);
    lv_obj_set_style_bg_opa(table, 128, LV_PART_ITEMS | LV_STATE_EDITED);

    lv_obj_add_event_cb(table, msg_cb, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(MSG_PTT, table, NULL);

    lv_obj_add_event_cb(table, key_cb, LV_EVENT_KEY, NULL);
    lv_group_add_obj(keyboard_group, table);
    lv_group_set_editing(keyboard_group, true);

    lv_obj_center(table);

    /* * */

    pthread_mutex_init(&mux, NULL);
    pthread_cond_init(&cond, NULL);

    resamp = rresamp_rrrf_create_default(INTER, DECIM);     /* DAC_RATE <- AUDIO_CAPTURE_RATE */
    out_buf = cbufferf_create(DAC_RATE / 4);

    mkdir(path, 0755);
    load_table();
    load_page(0);
}

static void destruct_cb() {
    if (beacon != VOICE_BEACON_OFF) {
        beacon_stop_cb(NULL);
    }

    if (state != MSG_VOICE_OFF) {
        send_stop_cb(NULL);
    }

    textarea_window_close();
    rresamp_rrrf_destroy(resamp);
    cbufferf_destroy(out_buf);
}

static void key_cb(lv_event_t * e) {
    uint32_t key = *((uint32_t *)lv_event_get_param(e));

    switch (key) {
        case LV_KEY_ESC:
            dialog_destruct();
            break;

        case KEY_VOL_LEFT_EDIT:
        case KEY_VOL_LEFT_SELECT:
            dsp_change_vol(-1);
            break;

        case KEY_VOL_RIGHT_EDIT:
        case KEY_VOL_RIGHT_SELECT:
            dsp_change_vol(1);
            break;
    }
}

static bool keypad_cb(event_keypad_t *keypad) {
    switch (keypad->key) {
        case KEYPAD_VOL:
        case KEYPAD_MFK:
            return true;

        case KEYPAD_APP:
            if (keypad->state == KEYPAD_RELEASE) {
                buttons_unload_page();

                switch (buttons_page) {
                    case 0:
                        load_page(1);
                        break;

                    case 1:
                        load_page(0);
                        break;
                }

                return true;
            }
            break;

        default:
            break;
    }

    return false;
}

static bool modulate_state_cb() {
    return state == MSG_VOICE_SEND;
}

static size_t modulate_cb(float complex *data, size_t max_size, radio_mode_t mode) {
    size_t size = 0;

    if (cbufferf_size(out_buf) > 0) {
        uint32_t n;
        float *buf;

        cbufferf_read(out_buf, max_size, &buf, &n);

        for (uint32_t i = 0; i < n; i++) {
            data[i] = dsp_modulate(buf[i], mode);
        }

        cbufferf_release(out_buf, n);
        size = n;
    }

    pthread_mutex_lock(&mux);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mux);

    return size;
}

static void send_cb(lv_event_t * e) {
    if (state == MSG_VOICE_OFF) {
        if (send_file()) {
            buttons_unload_page();
            buttons_load(0, &button_send_stop);
        }
    }
}

static void send_stop_cb(lv_event_t * e) {
    state = MSG_VOICE_OFF;

    pthread_mutex_lock(&mux);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mux);
}

static void beacon_cb(lv_event_t * e) {
    beacon = VOICE_BEACON_PLAY;

    if (send_file()) {
        buttons_unload_page();
        buttons_load(1, &button_beacon_stop);
    }
}

static void beacon_stop_cb(lv_event_t * e) {
    switch (beacon) {
        case VOICE_BEACON_PLAY:
            state = MSG_VOICE_OFF;

            pthread_mutex_lock(&mux);
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mux);
            break;

        case VOICE_BEACON_IDLE:
            lv_timer_del(beacon_timer);
            beacon_timer = NULL;
            buttons_unload_page();
            load_page(0);
            break;
    }

    beacon = VOICE_BEACON_OFF;
}

static void beacon_period_cb(lv_event_t * e) {
    uint16_t period = options->msg.voice_period;

    switch (period) {
        case 10:
            period = 30;
            break;

        case 30:
            period = 60;
            break;

        case 60:
            period = 120;
            break;

        case 120:
            period = 10;
            break;

        default:
            period = 10;
            break;
    }

    options->msg.voice_period = period;
    msg_set_text_fmt("Beacon period: %i s", period);
}

static void rec_cb(lv_event_t * e) {
    if (state == MSG_VOICE_OFF) {
        if (create_file()) {
            dsp_set_mute(true);
            state = MSG_VOICE_RECORD;

            buttons_unload_page();
            buttons_load(2, &button_rec_stop);
        }
    }
}

static void rec_stop_cb(lv_event_t * e) {
    buttons_unload_page();
    load_page(0);

    state = MSG_VOICE_OFF;
    dsp_set_mute(false);
    close_file();
    load_table();
}

static void play_cb(lv_event_t * e) {
    if (state == MSG_VOICE_OFF) {
        pthread_create(&thread, NULL, play_thread, NULL);

        buttons_unload_page();
        buttons_load(3, &button_play_stop);
    }
}

static void play_stop_cb(lv_event_t * e) {
    state = MSG_VOICE_OFF;
}

static void rename_cb(lv_event_t * e) {
    prev_filename = strdup(get_item());

    if (prev_filename) {
        lv_group_remove_obj(table);
        textarea_window_open(textarea_window_edit_ok_cb, textarea_window_close_cb);
        textarea_window_set(prev_filename);
    }
}

static void delete_cb(lv_event_t * e) {
    const char *item = get_item();

    if (item) {
        char filename[64];

        strcpy(filename, path);
        strcat(filename, "/");
        strcat(filename, item);

        unlink(filename);
        load_table();
    }
}

msg_voice_state_t dialog_msg_voice_get_state() {
    return state;
}

void dialog_msg_voice_put_audio_samples(float *samples, size_t nsamples) {
    float peak = 0;

    for (uint16_t i = 0; i < nsamples; i++) {
        float x = fabs(samples[i]);

        if (x > peak) {
            peak = x;
        }
    }

    peak = S1 + peak * (S9_40 - S1);
    meter_update(peak, 0.25f);
    sf_write_float(file, samples, nsamples);
}
