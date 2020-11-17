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

    m.def("solve_ivp_odeint", &odeint::solve_ivp_const, R"pbdoc(
        Integrate over time with Boost::odeint wrapper.
    )pbdoc");
}
