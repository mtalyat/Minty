minty_collect_sources(MINTY_LAYER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")

set(MINTY_LAYER_STUB_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/minty_layer_stub.cpp")
file(WRITE "${MINTY_LAYER_STUB_SOURCE}" "namespace Minty { void _minty_layer_stub() {} }\n")

minty_add_layer(
    NAME minty_layer
    LAYER Layer
    SOURCES
        ${MINTY_LAYER_SOURCES}
        "${MINTY_LAYER_STUB_SOURCE}"
    PUBLIC_INCLUDE_DIRS
        "${MINTY_SOURCE_ROOT}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_library(Layer ALIAS minty_layer)

set_target_properties(minty_layer PROPERTIES
    OUTPUT_NAME "MintyLayer"
)