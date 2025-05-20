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
#include "src/widgets/lv_spectrum.h"
#include "src/widgets/lv_waterfall.h"
#include "src/widgets/lv_finder.h"
#include "src/main.h"
#include "src/msgs.h"

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
            lv_obj_invalidate(spectrum);
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

/* Waterfall */

static void waterfall_msg_cb(void *s, lv_msg_t *m) {
    lv_obj_t *waterfall = lv_msg_get_user_data(m);

    switch (lv_msg_get_id(m)) {
        case MSG_BAND_CHANGED:
            lv_waterfall_clear_data(waterfall);
            break;

        case MSG_FREQ_FFT_SHIFT: {
            const int32_t   *df = lv_msg_get_payload(m);

            lv_waterfall_scroll_data(waterfall, *df);
        } break;

        case MSG_RATE_FFT_CHANGED: {
            const uint8_t *zoom = lv_msg_get_payload(m);

            lv_waterfall_set_span(waterfall, 100000 / *zoom);
            lv_waterfall_clear_data(waterfall);
        } break;

        case MSG_WATERFALL_AUTO: {
            const msgs_auto_t *msg = lv_msg_get_payload(m);

            lv_waterfall_set_min(waterfall, msg->min + 3.0f);
            lv_waterfall_set_max(waterfall, msg->max + 3.0f);
        } break;

        case MSG_WATERFALL_DATA: {
            const msgs_floats_t *msg = lv_msg_get_payload(m);

            lv_waterfall_add_data(waterfall, msg->data, msg->size);
            lv_obj_invalidate(waterfall);
        } break;
    }
}

static PyObject * trx_connect_waterfall(PyObject *self, PyObject *args) {
    LV_LOG_INFO("begin");

    PyObject    *obj = NULL;

    if (PyArg_ParseTuple(args, "O", &obj)) {
        lv_obj_t *waterfall = python_lv_get_obj(obj);

        lv_msg_subsribe(MSG_FREQ_FFT_SHIFT, waterfall_msg_cb, waterfall);
        lv_msg_subsribe(MSG_RATE_FFT_CHANGED, waterfall_msg_cb, waterfall);
        lv_msg_subsribe(MSG_WATERFALL_AUTO, waterfall_msg_cb, waterfall);
        lv_msg_subsribe(MSG_BAND_CHANGED, waterfall_msg_cb, waterfall);
        lv_msg_subsribe(MSG_WATERFALL_DATA, waterfall_msg_cb, waterfall);
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

        case MSG_FREQ_FFT_CHANGED: {
            const uint64_t  *freq = lv_msg_get_payload(m);

            lv_finder_set_center(finder, *freq);
            lv_obj_invalidate(finder);
        } break;

        case MSG_FINDER_CURSOR: {
            const msg_finder_cursor_t *msg = lv_msg_get_payload(m);

            lv_finder_set_cursor_num(finder, msg->num);
            lv_finder_set_cursor(finder, 1, msg->cursor[0]);
            lv_finder_set_cursor(finder, 2, msg->cursor[1]);
            lv_finder_set_cursor(finder, 3, msg->cursor[2]);
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
        lv_msg_subsribe(MSG_FINDER_CURSOR, finder_event_cb, finder);
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
        lv_msg_subsribe(MSG_FINDER_CURSOR, finder_event_cb, finder);
        lv_msg_subsribe(MSG_FREQ_TX_CHANGED, tx_finder_event_cb, finder);
        lv_msg_subsribe(MSG_FINDER_CURSOR, tx_finder_event_cb, finder);
    }

    Py_RETURN_NONE;
}

/* * */

static PyMethodDef trx_methods[] = {
    { "connect_spectrum", (PyCFunction) trx_connect_spectrum, METH_VARARGS, "" },
    { "connect_waterfall", (PyCFunction) trx_connect_waterfall, METH_VARARGS, "" },
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

    /* Messages */

    PyModule_AddObjectRef(m, "MSG_MODE_CHANGED",        PyLong_FromLong(MSG_MODE_CHANGED));
    PyModule_AddObjectRef(m, "MSG_FILTER_CHANGED",      PyLong_FromLong(MSG_FILTER_CHANGED));
    PyModule_AddObjectRef(m, "MSG_BAND_CHANGED",        PyLong_FromLong(MSG_BAND_CHANGED));
    PyModule_AddObjectRef(m, "MSG_FREQ_RX_PRE_CHANGED", PyLong_FromLong(MSG_FREQ_RX_PRE_CHANGED));
    PyModule_AddObjectRef(m, "MSG_FREQ_RX_CHANGED",     PyLong_FromLong(MSG_FREQ_RX_CHANGED));
    PyModule_AddObjectRef(m, "MSG_FREQ_TX_PRE_CHANGED", PyLong_FromLong(MSG_FREQ_TX_PRE_CHANGED));
    PyModule_AddObjectRef(m, "MSG_FREQ_TX_CHANGED",     PyLong_FromLong(MSG_FREQ_TX_CHANGED));
    PyModule_AddObjectRef(m, "MSG_FREQ_FFT_CHANGED",    PyLong_FromLong(MSG_FREQ_FFT_CHANGED));
    PyModule_AddObjectRef(m, "MSG_FREQ_FFT_SHIFT",      PyLong_FromLong(MSG_FREQ_FFT_SHIFT));
    PyModule_AddObjectRef(m, "MSG_RATE_FFT_CHANGED",    PyLong_FromLong(MSG_RATE_FFT_CHANGED));
    PyModule_AddObjectRef(m, "MSG_SPECTRUM_AUTO",       PyLong_FromLong(MSG_SPECTRUM_AUTO));
    PyModule_AddObjectRef(m, "MSG_WATERFALL_AUTO",      PyLong_FromLong(MSG_WATERFALL_AUTO));
    PyModule_AddObjectRef(m, "MSG_SPECTRUM_DATA",       PyLong_FromLong(MSG_SPECTRUM_DATA));
    PyModule_AddObjectRef(m, "MSG_WATERFALL_DATA",      PyLong_FromLong(MSG_WATERFALL_DATA));
    PyModule_AddObjectRef(m, "MSG_PTT",                 PyLong_FromLong(MSG_PTT));
    PyModule_AddObjectRef(m, "MSG_TX",                  PyLong_FromLong(MSG_TX));
    PyModule_AddObjectRef(m, "MSG_RX",                  PyLong_FromLong(MSG_RX));
    PyModule_AddObjectRef(m, "MSG_FINDER_CURSOR",       PyLong_FromLong(MSG_FINDER_CURSOR));
    PyModule_AddObjectRef(m, "MSG_RECORDER",            PyLong_FromLong(MSG_RECORDER));
    PyModule_AddObjectRef(m, "MSG_MSG",                 PyLong_FromLong(MSG_MSG));
    PyModule_AddObjectRef(m, "MSG_MSG_TINY",            PyLong_FromLong(MSG_MSG_TINY));

    return m;
}
