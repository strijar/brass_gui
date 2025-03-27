/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#include "python_lv.h"
#include "src/widgets/lv_spectrum.h"
#include "src/widgets/lv_waterfall.h"
#include "src/widgets/lv_finder.h"
#include "src/widgets/lv_bandinfo.h"
#include "src/styles.h"
#include "src/msgs.h"
#include "src/fonts/jura.h"

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

    if (PyArg_ParseTuple(args, "I", &color)) {
        lv_style_set_bg_color(&self->style, color);
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
        lv_style_set_bg_img_src(&self->style, path);
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
    LV_LOG_INFO("begin");

    PyObject    *obj = NULL;
    lv_obj_t    *parent = NULL;

    if (PyArg_ParseTuple(args, "O", &obj)) {
        parent = python_lv_get_obj(obj);
    }

    self->obj = lv_obj_create(parent);

    return 0;
}

static void obj_msg_cb(void *s, lv_msg_t *m) {
    PyObject    *call = lv_msg_get_user_data(m);
    PyObject    *arg;
    uint32_t    msg = lv_msg_get_id(m);

    switch (msg) {
        case MSG_FREQ_FFT_CHANGED:
        case MSG_FREQ_TX_CHANGED:
        case MSG_FREQ_RX_CHANGED: {
            const uint64_t *freq = lv_msg_get_payload(m);

            arg = Py_BuildValue("IL", msg, *freq);
        } break;

        case MSG_RATE_FFT_CHANGED: {
            const uint8_t *zoom = lv_msg_get_payload(m);

            arg = Py_BuildValue("Ib", msg, *zoom);
        } break;

        case MSG_RECORDER: {
            const bool *on = lv_msg_get_payload(m);

            arg = Py_BuildValue("Ib", msg, *on);
        } break;

        case MSG_MSG:
        case MSG_MSG_TINY: {
            const char *text = lv_msg_get_payload(m);

            arg = Py_BuildValue("Is", msg, text);
        } break;

        default:
            arg = Py_BuildValue("IO", msg, Py_None);
            break;
    }

    PyObject *res = PyObject_Call(call, arg, NULL);

    Py_XDECREF(arg);

    if (res) {
        Py_XDECREF(res);
    }
}

static PyObject * obj_msg_subscribe(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    uint32_t    msg_id;
    PyObject    *obj = NULL;

    if (PyArg_ParseTuple(args, "iO", &msg_id, &obj)) {
        Py_XINCREF(obj);

        lv_msg_subscribe(msg_id, obj_msg_cb, obj);
    }

    Py_RETURN_NONE;
}

static PyObject * obj_add_style(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    PyObject    *obj = NULL;
    lv_part_t   selector;

    if (PyArg_ParseTuple(args, "Ol", &obj, &selector)) {
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

static PyObject * obj_set_pos(obj_object_t *self, PyObject *args) {
    lv_coord_t x, y;

    if (PyArg_ParseTuple(args, "ii", &x, &y)) {
        lv_obj_set_pos(self->obj, x, y);
    }

    Py_RETURN_NONE;
}

static PyObject * obj_set_size(obj_object_t *self, PyObject *args) {
    lv_coord_t w, h;

    if (PyArg_ParseTuple(args, "ii", &w, &h)) {
        lv_obj_set_size(self->obj, w, h);
    }

    Py_RETURN_NONE;
}

static PyObject * obj_set_style_line_width(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_coord_t          width;
    lv_style_selector_t selector;

    if (PyArg_ParseTuple(args, "il", &width, &selector)) {
        lv_obj_set_style_line_width(self->obj, width, selector);
    }

    Py_RETURN_NONE;
}

static PyObject * obj_set_style_line_color(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_color_t          color;
    lv_style_selector_t selector;

    if (PyArg_ParseTuple(args, "Ll", &color, &selector)) {
        lv_obj_set_style_line_color(self->obj, color, selector);
    }

    Py_RETURN_NONE;
}

static PyObject * obj_set_style_opa(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_opa_t            opa;
    lv_style_selector_t selector;

    if (PyArg_ParseTuple(args, "bl", &opa, &selector)) {
        lv_obj_set_style_opa(self->obj, opa, selector);
    }

    Py_RETURN_NONE;
}

static PyObject * obj_move_foreground(obj_object_t *self, PyObject *args) {
    lv_obj_move_foreground(self->obj);

    Py_RETURN_NONE;
}

static PyMethodDef obj_methods[] = {
    { "msg_subscribe", (PyCFunction) obj_msg_subscribe, METH_VARARGS, "" },
    { "add_style", (PyCFunction) obj_add_style, METH_VARARGS, "" },
    { "clear_flag", (PyCFunction) obj_clear_flag, METH_VARARGS, "" },
    { "set_pos", (PyCFunction) obj_set_pos, METH_VARARGS, "" },
    { "set_size", (PyCFunction) obj_set_size, METH_VARARGS, "" },
    { "set_style_line_width", (PyCFunction) obj_set_style_line_width, METH_VARARGS, "" },
    { "set_style_line_color", (PyCFunction) obj_set_style_line_color, METH_VARARGS, "" },
    { "set_style_opa", (PyCFunction) obj_set_style_opa, METH_VARARGS, "" },
    { "move_foreground", (PyCFunction) obj_move_foreground, METH_NOARGS, "" },
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

/* Hiding */

static int hiding_init(obj_object_t *self, PyObject *args, PyObject *kwds) {
    LV_LOG_INFO("begin");

    PyObject    *obj = NULL;
    lv_obj_t    *parent = NULL;

    if (PyArg_ParseTuple(args, "O", &obj)) {
        parent = python_lv_get_obj(obj);
    }

    self->obj = lv_hiding_create(parent);

    return 0;
}

static PyObject * hiding_set_timeout(obj_object_t *self, PyObject *args) {
    uint16_t timeout;

    if (PyArg_ParseTuple(args, "H", &timeout)) {
        lv_hiding_set_timeout(self->obj, timeout);
    }

    Py_RETURN_NONE;
}

static PyObject * hiding_touch(obj_object_t *self, PyObject *args) {
    lv_hiding_touch(self->obj);

    Py_RETURN_NONE;
}

static PyMethodDef hiding_methods[] = {
    { "set_timeout", (PyCFunction) hiding_set_timeout, METH_VARARGS, "" },
    { "touch", (PyCFunction) hiding_touch, METH_NOARGS, "" },
    { NULL }
};

static PyTypeObject hiding_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_base = &obj_type,
    .tp_name = "lv.hiding",
    .tp_doc = PyDoc_STR("LVGL hiding object"),
    .tp_basicsize = sizeof(obj_object_t),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_init = (initproc) hiding_init,
    .tp_methods = hiding_methods,
};

/* Label */

static int label_init(obj_object_t *self, PyObject *args, PyObject *kwds) {
    LV_LOG_INFO("begin");

    PyObject    *obj = NULL;
    lv_obj_t    *parent = NULL;

    if (PyArg_ParseTuple(args, "O", &obj)) {
        parent = python_lv_get_obj(obj);
    }

    self->obj = lv_label_create(parent);

    lv_label_set_recolor(self->obj, true);

    return 0;
}

static PyObject * label_set_text(obj_object_t *self, PyObject *args) {
    const char *text;

    if (PyArg_ParseTuple(args, "s", &text)) {
        lv_label_set_text(self->obj, text);
    }

    Py_RETURN_NONE;
}

static PyMethodDef label_methods[] = {
    { "set_text", (PyCFunction) label_set_text, METH_VARARGS, "" },
    { NULL }
};

static PyTypeObject label_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_base = &obj_type,
    .tp_name = "lv.label",
    .tp_doc = PyDoc_STR("LVGL label"),
    .tp_basicsize = sizeof(obj_object_t),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_init = (initproc) label_init,
    .tp_methods = label_methods,
};

/* Spectrum */

static int spectrum_init(obj_object_t *self, PyObject *args, PyObject *kwds) {
    LV_LOG_INFO("begin");

    PyObject    *obj = NULL;
    lv_obj_t    *parent = NULL;

    if (PyArg_ParseTuple(args, "O", &obj)) {
        parent = python_lv_get_obj(obj);
    }

    self->obj = lv_spectrum_create(parent);

    return 0;
}

static PyObject * spectrum_set_data_size(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    int size;

    if (PyArg_ParseTuple(args, "i", &size)) {
        lv_spectrum_set_data_size(self->obj, size);
    }

    Py_RETURN_NONE;
}

static PyObject * spectrum_clear_data(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_spectrum_clear_data(self->obj);

    Py_RETURN_NONE;
}

static PyObject * spectrum_set_peak(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    int on;

    if (PyArg_ParseTuple(args, "b", &on)) {
        lv_spectrum_set_peak(self->obj, on);
    }

    Py_RETURN_NONE;
}

static PyObject * spectrum_set_peak_hold(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    int ms;

    if (PyArg_ParseTuple(args, "i", &ms)) {
        lv_spectrum_set_peak_hold(self->obj, ms);
    }

    Py_RETURN_NONE;
}

static PyObject * spectrum_set_peak_speed(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    float db;

    if (PyArg_ParseTuple(args, "f", &db)) {
        lv_spectrum_set_peak_speed(self->obj, db);
    }

    Py_RETURN_NONE;
}

static PyMethodDef spectrum_methods[] = {
    { "set_data_size", (PyCFunction) spectrum_set_data_size, METH_VARARGS, "" },
    { "clear_data", (PyCFunction) spectrum_clear_data, METH_NOARGS, "" },
    { "set_peak", (PyCFunction) spectrum_set_peak, METH_VARARGS, "" },
    { "set_peak_hold", (PyCFunction) spectrum_set_peak_hold, METH_VARARGS, "" },
    { "set_peak_speed", (PyCFunction) spectrum_set_peak_speed, METH_VARARGS, "" },
    { NULL }
};

static PyTypeObject spectrum_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_base = &obj_type,
    .tp_name = "lv.spectrum",
    .tp_doc = PyDoc_STR("LVGL spectrum"),
    .tp_basicsize = sizeof(obj_object_t),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_init = (initproc) spectrum_init,
    .tp_methods = spectrum_methods,
};

/* Waterfall */

static int waterfall_init(obj_object_t *self, PyObject *args, PyObject *kwds) {
    LV_LOG_INFO("begin");

    PyObject    *obj = NULL;
    lv_obj_t    *parent = NULL;

    if (PyArg_ParseTuple(args, "O", &obj)) {
        parent = python_lv_get_obj(obj);
    }

    self->obj = lv_waterfall_create(parent);

    return 0;
}

static PyObject * waterfall_set_data_size(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    int w;

    if (PyArg_ParseTuple(args, "i", &w)) {
        lv_waterfall_set_data_size(self->obj, w);
    }

    Py_RETURN_NONE;
}

static PyObject * waterfall_set_palette(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    int stops;

    if (PyArg_ParseTuple(args, "i", &stops)) {
        lv_waterfall_set_palette(self->obj, stops);
    }

    Py_RETURN_NONE;
}

static PyObject * waterfall_set_palette_color(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    uint8_t     index;
    float       frac;
    lv_color_t  color;

    if (PyArg_ParseTuple(args, "bfI", &index, &frac, &color)) {
        lv_waterfall_set_palette_color(self->obj, index, frac, color);
    }

    Py_RETURN_NONE;
}

static PyObject * waterfall_clear_data(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    lv_waterfall_clear_data(self->obj);

    Py_RETURN_NONE;
}

static PyMethodDef waterfall_methods[] = {
    { "set_data_size", (PyCFunction) waterfall_set_data_size, METH_VARARGS, "" },
    { "set_palette", (PyCFunction) waterfall_set_palette, METH_VARARGS, "" },
    { "set_palette_color", (PyCFunction) waterfall_set_palette_color, METH_VARARGS, "" },
    { "clear_data", (PyCFunction) waterfall_clear_data, METH_NOARGS, "" },
    { NULL }
};

static PyTypeObject waterfall_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_base = &obj_type,
    .tp_name = "lv.waterfall",
    .tp_doc = PyDoc_STR("LVGL waterfall"),
    .tp_basicsize = sizeof(obj_object_t),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_init = (initproc) waterfall_init,
    .tp_methods = waterfall_methods,
};

/* Finder */

static int finder_init(obj_object_t *self, PyObject *args, PyObject *kwds) {
    LV_LOG_INFO("begin");

    PyObject    *obj = NULL;
    lv_obj_t    *parent = NULL;

    if (PyArg_ParseTuple(args, "O", &obj)) {
        parent = python_lv_get_obj(obj);
    }

    self->obj = lv_finder_create(parent);

    return 0;
}

static PyObject * finder_set_cursor(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    uint8_t index;
    int     hz;

    if (PyArg_ParseTuple(args, "bi", &index, &hz)) {
        lv_finder_set_cursor(self->obj, index, hz);
    }

    Py_RETURN_NONE;
}

static PyMethodDef finder_methods[] = {
    { "set_cursor", (PyCFunction) finder_set_cursor, METH_VARARGS, "" },
    { NULL }
};

static PyTypeObject finder_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_base = &obj_type,
    .tp_name = "lv.finder",
    .tp_doc = PyDoc_STR("LVGL finder"),
    .tp_basicsize = sizeof(obj_object_t),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_init = (initproc) finder_init,
    .tp_methods = finder_methods,
};

/* Band info */

static int bandinfo_init(obj_object_t *self, PyObject *args, PyObject *kwds) {
    LV_LOG_INFO("begin");

    PyObject    *obj = NULL;
    lv_obj_t    *parent = NULL;

    if (PyArg_ParseTuple(args, "O", &obj)) {
        parent = python_lv_get_obj(obj);
    }

    self->obj = lv_bandinfo_create(parent);

    return 0;
}

static PyObject * bandinfo_set_span(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    int32_t span;

    if (PyArg_ParseTuple(args, "i", &span)) {
        lv_bandinfo_set_span(self->obj, span);
    }

    Py_RETURN_NONE;
}

static PyObject * bandinfo_set_center(obj_object_t *self, PyObject *args) {
    LV_LOG_INFO("begin");

    uint64_t center;

    if (PyArg_ParseTuple(args, "K", &center)) {
        lv_bandinfo_set_center(self->obj, center);
    }

    Py_RETURN_NONE;
}


static PyMethodDef bandinfo_methods[] = {
    { "set_span", (PyCFunction) bandinfo_set_span, METH_VARARGS, "" },
    { "set_center", (PyCFunction) bandinfo_set_center, METH_VARARGS, "" },
    { NULL }
};

static PyTypeObject bandinfo_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_base = &hiding_type,
    .tp_name = "lv.bandinfo",
    .tp_doc = PyDoc_STR("LVGL band info"),
    .tp_basicsize = sizeof(obj_object_t),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_init = (initproc) bandinfo_init,
    .tp_methods = bandinfo_methods,
};

/* * */

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
    PyType_Ready(&style_type);
    PyType_Ready(&obj_type);
    PyType_Ready(&hiding_type);
    PyType_Ready(&label_type);
    PyType_Ready(&spectrum_type);
    PyType_Ready(&waterfall_type);
    PyType_Ready(&finder_type);
    PyType_Ready(&bandinfo_type);

    PyObject *m = PyModule_Create(&lv_module);

    if (m == NULL) {
        return NULL;
    }

    PyModule_AddObjectRef(m, "style", (PyObject *) &style_type);
    PyModule_AddObjectRef(m, "obj", (PyObject *) &obj_type);
    PyModule_AddObjectRef(m, "hiding", (PyObject *) &hiding_type);
    PyModule_AddObjectRef(m, "label", (PyObject *) &label_type);
    PyModule_AddObjectRef(m, "spectrum", (PyObject *) &spectrum_type);
    PyModule_AddObjectRef(m, "waterfall", (PyObject *) &waterfall_type);
    PyModule_AddObjectRef(m, "finder", (PyObject *) &finder_type);
    PyModule_AddObjectRef(m, "bandinfo", (PyObject *) &bandinfo_type);

    return m;
}

lv_obj_t * python_lv_get_obj(PyObject *obj) {
    if (PyObject_TypeCheck(obj, &obj_type)) {
        obj_object_t *self = (obj_object_t *) obj;

        return self->obj;
    }

    return NULL;
}
