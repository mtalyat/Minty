minty_collect_sources(MINTY_SCENE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")

set(MINTY_SCENE_STUB_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/minty_scene_stub.cpp")
file(WRITE "${MINTY_SCENE_STUB_SOURCE}" "namespace Minty { void _minty_scene_stub() {} }\n")

minty_add_layer(
    NAME minty_scene
    LAYER Scene
    SOURCES
        ${MINTY_SCENE_SOURCES}
        "${MINTY_SCENE_STUB_SOURCE}"
    PUBLIC_INCLUDE_DIRS
        "${MINTY_SOURCE_ROOT}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_library(Scene ALIAS minty_scene)

set_target_properties(minty_scene PROPERTIES
    OUTPUT_NAME "MintyScene"
)
