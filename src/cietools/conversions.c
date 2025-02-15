#include "color_structs.h"
#include "conversions.h"
#include <math.h>

static double gamma_correction(const double c) {
    if (c <= 0.04045)
        return c / 12.92;
    return pow((c + 0.055) / 1.055, 2.4);
}

static double inverse_gamma_correction(const double c) {
    return c <= 0.0031308 ? 12.92 * c : 1.055 * pow(c, 1.0 / 2.4) - 0.055;
}

// Function to apply the CIE 1931 standard transformation to the XYZ values
// This function is part of the conversion from XYZ to LAB
static double F(const double t) {
    if (t > 0.008856)
        return pow(t, 1.0 / 3.0);  // If t is greater than 0.008856, use cube root transformation
    return (903.3 * t + 16.0) / 116.0;  // Otherwise, apply the linear transformation
}

static double inverse_F(const double t) {
    return t > 6.0 / 29.0 ? pow(t, 3) : (t - 16.0 / 116.0) / 7.787;
}

static unsigned char clamp2rgb(double value) {
    if (value < 0.0) value = 0.0;
    if (value > 1.0) value = 1.0;
    return (unsigned char)round(value * 255.0);
}

RGB lab2rgb(const LAB *lab) {
    const XYZ xyz = lab2xyz(lab);
    return xyz2rgb(&xyz);
}

XYZ lab2xyz(const LAB *lab) {
    const double fy = (lab->l + 16.0) / 116.0;
    const double fx = fy + lab->a / 500.0;
    const double fz = fy - lab->b / 200.0;

    const double x = inverse_F(fx) * 0.95047;
    const double y = inverse_F(fy) * 1.00000;
    const double z = inverse_F(fz) * 1.08883;

    return (XYZ){{x, y, z}};
}

LCh lab2lch(const LAB *lab) {
    const double C = sqrt(pow(lab->a, 2) + pow(lab->b, 2));
    const double h = atan(lab->b/lab->a);
    return (LCh){{lab->l, C, h}};
}

XYZ rgb2xyz(const RGB *rgb) {
    // Apply gamma correction to each RGB component (normalize to [0, 1] ranges)
    const double r = gamma_correction(rgb->r / 255.0);  // Red component
    const double g = gamma_correction(rgb->g / 255.0);  // Green component
    const double b = gamma_correction(rgb->b / 255.0);  // Blue component

    // Linear transformation from RGB to XYZ color space using standard sRGB-to-XYZ matrix
    const double x = r * 0.4124 + g * 0.3576 + b * 0.1805;
    const double y = r * 0.2126 + g * 0.7152 + b * 0.0722;
    const double z = r * 0.0193 + g * 0.1192 + b * 0.9505;

    // Return the XYZ values as an XYZ struct
    return (XYZ){{x, y, z}};
}

LAB rgb2lab(const RGB *rgb) {
    const XYZ xyz = rgb2xyz(rgb);
    return xyz2lab(&xyz);
}

LCh rgb2lch(const RGB *rgb) {
    const LAB lab = rgb2lab(rgb);
    return lab2lch(&lab);
}

RGB xyz2rgb(const XYZ *xyz) {
    //XYZ -> linear RGB (sRGB)
    double r = xyz->x *  3.2406 + xyz->y * -1.5372 + xyz->z * -0.4986;
    double g = xyz->x * -0.9689 + xyz->y *  1.8758 + xyz->z *  0.0415;
    double b = xyz->x *  0.0557 + xyz->y * -0.2040 + xyz->z *  1.0570;

    r = inverse_gamma_correction(r);
    g = inverse_gamma_correction(g);
    b = inverse_gamma_correction(b);

    return (RGB){clamp2rgb(r), clamp2rgb(g), clamp2rgb(b)};
}

// The XYZ values are normalized to the D65 illuminant and then converted to LAB
LAB xyz2lab(const XYZ *xyz) {
    // Normalize XYZ values by the D65 reference white
    const double x = xyz->x / 0.95047;
    const double y = xyz->y / 1.00000;
    const double z = xyz->z / 1.08883;

    const double l = 116 * F(y) - 16;  // lightness
    const double a = 500 * (F(x) - F(y));  // green to red
    const double b = 200 * (F(y) - F(z));  // blue to yellow

    return (LAB){{l, a, b}};
}


LCh xyz2lch(const XYZ *xyz) {
    const LAB lab = xyz2lab(xyz);
    return lab2lch(&lab);
}

RGB lch2rgb(const LCh *lch) {
    const XYZ xyz = lch2xyz(lch);
    return xyz2rgb(&xyz);
}

XYZ lch2xyz(const LCh *lch) {
    const LAB lab = lch2lab(lch);
    return lab2xyz(&lab);
}

LAB lch2lab(const LCh *lch) {
    const double a = lch->c * cos(lch->h);
    const double b = lch->c * sin(lch->h);
    return (LAB){{lch->l, a, b}};
}
