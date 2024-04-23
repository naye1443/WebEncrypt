#include <pybind11/pybind11.h>
#include "BCM.hpp"
#include <string>

namespace py = pybind11;

PYBIND11_MODULE(BCM, m){
    py::class_<BCM>(m,"BCM")
        .def(py::init<std::string, std::string, char>())
        .def("OFB", &BCM::OFB)
        .def("AuxOFB", &BCM::OFB)
        .def("comtxt", &BCM::comtxt);
}