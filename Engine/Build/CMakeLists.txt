cmake_minimum_required(VERSION 3.24)

project(Minty VERSION 0.1.0 LANGUAGES CXX)

set(MINTY_ENGINE_ROOT "${CMAKE_CURRENT_LIST_DIR}/..")
set(MINTY_SOURCE_ROOT "${MINTY_ENGINE_ROOT}/Source")

set(MINTY_OUTPUT_DIR "${MINTY_ENGINE_ROOT}/Output" CACHE PATH "Root output directory for all generated files")
set(MINTY_ARTIFACTS_DIR "${MINTY_OUTPUT_DIR}/Artifacts" CACHE PATH "Root artifacts directory")

set(MINTY_CXX_STANDARD 20 CACHE STRING "C++ standard used by Minty layer targets")
set_property(CACHE MINTY_CXX_STANDARD PROPERTY STRINGS 17 20 23)

option(MINTY_ENABLE_PRECOMPILED_HEADERS "Use layer pch.hpp headers when available" ON)
option(MINTY_ENABLE_MSVC_MULTIPROCESS "Enable MSVC /MP for faster parallel compilation" ON)
option(MINTY_ENABLE_VULKAN "Enable Vulkan rendering backend compile definition" OFF)
option(MINTY_ENABLE_SOLOUD "Enable SoLoud audio backend compile definition" OFF)

set(MINTY_BUILD_LAYER "All" CACHE STRING "Top-level layer to build (dependencies are resolved automatically)")
set_property(CACHE MINTY_BUILD_LAYER PROPERTY STRINGS All Application Audio Core Event Independence Input Library Libraries Platform Render Resource Scene Window World)

add_compile_definitions(
	$<$<CONFIG:Debug>:MINTY_DEBUG>
	$<$<NOT:$<CONFIG:Debug>>:MINTY_RELEASE>
	$<$<BOOL:${MINTY_ENABLE_VULKAN}>:MINTY_VULKAN>
	$<$<BOOL:${MINTY_ENABLE_SOLOUD}>:MINTY_SOLOUD>
)

if(WIN32)
	add_compile_definitions(MINTY_WINDOWS)
elseif(APPLE)
	add_compile_definitions(MINTY_APPLE)
elseif(UNIX)
	add_compile_definitions(MINTY_LINUX)
endif()

if(MSVC AND MINTY_ENABLE_MSVC_MULTIPROCESS)
	add_compile_options(/MP)
endif()

include(CMakeParseArguments)

function(minty_collect_sources OUT_VAR BASE_DIR)
	file(GLOB_RECURSE _minty_sources CONFIGURE_DEPENDS
		"${BASE_DIR}/*.c"
		"${BASE_DIR}/*.cc"
		"${BASE_DIR}/*.cpp"
		"${BASE_DIR}/*.cxx"
		"${BASE_DIR}/*.hpp"
		"${BASE_DIR}/*.inl"
	)

	set(${OUT_VAR} ${_minty_sources} PARENT_SCOPE)
endfunction()

function(minty_set_target_output_dirs TARGET_NAME LAYER_NAME)
	set(_layer_root "${MINTY_ARTIFACTS_DIR}")

	set_target_properties(${TARGET_NAME} PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${_layer_root}"
		LIBRARY_OUTPUT_DIRECTORY "${_layer_root}"
		RUNTIME_OUTPUT_DIRECTORY "${_layer_root}"
		PDB_OUTPUT_DIRECTORY "${_layer_root}"
	)

	foreach(cfg IN ITEMS Debug Release RelWithDebInfo MinSizeRel)
		string(TOUPPER ${cfg} cfg_upper)
		set_target_properties(${TARGET_NAME} PROPERTIES
			ARCHIVE_OUTPUT_DIRECTORY_${cfg_upper} "${_layer_root}/${cfg}"
			LIBRARY_OUTPUT_DIRECTORY_${cfg_upper} "${_layer_root}/${cfg}"
			RUNTIME_OUTPUT_DIRECTORY_${cfg_upper} "${_layer_root}/${cfg}"
			PDB_OUTPUT_DIRECTORY_${cfg_upper} "${_layer_root}/${cfg}"
		)
	endforeach()
endfunction()

function(minty_add_layer)
	set(options HEADER_ONLY)
	set(oneValueArgs NAME LAYER)
	set(multiValueArgs SOURCES PUBLIC_INCLUDE_DIRS PRIVATE_INCLUDE_DIRS PUBLIC_DEPS PRIVATE_DEPS PUBLIC_DEFINITIONS PRIVATE_DEFINITIONS)

	cmake_parse_arguments(MINTY "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	if(NOT MINTY_NAME)
		message(FATAL_ERROR "minty_add_layer requires NAME")
	endif()

	if(NOT MINTY_LAYER)
		message(FATAL_ERROR "minty_add_layer requires LAYER")
	endif()

	if(MINTY_HEADER_ONLY)
		add_library(${MINTY_NAME} INTERFACE)

		if(MINTY_SOURCES)
			target_sources(${MINTY_NAME} INTERFACE ${MINTY_SOURCES})
		endif()

		if(MINTY_PUBLIC_INCLUDE_DIRS)
			target_include_directories(${MINTY_NAME} INTERFACE ${MINTY_PUBLIC_INCLUDE_DIRS})
		endif()

		if(MINTY_PUBLIC_DEPS)
			target_link_libraries(${MINTY_NAME} INTERFACE ${MINTY_PUBLIC_DEPS})
		endif()

		if(MINTY_PUBLIC_DEFINITIONS)
			target_compile_definitions(${MINTY_NAME} INTERFACE ${MINTY_PUBLIC_DEFINITIONS})
		endif()

		return()
	endif()

	add_library(${MINTY_NAME} STATIC ${MINTY_SOURCES})
	target_compile_features(${MINTY_NAME} PUBLIC cxx_std_${MINTY_CXX_STANDARD})
	minty_set_target_output_dirs(${MINTY_NAME} ${MINTY_LAYER})

	if(MINTY_ENABLE_PRECOMPILED_HEADERS)
		set(_minty_pch_header "${MINTY_SOURCE_ROOT}/${MINTY_LAYER}/pch.hpp")
		if(NOT EXISTS "${_minty_pch_header}")
			set(_minty_pch_header "${MINTY_SOURCE_ROOT}/${MINTY_LAYER}/pch.h")
		endif()

		if(EXISTS "${_minty_pch_header}")
			target_precompile_headers(${MINTY_NAME} PRIVATE "${_minty_pch_header}")
		endif()
	endif()

	if(MINTY_PUBLIC_INCLUDE_DIRS)
		target_include_directories(${MINTY_NAME} PUBLIC ${MINTY_PUBLIC_INCLUDE_DIRS})
	endif()

	if(MINTY_PRIVATE_INCLUDE_DIRS)
		target_include_directories(${MINTY_NAME} PRIVATE ${MINTY_PRIVATE_INCLUDE_DIRS})
	endif()

	if(MINTY_PUBLIC_DEPS)
		target_link_libraries(${MINTY_NAME} PUBLIC ${MINTY_PUBLIC_DEPS})
	endif()

	if(MINTY_PRIVATE_DEPS)
		target_link_libraries(${MINTY_NAME} PRIVATE ${MINTY_PRIVATE_DEPS})
	endif()

	if(MINTY_PUBLIC_DEFINITIONS)
		target_compile_definitions(${MINTY_NAME} PUBLIC ${MINTY_PUBLIC_DEFINITIONS})
	endif()

	if(MINTY_PRIVATE_DEFINITIONS)
		target_compile_definitions(${MINTY_NAME} PRIVATE ${MINTY_PRIVATE_DEFINITIONS})
	endif()
endfunction()

function(minty_import_layer_dependency TARGET_NAME LAYER_NAME OUTPUT_NAME)
	if(TARGET ${TARGET_NAME})
		return()
	endif()

	set(_minty_candidate_paths
		"${MINTY_ARTIFACTS_DIR}/Debug/${OUTPUT_NAME}.lib"
		"${MINTY_ARTIFACTS_DIR}/Release/${OUTPUT_NAME}.lib"
		"${MINTY_ARTIFACTS_DIR}/RelWithDebInfo/${OUTPUT_NAME}.lib"
		"${MINTY_ARTIFACTS_DIR}/MinSizeRel/${OUTPUT_NAME}.lib"
	)

	set(_minty_found_any FALSE)
	foreach(_minty_candidate IN LISTS _minty_candidate_paths)
		if(EXISTS "${_minty_candidate}")
			set(_minty_found_any TRUE)
			break()
		endif()
	endforeach()

	if(NOT _minty_found_any)
		set(_minty_dependency_dir "${MINTY_SOURCE_ROOT}/${LAYER_NAME}")
		set(_minty_dependency_binary_dir "${CMAKE_BINARY_DIR}/${LAYER_NAME}")
		if(EXISTS "${_minty_dependency_dir}/CMakeLists.txt")
			message(STATUS "Prebuilt dependency '${TARGET_NAME}' not found in ${MINTY_ARTIFACTS_DIR}/<Config>. Falling back to source dependency layer '${LAYER_NAME}'.")
			add_subdirectory("${_minty_dependency_dir}" "${_minty_dependency_binary_dir}")
			if(TARGET ${TARGET_NAME})
				return()
			endif()
		endif()

		message(FATAL_ERROR "Missing dependency '${TARGET_NAME}'. Expected prebuilt ${OUTPUT_NAME}.lib in ${MINTY_ARTIFACTS_DIR}/<Config> or source layer at ${_minty_dependency_dir}.")
	endif()

	add_library(${TARGET_NAME} STATIC IMPORTED GLOBAL)
	set_target_properties(${TARGET_NAME} PROPERTIES
		IMPORTED_LOCATION_DEBUG "${MINTY_ARTIFACTS_DIR}/Debug/${OUTPUT_NAME}.lib"
		IMPORTED_LOCATION_RELEASE "${MINTY_ARTIFACTS_DIR}/Release/${OUTPUT_NAME}.lib"
		IMPORTED_LOCATION_RELWITHDEBINFO "${MINTY_ARTIFACTS_DIR}/RelWithDebInfo/${OUTPUT_NAME}.lib"
		IMPORTED_LOCATION_MINSIZEREL "${MINTY_ARTIFACTS_DIR}/MinSizeRel/${OUTPUT_NAME}.lib"
	)
endfunction()

file(GLOB MINTY_LAYER_CMAKE_FILES RELATIVE "${MINTY_SOURCE_ROOT}" "${MINTY_SOURCE_ROOT}/*/CMakeLists.txt")
set(MINTY_DISCOVERED_LAYERS)

foreach(_layer_entry IN LISTS MINTY_LAYER_CMAKE_FILES)
	get_filename_component(_layer_dir "${_layer_entry}" DIRECTORY)
	list(APPEND MINTY_DISCOVERED_LAYERS "${_layer_dir}")
endforeach()

list(REMOVE_DUPLICATES MINTY_DISCOVERED_LAYERS)
list(SORT MINTY_DISCOVERED_LAYERS)

set(_minty_requested_layer "")
string(TOLOWER "${MINTY_BUILD_LAYER}" _minty_requested_lower)

if(_minty_requested_lower STREQUAL "all")
	set(_minty_requested_layer "All")
else()
	foreach(_layer IN LISTS MINTY_DISCOVERED_LAYERS)
		string(TOLOWER "${_layer}" _layer_lower)
		if(_layer_lower STREQUAL _minty_requested_lower)
			set(_minty_requested_layer "${_layer}")
			break()
		endif()
	endforeach()

	if(NOT _minty_requested_layer AND _minty_requested_lower STREQUAL "libraries")
		foreach(_layer IN LISTS MINTY_DISCOVERED_LAYERS)
			string(TOLOWER "${_layer}" _layer_lower)
			if(_layer_lower STREQUAL "library")
				set(_minty_requested_layer "${_layer}")
				break()
			endif()
		endforeach()
	endif()
endif()

if(NOT _minty_requested_layer)
	string(REPLACE ";" ", " _minty_layer_list "${MINTY_DISCOVERED_LAYERS}")
	message(FATAL_ERROR "Unknown MINTY_BUILD_LAYER='${MINTY_BUILD_LAYER}'. Discovered layers: ${_minty_layer_list}")
endif()

if(_minty_requested_layer STREQUAL "All")
	set(MINTY_USE_PREBUILT_DEPS OFF)
	foreach(_layer IN LISTS MINTY_DISCOVERED_LAYERS)
		add_subdirectory("${MINTY_SOURCE_ROOT}/${_layer}" "${CMAKE_BINARY_DIR}/${_layer}")
	endforeach()
else()
	set(MINTY_USE_PREBUILT_DEPS ON)
	add_subdirectory("${MINTY_SOURCE_ROOT}/${_minty_requested_layer}" "${CMAKE_BINARY_DIR}/${_minty_requested_layer}")
endif()
