#ifndef HSL_CONVERSIONS_H
#define HSL_CONVERSIONS_H

PyObject *PyHSL2RGB(PyObject *self, PyObject *arg);
PyObject *PyHSL2LCh(PyObject *self, PyObject *arg);
PyObject *PyHSL2LAB(PyObject *self, PyObject *arg);
PyObject *PyHSL2XYZ(PyObject *self, PyObject *arg);
PyObject *PyHSL2HSV(PyObject *self, PyObject *arg);

#endif //HSL_CONVERSIONS_H
