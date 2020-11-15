add_library(
        odeint_wrapper
        INTERFACE
)

target_include_directories(odeint_wrapper
        INTERFACE
        ${PROJECT_SOURCE_DIR}/src/sodes/odeint/)

target_sources(
        odeint_wrapper
        INTERFACE
        ${PROJECT_SOURCE_DIR}/src/sodes/odeint/BoostOdeint.hpp
)

#target_include_directories(odeint_wrapper
#        INTERFACE
#        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
#        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)