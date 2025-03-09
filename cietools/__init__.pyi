from collections.abc import Sequence

from typing import TypeAlias, Annotated, Literal

Number: TypeAlias = int | float
Float3Tuple: TypeAlias = tuple[float, float, float]
Int3Tuple: TypeAlias = tuple[int, int, int]
Number3Tuple: TypeAlias = Sequence[Number, Number, Number]

NumberGT2 = Annotated[int, Literal["gt", 2]]
GradientList: TypeAlias = list[Float3Tuple]


def rgb2lab(rgb: Number3Tuple) -> Float3Tuple:
    """
    Convert RGB values (in the range 0-255) to LAB color space.

    :param rgb: Sequence with RGB values (R, G, B), each being an int or float.
    :return: Tuple with LAB values (L, A, B).
    """
    ...


def rgb2lch(rgb: Number3Tuple) -> Float3Tuple:
    """
    Convert RGB values (in the range 0-255) to LCh color space.
    :param rgb: Tuple with RGB values (R, G, B), each being an int or float.
    :return: Tuple with LCh values (L, C, h)
    """
    ...


def rgb2xyz(rgb: Number3Tuple) -> Float3Tuple:
    """
    Convert RGB values (in the range 0-255) to XYZ color space.
    :param rgb: Tuple with RGB values (R, G, B), each being an int or float.
    :return: Tuple with XYZ values (X, Y, Z)
    """
    ...


def rgb2hsl(rgb: Number3Tuple) -> Float3Tuple:
    """
    Convert RGB values (in the range 0-255) to HSL color space.
    :param rgb: Tuple with RGB values (R, G, B), each being an int or float.
    :return: Tuple with HSL values (H, S, L)
    """
    ...


def rgb2hsv(rgb: Number3Tuple) -> Float3Tuple:
    """
    Convert RGB values (in the range 0-255) to HSV color space.
    :param rgb: Tuple with RGB values (R, G, B), each being an int or float.
    :return: Tuple with HSV values (H, S, V)
    """
    ...


def rgb2oklab(rgb: Number3Tuple) -> Float3Tuple:
    """
    Convert RGB values (in the range 0-255) to OKlab color space.
    :param rgb: Tuple with RGB values (R, G, B), each being an int or float.
    :return: Tuple with OKlab values (L, A, B)
    """
    ...


def rgb2oklch(rgb: Number3Tuple) -> Float3Tuple:
    """
    Convert RGB values (in the range 0-255) to OKlch color space.
    :param rgb: Tuple with RGB values (R, G, B), each being an int or float.
    :return: Tuple with OKlch values (L, C, H)
    """
    ...


def xyz2lab(xyz: Number3Tuple) -> Float3Tuple:
    """
    Convert XYZ values to LAB color space.
    :param xyz: Tuple with XYZ values (X > 0; 0 <= Y <= 100; Z > 0)
    :return: Tuple with LAB values (L, A, B)
    """
    ...


def xyz2lch(xyz: Number3Tuple) -> Float3Tuple:
    """
    Convert XYZ values to LCh color space.
    :param xyz: Tuple with XYZ values (X > 0; 0 <= Y <= 100; Z > 0)
    :return: Tuple with LCh values (L, C, h)
    """
    ...


def xyz2rgb(xyz: Number3Tuple) -> Int3Tuple:
    """
    Convert XYZ values to RGB color space.
    :param xyz: Tuple with XYZ values (X > 0; 0 <= Y <= 100; Z > 0)
    :return: Tuple with RGB values (R, G, B)
    """
    ...


def xyz2hsl(xyz: Number3Tuple) -> Float3Tuple:
    """
    Convert XYZ values to HSL color space.
    :param xyz: Tuple with XYZ values (X > 0; 0 <= Y <= 100; Z > 0)
    :return: Tuple with HSL values (H, S, L)
    """
    ...


def xyz2hsv(xyz: Number3Tuple) -> Float3Tuple:
    """
    Convert XYZ values to LAB color space.
    :param xyz: Tuple with XYZ values (X > 0; 0 <= Y <= 100; Z > 0)
    :return: Tuple with LAB values (L, A, B)
    """
    ...


def lab2lch(lab: Number3Tuple) -> Float3Tuple:
    """
    Convert LAB values to LCh color space.
    :param lab: Tuple with LAB values (0 <= L <= 100; -127 <= A <= 127; -127 <= B <= 127)
    :return: Tuple with LCh values (L, C, h)
    """
    ...


def lab2xyz(lab: Number3Tuple) -> Float3Tuple:
    """
    Convert LAB values to XYZ color space.
    :param lab: Tuple with LAB values (0 <= L <= 100; -127 <= A <= 127; -127 <= B <= 127)
    :return: Tuple with XYZ values (X, Y, Z)
    """
    ...


def lab2rgb(lab: Number3Tuple) -> Float3Tuple:
    """
    Convert LAB values to RGB color space.
    :param lab: Tuple with LAB values (0 <= L <= 100; -127 <= A <= 127; -127 <= B <= 127)
    :return: Tuple with RGB values (R, G, B)
    """
    ...


def lab2hsv(lab: Number3Tuple) -> Float3Tuple:
    """
    Convert LAB values to HSV color space.
    :param lab: Tuple with LAB values (0 <= L <= 100; -127 <= A <= 127; -127 <= B <= 127)
    :return: Tuple with HSV values (H, S, V)
    """
    ...


def lab2hsl(lab: Number3Tuple) -> Float3Tuple:
    """
    Convert LAB values to HSL color space.
    :param lab: Tuple with LAB values (0 <= L <= 100; -127 <= A <= 127; -127 <= B <= 127)
    :return: Tuple with HSL values (H, S, L)
    """
    ...


def lch2lab(lch: Number3Tuple) -> Float3Tuple:
    """
    Convert LCh values to LAB color space.
    :param lch: Tuple with LCh values (0 <= L <= 100; 0 <= C <= 100; 0 <= h <= 360)
    :return: Tuple with LAB values (L, A, B)
    """
    ...


def lch2xyz(lch: Number3Tuple) -> Float3Tuple:
    """
    Convert LCh values to XYZ color space.
    :param lch: Tuple with LCh values (0 <= L <= 100; 0 <= C <= 100; 0 <= h <= 360)
    :return: Tuple with XYZ values (X, Y, Z)
    """
    ...


def lch2hsv(lch: Number3Tuple) -> Float3Tuple:
    """
    Convert LCh values to HSV color space.
    :param lch: Tuple with LCh values (0 <= L <= 100; 0 <= C <= 100; 0 <= h <= 360)
    :return: Tuple with HSV values (H, S, V)
    """
    ...


def lch2hsl(lch: Number3Tuple) -> Float3Tuple:
    """
    Convert LCh values to HSL color space.
    :param lch: Tuple with LCh values (0 <= L <= 100; 0 <= C <= 100; 0 <= h <= 360)
    :return: Tuple with HSL values (H, S, L)
    """
    ...


def lch2rgb(lch: Number3Tuple) -> Int3Tuple:
    """
    Convert LCh values to RGB color space.
    :param lch: Tuple with LCh values (0 <= L <= 100; 0 <= C <= 100; 0 <= h <= 360)
    :return: Tuple with RGB values (R, G, B)
    """
    ...


def hsl2rgb(hsl: Number3Tuple) -> Int3Tuple:
    """
    Convert HSL values to RGB color space.
    :param hsl: Tuple with HSL values (0 <= H <= 360; 0 <= S <= 1; 0 <= L <= 1)
    :return: Tuple with RGB values (R, G, B)
    """
    ...


def hsl2xyz(hsl: Number3Tuple) -> Float3Tuple:
    """
    Convert HSL values to XYZ color space.
    :param hsl: Tuple with HSL values (0 <= H <= 360; 0 <= S <= 1; 0 <= L <= 1)
    :return: Tuple with XYZ values (X, T, Z)
    """
    ...


def hsl2lab(hsl: Number3Tuple) -> Float3Tuple:
    """
    Convert HSL values to LAB color space.
    :param hsl: Tuple with HSL values (0 <= H <= 360; 0 <= S <= 1; 0 <= L <= 1)
    :return: Tuple with LAB values (L, A, B)
    """
    ...


def hsl2lch(hsl: Number3Tuple) -> Float3Tuple:
    """
    Convert HSL values to LCh color space.
    :param hsl: Tuple with HSL values (0 <= H <= 360; 0 <= S <= 1; 0 <= L <= 1)
    :return: Tuple with LCh values (L, C, H)
    """
    ...


def hsl2hsv(hsl: Number3Tuple) -> Float3Tuple:
    """
    Convert HSL values to HSV color space.
    :param hsl: Tuple with HSL values (0 <= H <= 360; 0 <= S <= 1; 0 <= L <= 1)
    :return: Tuple with HSV values (H, S, V)
    """
    ...


def hsv2rgb(hsl: Number3Tuple) -> Int3Tuple:
    """
    Convert HSV values to RGB color space.
    :param hsl: Tuple with HSV values (0 <= H <= 360; 0 <= S <= 1; 0 <= V <= 1)
    :return: Tuple with RGB values (R, G, B)
    """
    ...


def hsv2xyz(hsl: Number3Tuple) -> Float3Tuple:
    """
    Convert HSV values to XYZ color space.
    :param hsl: Tuple with HSV values (0 <= H <= 360; 0 <= S <= 1; 0 <= V <= 1)
    :return: Tuple with XYZ values (X, Y, Z)
    """
    ...


def hsv2lab(hsv: Number3Tuple) -> Float3Tuple:
    """
    Convert HSV values to LAB color space.
    :param hsv: Tuple with HSV values (0 <= H <= 360; 0 <= S <= 1; 0 <= V <= 1)
    :return: Tuple with LAB values (L, A, B)
    """
    ...


def hsv2lch(hsv: Number3Tuple) -> Float3Tuple:
    """
    Convert HSV values to LCh color space.
    :param hsv: Tuple with HSV values (0 <= H <= 360; 0 <= S <= 1; 0 <= V <= 1)
    :return: Tuple with LCh values (L, C, H)
    """
    ...


def hsv2hsl(hsv: Number3Tuple) -> Float3Tuple:
    """
    Convert HSV values to HSL color space.
    :param hsv: Tuple with HSV values (0 <= H <= 360; 0 <= S <= 1; 0 <= V <= 1)
    :return: Tuple with HSL values (H, S, L)
    """
    ...


def oklab2rgb(oklab: Number3Tuple) -> Int3Tuple:
    """
    Convert OKlab values to RGB color space.
    :param oklab: Tuple with OKlab values (0 <= L <= 100; -127 <= A <= 127; -127 <= B <= 127)
    :return: Tuple with RGB values (R, G, B)
    """
    ...


def oklab2oklch(oklab: Number3Tuple) -> Float3Tuple:
    """
    Convert OKlab values to OKlch color space.
    :param oklab: Tuple with OKlab values (0 <= L <= 100; -127 <= A <= 127; -127 <= B <= 127)
    :return: Tuple with OKlch values (L, C, H)
    """
    ...


def oklch2rgb(oklch: Number3Tuple) -> Int3Tuple:
    """
    Convert OKlch values to RGB color space.
    :param oklch: Tuple with LCh values (0 <= L <= 100; 0 <= C <= 100; 0 <= h <= 360)
    :return: Tuple with RGB values (R, G, B)
    """
    ...


def oklch2oklab(oklch: Number3Tuple) -> Float3Tuple:
    """
    Convert OKlch values to OKlab color space.
    :param oklch: Tuple with LCh values (0 <= L <= 100; 0 <= C <= 100; 0 <= h <= 360)
    :return: Tuple with OKlab values (L, A, B)
    """
    ...


def deltaE76(lab1: Number3Tuple, lab2: Number3Tuple) -> float:
    """
    Calculates the CIE76 color difference (Delta E 1976) between two colors in the CIELAB color space.

    The CIE76 formula is the Euclidean distance between two LAB colors:

        ΔE* = sqrt(ΔL² + Δa² + Δb²)

    Where:
        - ΔL = L2 - L1 (lightness difference)
        - Δa = a2 - a1 (green-red chromatic difference)
        - Δb = b2 - b1 (blue-yellow chromatic difference)

    This metric is straightforward but may not always align with human color perception.

    :param lab1: The first color in CIELAB space (L*, a*, b*).
    :param lab2: The second color in CIELAB space (L*, a*, b*).


    :return: The Euclidean distance (ΔE*) between the two LAB colors.
    """
    ...


def deltaE_OK(oklab1: Number3Tuple, oklab2: Number3Tuple) -> float:
    """
    Calculates the OKLab color difference (Delta E OK) between two colors in the OKLab color space.

    The Delta E OK formula is a more perceptually uniform color difference metric compared to traditional methods 
    like CIE76 and CIE94.
    It provides better accuracy in predicting perceived color differences, particularly
    in high-chroma and low-lightness areas.

    The general formula is:

        ΔEOK = sqrt(ΔL² + Δa² + Δb²)

    Where:
        - ΔL = L2 - L1 (lightness difference)
        - Δa = a2 - a1 (green-red chromatic difference)
        - Δb = b2 - b1 (blue-yellow chromatic difference)

    This formula is similar to the Euclidean distance in CIE76 but benefits from the OKLab space's improved 
    perceptual uniformity, that is why it is more accurate color-difference formulae than the simple 1976 Euclidean distance in CIE Lab.

    :param oklab1: The first color in OKLab space (L*, a*, b*).
    :param oklab2: The second color in OKLab space (L*, a*, b*).

    :return: The perceptually improved color difference (ΔEOK) between the two OKLab colors.
    """
    ...


def deltaEOK_2(oklab1: Number3Tuple, oklab2: Number3Tuple) -> float:
    """
    Calculates the OKLab color difference (Delta E OK2) between two colors in the OKLab color space.

    The Delta E OK2 formula is an improved version of the standard OKLab color difference metric.
    It incorporates a scaling factor for the a and b axes relative to the L axis, resulting in better
    perceptual uniformity compared to the basic Euclidean distance.

    The general formula is:

        ΔEOK2 = sqrt(ΔL² + (Δa * S)² + (Δb * S)²)

    Where:
        - ΔL = L2 - L1 (lightness difference)
        - Δa = a2 - a1 (green-red chromatic difference)
        - Δb = b2 - b1 (blue-yellow chromatic difference)
        - S = 2 (scaling factor for a and b axes)

    This formula refines the perceptual accuracy of OKLab-based color differences, making it a
    more accurate color-difference formula than the simple 1976 Euclidean distance in CIE Lab.

    Björn Ottosson said:
        "I've recently done some tests with color distance datasets as implemented
        in Colorio and on both the Combvd dataset and the OSA-UCS dataset a
        scale factor of slightly more than 2 for a and b would give the best results
        (2.016 works best for Combvd and 2.045 for the OSA-UCS dataset)."

    :param oklab1: The first color in OKLab space (L*, a*, b*).
    :param oklab2: The second color in OKLab space (L*, a*, b*).

    :return: The perceptually improved color difference (ΔEOK2) between the two OKLab colors.
    """
    ...


def deltaE94(lab1: Number3Tuple, lab2: Number3Tuple) -> float:
    """
    Calculates the CIE94 color difference (Delta E 1994) between two colors in the CIELAB color space.

    The CIE94 formula improves upon CIE76 by incorporating weighting factors for better perceptual uniformity.
    The general formula is:

        ΔE94* = sqrt((ΔL / kL)² + (ΔC / kC)² + (ΔH / kH)²)

    Where:
        - ΔL = L2 - L1 (lightness difference)
        - ΔC = C2 - C1 (chroma difference)
        - ΔH = sqrt(Δa² + Δb² - ΔC²) (hue difference)
        - kL, kC, kH are weighting factors (typically 1 for graphics applications)

    :param lab1: The first color in CIELAB space (L*, a*, b*).
    :param lab2: The second color in CIELAB space (L*, a*, b*).

    :return: The perceptually improved color difference (ΔE94*) between the two LAB colors.
    """
    ...


def deltaE_CMC(lab1: Number3Tuple, lab2: Number3Tuple) -> float:
    """
    Calculates the CMC l:c color difference (Delta E CMC) between two colors in the CIELAB color space.

    The CMC formula improves upon CIE76 and CIE94 by introducing an ellipsoidal tolerance model
    that better represents human perception, especially for textiles.

    The general formula is:

        ΔE_CMC* = sqrt((ΔL / (l * SL))² + (ΔC / (c * SC))² + (ΔH / SH)²)

    where:
        - ΔL = L2 - L1 (lightness difference)
        - ΔC = C2 - C1 (chroma difference)
        - ΔH = sqrt(Δa² + Δb² - ΔC²) (hue difference)
        - SL, SC, SH are scaling factors based on chroma and hue
        - l (default=1) is the lightness factor (higher values make lightness differences more important)
        - c (default=1) is the chroma factor (higher values make chroma differences more important)

    :param lab1: The first color in CIELAB space (L*, a*, b*).
    :param lab2: The second color in CIELAB space (L*, a*, b*).


    :return: The perceptual color difference (ΔE_CMC*) between the two LAB colors.
    """
    ...


def deltaE2000(lab1: Number3Tuple, lab2: Number3Tuple) -> float:
    """
    Calculates the CIEDE2000 color difference (Delta E 2000) between two colors in the CIELAB color space.

    The CIEDE2000 formula is the most perceptually uniform Delta E metric, improving upon CIE76, CIE94, and CMC.
    It introduces corrections for chroma, hue, and neutral colors, making it more accurate for human vision.

    The general formula is:

        ΔE2000* = sqrt((ΔL' / (kL * SL))² + (ΔC' / (kC * SC))² + (ΔH' / (kH * SH))² + RT * (ΔC' / SC) * (ΔH' / SH))

    where:
        - ΔL' = L2 - L1 (lightness difference with scaling)
        - ΔC' = C2' - C1' (chroma difference with non-linear scaling)
        - ΔH' = 2 * sqrt(C1' * C2') * sin(Δh' / 2) (hue difference with weighting)
        - SL, SC, SH are weighting functions for lightness, chroma, and hue
        - RT is a rotation term that improves hue handling for blue colors
        - kL, kC, kH are weighting factors (default is 1 for standard use)

    :param lab1: The first color in CIELAB space (L*, a*, b*).
    :param lab2: The second color in CIELAB space (L*, a*, b*).


    :return: The perceptual color difference (ΔE2000*) between the two LAB colors.
    """
    ...


def linear_gradient(start_oklab: Number3Tuple, end_oklab: Number3Tuple, *, steps: NumberGT2 = 100) -> GradientList:
    """
    Generates a linear gradient between two colors in the OKLab color space.

    A linear gradient is computed by interpolating the lightness, a*, and b* components
    of the OKLab color space using linear interpolation. This provides a smooth transition
    between two colors, useful for blending and visualization.

    The interpolation formula for each step is:

        Oklab_t = (1 - t) * Oklab1 + t * Oklab2

    Where:
        - Oklab1 and Oklab2 are the start and end colors in OKLab space.
        - t is a normalized parameter ranging from 0 to 1, determined by the step index.
        - Linear interpolation is applied separately to the L, a, and b channels.
        - The number of steps must be greater than 2 to ensure a valid gradient.

    :param start_oklab: The starting color in OKLab space (L*, a*, b*).
    :param end_oklab: The ending color in OKLab space (L*, a*, b*).
    :param steps: The number of colors in the gradient (must be greater than 2, default is 100).

    :return: A list of OKLab colors forming a linear gradient from `start_oklab` to `end_oklab`.
    """
    ...


def cosine_gradient(start_oklab: Number3Tuple, end_oklab: Number3Tuple, *, steps: NumberGT2 = 100) -> GradientList:
    """
    Generates a cosine-interpolated gradient between two colors in the OKLab color space.

    Cosine interpolation provides a smoother and more visually natural transition compared to linear interpolation.
    It follows a cosine function curve, which results in a more gradual start and end while maintaining a
    smooth progression between colors.

    The interpolation formula for each step is:

        Oklab_t = Oklab1 + 0.5 * (Oklab2 - Oklab1) * (1 - cos(π * t))

    Where:
        - Oklab1 and Oklab2 are the start and end colors in OKLab space.
        - t is a normalized parameter ranging from 0 to 1, determined by the step index.
        - `Cos(π * t)` ensures a non-linear, smooth transition.
        - The number of steps must be greater than 2 to ensure a valid gradient.

    :param start_oklab: The starting color in OKLab space (L*, a*, b*).
    :param end_oklab: The ending color in OKLab space (L*, a*, b*).
    :param steps: The number of colors in the gradient (must be greater than 2, default is 100).

    :return: A list of OKLab colors forming a cosine-interpolated gradient from `start_oklab` to `end_oklab`.
    """
    ...
