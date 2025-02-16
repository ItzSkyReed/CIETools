#include <Python.h>
#include "xyz_conversions.h"
#include "../color_structs.h"
#include "../conversions.h"
#include "common.h"

#define PY_SSIZE_T_CLEAN

// Function to check and extract LCh values from the input
static int XYZ_check_and_extract(PyObject *xyz, XYZ *xyz_color) {
    if (!PySequence_Check(xyz)) {
        PyErr_SetString(PyExc_TypeError, "Expected a sequence");
        return 0; // Failure
    }

    if (PySequence_Size(xyz) != 3) {
        PyErr_SetString(PyExc_ValueError, "XYZ argument must have exactly 3 elements");
        return 0; // Failure
    }


    if (!get_float_from_sequence(xyz, 0, &xyz_color->x) ||
        !get_float_from_sequence(xyz, 1, &xyz_color->y) ||
        !get_float_from_sequence(xyz, 2, &xyz_color->z)) {
        return 0;
        }

    if (xyz_color->x < 0.0 || xyz_color->x > 1.0) {
        PyErr_SetString(PyExc_ValueError, "X element must be in range [0, 1]");
        return 0;
    }

    if (xyz_color->y < 0.0 || xyz_color->y > 1.0) {
        PyErr_SetString(PyExc_ValueError, "Y element must be in range [0, 1]");
        return 0;
    }

    if (xyz_color->z < 0.0 || xyz_color->z > 1.0) {
        PyErr_SetString(PyExc_ValueError, "Z element must be in range [0, 1]");
        return 0;
    }

    return 1; // Success
}


PyObject *PyXYZ2LCh(PyObject *self, PyObject *arg) {
    XYZ xyz_color;

    if (!XYZ_check_and_extract(arg, &xyz_color)) {
        return NULL; // Error is already set inside the check function
    }

    const LCh lch_color = xyz2lch(&xyz_color);

    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(lch_color.l));
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(lch_color.c));
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(lch_color.h));

    return tuple;
}

PyObject *PyXYZ2LAB(PyObject *self, PyObject *arg) {
    XYZ xyz_color;

    if (!XYZ_check_and_extract(arg, &xyz_color)) {
        return NULL; // Error is already set inside the check function
    }

    const LAB lab_color = xyz2lab(&xyz_color);

    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(lab_color.l));
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(lab_color.a));
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(lab_color.b));

    return tuple;
}

PyObject *PyXYZ2RGB(PyObject *self, PyObject *arg) {
    XYZ xyz_color;

    if (!XYZ_check_and_extract(arg, &xyz_color)) {
        return NULL; // Error is already set inside the check function
    }

    const RGB rgb_color = xyz2rgb(&xyz_color);

    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyLong_FromLong(rgb_color.r));
    PyTuple_SetItem(tuple, 1, PyLong_FromLong(rgb_color.g));
    PyTuple_SetItem(tuple, 2, PyLong_FromLong(rgb_color.b));

    return tuple;
}