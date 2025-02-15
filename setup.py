from setuptools import setup, Extension
import sys
is_msvc = sys.platform == "win32"

if is_msvc:
    extra_compile_args = ['/std:c11', '/O2', '/fp:fast', '/arch:AVX2']
else:
    extra_compile_args = ['-std=c11', '-O3', '-march=native', '-ffast-math']

module = Extension(
    'cietools',
    sources=[
        'src/cietools/cietools.c',
        'src/cietools/conversions.c',
        'src/cietools/color_difference.c',
        'src/cietools/py_operations/rgb_conversions.c',
        'src/cietools/py_operations/lch_conversions.c',
        'src/cietools/py_operations/lab_conversions.c',
        'src/cietools/py_operations/xyz_conversions.c',
        'src/cietools/py_operations/delta_e.c'
    ],

    extra_compile_args=extra_compile_args,
    extra_link_args=[]
)

setup(
    name='cietools',
    version='0.1',
    description='cietools is a library to work with CIE format',
    ext_modules=[module],
    include_package_data=True
)