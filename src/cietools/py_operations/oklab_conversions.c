#include <Python.h>
#include "oklab_conversions.h"
#include "../color_structs.h"
#include "../conversions.h"
#include "common.h"
#define PY_SSIZE_T_CLEAN

// Function to check and extract LAB values from the input
int OKlab_check_and_extract(PyObject *lab, OKlab *oklab_color) {
    if (!PySequence_Check(lab) || PyUnicode_Check(lab)) {
        PyErr_SetString(PyExc_TypeError, "Expected a sequence");
        return 0; // Failure
    }

    if (PySequence_Size(lab) != 3) {
        PyErr_SetString(PyExc_ValueError, "OKlab argument must have exactly 3 elements in sequence");
        return 0; // Failure
    }

    if (!get_float_from_sequence(lab, 0, &oklab_color->l) ||
    !get_float_from_sequence(lab, 1, &oklab_color->a) ||
    !get_float_from_sequence(lab, 2, &oklab_color->b)) {
        return 0;
    }

    if (oklab_color->l < 0.0 || oklab_color->l > 1.0) {
        PyErr_SetString(PyExc_ValueError, "L* element must be in range [0, 1]");
        return 0;
    }

    if (oklab_color->a < -0.5 || oklab_color->a > 0.5) {
        PyErr_SetString(PyExc_ValueError, "A* element must be in range [-0.5, 0.5]");
        return 0;
    }

    if (oklab_color->b < -0.5 || oklab_color->b > 0.5) {
        PyErr_SetString(PyExc_ValueError, "B* element must be in range [-0.5, 0.5]");
        return 0;
    }

    return 1; // Success
}



PyObject *PyOKlab2RGB(PyObject *self, PyObject *arg) {
    OKlab OKlab_color;

    if (!OKlab_check_and_extract(arg, &OKlab_color)) {
        return NULL; // Error is already set inside the check function
    }

    const RGB rgb_color = oklab2rgb(&OKlab_color);

    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyLong_FromLong(rgb_color.r));
    PyTuple_SetItem(tuple, 1, PyLong_FromLong(rgb_color.g));
    PyTuple_SetItem(tuple, 2, PyLong_FromLong(rgb_color.b));

    return tuple;
}

PyObject *PyOKlab2OKlch(PyObject *self, PyObject *arg) {
    OKlab OKlab_color;

    if (!OKlab_check_and_extract(arg, &OKlab_color)) {
        return NULL; // Error is already set inside the check function
    }

    const OKlch oklch_color = oklab2oklch(&OKlab_color);

    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(oklch_color.l));
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(oklch_color.c));
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(oklch_color.h));

    return tuple;
}