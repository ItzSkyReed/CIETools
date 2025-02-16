def rgb2lab(rgb: tuple[int, int, int]) -> tuple[float, float, float]:
    """
    Convert RGB values (in the range 0-255) to LAB color space.
    :param rgb: Tuple with RGB values (R, G, B)
    :return: Tuple with LAB values (L, A, B)
    """
    ...


def rgb2lch(rgb: tuple[int, int, int]) -> tuple[float, float, float]:
    """
    Convert RGB values (in the range 0-255) to LCh color space.
    :param rgb: Tuple with RGB values (R, G, B)
    :return: Tuple with LCh values (L, C, h)
    """
    ...


def rgb2xyz(rgb: tuple[int, int, int]) -> tuple[float, float, float]:
    """
    Convert RGB values (in the range 0-255) to XYZ color space.
    :param rgb: Tuple with RGB values (R, G, B)
    :return: Tuple with XYZ values (X, Y, Z)
    """
    ...


def xyz2lab(xyz: tuple[float, float, float]) -> tuple[float, float, float]:
    """
    Convert XYZ values to LAB color space.
    :param xyz: Tuple with XYZ values (X > 0; 0 <= Y <= 100; Z > 0)
    :return: Tuple with LAB values (L, A, B)
    """
    ...


def xyz2lch(xyz: tuple[float, float, float]) -> tuple[float, float, float]:
    """
    Convert XYZ values to LCh color space.
    :param xyz: Tuple with XYZ values (X > 0; 0 <= Y <= 100; Z > 0)
    :return: Tuple with LCh values (L, C, h)
    """
    ...


def xyz2rgb(xyz: tuple[float, float, float]) -> tuple[int, int, int]:
    """
    Convert XYZ values to RGB color space.
    :param xyz: Tuple with XYZ values (X > 0; 0 <= Y <= 100; Z > 0)
    :return: Tuple with RGB values (R, G, B)
    """
    ...


def lab2lch(lab: tuple[float, float, float]) -> tuple[float, float, float]:
    """
    Convert LAB values to LCh color space.
    :param lab: Tuple with LAB values (0 <= L <= 100; -127 <= A <= 127; -127 <= B <= 127)
    :return: Tuple with LCh values (L, C, h)
    """
    ...


def lab2xyz(lab: tuple[float, float, float]) -> tuple[float, float, float]:
    """
    Convert LAB values to XYZ color space.
    :param lab: Tuple with LAB values (0 <= L <= 100; -127 <= A <= 127; -127 <= B <= 127)
    :return: Tuple with XYZ values (X, Y, Z)
    """
    ...


def lab2rgb(lab: tuple[float, float, float]) -> tuple[int, int, int]:
    """
    Convert LAB values to RGB color space.
    :param lab: Tuple with LAB values (0 <= L <= 100; -127 <= A <= 127; -127 <= B <= 127)
    :return: Tuple with RGB values (R, G, B)
    """
    ...


def lch2lab(lch: tuple[float, float, float]) -> tuple[float, float, float]:
    """
    Convert LCh values to LAB color space.
    :param lch: Tuple with LCh values (0 <= L <= 100; 0 <= C <= 100; 0 <= h <= 360)
    :return: Tuple with LAB values (L, A, B)
    """
    ...


def lch2xyz(lch: tuple[float, float, float]) -> tuple[float, float, float]:
    """
    Convert LCh values to XYZ color space.
    :param lch: Tuple with LAB values (0 <= L <= 100; 0 <= C <= 100; 0 <= h <= 360)
    :return: Tuple with XYZ values (X, Y, Z)
    """
    ...


def lch2rgb(lch: tuple[float, float, float]) -> tuple[int, int, int]:
    """
    Convert LCh values to RGB color space.
    :param lch: Tuple with LAB values (0 <= L <= 100; 0 <= C <= 100; 0 <= h <= 360)
    :return: Tuple with RGB values (R, G, B)
    """
    ...


def deltaE76(lab1: tuple[float, float, float], lab2: tuple[float, float, float]) -> float:
    """
    Calculates the CIE76 color difference (Delta E 1976) between two colors in the CIELAB color space.

    The CIE76 formula is the Euclidean distance between two LAB colors:

        ΔE* = sqrt((L2 - L1)² + (a2 - a1)² + (b2 - b1)²)

    This metric is straightforward but may not always align with human color perception.

    :param lab1: Tuple[float, float, float]
        The first color in CIELAB space (L*, a*, b*).
    :param lab2: Tuple[float, float, float]
        The second color in CIELAB space (L*, a*, b*).

    :return: The Euclidean distance (ΔE*) between the two LAB colors.
    """
    ...


def deltaE94(lab1: tuple[float, float, float], lab2: tuple[float, float, float]) -> float:
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

    :param lab1: Tuple[float, float, float]
        The first color in CIELAB space (L*, a*, b*).
    :param lab2: Tuple[float, float, float]
        The second color in CIELAB space (L*, a*, b*).

    :return: The perceptually improved color difference (ΔE94*) between the two LAB colors.
    """
    ...

def deltaE_CMC(lab1: tuple[float, float, float], lab2: tuple[float, float, float]) -> float:
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

    :param lab1: Tuple[float, float, float]
        The first color in CIELAB space (L*, a*, b*).
    :param lab2: Tuple[float, float, float]
        The second color in CIELAB space (L*, a*, b*).

    :return: The perceptual color difference (ΔE_CMC*) between the two LAB colors.
    """
    ...

def deltaE2000(lab1: tuple[float, float, float], lab2: tuple[float, float, float]) -> float:
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

    :param lab1: Tuple[float, float, float]
        The first color in CIELAB space (L*, a*, b*).
    :param lab2: Tuple[float, float, float]
        The second color in CIELAB space (L*, a*, b*).

    :return: The perceptual color difference (ΔE2000*) between the two LAB colors.
    """
    ...