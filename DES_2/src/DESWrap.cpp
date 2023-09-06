#include <pybind11/pybind11.h>
#include "DES.hpp"
#include <string>

namespace py = pybind11;

PYBIND11_MODULE(DES, m){
    py::class_<DES>("DES", py::init<string, char()>)
    .def("expansion_ri", &DES::expansion_ri, py::call_guard<py::gil_scoped_release>())
    .def("encrypt", &DES::encrypt, py::call_guard<py::gil_scoped_release>())
    .def("key_sched_des", &DES::key_sched_des, py::call_guard<py::gil_scoped_release>())
    .def("F", &DES::F, py::call_guard<py::gil_scoped_release>())
    .def("pc_1", &DES::pc_1, byref)
    .def("num_leftShift", &DES::num_leftShift, byref)
    .def("num_rightShift", &DES::num_rightShift, byref)
    .def("pc_2", &DES::pc_2, byref)
    .def("IP_t", &DES::IP_t, byref)
    .def("E_t", &DES::E_t, byref)
    .def("S", &DES::S, byref)
    .def("P", &DES::P, byref)
    .def("P_1", &DES::P_1, byref)
    .def("cipherBlock", &DES::cipherBlock, byref)
    .def("PlainBlock", &DES::PlainBlock, byref)
    .def("Blocks", &DES::Blocks, byref)
}