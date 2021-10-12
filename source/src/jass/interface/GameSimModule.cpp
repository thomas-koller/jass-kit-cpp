//
// Created by Thomas Koller on 11/10/2021.
//

#include <pybind11/pybind11.h>
#include <jass/game/GameSim.hpp>
#include <jass/game/RuleSchieber.hpp>

namespace py = pybind11;

PYBIND11_MODULE(jasscpp, m) {
    m.doc() = "Binding to cpp jass interface";
    py::class_<jass::GameSim>(m, "GameSimCpp")
            .def(py::init([](){auto rule = std::make_shared<jass::RuleSchieber>();return jass::GameSim(rule);}))
            .def("initFromCards", &jass::GameSim::initFromCards)
            .def("performActionPlayCard", &jass::GameSim::performActionPlayCard)
            .def("performActionTrump", &jass::GameSim::performActionTrump)
            .def("performActionFull", &jass::GameSim::performActionFull)
            .def("isDone", &jass::GameSim::isDone)
            .def_readwrite("state", &jass::GameSim::state);
}
