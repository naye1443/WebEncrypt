from pathlib import Path

from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

# Change directory accordingly
Binary = Pybind11Extension(
    'Binary',
    sources=['../DES_2/src/Binary.cpp','../DES_2/src/BinaryWrap.cpp'],
    include_dirs=['../DES_2/include'],
    extra_compile_args=['-O3']
)

setup(
    name='Binary',
    version='0.1',
    author='Eyan Eubanks',
    author_email='N/A',
    description='Binary functionality for DES lib',
    ext_modules=[Binary],
    cmdclass={"build_ext": build_ext},
)