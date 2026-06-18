minty_collect_sources(MINTY_WORLD_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")

if(MINTY_USE_PREBUILT_DEPS)
    minty_import_layer_dependency(minty_independence Independence MintyIndependence)
endif()

minty_add_layer(
    NAME minty_world
    LAYER World
    SOURCES ${MINTY_WORLD_SOURCES}
    PUBLIC_INCLUDE_DIRS
        "${MINTY_SOURCE_ROOT}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
    PUBLIC_DEPS
        minty_independence
)

add_library(World ALIAS minty_world)

set_target_properties(minty_world PROPERTIES
    OUTPUT_NAME "MintyWorld"
)
