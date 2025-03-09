#ifndef CONVERSIONS_H
#define CONVERSIONS_H
#include "color_structs.h"
#include  <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// rgb2<colorspace>
XYZ rgb2xyz(const RGB *rgb);
LAB rgb2lab(const RGB *rgb);
LCh rgb2lch(const RGB *rgb);
HSV rgb2hsv(const RGB *rgb);
HSL rgb2hsl(const RGB *rgb);
OKlab rgb2oklab(const RGB *rgb);
OKlch rgb2oklch(const RGB *rgb);

// lab2<colorspace>
RGB lab2rgb(const LAB *lab);
XYZ lab2xyz(const LAB *lab);
LCh lab2lch(const LAB *lab);
HSV lab2hsv(const LAB *lab);
HSL lab2hsl(const LAB *lab);

// xyz2<colorspace>
RGB xyz2rgb(const XYZ *xyz);
LAB xyz2lab(const XYZ *xyz);
LCh xyz2lch(const XYZ *xyz);
HSV xyz2hsv(const XYZ *xyz);
HSL xyz2hsl(const XYZ *xyz);

// lch2<colorspace>
RGB lch2rgb(const LCh *lch);
XYZ lch2xyz(const LCh *lch);
LAB lch2lab(const LCh *lch);
HSV lch2hsv(const LCh *lch);
HSL lch2hsl(const LCh *lch);

// hsv2<colorspace>
RGB hsv2rgb(const HSV *hsv);
XYZ hsv2xyz(const HSV *hsv);
LAB hsv2lab(const HSV *hsv);
LCh hsv2lch(const HSV *hsv);
HSL hsv2hsl(const HSV *hsv);

// hsl2<colorspace>
RGB hsl2rgb(const HSL *hsl);
XYZ hsl2xyz(const HSL *hsl);
LAB hsl2lab(const HSL *hsl);
LCh hsl2lch(const HSL *hsl);
HSV hsl2hsv(const HSL *hsl);

// OKlab2<rgb/OKlch>
OKlch oklab2oklch(const OKlab *oklab);
RGB oklab2rgb(const OKlab *oklab);

// Oklch2<rgb/OKlab>
OKlab oklch2oklab(const OKlch *oklch);
RGB oklch2rgb(const OKlch *oklch);

#endif //CONVERSIONS_H
