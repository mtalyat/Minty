minty_collect_sources(MINTY_RESOURCE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")

if(MINTY_USE_PREBUILT_DEPS)
    minty_import_layer_dependency(minty_core Core MintyCore)
endif()

minty_add_layer(
    NAME minty_resource
    LAYER Resource
    SOURCES ${MINTY_RESOURCE_SOURCES}
    PUBLIC_INCLUDE_DIRS
        "${MINTY_SOURCE_ROOT}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
    PUBLIC_DEPS
        minty_core
)

add_library(Resource ALIAS minty_resource)

set_target_properties(minty_resource PROPERTIES
    OUTPUT_NAME "MintyResource"
)
