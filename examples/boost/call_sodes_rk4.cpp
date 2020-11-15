#include "BoostOdeint.hpp"

#include <Eigen/Core>

#include <tuple>
#include <iostream>

using namespace sodes::odeint;
using namespace Eigen;

// System to be solved
ArrayXd lorenz(const ArrayXd &x, ArrayXd &dxdt, const double &t)
{
    double sigma = 10.0;
    double R = 28.0;
    double b = 8.0 / 3.0;

    dxdt[0] = sigma * (x[1] - x[0]);
    dxdt[1] = R * x[0] - x[1] - x[0] * x[2];
    dxdt[2] = -b * x[2] + x[0] * x[1];

    return dxdt;
}

int main (){
    // Defining the state vector with initial conditions
    int num_of_states = 3;
    ArrayXd X(num_of_states);
    X << 0., 1., 0.1;

    // Set time range and increment
    auto t_init = 0.0;
    auto t_final = 10.0;
    auto t_span = std::make_tuple(t_init, t_final);
    auto dt = 0.01;

    // Containers to store solution
    std::vector<ArrayXd> x_sol;
    std::vector<double> times;
    std::tie(times, x_sol) = solve_ivp(lorenz, t_span, dt, X);

    // Displaying result on terminal
    auto steps = times.size();
    for (size_t i = 0; i < steps; i++)
    {
        std::cout << times[i] << '\t' << x_sol[i][0] << '\t' << x_sol[i][1] << '\t' << x_sol[i][2] << '\n';
    }
}
