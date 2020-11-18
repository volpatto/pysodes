#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/eigen.h>

#include "BoostOdeint.hpp"

using namespace sodes;

namespace py = pybind11;

PYBIND11_MODULE(sodes_bindings, m)
{
    m.doc() = "Binding for sODEs in Python"; // optional module docstring

    m.def("_integrate_const", &odeint::solve_ivp_const, R"pbdoc(
        Integrate over time with constant time-step from Boost::odeint.
    )pbdoc",
    py::arg("f"),
    py::arg("t_span"),
    py::arg("dt"),
    py::arg("y0"),
    py::arg("method")
    );
}
