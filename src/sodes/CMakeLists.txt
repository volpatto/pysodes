add_library(
        odeint_wrapper
        INTERFACE
)

target_include_directories(odeint_wrapper
        INTERFACE
        ${PROJECT_SOURCE_DIR}/src/sodes/odeint/
        ${PROJECT_SOURCE_DIR}/src/sodes/
        )

target_sources(
        odeint_wrapper
        INTERFACE
        ${PROJECT_SOURCE_DIR}/src/sodes/odeint/BoostOdeint.hpp
        ${PROJECT_SOURCE_DIR}/src/sodes/math_types.hpp
)