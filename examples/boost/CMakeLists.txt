add_executable(example_boost standalones/simple_boost.cpp)
add_executable(lorenz_boost standalones/lorenz_example.cpp)
add_executable(odeint_eigen_example standalones/odeint_eigen_example.cpp)
add_executable(dynamic_eigen_example standalones/dynamic_eigen.cpp)
add_executable(dynamic_eigen_example_2 standalones/dynamic_eigen_2.cpp)
add_executable(dynamic_lorenz_eigen_example standalones/dynamic_lorenz_eigen.cpp)
add_executable(call_sodes_rk4 call_sodes_rk4.cpp)

if(Boost_FOUND)
    target_link_libraries(
            example_boost
            PRIVATE
                Boost::boost
    )

    target_link_libraries(
            lorenz_boost
            PRIVATE
                Boost::boost
    )

    target_link_libraries(
            odeint_eigen_example
            PRIVATE
                Boost::boost
    )

    target_link_libraries(
            dynamic_lorenz_eigen_example
            PRIVATE
                Boost::boost
    )

    target_link_libraries(
            dynamic_eigen_example
            PRIVATE
                Boost::boost
    )

    target_link_libraries(
            dynamic_eigen_example_2
            PRIVATE
                Boost::boost
    )

    target_link_libraries(
            call_sodes_rk4
            PRIVATE
                Boost::boost
                odeint_wrapper
    )
endif()
