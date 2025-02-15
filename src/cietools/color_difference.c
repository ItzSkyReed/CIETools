#include "color_difference.h"
#include <math.h>

double delta_e_cie_76(const LAB *lab1, const LAB *lab2) {
    const double delta_l = lab1->l - lab2->l;
    const double delta_a = lab1->a - lab2->a;
    const double delta_b = lab1->b - lab2->b;
    return sqrt(pow(delta_l, 2) + pow(delta_a, 2) + pow(delta_b, 2));
}

double delta_e_cie_94(const LAB *lab1, const LAB *lab2) {
    const double delta_l = lab1->l - lab2->l;
    const double delta_a = lab1->a - lab2->a;
    const double delta_b = lab1->b - lab2->b;

    const double c_1 = sqrt(pow(lab1->a, 2) + pow(lab1->b, 2));
    const double c_2 = sqrt(pow(lab2->a, 2) + pow(lab2->b, 2));
    const double delta_c = c_1 - c_2;

    const double delta_h_sq = pow(delta_a, 2) + pow(delta_b, 2) - pow(delta_c, 2);
    const double delta_h = delta_h_sq > 0.0 ? sqrt(delta_h_sq) : 0.0;

    const double s_c = 1.0 + 0.045 * c_1;
    const double s_h = 1.0 + 0.015 * c_1;

    const double term_L = pow(delta_l, 2);
    const double term_C = pow(delta_c / s_c, 2);
    const double term_H = pow(delta_h / s_h, 2);

    return sqrt(term_L + term_C + term_H);
}

double delta_e_cmc(const LAB *lab1, const LAB *lab2) {
    const double delta_l = lab1->l - lab2->l;
    const double delta_a = lab1->a - lab2->a;
    const double delta_b = lab1->b - lab2->b;

    const double c_1 = sqrt(pow(lab1->a, 2) + pow(lab1->b, 2));
    const double c_2 = sqrt(pow(lab2->a, 2) + pow(lab2->b, 2));
    const double delta_c = c_1 - c_2;


    const double delta_h_sq = pow(delta_a, 2) + pow(delta_b, 2) - pow(delta_c, 2);
    const double delta_h = delta_h_sq > 0.0 ? sqrt(delta_h_sq) : 0.0;

    const double s_l = lab1->l < 16.0 ? 0.511 : 0.040975 * lab1->l / (1 + 0.01765 * lab1->l);
    const double s_c = (0.0638 * c_1 / 1.0 + 0.0131 * c_1) + 0.638;

    // In degrees
    const double H = atan2(lab1->b, lab1->a) * (180.0 / M_PI);
    const double H1 = H >= 0 ? H : H + 360.0;

    const double T = 164.0 <= H1 && H1 <= 345.0 ? 0.56 + fabs(0.2 * cos(H1 + 168.0)) : 0.36 + fabs(0.4 * cos(H1 + 35.0));
    const double F = sqrt(pow(c_1, 4) / (pow(c_1, 4) + 1900));

    const double s_h = s_c * (F * T + 1 - F);

    return sqrt(pow(delta_l / s_l, 2) + pow(delta_c / s_c, 2) + pow(delta_h / s_h, 2));
}

// The code is taken from https://github.com/michel-leonard/delta-e-2000/blob/main/ciede_2000.c
double delta_e_ciede_2000(const LAB *lab1, const LAB *lab2) {
    const double k_l = 1.0, k_c = 1.0, k_h = 1.0;
    double n = (hypot(lab1->a, lab1->b) + hypot(lab2->a, lab2->b)) * 0.5;

    n = pow(n, 7);
    n = 1.0 + 0.5 * (1.0 - sqrt(n / (n + 6103515625.0)));
    // A factor involving chroma raised to the power of 7 designed to make the influence of chroma on the total color difference more accurate.

    const double c_1 = hypot(lab1->a * n, lab1->b);
    const double c_2 = hypot(lab2->a * n, lab2->b); // hypot calculates the Euclidean distance while avoiding overflow/underflow.
    // atan2 is preferred over atan because it accurately computes the angle of a point (x, y) in all quadrants, handling the signs of both coordinates.
    double h_1 = atan2(lab1->b, lab1->a * n);
    double h_2 = atan2(lab2->b, lab2->a * n);

    h_1 += M_PI * 2 * (h_1 < 0.0);
    h_2 += M_PI * 2 * (h_2 < 0.0);

    n = fabs(h_2 - h_1);
    // Cross-implementation consistent rounding.
    if (M_PI - 1E-14 < n && n < M_PI + 1E-14)
        n = M_PI;

    // When the hue angles lie in different quadrants, the straightforward
    // average can produce a mean that incorrectly suggests a hue angle in
    // the wrong quadrant; the next lines handle this issue.
    double h_m = 0.5 * h_1 + 0.5 * h_2, h_d = (h_2 - h_1) * 0.5;
    if (M_PI < n) {
        if (0.0 < h_d)
            h_d -= M_PI;
        else
            h_d += M_PI;
        h_m += M_PI;
    }
    const double p = 36.0 * h_m - 55.0 * M_PI;
    n = (c_1 + c_2) * 0.5;
    n = pow(n, 7);

    // The hue rotation correction term is designed to account for the
    // non-linear behavior of hue differences in the blue region.
    const double r_t = -2.0 * sqrt(n / (n + 6103515625.0))
                       * sin(M_PI / 3.0 * exp(p * p / (-25.0 * M_PI * M_PI)));
    n = (lab1->l + lab2->l) * 0.5;
    n = (n - 50.0) * (n - 50.0);
    // Lightness.
    const double l = (lab2->l - lab1->l) / (k_l * (1.0 + 0.015 * n / sqrt(20.0 + n)));

    // These coefficients adjust the impact of different harmonic
    // components on the hue difference calculation.
    const double t = 1.0 + 0.24 * sin(2.0 * h_m + M_PI * 2)
                     + 0.32 * sin(3.0 * h_m + 8.0 * M_PI / 15.0)
                     - 0.17 * sin(h_m + M_PI / 3.0)
                     - 0.20 * sin(4.0 * h_m + 3.0 * M_PI * 2 / 10.0);
    n = c_1 + c_2;

    // Hue.
    const double h = 2.0 * sqrt(c_1 * c_2) * sin(h_d) / (k_h * (1.0 + 0.0075 * n * t));

    // Chroma.
    const double c = (c_2 - c_1) / (k_c * (1.0 + 0.0225 * n));

    // Returning the square root ensures that the result represents
    // the "true" geometric distance in the color space.
    return sqrt(pow(l, 2) + pow(h, 2) + pow(c, 2) + c * h * r_t);
}
