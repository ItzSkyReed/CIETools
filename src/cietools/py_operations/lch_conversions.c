#include <Python.h>
#include "../color_structs.h"
#include "../conversions.h"
#include "lch_conversions.h"
#include "common.h"
#define PY_SSIZE_T_CLEAN

// Function to check and extract LCh values from the input
static int LCh_check_and_extract(PyObject *lch, LCh *lch_color) {
    if (!PySequence_Check(lch) || PyUnicode_Check(lch)) {
        PyErr_SetString(PyExc_TypeError, "Expected a sequence");
        return 0; // Failure
    }

    if (PySequence_Size(lch) != 3) {
        PyErr_SetString(PyExc_ValueError, "LCh argument must have exactly 3 elements in sequence");
        return 0; // Failure
    }

    if (!get_float_from_sequence(lch, 0, &lch_color->l) ||
    !get_float_from_sequence(lch, 1, &lch_color->c) ||
    !get_float_from_sequence(lch, 2, &lch_color->h)) {
        return 0;
    }


    if (lch_color->l < 0.0 || lch_color->l > 100.0) {
        PyErr_SetString(PyExc_ValueError, "L* element must be in range [0, 100]");
        return 0;
    }

    if (lch_color->c < 0.0 || lch_color->c > 200.0) {
        PyErr_SetString(PyExc_ValueError, "C* element must be in range [0, 200]");
        return 0;
    }

    if (lch_color->h < 0.0 || lch_color->h > 360.0) {
        PyErr_SetString(PyExc_ValueError, "h* element must be in range [0, 360]");
        return 0;
    }

    return 1; // Success
}


PyObject *PyLCh2LAB(PyObject *self, PyObject *arg) {
    LCh LCh_color;

    if (!LCh_check_and_extract(arg, &LCh_color)) {
        return NULL; // Error is already set inside the check function
    }

    const LAB lab_color = lch2lab(&LCh_color);

    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(lab_color.l));
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(lab_color.a));
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(lab_color.b));

    return tuple;
}

PyObject *PyLCh2XYZ(PyObject *self, PyObject *arg) {
    LCh LCh_color;

    if (!LCh_check_and_extract(arg, &LCh_color)) {
        return NULL; // Error is already set inside the check function
    }

    const XYZ xyz_color = lch2xyz(&LCh_color);

    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(xyz_color.x));
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(xyz_color.y));
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(xyz_color.z));

    return tuple;
}

PyObject *PyLCh2RGB(PyObject *self, PyObject *arg) {
    LCh LCh_color;

    if (!LCh_check_and_extract(arg, &LCh_color)) {
        return NULL; // Error is already set inside the check function
    }

    const RGB rgb_color = lch2rgb(&LCh_color);

    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyLong_FromLong(rgb_color.r));
    PyTuple_SetItem(tuple, 1, PyLong_FromLong(rgb_color.g));
    PyTuple_SetItem(tuple, 2, PyLong_FromLong(rgb_color.b));

    return tuple;
}