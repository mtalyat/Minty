minty_collect_sources(MINTY_INDEPENDENCE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")

if(MINTY_USE_PREBUILT_DEPS)
    minty_import_layer_dependency(minty_library Library MintyLibrary)
endif()

minty_add_layer(
    NAME minty_independence
    LAYER Independence
    SOURCES ${MINTY_INDEPENDENCE_SOURCES}
    PUBLIC_INCLUDE_DIRS
        "${MINTY_SOURCE_ROOT}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
    PRIVATE_INCLUDE_DIRS
        "${MINTY_SOURCE_ROOT}/Library/Vulkan/Include"
        "${MINTY_SOURCE_ROOT}/Library/GLFW/include"
        "${MINTY_SOURCE_ROOT}/Library/Bullet/Include"
        "${MINTY_SOURCE_ROOT}/Library/SoLoud/Include"
    PUBLIC_DEPS
        minty_library
)

add_library(Independence ALIAS minty_independence)

set_target_properties(minty_independence PROPERTIES
    OUTPUT_NAME "MintyIndependence"
)
