#include <pybind11/pybind11.h>
#include "Binary.hpp"
#include <string>

namespace py = pybind11;

void exposeBinary(py::module &m){
    m.def("bit_to_dec", &Binary::bit_to_dec);
    m.def("shiftbits", &Binary::shiftbits);
    m.def("xOr", &Binary::xOr);
    m.def("hex2bin", &Binary::hex2bin);
    m.def("bin2hex", &Binary::bin2hex);
    m.def("hex2dec", &Binary::hex2dec);
    m.def("Dec_to_Bin", &Binary::Dec_to_Bin);
    m.def("txttoBits", &Binary::txttoBits);
    m.def("hex2char", &Binary::hex2char);
}

PYBIND11_MODULE(Binary, m){
    m.doc() = "My Binary Module";
    exposeBinary(m);
}