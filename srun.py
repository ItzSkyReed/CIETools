import timeit

import cietools
import math

def rgb2lab(rgb):
    def gamma_correction(c):
        if c <= 0.04045:
            return c / 12.92
        return ((c + 0.055) / 1.055) ** 2.4

    def xyz2lab(xyz):
        x, y, z = xyz
        # Normalize XYZ values by the D65 reference white
        x /= 0.95047
        y /= 1.00000
        z /= 1.08883

        l = 116 * F(y) - 16  # Lightness
        a = 500 * (F(x) - F(y))  # Green to red
        b = 200 * (F(y) - F(z))  # Blue to yellow

        return (l, a, b)

    def F(t):
        if t > 0.008856:
            return t ** (1.0 / 3.0)  # Cube root if t is greater than 0.008856
        return (903.3 * t + 16.0) / 116.0  # Linear transformation otherwise

    def rgb2xyz(rgb):
        r, g, b = rgb
        # Apply gamma correction to each RGB component (normalize to [0, 1] range)
        r = gamma_correction(r / 255.0)
        g = gamma_correction(g / 255.0)
        b = gamma_correction(b / 255.0)

        # Linear transformation from RGB to XYZ using the standard sRGB-to-XYZ matrix
        x = r * 0.4124 + g * 0.3576 + b * 0.1805
        y = r * 0.2126 + g * 0.7152 + b * 0.0722
        z = r * 0.0193 + g * 0.1192 + b * 0.9505

        return x, y, z

    # Convert RGB to XYZ and then XYZ to LAB
    xyz = rgb2xyz(rgb)
    return xyz2lab(xyz)

def delta_e_ciede_2000(lab1, lab2):
    k_l = 1.0
    k_c = 1.0
    k_h = 1.0

    # Chroma factor
    n = (math.hypot(lab1[1], lab1[2]) + math.hypot(lab2[1], lab2[2])) * 0.5
    n = n ** 7
    n = 1.0 + 0.5 * (1.0 - math.sqrt(n / (n + 6103515625.0)))

    # Chroma components
    c_1 = math.hypot(lab1[1] * n, lab1[2])
    c_2 = math.hypot(lab2[1] * n, lab2[2])

    # Hue components
    h_1 = math.atan2(lab1[2], lab1[1] * n)
    h_2 = math.atan2(lab2[2], lab2[1] * n)

    h_1 += 2 * math.pi * (h_1 < 0.0)
    h_2 += 2 * math.pi * (h_2 < 0.0)

    n = abs(h_2 - h_1)

    if math.pi - 1E-14 < n < math.pi + 1E-14:
        n = math.pi

    # Handle hue in different quadrants
    h_m = 0.5 * h_1 + 0.5 * h_2
    h_d = (h_2 - h_1) * 0.5
    if math.pi < n:
        h_d -= math.pi if h_d > 0.0 else h_d + math.pi
        h_m += math.pi

    p = 36.0 * h_m - 55.0 * math.pi

    n = (c_1 + c_2) * 0.5
    n = n ** 7

    r_t = -2.0 * math.sqrt(n / (n + 6103515625.0)) * math.sin(math.pi / 3.0 * math.exp(p * p / (-25.0 * math.pi * math.pi)))

    # Lightness
    n = (lab1[0] + lab2[0]) * 0.5
    n = (n - 50.0) ** 2
    l = (lab2[0] - lab1[0]) / (k_l * (1.0 + 0.015 * n / math.sqrt(20.0 + n)))

    # Saturation term
    t = 1.0 + 0.24 * math.sin(2.0 * h_m + 2 * math.pi) + 0.32 * math.sin(3.0 * h_m + 8.0 * math.pi / 15.0) \
        - 0.17 * math.sin(h_m + math.pi / 3.0) - 0.20 * math.sin(4.0 * h_m + 3.0 * 2 * math.pi / 10.0)

    n = c_1 + c_2

    # Hue
    h = 2.0 * math.sqrt(c_1 * c_2) * math.sin(h_d) / (k_h * (1.0 + 0.0075 * n * t))

    # Chroma
    c = (c_2 - c_1) / (k_c * (1.0 + 0.0225 * n))

    # Final result (geometric distance)
    return math.sqrt(l ** 2 + h ** 2 + c ** 2 + c * h * r_t)

lab1 = (50.0, 20.0, 12012.0)  # Пример LAB значений для первого цвета
lab2 = (60.0, 25.0, 35.0)  # Пример LAB значений для второго цвета
rgb = (100, 200, 150)
python_time = timeit.timeit('rgb2lab(rgb)', globals=globals(), number=100000)
c_time = timeit.timeit('cietools.rgb2lab(rgb)', globals=globals(), number=100000)
print(python_time, c_time)
