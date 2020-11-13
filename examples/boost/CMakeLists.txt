#add_library(
#        simple_boost
#        STATIC
#        simple_boost.cpp
#        ${Boost_INCLUDE_DIRS}
#)
add_executable(example_boost simple_boost.cpp)
add_executable(lorenz_boost lorenz_example.cpp)
add_executable(odeint_eigen_example odeint_eigen_example.cpp)

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
endif()

install(
        TARGETS example_boost
        RUNTIME DESTINATION ${ARTIFACTS_PATH}
        LIBRARY DESTINATION ${ARTIFACTS_PATH}
        ARCHIVE DESTINATION ${ARTIFACTS_PATH}
)