#include "color_difference.h"
#include <math.h>

double delta_e_cie_76(const LAB *lab1, const LAB *lab2) {
    const double delta_l = lab1->l - lab2->l;
    const double delta_a = lab1->a - lab2->a;
    const double delta_b = lab1->b - lab2->b;
    return hypot(delta_l, hypot(delta_a, delta_b));
}
// More accurate color-difference formulae
//than the simple1976 Euclidean distance in CIE Lab
double delta_e_OK(const OKlab *oklab1, const OKlab *oklab2) {
    const double delta_l = oklab1->l - oklab2->l;
    const double delta_a = oklab1->a - oklab2->a;
    const double delta_b = oklab1->b - oklab2->b;
    return hypot(delta_l, hypot(delta_a, delta_b));
}

// More accurate color-difference formulae
// than the simple 1976 Euclidean distance in CIE Lab
// The Oklab a and b axes are scaled relative to the L axis, for better uniformity
// Björn Ottosson said:
// "I've recently done some tests with color distance datasets as implemented
// in Colorio and on both the Combvd dataset and the OSA-UCS dataset a
// scale factor of slightly more than 2 for a and b would give the best results
// (2.016 works best for Combvd and 2.045 for the OSA-UCS dataset)."
double delta_e_OK2(const OKlab *oklab1, const OKlab *oklab2) {
    const double delta_l = oklab1->l - oklab2->l;
    const double delta_a = 2.0 * (oklab1->a - oklab2->a);
    const double delta_b = 2.0 * (oklab1->b - oklab2->b);
    return hypot(delta_l, hypot(delta_a, delta_b));
}

double delta_e_cie_94(const LAB *lab1, const LAB *lab2) {
    const double delta_l = lab1->l - lab2->l;
    const double delta_a = lab1->a - lab2->a;
    const double delta_b = lab1->b - lab2->b;

    const double c_1 = hypot(lab1->a, lab1->b);
    const double c_2 = hypot(lab2->a, lab2->b);
    const double delta_c = c_1 - c_2;

    const double delta_h_sq = delta_a * delta_a + delta_b * delta_b - delta_c * delta_c;
    const double delta_h = delta_h_sq > 0.0 ? sqrt(delta_h_sq) : 0.0;

    const double s_c = 1.0 + 0.045 * c_1;
    const double s_h = 1.0 + 0.015 * c_1;

    const double term_L = delta_l * delta_l;
    const double term_C = delta_c / s_c * (delta_c / s_c);
    const double term_H = delta_h / s_h * (delta_h / s_h);

    return sqrt(term_L + term_C + term_H);
}

double delta_e_cmc(const LAB *lab1, const LAB *lab2) {
    const double delta_l = lab1->l - lab2->l;
    const double delta_a = lab1->a - lab2->a;
    const double delta_b = lab1->b - lab2->b;

    const double c_1 = hypot(lab1->a, lab1->b);
    const double c_2 = hypot(lab2->a, lab2->b);
    const double delta_c = c_1 - c_2;

    const double delta_h_sq = delta_a * delta_a + delta_b * delta_b - delta_c * delta_c;
    const double delta_h = delta_h_sq > 0.0 ? sqrt(delta_h_sq) : 0.0;

    const double s_l = lab1->l < 16.0 ? 0.511 : 0.040975 * lab1->l / (1 + 0.01765 * lab1->l);
    const double s_c = 0.0638 * c_1 / (1.0 + 0.0131 * c_1) + 0.638;

    // In degrees
    const double H = atan2(lab1->b, lab1->a) * (180.0 / M_PI);
    const double H1 = H >= 0 ? H : H + 360.0;

    // Convert H1 to radians for trigonometric functions
    const double H1_rad = H1 * (M_PI / 180.0);

    const double T = 164.0 <= H1 && H1 <= 345.0 ? 0.56 + fabs(0.2 * cos(H1_rad + 168.0 * (M_PI / 180.0))) : 0.36 + fabs(0.4 * cos(H1_rad + 35.0 * (M_PI / 180.0)));
    const double F = sqrt(c_1 * c_1 * c_1 * c_1 / (c_1 * c_1 * c_1 * c_1 + 1900));

    const double s_h = s_c * (F * T + 1 - F);

    return sqrt(delta_l / s_l * (delta_l / s_l) + delta_c / s_c * (delta_c / s_c) + delta_h / s_h * (delta_h / s_h));
}

double delta_e_ciede_2000(const LAB *lab1, const LAB *lab2) {
    const double deg2rad = M_PI / 180.0;
    const double rad2deg  = 180.0 / M_PI;
    const double pow25_7  = 6103515625.0; // 25^7

    const double L_bar = (lab1->l + lab2->l) * 0.5;

    const double C1 = hypot(lab1->a, lab1->b);
    const double C2 = hypot(lab2->a, lab2->b);

    const double C_bar = (C1 + C2) * 0.5;
    const double C_bar7 = C_bar * C_bar * C_bar * C_bar * C_bar * C_bar * C_bar;
    const double G = 0.5 * (1.0 - sqrt(C_bar7 / (C_bar7 + pow25_7)));

    const double a1_prime = lab1->a * (1.0 + G);
    const double a2_prime = lab2->a * (1.0 + G);

    const double C1_prime = hypot(a1_prime, lab1->b);
    const double C2_prime = hypot(a2_prime, lab2->b);

    const double C_bar_prime = (C1_prime + C2_prime) * 0.5;

    double h1_prime = atan2(lab1->b, a1_prime) * rad2deg;
    if (h1_prime < 0)
        h1_prime += 360.0;
    double h2_prime = atan2(lab2->b, a2_prime) * rad2deg;
    if (h2_prime < 0)
        h2_prime += 360.0;

    double delta_h_prime;
    if (fabs(h2_prime - h1_prime) <= 180.0)
        delta_h_prime = h2_prime - h1_prime;
    else if (h2_prime <= h1_prime)
        delta_h_prime = h2_prime - h1_prime + 360.0;
    else
        delta_h_prime = h2_prime - h1_prime - 360.0;

    double H_bar;
    if (fabs(h1_prime - h2_prime) > 180.0) {
        H_bar = h1_prime + h2_prime < 360.0 ?
                (h1_prime + h2_prime + 360.0) * 0.5 :
                (h1_prime + h2_prime - 360.0) * 0.5;
    } else {
        H_bar = (h1_prime + h2_prime) * 0.5;
    }

    const double T = 1.0 - 0.17 * cos((H_bar - 30.0) * deg2rad)
                 + 0.24 * cos(2.0 * H_bar * deg2rad)
                 + 0.32 * cos((3.0 * H_bar + 6.0) * deg2rad)
                 - 0.20 * cos((4.0 * H_bar - 63.0) * deg2rad);

    const double delta_L_prime = lab2->l - lab1->l;
    const double delta_C_prime = C2_prime - C1_prime;
    const double delta_H_prime = 2.0 * sqrt(C1_prime * C2_prime) *
                           sin((delta_h_prime * 0.5) * deg2rad);

    const double S_L = 1.0 + 0.015 * ( (L_bar - 50.0) * (L_bar - 50.0) )
                     / sqrt(20.0 + (L_bar - 50.0) * (L_bar - 50.0));
    const double S_C = 1.0 + 0.045 * C_bar_prime;
    const double S_H = 1.0 + 0.015 * C_bar_prime * T;

    const double delta_theta = 30.0 * exp(-((H_bar - 275.0) / 25.0) * ((H_bar - 275.0) / 25.0));

    const double C_bar_prime7 = C_bar_prime * C_bar_prime * C_bar_prime *
                          C_bar_prime * C_bar_prime * C_bar_prime * C_bar_prime;
    const double R_C = 2.0 * sqrt(C_bar_prime7 / (C_bar_prime7 + pow25_7));

    const double R_T = -R_C * sin(2.0 * delta_theta * deg2rad);

    return sqrt(
        delta_L_prime / S_L * (delta_L_prime / S_L) +
        delta_C_prime / S_C * (delta_C_prime / S_C) +
        delta_H_prime / S_H * (delta_H_prime / S_H) +
        R_T * (delta_C_prime / S_C) * (delta_H_prime / S_H)
    );
}

