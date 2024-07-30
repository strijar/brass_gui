/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#include "python.h"
#include "python_lv.h"

static PyObject *module;
static PyObject *py_main_screen;

void python_init() {
    PyObject *name;

    if (PyImport_AppendInittab("lv", PyInit_lv) == -1) {
        LV_LOG_ERROR("LV could not extend in-built modules table");
    }
    
    Py_Initialize();

    name = PyUnicode_DecodeFSDefault("brass");
    module = PyImport_Import(name);
    Py_DECREF(name);
    
    if (module == NULL) {
        PyErr_Print();
        return;
    }
    
    py_main_screen = python_call("main");
}

PyObject * python_call(const char *func_name) {
    if (module == NULL) {
        return NULL;
    }

    PyObject *func = PyObject_GetAttrString(module, func_name);
    PyObject *value;

    if (func && PyCallable_Check(func)) {
        value = PyObject_CallObject(func, NULL);
    } else {
        if (PyErr_Occurred()) {
            PyErr_Print();
        }
    }

    Py_XDECREF(func);

    return value;
}

lv_obj_t * python_main_screen_get() {
    if (py_main_screen) {
        return python_lv_get_obj(py_main_screen);
    } else {
        LV_LOG_ERROR("Main screen object not found");
    }
    
    return NULL;
}
