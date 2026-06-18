include_guard(GLOBAL)
include(CMakeParseArguments)

function(minty_collect_sources OUT_VAR BASE_DIR)
    file(GLOB_RECURSE _minty_sources CONFIGURE_DEPENDS
        "${BASE_DIR}/*.c"
        "${BASE_DIR}/*.cc"
        "${BASE_DIR}/*.cpp"
        "${BASE_DIR}/*.cxx"
        "${BASE_DIR}/*.h"
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
        set(_minty_pch_header "${CMAKE_SOURCE_DIR}/${MINTY_LAYER}/pch.h")
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
