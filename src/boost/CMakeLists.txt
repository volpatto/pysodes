add_library(
        simple_boost
        STATIC
        simple_boost.cpp
)
add_executable(example_boost simple_boost)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(example_boost ${Boost_LIBRARIES})
#    target_link_libraries(example_boost Boost)


#
#    target_link_libraries(
#            example_boost
#            PUBLIC
#            simple_boost
#            ${Boost_LIBRARIES}
#    )
endif()

install(
        TARGETS example_boost
        RUNTIME DESTINATION ${ARTIFACTS_PATH}
        LIBRARY DESTINATION ${ARTIFACTS_PATH}
        ARCHIVE DESTINATION ${ARTIFACTS_PATH}
)