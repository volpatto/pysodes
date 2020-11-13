# CMake version required according to the env
cmake_minimum_required(VERSION 3.9)

# Add CMake modules path
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Project name and specifications
project(sODEs VERSION 0.1.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)

# Includes
include(CCache)
include(CondaAware)
include(FindEigen3)

# Find Eigen3 with a version specification
find_package(Eigen3 3.3)
message("-- Eigen3 include dir: " ${EIGEN3_INCLUDE_DIR})
include_directories(${EIGEN3_INCLUDE_DIR})

# Find Boost
find_package(Boost 1.74)
add_definitions(-DBOOST_ALLOW_DEPRECATED_HEADERS)

# Add subdirs to build with cmake
add_subdirectory(examples/boost)

set(ARTIFACTS_PATH ${CMAKE_SOURCE_DIR}/build/pysodes)