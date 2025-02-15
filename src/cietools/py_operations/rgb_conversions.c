#include <Python.h>
#include "../color_structs.h"
#include "../conversions.h"
#include "rgb_conversions.h"
#define PY_SSIZE_T_CLEAN

//Function to check and extract RGB values from the input
static int RGB_check_and_extract(PyObject* rgb, RGB* rgb_color) {
    if (!PySequence_Check(rgb)) {
        PyErr_SetString(PyExc_TypeError, "Expected a sequence");
        return 0;  // Failure
    }

    if (PySequence_Size(rgb) != 3) {
        PyErr_SetString(PyExc_ValueError, "RGB argument must have exactly 3 elements");
        return 0;  // Failure
    }

    for (char i = 0; i < 3; i++) {
        PyObject* item = PySequence_GetItem(rgb, i);  // Get sequence element

        if (!PyLong_Check(item)) {
            PyErr_SetString(PyExc_TypeError, "RGB elements must be integers");
            return 0;  // Failure
        }

        const long value = PyLong_AsLong(item);  // Convert to long

        if (value < 0 || value > 255) {
            PyErr_SetString(PyExc_ValueError, "RGB elements must be in range [0, 255]");
            return 0;  // Failure
        }

        rgb_color->channels[i] = (unsigned char)value; // Store in RGB struct
    }

    return 1;  // Success
}


PyObject* PyRGB2XYZ(PyObject* self, PyObject* arg) {
    RGB rgb_color;

    if (!RGB_check_and_extract(arg, &rgb_color)) {
        return NULL;  // Error is already set inside the check function
    }

    const XYZ xyz_color = rgb2xyz(&rgb_color);

    PyObject* tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(xyz_color.x));
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(xyz_color.y));
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(xyz_color.z));

    return tuple;
}

PyObject* PyRGB2LAB(PyObject* self, PyObject* arg) {
    RGB rgb_color;

    if (!RGB_check_and_extract(arg, &rgb_color)) {
        return NULL;  // Error is already set inside the check function
    }

    const LAB lab_color = rgb2lab(&rgb_color);

    PyObject* tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(lab_color.l));
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(lab_color.a));
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(lab_color.b));

    return tuple;
}

PyObject* PyRGB2LCh(PyObject* self, PyObject* arg) {
    RGB rgb_color;

    if (!RGB_check_and_extract(arg, &rgb_color)) {
        return NULL;  // Error is already set inside the check function
    }

    const LCh lch_color = rgb2lch(&rgb_color);

    PyObject* tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(lch_color.l));
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(lch_color.c));
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(lch_color.h));

    return tuple;
}



