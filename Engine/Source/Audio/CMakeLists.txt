minty_collect_sources(MINTY_AUDIO_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")

# if(MINTY_USE_PREBUILT_DEPS)
#     minty_import_layer_dependency(minty_independence Independence MintyIndependence)
# endif()

minty_add_layer(
    NAME minty_audio
    LAYER Audio
    SOURCES ${MINTY_AUDIO_SOURCES}
    PUBLIC_INCLUDE_DIRS
        "${MINTY_SOURCE_ROOT}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
    PUBLIC_DEPS
        minty_independence
)

add_library(Audio ALIAS minty_audio)

set_target_properties(minty_audio PROPERTIES
    OUTPUT_NAME "MintyAudio"
)
