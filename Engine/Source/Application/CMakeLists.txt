minty_collect_sources(MINTY_APPLICATION_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")

set(MINTY_APPLICATION_STUB_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/minty_application_stub.cpp")
file(WRITE "${MINTY_APPLICATION_STUB_SOURCE}" "namespace Minty { void _minty_application_stub() {} }\n")

if(MINTY_USE_PREBUILT_DEPS)
    minty_import_layer_dependency(minty_scene Scene MintyScene)
endif()

minty_add_layer(
    NAME minty_application
    LAYER Application
    SOURCES
        ${MINTY_APPLICATION_SOURCES}
        "${MINTY_APPLICATION_STUB_SOURCE}"
    PUBLIC_INCLUDE_DIRS
        "${MINTY_SOURCE_ROOT}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
    PUBLIC_DEPS
        minty_scene
)

add_library(Application ALIAS minty_application)

set_target_properties(minty_application PROPERTIES
    OUTPUT_NAME "MintyApplication"
)
