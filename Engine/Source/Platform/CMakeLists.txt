minty_collect_sources(MINTY_PLATFORM_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")

minty_add_layer(
	NAME minty_platform
	LAYER Platform
	SOURCES ${MINTY_PLATFORM_SOURCES}
	PUBLIC_INCLUDE_DIRS
		"${MINTY_SOURCE_ROOT}"
		"${CMAKE_CURRENT_SOURCE_DIR}"
	PUBLIC_DEPS
		minty_library
)

add_library(Platform ALIAS minty_platform)

set_target_properties(minty_platform PROPERTIES
	OUTPUT_NAME "MintyPlatform"
)
