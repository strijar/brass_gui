/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include <time.h>
#include <sys/time.h>
#include <sndfile.h>

#include "audio.h"
#include "dialog_recorder.h"
#include "recorder.h"
#include "msg.h"
#include "params.h"
#include "fpga/adc.h"

#define BUFS    32

char            *recorder_path = "/mnt/rec";

static bool     on = false;
static SNDFILE  *file = NULL;

typedef int16_t buf_t[ADC_SAMPLES];

static buf_t    buf[BUFS];
static int16_t  buf_index = 0;

static bool create_file() {
    SF_INFO sfinfo;

    memset(&sfinfo, 0, sizeof(sfinfo));

    sfinfo.samplerate = ADC_RATE;
    sfinfo.channels = 1;
    #if 1
    sfinfo.format = SF_FORMAT_MPEG | SF_FORMAT_MPEG_LAYER_III;
    #else
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    #endif
    
    char        filename[64];
    time_t      now = time(NULL);
    struct tm   *t = localtime(&now);

    snprintf(filename, sizeof(filename),
        "%s/REC_%04i%02i%02i_%02i%02i%02i.mp3", 
        recorder_path, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec
    );
    
    file = sf_open(filename, SFM_WRITE, &sfinfo);
    
    if (file == NULL) {
        return false;
    }

    buf_index = 0;

    double q = 0.25;
    sf_command(file, SFC_SET_VBR_ENCODING_QUALITY, &q, sizeof(q));

    return true;
}

void recorder_set_on(bool x) {
    if (x) {
        if (!create_file()) {
            msg_set_text_fmt("Problem with create file");
            return;
        } else {
            msg_set_text_fmt("Recorder is on");
        }
        on = true;
    } else {
        msg_set_text_fmt("Recorder is off");
        on = false;
        sf_close(file);
    }

    dialog_recorder_set_on(on);
}

bool recorder_is_on() {
    return on;
}

void recorder_put_audio_samples(int16_t *samples) {
    memcpy(buf[buf_index], samples, ADC_SAMPLES * (sizeof(int16_t)));
    
    buf_index++;
    
    if (buf_index == BUFS) {
        buf_index = 0;
        sf_write_short(file, buf, ADC_SAMPLES * BUFS);
    }
}
