/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#include "lvgl/lvgl.h"
#include "python_lv.h"
#include "python_trx.h"
#include "src/msgs.h"
#include "src/events.h"
#include "src/params.h"
#include "src/widgets/lv_spectrum.h"
#include "src/widgets/lv_finder.h"

/* Spectrum */

static void spectrum_msg_cb(void *s, lv_msg_t *m) {
    lv_obj_t *spectrum = lv_msg_get_user_data(m);
    
    switch (lv_msg_get_id(m)) {
        case MSG_FREQ_FFT_SHIFT: {
            const int32_t *df = lv_msg_get_payload(m);

            lv_spectrum_scroll_data(spectrum, *df);
        } break;
        
        case MSG_RATE_FFT_CHANGED: {
            const uint8_t *zoom = lv_msg_get_payload(m);

            lv_spectrum_set_span(spectrum, 100000 / *zoom);
            lv_spectrum_clear_data(spectrum);
        } break;

        case MSG_SPECTRUM_AUTO: {
            const msgs_auto_t *msg = lv_msg_get_payload(m);

            lv_spectrum_set_min(spectrum, msg->min + 3.0f);
            lv_spectrum_set_max(spectrum, msg->max + 10.0f);
        } break;

        case MSG_SPECTRUM_DATA: {
            const msgs_floats_t *msg = lv_msg_get_payload(m);

            lv_spectrum_add_data(spectrum, msg->data, msg->size);
            event_send(spectrum, LV_EVENT_REFRESH, NULL);
        } break;
    }
}

static PyObject * trx_connect_spectrum(PyObject *self, PyObject *args) {
    LV_LOG_INFO("begin");

    PyObject    *obj = NULL;

    if (PyArg_ParseTuple(args, "O", &obj)) {
        lv_obj_t *spectrum = python_lv_get_obj(obj);
    
        lv_msg_subsribe(MSG_FREQ_FFT_SHIFT, spectrum_msg_cb, spectrum);
        lv_msg_subsribe(MSG_RATE_FFT_CHANGED, spectrum_msg_cb, spectrum);
        lv_msg_subsribe(MSG_SPECTRUM_AUTO, spectrum_msg_cb, spectrum);
        lv_msg_subsribe(MSG_SPECTRUM_DATA, spectrum_msg_cb, spectrum);
    }

    Py_RETURN_NONE;
}

/* Finder */

static void finder_event_cb(void *s, lv_msg_t *m) {
    lv_obj_t *finder = lv_msg_get_user_data(m);
    
    switch (lv_msg_get_id(m)) {
        case MSG_FILTER_CHANGED: {
            int32_t from, to;

            radio_filter_get(&from, &to);
            lv_finder_set_offsets(finder, from, to);
            lv_obj_invalidate(finder);
        } break;

        case MSG_RATE_FFT_CHANGED: {
            const uint8_t *zoom = lv_msg_get_payload(m);

            lv_finder_set_span(finder, 100000 / *zoom);
            lv_obj_invalidate(finder);
        } break;
        
        case MSG_FREQ_RX_CHANGED: {
            const uint64_t *freq = lv_msg_get_payload(m);
            
            lv_finder_set_value(finder, *freq);
            lv_obj_invalidate(finder);
        } break;

        case MSG_FREQ_FFT_CHANGED: {
            const uint64_t  *freq = lv_msg_get_payload(m);

            lv_finder_set_center(finder, *freq);
            lv_obj_invalidate(finder);
        } break;
        
        default:
            break;
    }
}

static void rx_finder_event_cb(void *s, lv_msg_t *m) {
    lv_obj_t *finder = lv_msg_get_user_data(m);
    
    switch (lv_msg_get_id(m)) {
        case MSG_FREQ_RX_CHANGED: {
            const uint64_t *freq = lv_msg_get_payload(m);
            
            lv_finder_set_value(finder, *freq);
            lv_obj_invalidate(finder);
        } break;

        default:
            break;
    }
}

static void tx_finder_event_cb(void *s, lv_msg_t *m) {
    lv_obj_t *finder = lv_msg_get_user_data(m);
    
    switch (lv_msg_get_id(m)) {
        case MSG_FREQ_TX_CHANGED: {
            const uint64_t *freq = lv_msg_get_payload(m);
            
            lv_finder_set_value(finder, *freq);
            lv_obj_invalidate(finder);
        } break;

        default:
            break;
    }
}

static PyObject * trx_connect_rx_finder(PyObject *self, PyObject *args) {
    LV_LOG_INFO("begin");

    PyObject    *obj = NULL;

    if (PyArg_ParseTuple(args, "O", &obj)) {
        lv_obj_t *finder = python_lv_get_obj(obj);
    
        lv_msg_subsribe(MSG_FILTER_CHANGED, finder_event_cb, finder);
        lv_msg_subsribe(MSG_RATE_FFT_CHANGED, finder_event_cb, finder);
        lv_msg_subsribe(MSG_FREQ_FFT_CHANGED, finder_event_cb, finder);
        lv_msg_subsribe(MSG_FREQ_RX_CHANGED, rx_finder_event_cb, finder);
    }

    Py_RETURN_NONE;
}

static PyObject * trx_connect_tx_finder(PyObject *self, PyObject *args) {
    LV_LOG_INFO("begin");

    PyObject    *obj = NULL;

    if (PyArg_ParseTuple(args, "O", &obj)) {
        lv_obj_t *finder = python_lv_get_obj(obj);
    
        lv_msg_subsribe(MSG_FILTER_CHANGED, finder_event_cb, finder);
        lv_msg_subsribe(MSG_RATE_FFT_CHANGED, finder_event_cb, finder);
        lv_msg_subsribe(MSG_FREQ_FFT_CHANGED, finder_event_cb, finder);
        lv_msg_subsribe(MSG_FREQ_TX_CHANGED, tx_finder_event_cb, finder);
    }

    Py_RETURN_NONE;
}

/* * */

static PyMethodDef trx_methods[] = {
    { "connect_spectrum", (PyCFunction) trx_connect_spectrum, METH_VARARGS, "" },
    { "connect_rx_finder", (PyCFunction) trx_connect_rx_finder, METH_VARARGS, "" },
    { "connect_tx_finder", (PyCFunction) trx_connect_tx_finder, METH_VARARGS, "" },
    { NULL }
};

static PyModuleDef trx_module = {
    PyModuleDef_HEAD_INIT,
    "trx",
    NULL,
    -1,
    trx_methods
};

PyMODINIT_FUNC PyInit_trx() {
    PyObject *m = PyModule_Create(&trx_module);

    return m;
}
