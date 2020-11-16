/*
 * This example reproduces one of the tests with Eigen in the
 * Boost odeint repository.
 *
 * Check here: https://github.com/boostorg/odeint/blob/develop/test_external/eigen/runge_kutta4.cpp
 */

#include <iostream>
#include <Eigen/Core>
#include <boost/numeric/odeint.hpp>

#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint/external/eigen/eigen_resize.hpp>

using namespace boost::numeric::odeint;
using namespace Eigen;

typedef Matrix< double , Dynamic , 1 > state_type;

// System to be solved
struct sys
{
    template<class State, class Deriv>
    void operator()(const State& x, Deriv& dxdt, double t) const
    {
        dxdt[0] = 1.0;
    }
};

int main()
{
    state_type x( 1 );
    x[0] = 10.0;
    runge_kutta4< state_type , double , state_type , double , vector_space_algebra > rk4;
    rk4.do_step( sys() , x , 0.0 , 0.1 );

    std::cout << x << std::endl;
}