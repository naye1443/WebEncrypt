from pathlib import Path

from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

files = ['../DES_2/src/Binary.cpp', '../DES_2/src/BinaryWrap.cpp', '../DES_2/src/DES.cpp', '../DES_2/src/DESWrap.cpp', '../DES_2/src/BCM.cpp', '../DES_2/src/BCMWrap.cpp' ]

abs_filepath = []

# for each files, resolve the absolute file path and append to list
for file in files:
    file_path_obj = Path(file)
    abs_filepath.append(str(file_path_obj.resolve()))

Binary = Pybind11Extension(
    'Binary',
    sources=[abs_filepath[0],abs_filepath[1]],
    include_dirs=['../DES_2/include'],
    extra_compile_args=['-O3']
)


DES = Pybind11Extension(
    'DES',
    sources=[abs_filepath[2], abs_filepath[3], abs_filepath[0]],
    include_dirs=['../DES_2/include'],
    extra_compile_args=['-O3']
)

BCM = Pybind11Extension(
    'BCM',
    sources=[abs_filepath[4], abs_filepath[5], abs_filepath[0], abs_filepath[2]],
    include_dirs=['../DES_2/include'],
    extra_compile_args=['-O3']
)


setup(
    name='DES Encrypt&Decrypt',
    version='0.1',
    author='Eyan Eubanks',
    author_email='N/A',
    description='Gives Encryption and decryption using Block cipher encryption modes',
    ext_modules=[Binary, DES, BCM],
    cmdclass={"build_ext": build_ext},
)