/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#include "cw_key.h"
#include "generator.h"
#include "params.h"
#include "util.h"
#include "fpga/dac.h"

static generator_tone_t tone;

void cw_key_init() {
    generator_tone_set_freq(&tone, params.key_tone, DAC_RATE);
}

uint16_t cw_key_change_speed(int16_t d) {
    if (d == 0) {
        return params.key_speed;
    }
    
    params_lock();
    params.key_speed = limit(params.key_speed + d, 5, 50);
    params_unlock(&params.durty.key_speed);

    return params.key_speed;
}

cw_key_mode_t cw_key_change_mode(int16_t d) {
    if (d == 0) {
        return params.key_mode;
    }

    params_lock();

    switch (params.key_mode) {
        case cw_key_manual:
            params.key_mode = d > 0 ? cw_key_auto_left : cw_key_auto_right;
            break;
            
        case cw_key_auto_left:
            params.key_mode = d > 0 ? cw_key_auto_right : cw_key_manual;
            break;
            
        case cw_key_auto_right:
            params.key_mode = d > 0 ? cw_key_manual : cw_key_auto_left;
            break;
    }

    params_unlock(&params.durty.key_mode);

    return params.key_mode;
}

cw_key_iambic_mode_t cw_key_change_iambic_mode(int16_t d) {
    if (d == 0) {
        return params.iambic_mode;
    }

    params_lock();

    params.iambic_mode = (params.iambic_mode == cw_key_iambic_a) ? cw_key_iambic_b : cw_key_iambic_a;

    params_unlock(&params.durty.iambic_mode);

    return params.iambic_mode;
}

uint16_t cw_key_change_tone(int16_t d) {
    if (d == 0) {
        return params.key_tone;
    }

    params_lock();

    params.key_tone += (d > 0) ? 10 : -10;

    if (params.key_tone < 400) {
        params.key_tone = 400;
    } else if (params.key_tone > 1200) {
        params.key_tone = 1200;
    }

    params_unlock(&params.durty.key_tone);

    generator_tone_set_freq(&tone, params.key_tone, DAC_RATE);

    return params.key_tone;
}

uint16_t cw_key_change_vol(int16_t d) {
    if (d == 0) {
        return params.key_vol;
    }

    params_lock();

    params.key_vol = limit(params.key_vol + d, 0, 32);
    params_unlock(&params.durty.key_vol);

    return params.key_vol;
}

bool cw_key_change_train(int16_t d) {
    if (d == 0) {
        return params.key_train;
    }

    params_lock();
    params.key_train = !params.key_train;
    params_unlock(&params.durty.key_train);

    return params.key_train;
}

uint16_t cw_key_change_qsk_time(int16_t d) {
    if (d == 0) {
        return params.qsk_time;
    }

    params_lock();

    int16_t x = params.qsk_time;
    
    if (d > 0) {
        x += 10;
    } else {
        x -= 10;
    }
    
    params.qsk_time = limit(x, 0, 1000);
    params_unlock(&params.durty.qsk_time);

    return params.qsk_time;
}

uint8_t cw_key_change_ratio(int16_t d) {
    if (d == 0) {
        return params.key_ratio;
    }

    params_lock();

    int16_t x = params.key_ratio;

    if (d > 0) {
        x += 5;
    } else {
        x -= 5;
    }

    params.key_ratio = limit(x, 25, 45);
    params_unlock(&params.durty.key_ratio);

    return params.key_ratio;
}

size_t cw_key_generator(float complex *data, size_t max_size, bool reverse) {
    size_t size = 128;

    for (uint16_t i = 0; i < size; i++) {
        data[i] = generator_tone(&tone);
    }
    
    return size;
}
