#include <Python.h>
#include "hsl_conversions.h"
#include "../color_structs.h"
#include "../conversions.h"
#include "common.h"
#define PY_SSIZE_T_CLEAN

// Function to check and extract HSV values from the input
int HSL_check_and_extract(PyObject *hsl, HSL *hsl_color) {
    if (!PySequence_Check(hsl) || PyUnicode_Check(hsl)) {
        PyErr_SetString(PyExc_TypeError, "Expected a sequence");
        return 0; // Failure
    }

    if (PySequence_Size(hsl) != 3) {
        PyErr_SetString(PyExc_ValueError, "HSL argument must have exactly 3 elements in sequence");
        return 0; // Failure
    }

    if (!get_float_from_sequence(hsl, 0, &hsl_color->h) ||
    !get_float_from_sequence(hsl, 1, &hsl_color->s) ||
    !get_float_from_sequence(hsl, 2, &hsl_color->l)) {
        return 0;
    }

    if (hsl_color->h < 0.0 || hsl_color->h > 360.0) {
        PyErr_SetString(PyExc_ValueError, "H element must be in range [0, 360]");
        return 0;
    }

    if (hsl_color->s < 0.0 || hsl_color->s > 1.0) {
        PyErr_SetString(PyExc_ValueError, "S element must be in range [0, 1]");
        return 0;
    }

    if (hsl_color->l < 0.0 || hsl_color->l > 1.0) {
        PyErr_SetString(PyExc_ValueError, "L element must be in range [0, 1]");
        return 0;
    }

    return 1; // Success
}

PyObject *PyHSL2HSV(PyObject *self, PyObject *arg) {
    HSL HSL_color;

    if (!HSL_check_and_extract(arg, &HSL_color)) {
        return NULL; // Error is already set inside the check function
    }

    const HSV hsv_color = hsl2hsv(&HSL_color);

    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(hsv_color.h));
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(hsv_color.s));
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(hsv_color.v));

    return tuple;
}

PyObject *PyHSL2XYZ(PyObject *self, PyObject *arg) {
    HSL HSL_color;

    if (!HSL_check_and_extract(arg, &HSL_color)) {
        return NULL; // Error is already set inside the check function
    }

    const XYZ xyz_color = hsl2xyz(&HSL_color);

    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(xyz_color.x));
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(xyz_color.y));
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(xyz_color.z));

    return tuple;
}

PyObject *PyHSL2LAB(PyObject *self, PyObject *arg) {
    HSL HSL_color;

    if (!HSL_check_and_extract(arg, &HSL_color)) {
        return NULL; // Error is already set inside the check function
    }

    const LAB lab_color = hsl2lab(&HSL_color);

    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(lab_color.l));
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(lab_color.a));
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(lab_color.b));

    return tuple;
}

PyObject *PyHSL2LCh(PyObject *self, PyObject *arg) {
    HSL HSL_color;

    if (!HSL_check_and_extract(arg, &HSL_color)) {
        return NULL; // Error is already set inside the check function
    }

    const LCh lch_color = hsl2lch(&HSL_color);

    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(lch_color.l));
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(lch_color.c));
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(lch_color.h));

    return tuple;
}

PyObject *PyHSL2RGB(PyObject *self, PyObject *arg) {
    HSL HSL_color;

    if (!HSL_check_and_extract(arg, &HSL_color)) {
        return NULL; // Error is already set inside the check function
    }

    const RGB rgb_color = hsl2rgb(&HSL_color);

    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyLong_FromLong(rgb_color.r));
    PyTuple_SetItem(tuple, 1, PyLong_FromLong(rgb_color.g));
    PyTuple_SetItem(tuple, 2, PyLong_FromLong(rgb_color.b));
    return tuple;
}