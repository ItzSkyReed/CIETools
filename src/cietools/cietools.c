#include <Python.h>
#include "py_operations/rgb_conversions.h"
#include "py_operations/xyz_conversions.h"
#include "py_operations/lab_conversions.h"
#include "py_operations/lch_conversions.h"
#include "py_operations/hsv_conversions.h"
#include "py_operations/hsl_conversions.h"
#include "py_operations/oklab_conversions.h"
#include "py_operations/oklch_conversions.h"
#include "py_operations/delta_e.h"
#include "py_operations/color_utils.h"
#define PY_SSIZE_T_CLEAN

static PyMethodDef CieToolsMethods[] = {
    {
        "rgb2lab",
        PyRGB2LAB,
        METH_O,
        "Convert RGB color to CIE LAB"
    },
    {
        "rgb2lch",
        PyRGB2LCh,
        METH_O,
        "Convert RGB color to CIE LCh"
    },
    {
        "rgb2xyz",
        PyRGB2XYZ,
        METH_O,
        "Convert RGB color to CIE XYZ"
    },
    {
        "rgb2hsl",
        PyRGB2HSL,
        METH_O,
        "Convert RGB color to HSL"
    },
    {
        "rgb2hsv",
        PyRGB2HSV,
        METH_O,
        "Convert RGB color to HSV"
    },
    {
        "rgb2oklab",
        PyRGB2OKlab,
        METH_O,
        "Convert RGB color to OKlab"
    },
    {
        "rgb2oklch",
        PyRGB2OKlch,
        METH_O,
        "Convert RGB color to OKlab"
    },
    {
        "xyz2lab",
        PyXYZ2LAB,
        METH_O,
        "Convert XYZ color to CIE LAB"
    },
    {
        "xyz2lch",
        PyXYZ2LCh,
        METH_O,
        "Convert XYZ color to CIE LCh"
    },
    {
        "xyz2rgb",
        PyXYZ2RGB,
        METH_O,
        "Convert XYZ color to RGB"
    },
    {
        "xyz2hsl",
        PyXYZ2HSL,
        METH_O,
        "Convert XYZ color to HSL"
    },
    {
        "xyz2hsv",
        PyXYZ2HSV,
        METH_O,
        "Convert XYZ color to HSV"
    },
    {
        "lab2lch",
        PyLAB2LCh,
        METH_O,
        "Convert LAB color to CIE LCh"
    },
    {
        "lab2xyz",
        PyLAB2XYZ,
        METH_O,
        "Convert LAB color to CIE LCh"
    },
    {
        "lab2rgb",
        PyLAB2RGB,
        METH_O,
        "Convert LAB color to RGB"
    },
    {
        "lab2hsl",
        PyLAB2HSL,
        METH_O,
        "Convert LAB color to HSL"
    },
    {
        "lab2hsv",
        PyLAB2HSV,
        METH_O,
        "Convert LAB color to HSV"
    },
    {
        "lch2lab",
        PyLCh2LAB,
        METH_O,
        "Convert LCh color to CIE LAB"
    },
    {
        "lch2xyz",
        PyLCh2XYZ,
        METH_O,
        "Convert LCh color to CIE XYZ"
    },
    {
        "lch2rgb",
        PyLCh2RGB,
        METH_O,
        "Convert LCh color to RGB"
    },
    {
        "lch2hsl",
        PyLCh2HSL,
        METH_O,
        "Convert LCh color to HSL"
    },
    {
        "lch2hsv",
        PyLCh2HSV,
        METH_O,
        "Convert LCh color to HSV"
    },
    {
        "hsv2rgb",
        PyHSV2RGB,
        METH_O,
        "Convert HSV color to RGB"
    },
    {
        "hsv2hsl",
        PyHSV2HSL,
        METH_O,
        "Convert HSV color to HSL"
    },
    {
        "hsv2xyz",
        PyHSV2XYZ,
        METH_O,
        "Convert HSV color to XYZ"
    },
    {
        "hsv2lab",
        PyHSV2LAB,
        METH_O,
        "Convert HSV color to LAB"
    },
    {
        "hsv2lch",
        PyHSV2LCh,
        METH_O,
        "Convert HSV color to LCh"
    },
    {
        "hsl2rgb",
        PyHSL2RGB,
        METH_O,
        "Convert HSL color to RGB"
    },
    {
        "hsl2xyz",
        PyHSL2XYZ,
        METH_O,
        "Convert HSL color to XYZ"
    },
    {
        "hsl2lab",
        PyHSL2LAB,
        METH_O,
        "Convert HSL color to LAB"
    },
    {
        "hsl2lch",
        PyHSL2LCh,
        METH_O,
        "Convert HSL color to LCh"
    },
    {
        "hsl2hsv",
        PyHSL2HSV,
        METH_O,
        "Convert HSL color to HSV"
    },
    {
        "oklab2rgb",
        PyOKlab2RGB,
        METH_O,
        "Convert OKlab color to RGB"
    },
    {
        "oklab2oklch",
        PyOKlab2OKlch,
        METH_O,
        "Convert OKlab color to OKlch"
    },
    {
        "oklch2oklab",
        PyOKlch2OKlab,
        METH_O,
        "Convert OKlch color to RGB"
    },
    {
        "oklch2rgb",
        PyOKlch2RGB,
        METH_O,
        "Convert OKlch color to RGB"
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
    {
        "deltaE_OK",
        PyDeltaE_OK,
        METH_VARARGS,
        "Computes the OKLab color difference between two OKLab color values."
    },
    {
        "deltaE_OK2",
        PyDeltaE_OK2,
        METH_VARARGS,
        "Computes an alternative OKLab color difference metric between two OKLab color values."
    },

    {
        "linear_gradient",
        (PyCFunction)PyLinearGradient,
        METH_VARARGS | METH_KEYWORDS,
        "Computes a linear gradient between two OKlab colors."
    },
    {
        "cosine_gradient",
        (PyCFunction)PyCosineGradient,
        METH_VARARGS | METH_KEYWORDS,
        "Computes a cosine gradient between two OKlab colors."
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
