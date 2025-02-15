#pragma once
#ifndef CONVERSIONS_H
#define CONVERSIONS_H
#include "color_structs.h"
static double gamma_correction(double c);
static double F(double t);

// rgb2<colorspace>
XYZ rgb2xyz(const RGB *rgb);
LAB rgb2lab(const RGB *rgb);
LCh rgb2lch(const RGB *rgb);

// lab2<colorspace>
XYZ lab2xyz(const LAB *lab);
LCh lab2lch(const LAB *lab);
RGB lab2rgb(const LAB *lab);

// xyz2<colorspace>
RGB xyz2rgb(const XYZ *xyz);
LAB xyz2lab(const XYZ *xyz);
LCh xyz2lch(const XYZ *xyz);

// lch2<colorspace>
RGB lch2rgb(const LCh *lch);
XYZ lch2xyz(const LCh *lch);
LAB lch2lab(const LCh *lch);

#endif //CONVERSIONS_H
