#include <math.h>
#include "color_structs.h"
#include "gradients.h"

OKlab *oklab_linear_gradient(const OKlab *color1 ,const OKlab *color2, OKlab *gradient, const int steps) {

    const double inv_steps = 1.0 / (steps - 1);
    for (int i = 0; i < steps; i++) {
        const double t = i * inv_steps;
        gradient[i].l = color1->l * (1 - t) + color2->l * t;
        gradient[i].a = color1->a * (1 - t) + color2->a * t;
        gradient[i].b = color1->b * (1 - t) + color2->b * t;
    }

    return gradient;
}

OKlab *oklab_cosine_gradient(const OKlab *color1, const OKlab *color2, OKlab *gradient, const unsigned int steps) {

    const double step_factor = M_PI / (steps - 1);
    const double l_diff = (color2->l - color1->l) * 0.5;
    const double a_diff = (color2->a - color1->a) * 0.5;
    const double b_diff = (color2->b - color1->b) * 0.5;

    for (unsigned int i = 0; i < steps; i++) {
        const double cos_t = 1 - cos(i * step_factor);
        gradient[i].l = color1->l + l_diff * cos_t;
        gradient[i].a = color1->a + a_diff * cos_t;
        gradient[i].b = color1->b + b_diff * cos_t;
    }

    return gradient;
}