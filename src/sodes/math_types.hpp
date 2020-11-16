#ifndef SODES_MATH_TYPES_HPP
#define SODES_MATH_TYPES_HPP

/*
 * This header defines several useful math types using Eigen. This is necessary due to
 * the differences of how NumPy and Eigen store information. NumPy arrays are Row Major by default,
 * while Eigen is Column Major. Such different approach causes problems in conversions and bindings,
 * especially when modifications in parameters passed by reference are performed.
 */

#include <Eigen/Core>

namespace sodes::math_types {

using namespace Eigen;

using eigen_array_1d = Array<double, Dynamic, 1>;
using eigen_array_1d_ref = Ref<eigen_array_1d>;
using eigen_array_1d_constref = Ref<eigen_array_1d> const&;

}

#endif //SODES_MATH_TYPES_HPP
