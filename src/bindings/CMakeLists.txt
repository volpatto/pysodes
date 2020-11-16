# Generate Python module with pybind11
pybind11_add_module(
        sodes_bindings
        bindings.cpp
)

target_link_libraries(
        sodes_bindings
        PRIVATE
            odeint_wrapper
)

if(OPTIMIZE_FLAG MATCHES ON)
    target_compile_options(sodes_bindings INTERFACE "-Ofast")
endif()

set(ARTIFACTS_PATH ${PROJECT_SOURCE_DIR}/src/pysodes/_bindings)
message("-- Python bindings artifacts path: ${ARTIFACTS_PATH}")

install(TARGETS sodes_bindings
        CONFIGURATIONS Release Debug
        RUNTIME DESTINATION ${ARTIFACTS_PATH}
        LIBRARY DESTINATION ${ARTIFACTS_PATH}
)
