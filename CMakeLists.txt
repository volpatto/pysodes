# CMake version required according to the env
cmake_minimum_required(VERSION 3.9)

# Add CMake modules path
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Project name and specifications
#project(sODEs VERSION 0.1.0 LANGUAGES CXX C)
project(sODEs CXX C)
set(CMAKE_CXX_STANDARD 17)

# Includes
include(CCache)
include(CondaAware)
include(FindEigen3)
include(FindDeps)

# Add subdirs to build with cmake
add_subdirectory(examples/boost)
add_subdirectory(src/sodes)
add_subdirectory(src/bindings)

include_directories(src)