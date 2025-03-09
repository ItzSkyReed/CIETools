#ifndef COLOR_DIFFERENCE_H
#define COLOR_DIFFERENCE_H
#include "color_structs.h"
#include  <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double delta_e_cie_76(const LAB *lab1, const LAB *lab2);
double delta_e_cie_94(const LAB *lab1, const LAB *lab2);
double delta_e_cmc(const LAB *lab1, const LAB *lab2);
double delta_e_ciede_2000(const LAB *lab1, const LAB *lab2);
double delta_e_OK(const OKlab *oklab1, const OKlab *oklab2);
double delta_e_OK2(const OKlab *oklab1, const OKlab *oklab2);

#endif //COLOR_DIFFERENCE_H
