minty_collect_sources(MINTY_RENDER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")

if(MINTY_USE_PREBUILT_DEPS)
    minty_import_layer_dependency(minty_independence Independence MintyIndependence)
endif()

minty_add_layer(
    NAME minty_render
    LAYER Render
    SOURCES ${MINTY_RENDER_SOURCES}
    PUBLIC_INCLUDE_DIRS
        "${MINTY_SOURCE_ROOT}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
    PUBLIC_DEPS
        minty_independence
)

add_library(Render ALIAS minty_render)

set_target_properties(minty_render PROPERTIES
    OUTPUT_NAME "MintyRender"
)
