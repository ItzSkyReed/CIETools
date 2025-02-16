#include <Python.h>
#include "py_operations/rgb_conversions.h"
#include "py_operations/xyz_conversions.h"
#include "py_operations/lab_conversions.h"
#include "py_operations/lch_conversions.h"
#include "py_operations/delta_e.h"
#define PY_SSIZE_T_CLEAN

static PyMethodDef CieToolsMethods[] = {
    {
        "rgb2lab",
        PyRGB2LAB,
        METH_O,
        "Convert RGB color (tuple[int, int, int] to CIE LAB"
    },
    {
        "rgb2lch",
        PyRGB2LCh,
        METH_O,
        "Convert RGB color (tuple[int, int, int] to CIE LCh"
    },
    {
        "rgb2xyz",
        PyRGB2XYZ,
        METH_O,
        "Convert RGB color (tuple[int, int, int] to CIE XYZ"
    },
    {
        "xyz2lab",
        PyXYZ2LAB,
        METH_O,
        "Convert XYZ color (tuple[float, float, float] to CIE LAB"
    },
    {
        "xyz2lch",
        PyXYZ2LCh,
        METH_O,
        "Convert XYZ color (tuple[float, float, float] to CIE LCh"
    },
    {
        "xyz2rgb",
        PyXYZ2RGB,
        METH_O,
        "Convert XYZ color (tuple[float, float, float] to RGB"
    },
    {
        "lab2lch",
        PyLAB2LCh,
        METH_O,
        "Convert LAB color (tuple[float, float, float] to CIE LCh"
    },
    {
        "lab2xyz",
        PyLAB2XYZ,
        METH_O,
        "Convert LAB color (tuple[float, float, float] to CIE LCh"
    },
    {
        "lab2rgb",
        PyLAB2RGB,
        METH_O,
        "Convert LAB color (tuple[float, float, float] to RGB"
    },
    {
        "lch2lab",
        PyLCh2LAB,
        METH_O,
        "Convert LCh color (tuple[float, float, float] to CIE LAB"
    },
    {
        "lch2xyz",
        PyLCh2XYZ,
        METH_O,
        "Convert LCh color (tuple[float, float, float] to CIE XYZ"
    },
    {
        "lch2rgb",
        PyLCh2RGB,
        METH_O,
        "Convert LCh color (tuple[float, float, float] to RGB"
    },
    {
        "deltaE76",
        PyDeltaE76,
        METH_VARARGS,
        "Computes the CIE76 color difference (E*76) between two LAB color values. Least accurate."
    },
    {
        "deltaE94",
        PyDeltaE94,
        METH_VARARGS,
        "Computes the CIE94 color difference (E*94) between two LAB color values."
    },
    {
        "deltaE2000",
        PyDeltaE2000,
        METH_VARARGS,
        "Computes the CIE2000 color difference (E*2000) between two LAB color values. Most Accurate"
    },
    {
        "deltaE_CMC",
        PyDeltaE_CMC,
        METH_VARARGS,
        "Computes the CIE_CMC color difference ((CMC l:c)) between two LAB color values."
    },
    {NULL, NULL, 0, NULL} // END
};

static PyModuleDef cietools_c_ext = {
    PyModuleDef_HEAD_INIT,
    "_cietools_c_ext",
    "Library to work with CIE color spaces",
    -1,
    CieToolsMethods
};

PyMODINIT_FUNC PyInit__cietools_c_ext(void) {
    return PyModule_Create(&cietools_c_ext);
}