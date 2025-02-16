#include <Python.h>
#include "delta_e.h"
#include "lab_conversions.h"
#include "../color_difference.h"
#define PY_SSIZE_T_CLEAN

static int parse_lab_args(PyObject *args, LAB *lab1, LAB *lab2) {
    PyObject *arg1, *arg2;

    if (PyTuple_Size(args) != 2) {
        PyErr_SetString(PyExc_TypeError, "Expected exactly two arguments.");
        return 0;
    }

    if (!PyArg_ParseTuple(args, "OO", &arg1, &arg2)) {
        return 0;
    }

    if (!LAB_check_and_extract(arg1, lab1)) {
        return 0;
    }
    if (!LAB_check_and_extract(arg2, lab2)) {
        return 0;
    }

    return 1;
}

// Function to compute Delta E 1976
PyObject* PyDeltaE76(PyObject* self, PyObject* args) {
    LAB lab1, lab2;

    if (!parse_lab_args(args, &lab1, &lab2)) {
        return NULL;
    }

    return PyFloat_FromDouble(delta_e_cie_76(&lab1, &lab2));
}

// Function to compute Delta E 1994
PyObject* PyDeltaE94(PyObject* self, PyObject* args) {
    LAB lab1, lab2;

    if (!parse_lab_args(args, &lab1, &lab2)) {
        return NULL;
    }

    return PyFloat_FromDouble(delta_e_cie_94(&lab1, &lab2));
}

// Function to compute Delta E CMC
PyObject* PyDeltaE_CMC(PyObject* self, PyObject* args) {
    LAB lab1, lab2;

    if (!parse_lab_args(args, &lab1, &lab2)) {
        return NULL;
    }

    return PyFloat_FromDouble(delta_e_cmc(&lab1, &lab2));
}

// Function to compute Delta E 2000
PyObject* PyDeltaE2000(PyObject* self, PyObject* args) {
    LAB lab1, lab2;

    if (!parse_lab_args(args, &lab1, &lab2)) {
        return NULL;
    }

    return PyFloat_FromDouble(delta_e_ciede_2000(&lab1, &lab2));
}