minty_collect_sources(MINTY_EVENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")

if(MINTY_USE_PREBUILT_DEPS)
    minty_import_layer_dependency(minty_core Core MintyCore)
endif()

minty_add_layer(
    NAME minty_event
    LAYER Event
    SOURCES ${MINTY_EVENT_SOURCES}
    PUBLIC_INCLUDE_DIRS
        "${MINTY_SOURCE_ROOT}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
    PUBLIC_DEPS
        minty_core
)

add_library(Event ALIAS minty_event)

set_target_properties(minty_event PROPERTIES
    OUTPUT_NAME "MintyEvent"
)