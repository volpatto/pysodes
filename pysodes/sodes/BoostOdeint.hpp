#ifndef SODES_BOOSTODEINT_HPP
#define SODES_BOOSTODEINT_HPP

#include <Eigen/Core>
#include <boost/numeric/odeint.hpp>
#include <boost/numeric/odeint/external/eigen/eigen_algebra.hpp>

namespace sodes::backend::odeint{

using namespace Eigen;
using namespace boost::numeric::odeint;

template <std::size_t N>
using eigen_vector = Matrix<double, N, 1>;

typedef eigen_vector<3> state_type;

}

#endif //SODES_BOOSTODEINT_HPP
