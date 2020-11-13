/*
 * This example was gathered from Stack Overflow. Only small modification were introduced.
 *
 * Check here: https://stackoverflow.com/questions/35656237/dynamic-eigen-vectors-in-boostodeint
 *
 * Credit: Sjonnie (user nickname)
 */

#include <iostream>
#include <Eigen/Core>
#include <cstdlib>
#include <boost/numeric/odeint.hpp>
#include <boost/numeric/odeint/external/eigen/eigen_algebra.hpp>

using namespace boost::numeric::odeint;

typedef Eigen::VectorXd state_type;

Eigen::MatrixXd A;

void ODE_function (const state_type &x, state_type &dxdt, const double &t)
{
    dxdt = A * x;
}

void write_states(const state_type &x, const double &t)
{
    std::cout << t << "\t";
    for (int i = 0; i < x.size(); i++)
    {
        std::cout << *(x.data()+i) << "\t";
    }
    std::cout << std::endl;
}

int main()
{
    int nr_of_states = 10;
    state_type x;

    std::cout << "Simulation with " << nr_of_states << " states\n";

    x = state_type(nr_of_states);
    A = Eigen::MatrixXd(nr_of_states, nr_of_states);

    srand(365);

    for (int i = 0; i < A.size(); i++)
    {
        *(A.data()+i) = ((double)rand()/(double)RAND_MAX);
    }

    for (int i = 0; i < x.size(); i++)
    {
        *(x.data()+i) = i;
    }

    typedef runge_kutta_dopri5<state_type, double, state_type, double, vector_space_algebra> stepper;
    integrate_adaptive(stepper(), ODE_function, x, 0.0, 25.0, 0.1, write_states);

    std::cout <<std::endl << "final state vector: " << std::endl << x << std::endl;

    return 0;
}