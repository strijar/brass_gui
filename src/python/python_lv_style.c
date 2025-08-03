/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#include "python_lv_style.h"
#include "python_lv_grad.h"

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

    if (PyArg_ParseTuple(args, "I", &color)) {
        lv_style_set_bg_color(&self->style, color);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_bg_grad(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    PyObject *obj = NULL;

    if (PyArg_ParseTuple(args, "O", &obj)) {
        if (PyObject_TypeCheck(obj, &grad_type)) {
            Py_INCREF(obj);

            grad_object_t *grad = (grad_object_t *) obj;

            lv_style_set_bg_grad(&self->style, &grad->grad);
        }
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_bg_grad_color(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_color_t color;

    if (PyArg_ParseTuple(args, "I", &color)) {
        lv_style_set_bg_grad_color(&self->style, color);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_bg_grad_dir(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_grad_dir_t value;

    if (PyArg_ParseTuple(args, "b", &value)) {
        lv_style_set_bg_grad_dir(&self->style, value);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_bg_main_stop(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_coord_t value;

    if (PyArg_ParseTuple(args, "i", &value)) {
        lv_style_set_bg_main_stop(&self->style, value);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_bg_grad_stop(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_coord_t value;

    if (PyArg_ParseTuple(args, "i", &value)) {
        lv_style_set_bg_grad_stop(&self->style, value);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_bg_opa(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_opa_t opa;

    if (PyArg_ParseTuple(args, "b", &opa)) {
        lv_style_set_bg_opa(&self->style, opa);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_bg_img_opa(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_opa_t opa;

    if (PyArg_ParseTuple(args, "b", &opa)) {
        lv_style_set_bg_img_opa(&self->style, opa);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_bg_img_src(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    const char *path;

    if (PyArg_ParseTuple(args, "s", &path)) {
        lv_style_set_bg_img_src(&self->style, strdup(path));
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_border_color(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_color_t color;

    if (PyArg_ParseTuple(args, "I", &color)) {
        lv_style_set_border_color(&self->style, color);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_border_opa(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_opa_t opa;

    if (PyArg_ParseTuple(args, "b", &opa)) {
        lv_style_set_border_opa(&self->style, opa);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_border_width(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_coord_t width;

    if (PyArg_ParseTuple(args, "i", &width)) {
        lv_style_set_border_width(&self->style, width);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_radius(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_coord_t radius;

    if (PyArg_ParseTuple(args, "i", &radius)) {
        lv_style_set_radius(&self->style, radius);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_x(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_coord_t x;

    if (PyArg_ParseTuple(args, "i", &x)) {
        lv_style_set_x(&self->style, x);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_y(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_coord_t y;

    if (PyArg_ParseTuple(args, "i", &y)) {
        lv_style_set_y(&self->style, y);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_width(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_coord_t width;

    if (PyArg_ParseTuple(args, "i", &width)) {
        lv_style_set_width(&self->style, width);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_height(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_coord_t height;

    if (PyArg_ParseTuple(args, "i", &height)) {
        lv_style_set_height(&self->style, height);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_pad_hor(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_coord_t pad;

    if (PyArg_ParseTuple(args, "i", &pad)) {
        lv_style_set_pad_hor(&self->style, pad);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_pad_ver(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_coord_t pad;

    if (PyArg_ParseTuple(args, "i", &pad)) {
        lv_style_set_pad_ver(&self->style, pad);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_line_width(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_coord_t width;

    if (PyArg_ParseTuple(args, "i", &width)) {
        lv_style_set_line_width(&self->style, width);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_line_color(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_color_t color;

    if (PyArg_ParseTuple(args, "I", &color)) {
        lv_style_set_line_color(&self->style, color);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_line_opa(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_opa_t opa;

    if (PyArg_ParseTuple(args, "b", &opa)) {
        lv_style_set_line_opa(&self->style, opa);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_text_color(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_color_t color;

    if (PyArg_ParseTuple(args, "I", &color)) {
        lv_style_set_text_color(&self->style, color);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_text_align(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_text_align_t align;

    if (PyArg_ParseTuple(args, "b", &align)) {
        lv_style_set_text_align(&self->style, align);
    }

    Py_RETURN_NONE;
}

static PyObject * style_set_text_font(style_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    void *font;

    if (PyArg_ParseTuple(args, "k", &font)) {
        lv_style_set_text_font(&self->style, font);
    }

    Py_RETURN_NONE;
}

static PyMethodDef style_methods[] = {
    { "set_bg_color", (PyCFunction) style_set_bg_color, METH_VARARGS, "" },
    { "set_bg_opa", (PyCFunction) style_set_bg_opa, METH_VARARGS, "" },
    { "set_bg_img_src", (PyCFunction) style_set_bg_img_src, METH_VARARGS, "" },
    { "set_bg_img_opa", (PyCFunction) style_set_bg_img_opa, METH_VARARGS, "" },
    { "set_bg_grad", (PyCFunction) style_set_bg_grad, METH_VARARGS, "" },
    { "set_bg_grad_color", (PyCFunction) style_set_bg_grad_color, METH_VARARGS, "" },
    { "set_bg_grad_dir", (PyCFunction) style_set_bg_grad_dir, METH_VARARGS, "" },
    { "set_bg_main_stop", (PyCFunction) style_set_bg_main_stop, METH_VARARGS, "" },
    { "set_bg_grad_stop", (PyCFunction) style_set_bg_grad_stop, METH_VARARGS, "" },
    { "set_border_color", (PyCFunction) style_set_border_color, METH_VARARGS, "" },
    { "set_border_width", (PyCFunction) style_set_border_width, METH_VARARGS, "" },
    { "set_border_opa", (PyCFunction) style_set_border_opa, METH_VARARGS, "" },
    { "set_radius", (PyCFunction) style_set_radius, METH_VARARGS, "" },
    { "set_x", (PyCFunction) style_set_x, METH_VARARGS, "" },
    { "set_y", (PyCFunction) style_set_y, METH_VARARGS, "" },
    { "set_width", (PyCFunction) style_set_width, METH_VARARGS, "" },
    { "set_height", (PyCFunction) style_set_height, METH_VARARGS, "" },
    { "set_pad_hor", (PyCFunction) style_set_pad_hor, METH_VARARGS, "" },
    { "set_pad_ver", (PyCFunction) style_set_pad_ver, METH_VARARGS, "" },
    { "set_line_width", (PyCFunction) style_set_line_width, METH_VARARGS, "" },
    { "set_line_color", (PyCFunction) style_set_line_color, METH_VARARGS, "" },
    { "set_line_opa", (PyCFunction) style_set_line_opa, METH_VARARGS, "" },
    { "set_text_color", (PyCFunction) style_set_text_color, METH_VARARGS, "" },
    { "set_text_align", (PyCFunction) style_set_text_align, METH_VARARGS, "" },
    { "set_text_font", (PyCFunction) style_set_text_font, METH_VARARGS, "" },
    { NULL }
};

PyTypeObject style_type = {
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

lv_style_t * python_lv_get_style(PyObject *obj) {
    if (PyObject_TypeCheck(obj, &style_type)) {
        style_object_t *self = (style_object_t *) obj;

        return &self->style;
    }

    return NULL;
}
