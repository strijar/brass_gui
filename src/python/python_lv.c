/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#include "python_lv.h"

/* Style */

typedef struct {
    PyObject_HEAD
    lv_style_t  style;
} style_object_t;

static void style_dealloc(style_object_t *self) {
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject * style_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    LV_LOG_INFO("begin");

    style_object_t *self = (style_object_t *) type->tp_alloc(type, 0);
    
    if (self != NULL) {
        lv_style_init(&self->style);
    }
    
    return (PyObject *) self;
}

static PyObject * style_set_bg_color(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_color_t color;
    
    if (PyArg_ParseTuple(args, "i", &color)) {
        lv_style_set_bg_color(&self->style, color);
    }
    
    Py_RETURN_NONE;
}

static PyMethodDef style_methods[] = {
    { "set_bg_color", (PyCFunction) style_set_bg_color, METH_VARARGS, "" },
    { NULL }
};

static PyTypeObject style_type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "lv.style",
    .tp_doc = PyDoc_STR("LVGL style objects"),
    .tp_basicsize = sizeof(style_object_t),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = style_new,
    .tp_init = NULL,
    .tp_dealloc = (destructor) style_dealloc,
    .tp_members = NULL,
    .tp_methods = style_methods,
};


/* Object */

typedef struct {
    PyObject_HEAD
    lv_obj_t  *obj;
} obj_object_t;

static void obj_dealloc(obj_object_t *self) {
    lv_obj_del(self->obj);
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject * obj_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    LV_LOG_INFO("begin");

    obj_object_t *self = (obj_object_t *) type->tp_alloc(type, 0);
    self->obj = NULL;
    
    return (PyObject *) self;
}

static int obj_init(obj_object_t *self, PyObject *args, PyObject *kwds) {
    self->obj = lv_obj_create(NULL);

    return 0;
}

static PyObject * obj_add_style(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    PyObject    *obj = NULL;
    lv_part_t   selector;
    
    if (PyArg_ParseTuple(args, "Oi", &obj, &selector)) {
        if (PyObject_TypeCheck(obj, &style_type)) {
            Py_INCREF(obj);

            style_object_t *style = (style_object_t *) obj;
            
            lv_obj_add_style(self->obj, &style->style, selector);
        }
    }

    Py_RETURN_NONE;
}

static PyObject * obj_clear_flag(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_obj_flag_t flag;
    
    if (PyArg_ParseTuple(args, "i", &flag)) {
        lv_obj_clear_flag(self->obj, flag);
    }

    Py_RETURN_NONE;
}

static PyMethodDef obj_methods[] = {
    { "add_style", (PyCFunction) obj_add_style, METH_VARARGS, "" },
    { "clear_flag", (PyCFunction) obj_clear_flag, METH_VARARGS, "" },
    { NULL }
};

static PyTypeObject obj_type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "lv.obj",
    .tp_doc = PyDoc_STR("LVGL object"),
    .tp_basicsize = sizeof(obj_object_t),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = obj_new,
    .tp_init = (initproc) obj_init,
    .tp_dealloc = (destructor) obj_dealloc,
    .tp_members = NULL,
    .tp_methods = obj_methods,
};

/* * */

static PyModuleDef lv_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "lv",
    .m_doc = "",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit_lv() {
    PyType_Ready(&style_type);
    PyType_Ready(&obj_type);

    PyObject *m = PyModule_Create(&lv_module);

    if (m == NULL) {
        return NULL;
    }

    PyModule_AddObjectRef(m, "style", (PyObject *) &style_type);
    PyModule_AddObjectRef(m, "obj", (PyObject *) &obj_type);
    
    return m;
}

lv_obj_t * python_lv_get_obj(PyObject *obj) {
    if (PyObject_TypeCheck(obj, &obj_type)) {
        obj_object_t *self = (obj_object_t *) obj;

        return self->obj;
    }
    
    return NULL;
}
