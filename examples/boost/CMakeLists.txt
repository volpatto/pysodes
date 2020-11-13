#add_library(
#        simple_boost
#        STATIC
#        simple_boost.cpp
#        ${Boost_INCLUDE_DIRS}
#)
add_executable(example_boost simple_boost.cpp)
add_executable(lorenz_boost lorenz_example.cpp)
add_executable(odeint_eigen_example odeint_eigen_example.cpp)
add_executable(dynamic_eigen_example dynamic_eigen.cpp)
add_executable(dynamic_eigen_example_2 dynamic_eigen_2.cpp)
add_executable(dynamic_lorenz_eigen_example dynamic_lorenz_eigen.cpp)

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
endif()

install(
        TARGETS example_boost
        RUNTIME DESTINATION ${ARTIFACTS_PATH}
        LIBRARY DESTINATION ${ARTIFACTS_PATH}
        ARCHIVE DESTINATION ${ARTIFACTS_PATH}
)