# CMake version required according to the env
cmake_minimum_required(VERSION 3.9)

# Add CMake modules path
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Project name and specifications
project(sODEs VERSION 0.1.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Includes
include(CCache)
include(CondaAware)
include(FindEigen3)
include(FindDeps)

# Some additional build options
option(OPTIMIZE_FLAG "Compile using g++ optimization flag" OFF)
option(USE_EIGEN_MKL "Use Eigen with Intel MKL" ON)

if(USE_EIGEN_MKL MATCHES ON)
    include(FindMKL REQUIRED)
    add_definitions(
            -DEIGEN_USE_MKL_ALL
            -DMKL_ILP64
            -m64
    )
endif()

# Add subdirs to build with cmake
add_subdirectory(examples/boost)
add_subdirectory(src/sodes)
add_subdirectory(src/bindings)

include_directories(src)