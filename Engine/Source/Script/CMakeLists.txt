minty_collect_sources(MINTY_SCRIPT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")

if(MINTY_USE_PREBUILT_DEPS)
    minty_import_layer_dependency(minty_core Core MintyCore)
    minty_import_layer_dependency(minty_resource Resource MintyResource)
    minty_import_layer_dependency(minty_independence Independence MintyIndependence)
endif()

minty_add_layer(
    NAME minty_script
    LAYER Script
    SOURCES ${MINTY_SCRIPT_SOURCES}
    PUBLIC_INCLUDE_DIRS
        "${MINTY_SOURCE_ROOT}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
    PUBLIC_DEPS
        minty_core
        minty_resource
        minty_independence
)

add_library(Script ALIAS minty_script)

set_target_properties(minty_script PROPERTIES
    OUTPUT_NAME "MintyScript"
)