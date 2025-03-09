#ifndef HSV_CONVERSIONS_H
#define HSV_CONVERSIONS_H

PyObject *PyHSV2RGB(PyObject *self, PyObject *arg);
PyObject *PyHSV2LCh(PyObject *self, PyObject *arg);
PyObject *PyHSV2LAB(PyObject *self, PyObject *arg);
PyObject *PyHSV2XYZ(PyObject *self, PyObject *arg);
PyObject *PyHSV2HSL(PyObject *self, PyObject *arg);

#endif //HSV_CONVERSIONS_H
