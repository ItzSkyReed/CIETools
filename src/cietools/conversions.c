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
        return cbrt(t); // If t is greater than 0.008856, use cube root transformation
    return (903.3 * t + 16.0) / 116.0; // Otherwise, apply the linear transformation
}

static double inverse_F(const double t) {
    return t > 6.0 / 29.0 ? t * t * t : (t - 16.0 / 116.0) / 7.787;
}

static unsigned char clamp2rgb(double value) {
    if (value < 0.0) value = 0.0;
    if (value > 1.0) value = 1.0;
    return (unsigned char) round(value * 255.0);
}

static double hue2rgb(const double p, const double q, double t) {
    if (t < 0.0) t += 1;
    if (t > 1.0) t -= 1;
    if (t < 1.0 / 6.0) return p + (q - p) * 6.0 * t;
    if (t < 1.0 / 2.0) return q;
    if (t < 2.0 / 3.0) return p + (q - p) * (2.0 / 3.0 - t) * 6.0;
    return p;
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
    const double C = hypot(lab->a, lab->b);
    const double h = atan2(lab->b, lab->a) * (180.0 / M_PI);
    return (LCh){{lab->l, C, h < 0 ? h + 360.0 : h}};
}

HSV lab2hsv(const LAB *lab) {
    const RGB rgb = lab2rgb(lab);
    return rgb2hsv(&rgb);
}

HSL lab2hsl(const LAB *lab) {
    const RGB rgb = lab2rgb(lab);
    return rgb2hsl(&rgb);
}

XYZ rgb2xyz(const RGB *rgb) {
    // Apply gamma correction to each RGB component (normalize to [0, 1] ranges)
    const double r = gamma_correction(rgb->r / 255.0); // Red component
    const double g = gamma_correction(rgb->g / 255.0); // Green component
    const double b = gamma_correction(rgb->b / 255.0); // Blue component

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

HSV rgb2hsv(const RGB *rgb) {
    const double r = (double) rgb->r / 255.0, g = (double) rgb->g / 255.0, b = (double) rgb->b / 255.0;
    double min, max;

    // Finding min/max of r,g,b
    if (r > g) {
        if (r > b) {
            max = r;
            min = g < b ? g : b;
        } else {
            max = b;
            min = g;
        }
    } else {
        if (g > b) {
            max = g;
            min = r < b ? r : b;
        } else {
            max = b;
            min = r;
        }
    }

    const double v = max;
    const double d = min - max;
    const double s = max == 0.0 ? 0.0 : d / max;

    if (max == min) {
        return (HSV){{0.0, s, v}};
    }

    double h;
    if (max == r) {
        h = (g - b) / d + (g < b ? 6.0 : 0.0);
    } else if (max == g) {
        h = (b - r) / d + 2.0;
    } else {
        h = (r - g) / d + 4.0;
    }

    h /= 6.0;
    return (HSV){{h, s, v}};
}

HSL rgb2hsl(const RGB *rgb) {
    const double r = (double) rgb->r / 255.0, g = (double) rgb->g / 255.0, b = (double) rgb->b / 255.0;
    double min, max;

    // Finding min/max of r,g,b
    if (r > g) {
        if (r > b) {
            max = r;
            min = g < b ? g : b;
        } else {
            max = b;
            min = g;
        }
    } else {
        if (g > b) {
            max = g;
            min = r < b ? r : b;
        } else {
            max = b;
            min = r;
        }
    }

    const double l = (max + min) / 2.0;

    if (max == min) {
        return (HSL){{0.0, 0.0, l}};
    }

    double h;
    const double d = max - min;
    const double s = l > 0.5 ? d / (2 - max - min) : d / (max + min);

    if (max == r) {
        h = (g - b) / d + (g < b ? 6.0 : 0.0);
    } else if (max == g) {
        h = (b - r) / d + 2.0;
    } else {
        h = (r - g) / d + 4.0;
    }
    h /= 6;

    return (HSL){{h, s, l}};
}

OKlab rgb2oklab(const RGB *rgb) {
    const double r = inverse_gamma_correction(rgb->r / 255.0);
    const double g = inverse_gamma_correction(rgb->g / 255.0);
    const double b = inverse_gamma_correction(rgb->b / 255.0);

    const double l = cbrt(0.4122214708 * r + 0.5363325363 * g + 0.0514459929 * b);
    const double m = cbrt(0.2119034982 * r + 0.6806995451 * g + 0.1073969566 * b);
    const double s = cbrt(0.0883024619 * r + 0.2817188376 * g + 0.6299787005 * b);

    const double L = l * 0.2104542553 + m * 0.793617785 + s * -0.0040720468;
    const double A = l * 1.9779984951 + m * -2.428592205 + s * 0.4505937099;
    const double B = l * 0.0259040371 + m * 0.7827717662 + s * -0.808675766;

    return (OKlab){{L, A, B}};
}

RGB xyz2rgb(const XYZ *xyz) {
    //XYZ -> linear RGB (sRGB)
    double r = xyz->x * 3.2406 + xyz->y * -1.5372 + xyz->z * -0.4986;
    double g = xyz->x * -0.9689 + xyz->y * 1.8758 + xyz->z * 0.0415;
    double b = xyz->x * 0.0557 + xyz->y * -0.2040 + xyz->z * 1.0570;

    // Обратная гамма-коррекция
    r = inverse_gamma_correction(r);
    g = inverse_gamma_correction(g);
    b = inverse_gamma_correction(b);

    // Ограничение в диапазоне [0,255]
    return (RGB){{clamp2rgb(r), clamp2rgb(g), clamp2rgb(b)}};
}

// The XYZ values are normalized to the D65 illuminant and then converted to LAB
LAB xyz2lab(const XYZ *xyz) {
    // Normalize XYZ values by the D65 reference white
    const double x = xyz->x / 0.95047;
    const double y = xyz->y / 1.00000;
    const double z = xyz->z / 1.08883;

    const double l = 116 * F(y) - 16; // lightness
    const double a = 500 * (F(x) - F(y)); // green to red
    const double b = 200 * (F(y) - F(z)); // blue to yellow

    return (LAB){{l, a, b}};
}

LCh xyz2lch(const XYZ *xyz) {
    const LAB lab = xyz2lab(xyz);
    return lab2lch(&lab);
}

HSV xyz2hsv(const XYZ *xyz) {
    const RGB rgb = xyz2rgb(xyz);
    return rgb2hsv(&rgb);
}

HSL xyz2hsl(const XYZ *xyz) {
    const RGB rgb = xyz2rgb(xyz);
    return rgb2hsl(&rgb);
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
    const double h_rad = lch->h * (M_PI / 180.0);
    const double a = lch->c * cos(h_rad);
    const double b = lch->c * sin(h_rad);
    return (LAB){{lch->l, a, b}};
}

HSV lch2hsv(const LCh *lch) {
    const RGB rgb = lch2rgb(lch);
    return rgb2hsv(&rgb);
}

HSL lch2hsl(const LCh *lch) {
    const RGB rgb = lch2rgb(lch);
    return rgb2hsl(&rgb);
}

RGB hsv2rgb(const HSV *hsv) {
    // Ensure h is in the range [0, 1), so if h == 1, it will be treated as 0
    const double h = fmod(hsv->h, 1.0); // This operation guarantees that h is always in the range [0, 1)

    // Convert H to an integer index (in the range [0, 5])
    const unsigned char i = (unsigned char) (h * 6);
    const double f = h * 6 - i;
    const double p = hsv->v * (1 - hsv->s);
    const double q = hsv->v * (1 - f * hsv->s);
    const double t = hsv->v * (1 - (1 - f) * hsv->s);

    // Determine r, g, b values based on the hue sector (i % 6)
    double r, g, b;
    switch (i % 6) {
        case 0: r = hsv->v, g = t, b = p;
            break;
        case 1: r = q, g = hsv->v, b = p;
            break;
        case 2: r = p, g = hsv->v, b = t;
            break;
        case 3: r = p, g = q, b = hsv->v;
            break;
        case 4: r = t, g = p, b = hsv->v;
            break;
        default: r = hsv->v, g = p, b = q;
            break;
    }

    // Convert values from the range [0, 1] to [0, 255] and return the structure
    return (RGB){{(unsigned char) (r * 255), (unsigned char) (g * 255), (unsigned char) (b * 255)}};
}

XYZ hsv2xyz(const HSV *hsv) {
    const RGB rgb = hsv2rgb(hsv);
    return rgb2xyz(&rgb);
}

LAB hsv2lab(const HSV *hsv) {
    const XYZ xyz = hsv2xyz(hsv);
    return xyz2lab(&xyz);
}

LCh hsv2lch(const HSV *hsv) {
    const LAB lab = hsv2lab(hsv);
    return lab2lch(&lab);
}

HSL hsv2hsl(const HSV *hsv) {
    const RGB rgb = hsv2rgb(hsv);
    return rgb2hsl(&rgb);
}

RGB hsl2rgb(const HSL *hsl) {
    if (hsl->s == 0.0) {
        return (RGB){{hsl->l, hsl->l, hsl->l}};
    }

    const double q = hsl->l < 0.5 ? hsl->l * (1 + hsl->s) : hsl->l + hsl->s - hsl->l * hsl->s;
    const double p = 2 * hsl->l - q;

    return (RGB){{hue2rgb(p, q, hsl->h + 1.0 / 3.0), hue2rgb(p, q, hsl->h), hue2rgb(p, q, hsl->h - 1.0 / 3.0)}};
}

XYZ hsl2xyz(const HSL *hsl) {
    const RGB rgb = hsl2rgb(hsl);
    return rgb2xyz(&rgb);
}

LAB hsl2lab(const HSL *hsl) {
    const RGB rgb = hsl2rgb(hsl);
    return rgb2lab(&rgb);
}

LCh hsl2lch(const HSL *hsl) {
    const RGB rgb = hsl2rgb(hsl);
    return rgb2lch(&rgb);
}

HSV hsl2hsv(const HSL *hsl) {
    const RGB rgb = hsl2rgb(hsl);
    return rgb2hsv(&rgb);
}

RGB oklab2rgb(const OKlab *oklab) {
    const double l = pow(oklab->l + 0.3963377774 * oklab->a + 0.2158037573 * oklab->b, 3);
    const double m = pow(oklab->l - 0.1055613458 * oklab->a - 0.0638541728 * oklab->b, 3);
    const double s = pow(oklab->l - 0.0894841775 * oklab->a - 1.291485548 * oklab->b, 3);

    const double r = 255 * gamma_correction(4.0767416621 * l - 3.3077115913 * m + 0.2309699292 * s);
    const double g = 255 * gamma_correction(-1.2684380046 * l + 2.6097574011 * m - 0.3413193965 * s);
    const double b = 255 * gamma_correction(-0.0041960863 * l - 0.7034186147 * m + 1.707614701 * s);

    return (RGB){{clamp2rgb(r), clamp2rgb(g), clamp2rgb(b)}};
}

OKlch oklab2oklch(const OKlab *oklab) {
    const double C = hypot(oklab->a, oklab->b);
    const double h = atan2(oklab->b, oklab->a) * (180.0 / M_PI);
    return (OKlch){{oklab->l, C, h < 0 ? h + 360.0 : h}};
}

OKlab oklch2oklab(const OKlch *oklch) {
    const double h_rad = oklch->h * (M_PI / 180.0);
    const double a = oklch->c * cos(h_rad);
    const double b = oklch->c * sin(h_rad);
    return (OKlab){{oklch->l, a, b}};
}

RGB oklch2rgb(const OKlch *oklch) {
    const OKlab oklab = oklch2oklab(oklch);
    return oklab2rgb(&oklab);
}

OKlch rgb2oklch(const RGB *rgb) {
    const OKlab oklab = rgb2oklab(rgb);
    return oklab2oklch(&oklab);
}