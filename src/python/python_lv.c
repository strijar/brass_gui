/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#include "python_lv.h"
#include "python_lv_grad.h"
#include "python_lv_style.h"
#include "python_lv_object.h"
#include "python_lv_hiding.h"
#include "python_lv_label.h"
#include "python_lv_spectrum.h"
#include "python_lv_spectrum3d.h"
#include "python_lv_waterfall.h"
#include "python_lv_finder.h"
#include "python_lv_bandinfo.h"
#include "python_lv_btn.h"
#include "python_lv_xmeter.h"

static PyObject * lv_load_font(PyObject *self, PyObject *args) {
    const char      *path;
    lv_coord_t      font_size;
    lv_ft_info_t    info;
    PyObject        *res;

    if (PyArg_ParseTuple(args, "si", &path, &font_size)) {
        info.name = path;
        info.weight = font_size;
        info.style = FT_FONT_STYLE_NORMAL;
        info.mem = NULL;

        if (!lv_ft_font_init(&info)) {
            LV_LOG_ERROR("create failed.");
        }
    }

    res = PyLong_FromVoidPtr((void *) info.font);
    Py_XINCREF(res);

    return res;
};

static PyMethodDef lv_methods[] = {
    { "load_font", (PyCFunction) lv_load_font, METH_VARARGS, "" },
    { NULL }
};

static PyModuleDef lv_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "lv",
    .m_doc = "",
    .m_size = -1,
    .m_methods = lv_methods
};

PyMODINIT_FUNC PyInit_lv() {
    PyType_Ready(&grad_type);
    PyType_Ready(&style_type);
    PyType_Ready(&obj_type);
    PyType_Ready(&hiding_type);
    PyType_Ready(&label_type);
    PyType_Ready(&spectrum_type);
    PyType_Ready(&spectrum3d_type);
    PyType_Ready(&waterfall_type);
    PyType_Ready(&finder_type);
    PyType_Ready(&bandinfo_type);
    PyType_Ready(&btn_type);
    PyType_Ready(&xmeter_type);

    PyObject *m = PyModule_Create(&lv_module);

    if (m == NULL) {
        return NULL;
    }

    PyModule_AddObjectRef(m, "grad", (PyObject *) &grad_type);
    PyModule_AddObjectRef(m, "style", (PyObject *) &style_type);
    PyModule_AddObjectRef(m, "obj", (PyObject *) &obj_type);
    PyModule_AddObjectRef(m, "hiding", (PyObject *) &hiding_type);
    PyModule_AddObjectRef(m, "label", (PyObject *) &label_type);
    PyModule_AddObjectRef(m, "spectrum", (PyObject *) &spectrum_type);
    PyModule_AddObjectRef(m, "spectrum3d", (PyObject *) &spectrum3d_type);
    PyModule_AddObjectRef(m, "waterfall", (PyObject *) &waterfall_type);
    PyModule_AddObjectRef(m, "finder", (PyObject *) &finder_type);
    PyModule_AddObjectRef(m, "bandinfo", (PyObject *) &bandinfo_type);
    PyModule_AddObjectRef(m, "btn", (PyObject *) &btn_type);
    PyModule_AddObjectRef(m, "xmeter", (PyObject *) &xmeter_type);

    return m;
}
