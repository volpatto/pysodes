# Find Eigen3 with a version specification
find_package(Eigen3 3.3)
message("-- Eigen3 include dir: " ${EIGEN3_INCLUDE_DIR})
include_directories(${EIGEN3_INCLUDE_DIR})

# Find Boost
find_package(Boost 1.74)
add_definitions(-DBOOST_ALLOW_DEPRECATED_HEADERS)

# Find pybind11
find_package(pybind11 REQUIRED)