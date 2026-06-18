minty_collect_sources(MINTY_CORE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")

if(MINTY_USE_PREBUILT_DEPS)
    minty_import_layer_dependency(minty_platform Platform MintyPlatform)
endif()

minty_add_layer(
    NAME minty_core
    LAYER Core
    SOURCES ${MINTY_CORE_SOURCES}
    PUBLIC_INCLUDE_DIRS
        "${MINTY_SOURCE_ROOT}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
    PUBLIC_DEPS
        minty_platform
)

add_library(Core ALIAS minty_core)

set_target_properties(minty_core PROPERTIES
    OUTPUT_NAME "MintyCore"
)
