/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#include "bands.h"
#include "band_info.h"
#include "styles.h"
#include "events.h"
#include "backlight.h"

#include "settings/bands.h"
#include "settings/modes.h"

static lv_obj_t         *obj;

static lv_coord_t       band_info_height = 24;
static int32_t          width_hz = 100000;
static uint64_t         freq;
static lv_anim_t        fade;
static bool             fade_run = false;
static int16_t          band_id = -1;

static lv_timer_t       *timer = NULL;

static void band_info_timer(lv_timer_t *t) {
    lv_anim_set_values(&fade, lv_obj_get_style_opa(obj, 0), LV_OPA_TRANSP);
    lv_anim_start(&fade);
    timer = NULL;
}

static void band_info_draw_cb(lv_event_t * e) {
    lv_event_code_t     code = lv_event_get_code(e);
    lv_obj_t            *obj = lv_event_get_target(e);
    lv_draw_ctx_t       *draw_ctx = lv_event_get_draw_ctx(e);

    if (!bands || band_id < 0) {
        return;
    }

    lv_coord_t x1 = obj->coords.x1;
    lv_coord_t y1 = obj->coords.y1;

    lv_coord_t w = lv_obj_get_width(obj);
    lv_coord_t h = lv_obj_get_height(obj) - 1;

    for (uint16_t i = band_id; i < bands->count; i++) {
        band_t  *band = &(bands->item[i]);
        int32_t start = (int64_t)(band->settings.start - freq) * w / width_hz;
        int32_t stop = (int64_t)(band->settings.stop - freq) * w / width_hz;

        start += w / 2;
        stop += w / 2;

        if (start > w) {
            break;
        }

        if (start < 0) {
            start = 0;
        }

        if (stop > w) {
            stop = w;
        }

        /* Rect */

        lv_draw_rect_dsc_t  rect_dsc;
        lv_area_t           area;

        lv_draw_rect_dsc_init(&rect_dsc);

        rect_dsc.bg_color = bg_color;
        rect_dsc.bg_opa = LV_OPA_50;
        rect_dsc.border_width = 2;
        rect_dsc.border_color = lv_color_white();
        rect_dsc.border_opa = LV_OPA_50;

        area.x1 = x1 + start + 2;
        area.y1 = y1;
        area.x2 = x1 + stop - 2;
        area.y2 = y1 + h;

        lv_draw_rect(draw_ctx, &rect_dsc, &area);

        /* Label */

        lv_draw_label_dsc_t dsc_label;
        lv_draw_label_dsc_init(&dsc_label);

        dsc_label.color = lv_color_white();
        dsc_label.font = font_band_info;

        lv_point_t label_size;
        lv_txt_get_size(&label_size, band->settings.label, dsc_label.font, 0, 0, LV_COORD_MAX, 0);

        if (stop - start > label_size.x) {
            area.x1 = x1 + (start + stop) / 2 - label_size.x / 2;
            area.y1 = y1 + (h - label_size.y) / 2;
            area.x2 = x1 + (start + stop / 2 + label_size.x / 2);
            area.y2 = y1 + h;

            lv_draw_label(draw_ctx, &dsc_label, &area, band->settings.label, NULL);
        }
    }
}

static void fade_anim(void * obj, int32_t v) {
    lv_obj_set_style_opa_layered(obj, v, 0);
}

static void fade_ready(lv_anim_t * a) {
    fade_run = false;
}

lv_obj_t * band_info_init(lv_obj_t *parent) {
    obj = lv_obj_create(parent);

    lv_obj_set_size(obj, lv_obj_get_width(parent), band_info_height);
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, -lv_obj_get_height(parent) / 2 + 18);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_radius(obj, 0, 0);
    lv_obj_set_style_border_width(obj, 0, 0);
    lv_obj_set_style_bg_opa(obj, LV_OPA_0, 0);

    lv_obj_add_event_cb(obj, band_info_draw_cb, LV_EVENT_DRAW_MAIN_END, NULL);

    lv_anim_init(&fade);
    lv_anim_set_var(&fade, obj);
    lv_anim_set_time(&fade, 250);
    lv_anim_set_exec_cb(&fade, fade_anim);
    lv_anim_set_ready_cb(&fade, fade_ready);

    return obj;
}

void band_info_update(uint64_t f) {
    freq = f;
    band_id = -1;

    lv_coord_t w = lv_obj_get_width(obj);

    for (uint16_t i = 0; i < bands->count; i++) {
        band_t *band = &(bands->item[i]);

        int32_t start = (int64_t)(band->settings.start - freq) * w / width_hz;
        int32_t stop = (int64_t)(band->settings.stop - freq) * w / width_hz;

        start += w / 2;
        stop += w / 2;

        if ((start > 0 && start < w) || (stop > 0 && stop < w) || (start < 0 && stop > w)) {
            band_id = i;
            break;
        }
    }

    if (backlight_is_on()) {
        lv_obj_invalidate(obj);
    }

    if (!fade_run) {
        fade_run = true;
        lv_anim_set_values(&fade, lv_obj_get_style_opa(obj, 0), LV_OPA_COVER);
        lv_anim_start(&fade);
    }

    if (timer) {
        lv_timer_reset(timer);
    } else {
        timer = lv_timer_create(band_info_timer, 2000, NULL);
        lv_timer_set_repeat_count(timer, 1);
    }
}

void band_info_update_range() {
    width_hz = 100000 / op_mode->spectrum_factor;
}
