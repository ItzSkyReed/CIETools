#ifndef COLOR_STRUCTS_H
#define COLOR_STRUCTS_H

typedef union {
    struct {
        unsigned char r, g, b;
    };
    unsigned char channels[3];
} RGB;

typedef union {
    struct {
        double l, a, b;
    };
    double channels[3];
} LAB;

typedef union {
    struct {
        double l, a, b;
    };
    double channels[3];
} OKlab;


typedef union {
    struct {
        double x, y, z;
    };
    double channels[3];
} XYZ;

typedef union {
    struct {
        double l, c, h;
    };
    double channels[3];
} LCh;

typedef union {
    struct {
        double l, c, h;
    };
    double channels[3];
} OKlch;


typedef union {
    struct {
        double h, s, v;
    };
    double channels[3];
} HSV;

typedef union {
    struct {
        double h, s, l;
    };
    double channels[3];
} HSL;



#endif //COLOR_STRUCTS_H
