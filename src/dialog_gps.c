/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include "lvgl/lvgl.h"
#include "gps.h"
#include "dialog.h"
#include "dialog_gps.h"
#include "styles.h"
#include "events.h"
#include "dsp.h"
#include "keyboard.h"
#include "qth.h"

#define HEIGHT 42

static void construct_cb(lv_obj_t *parent);
static void destruct_cb();

typedef enum { 
    deg_dd, 
    deg_ddmm,
    deg_ddmmss 
} deg_str_type;

static deg_str_type         deg_type = deg_ddmm;

static lv_obj_t             *fix;
static lv_obj_t             *date;
static lv_obj_t             *lat;
static lv_obj_t             *lon;
static lv_obj_t             *qth;

static dialog_t             dialog = {
    .run = false,
    .construct_cb = construct_cb,
    .destruct_cb = destruct_cb,
    .audio_cb = NULL,
    .buttons = true,
    .key_cb = dialog_key_cb
};

dialog_t                    *dialog_gps = &dialog;

char *deg_to_str2(deg_str_type type, double f, char *buf, unsigned int buf_size, const char *suffix_pos, const char *suffix_neg) {
    int dsec, sec, deg, min;
    double fdsec, fsec, fdeg, fmin;
    const char *suffix = "";

    if (20 > buf_size) {
        strncpy(buf, "Err", buf_size);
        return buf;
    }

    if (!isfinite(f) || 360.0 < fabs(f)) {
        strncpy(buf, "N/A", buf_size);
        return buf;
    }

    /* suffix? */
    if (0.0 > f) {
        f = -f;
        if (NULL != suffix_neg) {
            suffix = suffix_neg;
        }
    } else if (NULL != suffix_pos) {
        suffix = suffix_pos;
    }

    /* add rounding quanta */
    /* IEEE 754 wants round to nearest even.
     * We cheat and just round to nearest.
     * Intel trying to kill off round to nearest even. */
    switch (type) {
        default:
            /* huh? */
            type = deg_dd;
            /* It's not worth battling fallthrough warnings just for two lines */
            f += 0.5 * 1e-8;              /* round up */
            break;
            
        case deg_dd:
            /* DD.dddddddd */
            f += 0.5 * 1e-8;              /* round up */
            break;
            
        case deg_ddmm:
            /* DD MM.mmmmmm */
            f += (0.5 * 1e-6) / 60;       /* round up */
            break;
            
        case deg_ddmmss:
            f += (0.5 * 1e-5) / 3600;     /* round up */
            break;
    }
    
    fmin = modf(f, &fdeg);
    deg = (int)fdeg;
    
    if (360 == deg) {
        /* fix round-up roll-over */
        deg = 0;
        fmin = 0.0;
    }

    if (deg_dd == type) {
        /* DD.dddddddd */
        long frac_deg = (long)(fmin * 100000000.0);
        /* cm level accuracy requires the %08ld */
        snprintf(buf, buf_size, "%d.%08ld%s", deg, frac_deg, suffix);
        return buf;
    }

    fsec = modf(fmin * 60, &fmin);
    min = (int)fmin;

    if (deg_ddmm == type) {
        /* DD MM.mmmmmm */
        sec = (int)(fsec * 1000000.0);
        snprintf(buf, buf_size, "%d %s %02d.%06d'", deg, suffix, min, sec);
        return buf;
    }
    
    /* else DD MM SS.sss */
    fdsec = modf(fsec * 60.0, &fsec);
    sec = (int)fsec;
    dsec = (int)(fdsec * 100000.0);
    snprintf(buf, buf_size, "%d %s %02d' %02d.%05d\"", deg, suffix, min, sec, dsec);

    return buf;
}

static void gps_cb(lv_event_t * e) {
    struct gps_data_t   *msg = lv_event_get_param(e);
    char                str[64];

    switch (msg->fix.mode) {
        case MODE_3D:
            lv_label_set_text(fix, "3D");
            break;
            
        case MODE_2D:
            lv_label_set_text(fix, "2D");
            break;
            
        case MODE_NO_FIX:
            lv_label_set_text(fix, "None");
            break;
            
        default:
            break;
    }

    timespec_to_iso8601(msg->fix.time, str, sizeof(str));
    lv_label_set_text(date, str);

    if (msg->fix.mode >= MODE_2D) {
        deg_to_str2(deg_type, msg->fix.latitude, str, sizeof(str), "N", "S");
        lv_label_set_text(lat, str);
    } else {
        lv_label_set_text(lat, "N/A");
    }

    if (msg->fix.mode >= MODE_2D) {
        deg_to_str2(deg_type, msg->fix.longitude, str, sizeof(str), "E", "W");
        lv_label_set_text(lon, str);
    } else {
        lv_label_set_text(lon, "N/A");
    }
    
    if (msg->fix.mode >= MODE_2D) {
        lv_label_set_text(qth, pos_grid(msg->fix.latitude, msg->fix.longitude));
    } else {
        lv_label_set_text(qth, "N/A");
    }
}

static void construct_cb(lv_obj_t *parent) {
    lv_obj_t    *label;
    lv_coord_t  y = 32;

    dialog_init(parent, &dialog);

    lv_group_add_obj(keyboard_group, dialog.obj);
    lv_obj_add_event_cb(dialog.obj, dialog_key_cb, LV_EVENT_KEY, NULL);
    lv_obj_add_event_cb(dialog.obj, gps_cb, EVENT_GPS, NULL);
    
    /* Fix */
    
    label = lv_label_create(dialog.obj);
    
    lv_label_set_text(label, "Fix:");
    lv_obj_set_size(label, 200, HEIGHT);
    lv_obj_set_pos(label, 30, y);

    fix = lv_label_create(dialog.obj);
    
    lv_label_set_text(fix, "N/A");
    lv_obj_set_size(fix, 450, HEIGHT);
    lv_obj_set_pos(fix, 250, y);

    y += HEIGHT;

    /* Date, time */
    
    label = lv_label_create(dialog.obj);
    
    lv_label_set_text(label, "Date, time:");
    lv_obj_set_size(label, 200, HEIGHT);
    lv_obj_set_pos(label, 30, y);

    date = lv_label_create(dialog.obj);
    
    lv_label_set_text(date, "N/A");
    lv_obj_set_size(date, 450, HEIGHT);
    lv_obj_set_pos(date, 250, y);

    y += HEIGHT;

    /* Lat */
    
    label = lv_label_create(dialog.obj);
    
    lv_label_set_text(label, "Latitude:");
    lv_obj_set_size(label, 200, HEIGHT);
    lv_obj_set_pos(label, 30, y);

    lat = lv_label_create(dialog.obj);
    
    lv_label_set_text(lat, "N/A");
    lv_obj_set_size(lat, 450, HEIGHT);
    lv_obj_set_pos(lat, 250, y);

    y += HEIGHT;

    /* Lon */
    
    label = lv_label_create(dialog.obj);
    
    lv_label_set_text(label, "Longitude:");
    lv_obj_set_size(label, 200, HEIGHT);
    lv_obj_set_pos(label, 30, y);

    lon = lv_label_create(dialog.obj);
    
    lv_label_set_text(lon, "N/A");
    lv_obj_set_size(lon, 450, HEIGHT);
    lv_obj_set_pos(lon, 250, y);

    y += HEIGHT;

    /* QTH Grid */
    
    label = lv_label_create(dialog.obj);
    
    lv_label_set_text(label, "QTH Grid:");
    lv_obj_set_size(label, 200, HEIGHT);
    lv_obj_set_pos(label, 30, y);

    qth = lv_label_create(dialog.obj);
    
    lv_label_set_text(qth, "N/A");
    lv_obj_set_size(qth, 450, HEIGHT);
    lv_obj_set_pos(qth, 250, y);

    y += HEIGHT;
}

static void destruct_cb() {
}
