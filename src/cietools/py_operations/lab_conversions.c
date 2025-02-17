#include <Python.h>
#include "lab_conversions.h"
#include "../color_structs.h"
#include "../conversions.h"
#include "common.h"
#define PY_SSIZE_T_CLEAN

// Function to check and extract LCh values from the input
int LAB_check_and_extract(PyObject *lab, LAB *lab_color) {
    if (!PySequence_Check(lab) || PyUnicode_Check(lab)) {
        PyErr_SetString(PyExc_TypeError, "Expected a sequence");
        return 0; // Failure
    }

    if (PySequence_Size(lab) != 3) {
        PyErr_SetString(PyExc_ValueError, "LAB argument must have exactly 3 elements in sequence");
        return 0; // Failure
    }

    if (!get_float_from_sequence(lab, 0, &lab_color->l) ||
    !get_float_from_sequence(lab, 1, &lab_color->a) ||
    !get_float_from_sequence(lab, 2, &lab_color->b)) {
        return 0;
    }

    if (lab_color->l < 0.0 || lab_color->l > 100.0) {
        PyErr_SetString(PyExc_ValueError, "L* element must be in range [0, 100]");
        return 0;
    }

    if (lab_color->a < -127.0 || lab_color->a > 127.0) {
        PyErr_SetString(PyExc_ValueError, "A* element must be in range [-127, 127]");
        return 0;
    }

    if (lab_color->b < -127.0 || lab_color->b > 127.0) {
        PyErr_SetString(PyExc_ValueError, "B* element must be in range [-127, 127]");
        return 0;
    }

    return 1; // Success
}


PyObject *PyLAB2LCh(PyObject *self, PyObject *arg) {
    LAB LAB_color;

    if (!LAB_check_and_extract(arg, &LAB_color)) {
        return NULL; // Error is already set inside the check function
    }

    const LCh lch_color = lab2lch(&LAB_color);

    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(lch_color.l));
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(lch_color.c));
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(lch_color.h));

    return tuple;
}

PyObject *PyLAB2XYZ(PyObject *self, PyObject *arg) {
    LAB LAB_color;

    if (!LAB_check_and_extract(arg, &LAB_color)) {
        return NULL; // Error is already set inside the check function
    }

    const XYZ xyz_color = lab2xyz(&LAB_color);

    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(xyz_color.x));
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(xyz_color.y));
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(xyz_color.z));

    return tuple;
}

PyObject *PyLAB2RGB(PyObject *self, PyObject *arg) {
    LAB LAB_color;

    if (!LAB_check_and_extract(arg, &LAB_color)) {
        return NULL; // Error is already set inside the check function
    }

    const RGB rgb_color = lab2rgb(&LAB_color);

    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyLong_FromLong(rgb_color.r));
    PyTuple_SetItem(tuple, 1, PyLong_FromLong(rgb_color.g));
    PyTuple_SetItem(tuple, 2, PyLong_FromLong(rgb_color.b));

    return tuple;
}