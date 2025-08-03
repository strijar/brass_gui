/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#include "python_lv_smeter.h"
#include "python_lv_object.h"
#include "src/widgets/lv_smeter.h"

static int smeter_init(obj_object_t *self, PyObject *args, PyObject *kwds) {
    LV_LOG_INFO("begin");

    PyObject    *obj = NULL;
    lv_obj_t    *parent = NULL;

    if (PyArg_ParseTuple(args, "O", &obj)) {
        parent = python_lv_get_obj(obj);
    }

    self->obj = lv_smeter_create(parent);

    return 0;
}

static PyObject * smeter_set_value(obj_object_t *self, PyObject *args) {
    int32_t value;

    if (PyArg_ParseTuple(args, "i", &value)) {
        lv_smeter_set_value(self->obj, value);
    }

    Py_RETURN_NONE;
}

static PyObject * smeter_set_part(obj_object_t *self, PyObject *args) {
    uint8_t index;
    int32_t db;

    if (PyArg_ParseTuple(args, "bi", &index, &db)) {
        lv_smeter_set_part(self->obj, index, db);
    }

    Py_RETURN_NONE;
}

static PyMethodDef smeter_methods[] = {
    { "set_value", (PyCFunction) smeter_set_value, METH_VARARGS, "" },
    { "set_part", (PyCFunction) smeter_set_part, METH_VARARGS, "" },
    { NULL }
};

PyTypeObject smeter_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_base = &obj_type,
    .tp_name = "lv.smeter",
    .tp_doc = PyDoc_STR("LVGL S-Meter"),
    .tp_basicsize = sizeof(obj_object_t),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_init = (initproc) smeter_init,
    .tp_methods = smeter_methods,
};
