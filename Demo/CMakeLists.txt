cmake_minimum_required(VERSION 3.24)

project(DemoWithEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ENGINE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Engine")
set(ENGINE_SOURCE_DIR "${ENGINE_DIR}/Source")
set(ENGINE_ARTIFACTS_DIR "${ENGINE_DIR}/Output/Artifacts")

if(NOT EXISTS "${ENGINE_SOURCE_DIR}/Minty.hpp" AND NOT EXISTS "${ENGINE_SOURCE_DIR}/Minty.h")
    message(FATAL_ERROR "Expected Engine root at ${ENGINE_SOURCE_DIR}, but neither Minty.hpp nor Minty.h was found.")
endif()

function(resolve_engine_bundle out_var config_name)
    set(_bundle "${ENGINE_ARTIFACTS_DIR}/${config_name}/Engine.lib")
    set(${out_var} "${_bundle}" PARENT_SCOPE)
endfunction()

resolve_engine_bundle(_engine_debug "Debug")
if(NOT EXISTS "${_engine_debug}")
    message(FATAL_ERROR "Missing required Engine artifact: ${_engine_debug}. Please build the engine.")
endif()

resolve_engine_bundle(_engine_release "Release")
resolve_engine_bundle(_engine_relwithdebinfo "RelWithDebInfo")
resolve_engine_bundle(_engine_minsizerel "MinSizeRel")

add_library(minty_engine_prebuilt STATIC IMPORTED GLOBAL)
set_target_properties(minty_engine_prebuilt PROPERTIES
    IMPORTED_LOCATION_DEBUG "${_engine_debug}"
    IMPORTED_LOCATION_RELEASE "${_engine_release}"
    IMPORTED_LOCATION_RELWITHDEBINFO "${_engine_relwithdebinfo}"
    IMPORTED_LOCATION_MINSIZEREL "${_engine_minsizerel}"
)

add_executable(demo_app
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/main.cpp"
)

target_include_directories(demo_app PRIVATE
    "${ENGINE_SOURCE_DIR}"
)

target_link_libraries(demo_app PRIVATE
    minty_engine_prebuilt
)

target_compile_definitions(demo_app PRIVATE
    $<$<CONFIG:Debug>:MINTY_DEBUG>
    $<$<NOT:$<CONFIG:Debug>>:MINTY_RELEASE>
    _ALLOW_KEYWORD_MACROS
)

if(WIN32)
    target_compile_definitions(demo_app PRIVATE MINTY_WINDOWS)
elseif(APPLE)
    target_compile_definitions(demo_app PRIVATE MINTY_APPLE)
elseif(UNIX)
    target_compile_definitions(demo_app PRIVATE MINTY_LINUX)
endif()
