#include <pybind11/pybind11.h>
#include "DES.hpp"
#include <string>
#include <vector>
#include "Binary.hpp"

class PublicDES : public DES {

public:
    using DES::DES;
    using DES::expansion_ri;
    using DES::encrypt;
    using DES::key_sched_des;
    using DES::F;
    using DES::pc_1;
	using DES::num_leftShift;
	using DES::num_rightShift;
	using DES::pc_2;
	using DES::IP_t;
	using DES::E_t;
	using DES::S;
	using DES::P;
	using DES::P_1;
    using DES::get_S;

	using DES::cipherBlock;
	using DES::PlainBlock;
	using DES::Blocks;
};

namespace py = pybind11;

PYBIND11_MODULE(DES, m){
    py::class_<DES>(m,"DES")
        .def(py::init< std::string, char>())
        .def("expansion_ri", &PublicDES::expansion_ri)
        .def("encrypt", &PublicDES::encrypt)
        .def("key_sched_des", &PublicDES::key_sched_des)
        .def("F", &PublicDES::F)
        .def_readonly("pc_1", &PublicDES::pc_1)
        .def_readonly("numleftShift", &PublicDES::num_leftShift)
        .def_readonly("numrightShift", &PublicDES::num_rightShift)
        .def_readonly("pc_2", &PublicDES::pc_2)
        .def_readonly("IPt", &PublicDES::IP_t)
        .def_readonly("Et", &PublicDES::E_t)
        .def("S", &PublicDES::get_S)
        .def_readonly("P", &PublicDES::P)
        .def_readonly("P1", &PublicDES::P_1)
        .def_readwrite("cipherBlock", &PublicDES::cipherBlock)
        .def_readwrite("plainBlock", &PublicDES::PlainBlock)
        .def_readwrite("Blocks", &PublicDES::Blocks);
    
}