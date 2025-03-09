#ifndef LAB_CONVERSIONS_H
#define LAB_CONVERSIONS_H
#include "../color_structs.h"
int LAB_check_and_extract(PyObject *lab, LAB *lab_color);

PyObject* PyLAB2LCh(PyObject* self, PyObject* arg);
PyObject* PyLAB2XYZ(PyObject* self, PyObject* arg);
PyObject* PyLAB2RGB(PyObject* self, PyObject* arg);
PyObject* PyLAB2HSL(PyObject* self, PyObject* arg);
PyObject* PyLAB2HSV(PyObject* self, PyObject* arg);


#endif //LAB_CONVERSIONS_H
