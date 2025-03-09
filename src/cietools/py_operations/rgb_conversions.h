#ifndef RGB_CONVERSIONS_H
#define RGB_CONVERSIONS_H

PyObject* PyRGB2XYZ(PyObject* self, PyObject* arg);
PyObject* PyRGB2LAB(PyObject* self, PyObject* arg);
PyObject* PyRGB2LCh(PyObject* self, PyObject* arg);
PyObject* PyRGB2HSV(PyObject* self, PyObject* arg);
PyObject* PyRGB2HSL(PyObject* self, PyObject* arg);
PyObject* PyRGB2OKlab(PyObject* self, PyObject* arg);
PyObject* PyRGB2OKlch(PyObject* self, PyObject* arg);

#endif //RGB_CONVERSIONS_H
