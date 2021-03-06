#include <iostream>
#include <Eigen/Core>
#include <cstdlib>
#include <boost/numeric/odeint.hpp>

// DO NOT USE <boost/numeric/odeint/external/eigen/eigen_algebra.hpp>
// It does not work with Dynamic Eigen Matrix. You have to use regular
// vector_space_algebra combined with eigen_resize in order to deal
// with dynamic sizes.
#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint/external/eigen/eigen_resize.hpp>

using namespace boost::numeric::odeint;
using namespace Eigen;

typedef ArrayXd state_type;

// System to be solved
void lorenz(const state_type &x, state_type &dxdt, const double &t)
{
    double sigma = 10.0;
    double R = 28.0;
    double b = 8.0 / 3.0;

    dxdt[0] = sigma * (x[1] - x[0]);
    dxdt[1] = R * x[0] - x[1] - x[0] * x[2];
    dxdt[2] = -b * x[2] + x[0] * x[1];
}

// An example of observer to record steps in the integration
struct observer
{
    std::vector<state_type> &m_states;
    std::vector<double> &m_times;

    observer(std::vector<state_type> &states, std::vector<double> &times)
        : m_states(states), m_times(times) {}

    void operator()(const state_type &x, const double &t)
    {
        m_states.push_back(x);
        m_times.push_back(t);
    }
};

int main()
{
    // Defining the state vector with initial conditions
    int num_of_states = 3;
    state_type X(num_of_states);
    X << 0., 1., 0.1;

    // Containers to store solution
    std::vector<state_type> x_sol;
    std::vector<double> times;

    // Set custom stepper for Eigen algebra and state
    typedef runge_kutta4<state_type, double, state_type, double, vector_space_algebra> stepper;

    // Integrate over time
    auto t_init = 0.0;
    auto t_final = 10.0;
    auto dt = 0.01;
    auto steps = integrate_const(
        stepper(),
        lorenz,
        X,
        t_init,
        t_final,
        dt,
        observer(x_sol, times));

    // Displaying result on terminal
    for (size_t i = 0; i <= steps; i++)
    {
        std::cout << times[i] << '\t' << x_sol[i][0] << '\t' << x_sol[i][1] << '\t' << x_sol[i][2] << '\n';
    }

    // And, of course, it can be integrated step-wisely
    std::cout << "\n*******************\n\n";

    X << 0., 1., 0.1;
    std::cout << 0.0 << '\t' << X[0] << '\t' << X[1] << '\t' << X[2] << '\n';
    for (auto t = t_init; t < t_final; t += dt)
    {
        stepper().do_step(lorenz, X, t, dt);
        std::cout << t << '\t' << X[0] << '\t' << X[1] << '\t' << X[2] << '\n';
    }
}