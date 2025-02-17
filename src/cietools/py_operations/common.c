#include <Python.h>

int get_float_from_sequence(PyObject *seq, const Py_ssize_t index, double *out_value) {
    PyObject *item = PySequence_GetItem(seq, index);
    if (!item) {
        return 0;  // Уже установлена ошибка (например, IndexError)
    }

    PyObject *float_item = PyNumber_Float(item);
    Py_DECREF(item);

    if (!float_item) {
        return 0;
    }

    *out_value = PyFloat_AsDouble(float_item);
    Py_DECREF(float_item);

    return 1;
}
