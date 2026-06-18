minty_collect_sources(MINTY_WINDOW_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")

if(MINTY_USE_PREBUILT_DEPS)
    minty_import_layer_dependency(minty_platform Platform MintyPlatform)
endif()

minty_add_layer(
    NAME minty_window
    LAYER Window
    SOURCES ${MINTY_WINDOW_SOURCES}
    PUBLIC_INCLUDE_DIRS
        "${MINTY_SOURCE_ROOT}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
    PUBLIC_DEPS
        minty_platform
)

add_library(Window ALIAS minty_window)

set_target_properties(minty_window PROPERTIES
    OUTPUT_NAME "MintyWindow"
)
