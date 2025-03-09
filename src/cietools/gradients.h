#ifndef GRADIENTS_H
#define GRADIENTS_H
#include "color_structs.h"
#include  <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

OKlab oklab_linear_gradient(const OKlab *color1 ,const OKlab *color2, OKlab *gradient, int steps);
OKlab oklab_cosine_gradient(const OKlab *color1, const OKlab *color2, OKlab *gradient, int steps);

#endif //GRADIENTS_H
