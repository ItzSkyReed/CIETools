#include <Python.h>
#include "../color_structs.h"
#include "oklab_conversions.h"
#include "color_utils.h"
#include "../gradients.h"

static int extract_gradient_args(PyObject *args, PyObject *kwargs, OKlab *oklab1, OKlab *oklab2, int *steps) {
    PyObject *sequence1;
    PyObject *sequence2;

    static char *kwlist[] = {"start_oklab", "end_oklab", "steps", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO|i", kwlist,
                                     &sequence1, &sequence2, steps)) {
        return 0;
    }

    if (!PySequence_Check(sequence1) || !PySequence_Check(sequence2)) {
        PyErr_SetString(PyExc_TypeError, "First two arguments must be sequences");
        return 0;
    }

    if (!OKlab_check_and_extract(sequence1, oklab1) || !OKlab_check_and_extract(sequence2, oklab2)) {
        return 0;
    }

    if (*steps < 2) {
        PyErr_SetString(PyExc_ValueError, "steps argument must be greater than 2");
        return 0;
    }

    return 1;
}

// Helper function to create a gradient list
static PyObject *create_gradient_list(OKlab *gradient_array, const int steps) {
    PyObject *list = PyList_New(steps);
    if (!list) {
        free(gradient_array);
        return NULL;
    }

    for (int i = 0; i < steps; ++i) {
        PyObject *tuple = PyTuple_New(3);
        if (!tuple) {
            Py_DECREF(list);
            free(gradient_array);
            return NULL;
        }

        PyTuple_SET_ITEM(tuple, 0, PyFloat_FromDouble(gradient_array[i].l));
        PyTuple_SET_ITEM(tuple, 1, PyFloat_FromDouble(gradient_array[i].a));
        PyTuple_SET_ITEM(tuple, 2, PyFloat_FromDouble(gradient_array[i].b));

        PyList_SET_ITEM(list, i, tuple);
    }

    free(gradient_array);
    return list;
}

// Function to compute linear gradient for OKlab colors
PyObject *PyLinearGradient(PyObject *self, PyObject *args, PyObject *kwargs) {
    OKlab oklab1;
    OKlab oklab2;
    int steps = 100; // Do not make it const!

    if (!extract_gradient_args(args, kwargs, &oklab1, &oklab2, &steps)) {
        return NULL; // Error is already set inside the check function
    }

    OKlab *gradient_array = malloc(steps * sizeof(OKlab));
    if (gradient_array == NULL) {
        PyErr_SetString(PyExc_OSError, "Impossible to allocate memory for an array");
        return NULL;
    }

    oklab_linear_gradient(&oklab1, &oklab2, gradient_array, steps);
    return create_gradient_list(gradient_array, steps);
}

// Function to compute cosine gradient for OKlab colors
PyObject *PyCosineGradient(PyObject *self, PyObject *args, PyObject *kwargs) {
    OKlab oklab1;
    OKlab oklab2;
    int steps = 100; // Do not make it const!

    if (!extract_gradient_args(args, kwargs, &oklab1, &oklab2, &steps)) {
        return NULL; // Error is already set inside the check function
    }

    OKlab *gradient_array = malloc(steps * sizeof(OKlab));
    if (gradient_array == NULL) {
        PyErr_SetString(PyExc_OSError, "Impossible to allocate memory for an array");
        return NULL;
    }

    oklab_cosine_gradient(&oklab1, &oklab2, gradient_array, steps);
    return create_gradient_list(gradient_array, steps);
}
