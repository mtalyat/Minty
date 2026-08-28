minty_collect_sources(MINTY_COLLISION_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")

set(MINTY_COLLISION_STUB_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/minty_collision_stub.cpp")
file(WRITE "${MINTY_COLLISION_STUB_SOURCE}" "namespace Minty { void _minty_collision_stub() {} }\n")

minty_add_layer(
    NAME minty_collision
    LAYER Collision
    SOURCES
        ${MINTY_COLLISION_SOURCES}
        "${MINTY_COLLISION_STUB_SOURCE}"
    PUBLIC_INCLUDE_DIRS
        "${MINTY_SOURCE_ROOT}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_library(Collision ALIAS minty_collision)

set_target_properties(minty_collision PROPERTIES
    OUTPUT_NAME "MintyCollision"
)