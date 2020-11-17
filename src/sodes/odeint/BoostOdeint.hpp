#ifndef SODES_BOOSTODEINT_HPP
#define SODES_BOOSTODEINT_HPP

#include <Eigen/Core>
#include <boost/numeric/odeint.hpp>
#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint/external/eigen/eigen_resize.hpp>

#include <tuple>
#include <functional>
#include <vector>
#include <utility>
#include <stdexcept>

#include "math_types.hpp"

namespace sodes::detail::odeint {

using namespace boost::numeric::odeint;
using namespace Eigen;
using namespace std;

using namespace sodes::math_types;

typedef eigen_array_1d state_type;

struct Observer
{
    vector<state_type>& m_states;
    vector<double>& m_times;

    Observer(vector<state_type>& states, vector<double>& times)
        : m_states(states), m_times(times) {}

    void operator()(const state_type& x, const double& t)
    {
        m_states.push_back(x);
        m_times.push_back(t);
    }
};

template<typename Stepper>
pair<vector<double>, vector<state_type>> _integrate_const_stepper(
    const function<state_type(eigen_array_1d_constref, eigen_array_1d_ref, const double&)>& f,
    const tuple<double, double>& t_span,
    const double& dt,
    state_type& y0,
    Stepper stepper)
{
    // Containers to store solution
    vector<state_type> states;
    vector<double> times;

    // Integrate over time
    auto[t_init, t_final] = t_span;
    auto observer = Observer(states, times);
    integrate_const(
        stepper,
        f,
        y0,
        t_init,
        t_final,
        dt,
        observer);

    auto solution_pair = make_pair(times, states);

    return solution_pair;
}
}  // namespace sodes::detail::odeint

namespace sodes::odeint {

using namespace std;
using namespace Eigen;
using namespace sodes::math_types;

pair<vector<double>, vector<ArrayXd>> solve_ivp_const(
    const function<ArrayXd(eigen_array_1d_constref, eigen_array_1d_ref, const double&)>& f,
    const tuple<double, double>& t_span,
    const double& dt,
    ArrayXd& y0,
    const string& method = "runge_kutta4")
{
    using namespace sodes::detail::odeint;

    if (method == "runge_kutta4") {
        typedef runge_kutta4<state_type, double, state_type, double, vector_space_algebra> stepper;
        return _integrate_const_stepper<stepper>(f, t_span, dt, y0, stepper());
    }
//    else if (method == "runge_kutta_dopri5") {
//        typedef runge_kutta_dopri5<state_type, double, state_type, double, vector_space_algebra> stepper;
//        auto dense_output = make_dense_output<stepper>(1e-6, 1e-6);
//        return _integrate_const_stepper<dense_output>(f, t_span, dt, y0, dense_output);
//    }
    else if (method == "runge_kutta_cash_karp54") {
        typedef runge_kutta_cash_karp54<state_type, double, state_type, double, vector_space_algebra> stepper;
        return _integrate_const_stepper<stepper>(f, t_span, dt, y0, stepper());
    }
    else if (method == "runge_kutta_fehlberg78") {
        typedef runge_kutta_fehlberg78<state_type, double, state_type, double, vector_space_algebra> stepper;
        return _integrate_const_stepper<stepper>(f, t_span, dt, y0, stepper());
    }
    else if (method == "modified_midpoint") {
        typedef modified_midpoint<state_type, double, state_type, double, vector_space_algebra> stepper;
        return _integrate_const_stepper<stepper>(f, t_span, dt, y0, stepper());
    }
    else if (method == "euler") {
        typedef euler<state_type, double, state_type, double, vector_space_algebra> stepper;
        return _integrate_const_stepper<stepper>(f, t_span, dt, y0, stepper());
    }
    else {
        throw invalid_argument("Unavailable integration method from Boost::odeint");
    }
}
}  // namespace sodes::odeint

#endif //SODES_BOOSTODEINT_HPP
