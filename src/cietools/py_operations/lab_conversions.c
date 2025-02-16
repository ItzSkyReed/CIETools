#include <Python.h>
#include "lab_conversions.h"
#include "../color_structs.h"
#include "../conversions.h"
#define PY_SSIZE_T_CLEAN

// Function to check and extract LCh values from the input
int LAB_check_and_extract(PyObject *lab, LAB *lab_color) {
    if (!PySequence_Check(lab)) {
        PyErr_SetString(PyExc_TypeError, "Expected a sequence");
        return 0; // Failure
    }

    if (PySequence_Size(lab) != 3) {
        PyErr_SetString(PyExc_ValueError, "LAB argument must have exactly 3 elements");
        return 0; // Failure
    }

    for (char i = 0; i < 3; i++) {
        PyObject *item = PySequence_GetItem(lab, i); // Get sequence element

        if (!PyFloat_Check(item)) {
            PyErr_SetString(PyExc_TypeError, "LAB elements must be floats");
            return 0; // Failure
        }
    }

    const double L = PyFloat_AsDouble(PySequence_GetItem(lab, 0));
    if (L < 0.0 || L > 100.0) {
        PyErr_SetString(PyExc_ValueError, "L* element must be in range [0, 100]");
        return 0;
    }

    const double A = PyFloat_AsDouble(PySequence_GetItem(lab, 1));
    if (A < -127.0 || A > 127.0) {
        PyErr_SetString(PyExc_ValueError, "A* element must be in range [-127, 127]");
        return 0;
    }
    const double B = PyFloat_AsDouble(PySequence_GetItem(lab, 2));
    if (B < -127.0 || B > 127.0) {
        PyErr_SetString(PyExc_ValueError, "B* element must be in range [-127, 127]");
        return 0;
    }
    lab_color->l = L;
    lab_color->a = A;
    lab_color->b = B;

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