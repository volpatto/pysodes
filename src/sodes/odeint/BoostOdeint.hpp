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

namespace sodes::detail::odeint {

using namespace boost::numeric::odeint;
using namespace Eigen;
using namespace std;

typedef ArrayXd state_type;

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

pair<vector<double>, vector<state_type>> integrate_rk4(
    const function<state_type(const state_type&, state_type&, const double&)>& f,
    const tuple<double, double>& t_span,
    const double& dt,
    state_type& y0)
{
    // Containers to store solution
    vector<state_type> states;
    vector<double> times;

    // Set custom stepper for Eigen algebra and state
    typedef runge_kutta4<state_type, double, state_type, double, vector_space_algebra> stepper;

    // Integrate over time
    auto[t_init, t_final] = t_span;
    auto observer = Observer(states, times);
    integrate_const(
        stepper(),
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

pair<vector<double>, vector<ArrayXd>> solve_ivp(
    const function<ArrayXd(const ArrayXd&, ArrayXd&, const double&)>& f,
    const tuple<double, double>& t_span,
    const double& dt,
    ArrayXd& y0,
    const string& method = "runge_kutta4")
{
    using namespace sodes::detail::odeint;

    if (method == "runge_kutta4")
    {
        return integrate_rk4(f, t_span, dt, y0);
    }
    else
        throw invalid_argument("Unavailable integration method from Boost::odeint");
}
}  // namespace sodes::odeint

#endif //SODES_BOOSTODEINT_HPP
