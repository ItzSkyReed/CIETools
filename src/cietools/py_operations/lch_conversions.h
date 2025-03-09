#ifndef LCH_CONVERSIONS_H
#define LCH_CONVERSIONS_H

PyObject* PyLCh2LAB(PyObject* self, PyObject* arg);
PyObject* PyLCh2XYZ(PyObject* self, PyObject* arg);
PyObject* PyLCh2RGB(PyObject* self, PyObject* arg);
PyObject *PyLCh2HSV(PyObject *self, PyObject *arg);
PyObject *PyLCh2HSL(PyObject *self, PyObject *arg);

#endif //LCH_CONVERSIONS_H
