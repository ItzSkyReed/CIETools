#ifndef OKLAB_CONVERSIONS_H
#define OKLAB_CONVERSIONS_H
#include "../color_structs.h"

int OKlab_check_and_extract(PyObject *lab, OKlab *oklab_color);

PyObject *PyOKlab2RGB(PyObject *self, PyObject *arg);
PyObject *PyOKlab2OKlch(PyObject *self, PyObject *arg);

#endif //OKLAB_CONVERSIONS_H
