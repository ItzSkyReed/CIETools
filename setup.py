from setuptools import setup, Extension, find_packages
import sys

is_msvc = sys.platform == "win32"
if is_msvc:
    extra_compile_args = ['/std:c11', '/O2', '/fp:fast']
else:
    extra_compile_args = ['-std=c11', '-O3', '-ffast-math']

module = Extension(
    'cietools._cietools_c_ext',
    sources=[
        'src/cietools/cietools.c',
        'src/cietools/conversions.c',
        'src/cietools/color_difference.c',
        'src/cietools/gradients.c',
        'src/cietools/py_operations/rgb_conversions.c',
        'src/cietools/py_operations/lch_conversions.c',
        'src/cietools/py_operations/lab_conversions.c',
        'src/cietools/py_operations/xyz_conversions.c',
        'src/cietools/py_operations/hsv_conversions.c',
        'src/cietools/py_operations/hsl_conversions.c',
        'src/cietools/py_operations/oklab_conversions.c',
        'src/cietools/py_operations/oklch_conversions.c',
        'src/cietools/py_operations/delta_e.c',
        'src/cietools/py_operations/color_utils.c',
        'src/cietools/py_operations/common.c'
    ],
    extra_compile_args=extra_compile_args,
    extra_link_args=[]
)


setup(
    name='cietools',
    version='0.4.0',
    description='cietools is a library to work with CIE format',
    ext_modules=[module],
    packages=find_packages(),
    package_data={
        'cietools': [
            '*.pyi',
            'py.typed'
        ]
    },
    include_package_data=True,
    zip_safe=False
)