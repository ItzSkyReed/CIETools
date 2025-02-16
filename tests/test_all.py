import unittest

import cietools as ct
import math
import sys

def assertCloseEqualTuple(self, clr1, clr2, tolerance=sys.float_info.epsilon):
    for a, b in zip(clr1, clr2):
        self.assertTrue(math.isclose(a, b, abs_tol=tolerance))

def assertCloseEqual(self, clr1, clr2, tolerance=sys.float_info.epsilon * 3):
    self.assertTrue(math.isclose(clr1, clr2, abs_tol=tolerance))

functions = {
    "rgb": [
        ct.rgb2lab,
        ct.rgb2lch,
        ct.rgb2xyz
    ],
    "xyz": [
        ct.xyz2lab,
        ct.xyz2lch,
        ct.xyz2rgb
    ],
    "lab": [
        ct.lab2lch,
        ct.lab2rgb,
        ct.lab2xyz],
    "lch": [
        ct.lch2lab,
        ct.lch2rgb,
        ct.lch2xyz
    ]}


class TestConversionsArgumentsConfiguration(unittest.TestCase):
    def test_too_many_arguments(self):
        for func in functions["rgb"]:
            with self.assertRaises(TypeError):
                func((100, 200, 100), 100)
        for func in functions["xyz"]:
            with self.assertRaises(TypeError):
                func((0, 0, 0), 100)
        for func in functions["lab"]:
            with self.assertRaises(TypeError):
                func((0, 0, 0), 100)
        for func in functions["lch"]:
            with self.assertRaises(TypeError):
                func((0, 0, 0), 100)

    def test_too_few_arguments(self):
        for func in functions["rgb"]:
            with self.assertRaises(TypeError):
                func()
        for func in functions["xyz"]:
            with self.assertRaises(TypeError):
                func()
        for func in functions["lab"]:
            with self.assertRaises(TypeError):
                func()
        for func in functions["lch"]:
            with self.assertRaises(TypeError):
                func()

    def test_invalid_arguments(self):
        for func in functions["rgb"]:
            with self.assertRaises(TypeError):
                func(("v", 100, 100))
            with self.assertRaises(ValueError):
                func((100000000, 100, 100))
            with self.assertRaises(ValueError):
                func((100, 100))
        for func in functions["lab"]:
            with self.assertRaises(TypeError):
                func(("v", 100, 100))
            with self.assertRaises(ValueError):
                func((-1.0, 100.0, 100.0))
            with self.assertRaises(ValueError):
                func((101.0, 100.0, 100.0))
            with self.assertRaises(ValueError):
                func((10.0, 128.0, 100.0))
            with self.assertRaises(ValueError):
                func((10.0, 100.0, 128.0))
            with self.assertRaises(ValueError):
                func((100, 100))
        for func in functions["xyz"]:
            with self.assertRaises(TypeError):
                func(("v", 100, 100))
            with self.assertRaises(ValueError):
                func((-1.0, 100.0, 100.0))
            with self.assertRaises(ValueError):
                func((10.0, 128.0, 100.0))
            with self.assertRaises(ValueError):
                func((10.0, 99.0, -1.0))
            with self.assertRaises(ValueError):
                func((100, 100))
        for func in functions["lch"]:
            with self.assertRaises(TypeError):
                func(("v", 100, 100))
            with self.assertRaises(ValueError):
                func((-1.0, 100.0, 100.0))
            with self.assertRaises(ValueError):
                func((101.0, 100.0, 100.0))
            with self.assertRaises(ValueError):
                func((10.0, 128.0, 361.0))
            with self.assertRaises(ValueError):
                func((10.0, 128.0, -1.0))
            with self.assertRaises(ValueError):
                func((10.0, 1000.0, 1.0))
            with self.assertRaises(ValueError):
                func((10.0, -1.0, 1.0))
            with self.assertRaises(ValueError):
                func((100, 100))


class TestConversions(unittest.TestCase):
    def test_rgb(self):
        assertCloseEqualTuple(self, ct.rgb2lab((51, 45, 72)), (20.23693419943732, 9.728977611613232, -15.83289379823567))
        assertCloseEqualTuple(self, ct.rgb2lab((0, 0, 0)), (0.0, 0.0, 0.0))
        assertCloseEqualTuple(self, ct.rgb2lab((255, 255, 255)), (100, 0.00526049995830391, -0.010408184525267927))

        assertCloseEqualTuple(self, ct.rgb2xyz((51, 45, 72)), (0.0347332563215008, 0.030484591127394597, 0.06536238063629113))
        assertCloseEqualTuple(self, ct.rgb2xyz((0, 0, 0)), (0.0, 0.0, 0.0))
        assertCloseEqualTuple(self, ct.rgb2xyz((255, 255, 255)), (0.9505, 1.0, 1.089))

        assertCloseEqualTuple(self, ct.rgb2lch((51, 45, 72)), (20.23693419943732, 18.58315181538054, 301.56984333456785))
        assertCloseEqualTuple(self, ct.rgb2lch((0, 0, 0)), (0.0, 0.0, 0.0))
        assertCloseEqualTuple(self, ct.rgb2lch((255, 255, 255)), (100.0, 0.011662039483869973, 296.81292623674057))

    def test_xyz(self):
        assertCloseEqualTuple(self, ct.xyz2lab((0.12, 0.13, 0.41)), (42.763245421570275, -2.457076553917248, -43.10757831194276))
        assertCloseEqualTuple(self, ct.xyz2lab((0.0, 0.0, 0.0)), (0.0, 0.0, 0.0))
        assertCloseEqualTuple(self, ct.xyz2lab((1.0, 1.0, 1.0)), (100.0, 8.538533672582393, 5.593863452017245))

        self.assertEqual(ct.xyz2rgb((0.12, 0.13, 0.41)), (0, 106, 172))
        self.assertEqual(ct.xyz2rgb((0.0, 0.0, 0.0)), (0, 0, 0))
        self.assertEqual(ct.xyz2rgb((1.0, 1.0, 1.0)), (255, 249, 244))

        assertCloseEqualTuple(self, ct.xyz2lch((0.12, 0.13, 0.41)), (42.763245421570275, 43.17754663146214, 266.7377440232716))
        assertCloseEqualTuple(self, ct.xyz2lch((0.0, 0.0, 0.0)), (0.0, 0.0, 0.0))
        assertCloseEqualTuple(self, ct.xyz2lch((1.0, 1.0, 1.0)), (100.0, 10.207735576396837, 33.230075953383746))

    def test_lab(self):
        assertCloseEqualTuple(self, ct.lab2xyz((43.54, -54.58, 22.87)), (0.0627272294323145, 0.1352236091731928, 0.06912524043521166))
        assertCloseEqualTuple(self, ct.lab2xyz((0.0, 0.0, 0.0)), (0.0, 0.0, 0.0))
        assertCloseEqualTuple(self, ct.lab2xyz((100.0, 127.0, 127.0)), (1.87426512028008, 0.9999999999999999, 0.052946672513749994))

        self.assertEqual(ct.lab2rgb((43.54, -54.58, 22.87)), (0, 122, 63))
        self.assertEqual(ct.lab2rgb((0.0, 0.0, 0.0)), (0, 0, 0))
        self.assertEqual(ct.lab2rgb((100.0, 127.0, 127.0)), (255, 70, 0))

        assertCloseEqualTuple(self, ct.lab2lch((43.54, -54.58, 22.87)), (43.54, 59.17781087536105, 157.26544086809096))
        assertCloseEqualTuple(self, ct.lab2lch((0.0, 0.0, 0.0)), (0.0, 0.0, 0.0))
        assertCloseEqualTuple(self, ct.lab2lch((100.0, 127.0, 127.0)), (100.0, 179.60512242138307, 45.0))

    def test_lch(self):
        assertCloseEqualTuple(self, ct.lch2xyz((43.54, 54.58, 22.87)), (0.21985439114262495, 0.1352236091731928, 0.07352469503268395))
        assertCloseEqualTuple(self, ct.lch2xyz((0.0, 0.0, 0.0)), (0.0, 0.0, 0.0))
        assertCloseEqualTuple(self, ct.lch2xyz((100.0, 127.0, 127.0)), (0.5778331015482137, 0.9999999999999999, 0.13036105001204157))

        self.assertEqual(ct.lch2rgb((43.54, 54.58, 22.87)), (182, 59, 71))
        self.assertEqual(ct.lch2rgb((0.0, 0.0, 0.0)), (0, 0, 0))
        self.assertEqual(ct.lch2rgb((100.0, 127.0, 127.0)), (142, 255, 0))

        assertCloseEqualTuple(self, ct.lch2lab((43.54, 54.58, 22.87)), (43.54, 50.28941293571417, 21.212056632519733))
        assertCloseEqualTuple(self, ct.lch2lab((0.0, 0.0, 0.0)), (0.0, 0.0, 0.0))
        assertCloseEqualTuple(self, ct.lch2lab((100.0, 127.0, 127.0)), (100.0, -76.43050794031014, 101.42670977600619))

class TestDeltaEArgumentConfigurations(unittest.TestCase):
    lab1 = (43.54, 54.58, 22.87)
    lab2 = (43.54, 60.58, 87.87)
    lab3 = (1.51, 60.58, 57.87)
    def test_too_many_arguments(self):
        with self.assertRaises(TypeError):
            ct.deltaE76(self.lab1, self.lab2, self.lab3)
        with self.assertRaises(TypeError):
            ct.deltaE94(self.lab1, self.lab2, self.lab3)
        with self.assertRaises(TypeError):
            ct.deltaE_CMC(self.lab1, self.lab2, self.lab3)
        with self.assertRaises(TypeError):
            ct.deltaE2000(self.lab1, self.lab2, self.lab3)

    def test_too_few_arguments(self):
        with self.assertRaises(TypeError):
            ct.deltaE76(self.lab1)
        with self.assertRaises(TypeError):
            ct.deltaE94(self.lab1)
        with self.assertRaises(TypeError):
            ct.deltaE_CMC(self.lab1)
        with self.assertRaises(TypeError):
            ct.deltaE2000(self.lab1)

    def test_wrong_type_arguments(self):
        with self.assertRaises(TypeError):
            ct.deltaE76(self.lab1, "123")
        with self.assertRaises(TypeError):
            ct.deltaE94(self.lab1, "123")
        with self.assertRaises(TypeError):
            ct.deltaE_CMC(self.lab1, "123")
        with self.assertRaises(TypeError):
            ct.deltaE2000(self.lab1, "123")
        with self.assertRaises(TypeError):
            ct.deltaE76("123", self.lab2)
        with self.assertRaises(TypeError):
            ct.deltaE94("123", self.lab2)
        with self.assertRaises(TypeError):
            ct.deltaE_CMC("123", self.lab2)
        with self.assertRaises(TypeError):
            ct.deltaE2000("123", self.lab2)

class TestDeltaEResults(unittest.TestCase):
    lab1 = (43.54, 54.58, 22.87)
    lab2 = (43.54, 60.58, 87.87)
    lab3 = (1.51, 60.58, 57.87)
    lab4 = (43.54, 55.58, 22.87)
    def test_delta_e1976(self):
        assertCloseEqual(self, ct.deltaE76(self.lab1, self.lab2), 65.27633568147036)
        assertCloseEqual(self, ct.deltaE76(self.lab1, self.lab3), 55.0229125001576)
        assertCloseEqual(self, ct.deltaE76(self.lab1, self.lab4), 1.0)
    def test_delta_e1994(self):
        assertCloseEqual(self, ct.deltaE94(self.lab1, self.lab2), 27.014190237467364)
        assertCloseEqual(self, ct.deltaE94(self.lab1, self.lab3), 44.672905702167995)
        assertCloseEqual(self, ct.deltaE94(self.lab1, self.lab4), 0.3237895227067665)

    def test_delta_e_CMC(self):
        assertCloseEqual(self, ct.deltaE_CMC(self.lab1, self.lab2), 33.03114344533832)
        assertCloseEqual(self, ct.deltaE_CMC(self.lab1, self.lab3), 45.560631870569885)
        assertCloseEqual(self, ct.deltaE_CMC(self.lab1, self.lab4), 0.41238366109844626)

    def test_delta_e2000(self):
        assertCloseEqual(self, ct.deltaE2000(self.lab1, self.lab2), 25.67274409689742)
        assertCloseEqual(self, ct.deltaE2000(self.lab1, self.lab3), 33.51375140397363)
        assertCloseEqual(self, ct.deltaE2000(self.lab1, self.lab4), 0.32775686163897877)

if __name__ == "__main__":
    unittest.main()
