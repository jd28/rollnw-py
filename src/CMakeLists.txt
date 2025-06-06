find_package(Threads)

nanobind_add_module(_core MODULE
    wrapper.cpp
    opaque_types.cpp

    glm/glm_util.cpp
    glm/wrap_vmath.cpp

    wrapper_core_scriptapi.cpp
    wrapper_formats.cpp
    wrapper_i18n.cpp
    wrapper_kernel.cpp
    wrapper_model.cpp
    wrapper_nwn1.cpp
    wrapper_objects_components.cpp
    wrapper_objects.cpp
    wrapper_resources.cpp
    wrapper_rules.cpp
    wrapper_script.cpp
    wrapper_serialization.cpp
    wrapper_util.cpp

    STABLE_ABI
    NB_STATIC
)

if(MSVC)
target_compile_options(_core PRIVATE /bigobj)
endif()

target_link_libraries(_core PRIVATE
    nw
)

target_include_directories(_core SYSTEM PRIVATE
    ../external/nanobind/include
    ../external/rollnw/lib
    ../external/rollnw/external/
    ../external/rollnw/external/immer
    ../external/rollnw/external/nowide/include
    ../external/rollnw/external/xsimd-13.0.0/include
    ../external/rollnw/external/xxhash-0.8.3
)

install(TARGETS _core DESTINATION ${SKBUILD_PROJECT_NAME})
