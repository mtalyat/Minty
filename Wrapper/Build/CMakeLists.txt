cmake_minimum_required(VERSION 3.20)

project(Wrapper)

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Debug-Trace;Release" CACHE STRING "" FORCE)

# Set linker flags for Debug-Trace configuration (copy from Debug)
set(CMAKE_EXE_LINKER_FLAGS_DEBUG-TRACE ${CMAKE_EXE_LINKER_FLAGS_DEBUG})
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG-TRACE ${CMAKE_SHARED_LINKER_FLAGS_DEBUG})
set(CMAKE_STATIC_LINKER_FLAGS_DEBUG-TRACE ${CMAKE_STATIC_LINKER_FLAGS_DEBUG})
set(CMAKE_MODULE_LINKER_FLAGS_DEBUG-TRACE ${CMAKE_MODULE_LINKER_FLAGS_DEBUG})

# Set compiler flags for Debug-Trace configuration (copy from Debug)
set(CMAKE_CXX_FLAGS_DEBUG-TRACE ${CMAKE_CXX_FLAGS_DEBUG})
set(CMAKE_C_FLAGS_DEBUG-TRACE ${CMAKE_C_FLAGS_DEBUG})

# Get MINTY_PATH from environment variable
if(NOT DEFINED ENV{MINTY_PATH})
    message(FATAL_ERROR "MINTY_PATH environment variable is not set")
endif()
set(MINTY_PATH $ENV{MINTY_PATH})

# Options for features
option(MINTY_VULKAN "Enable Vulkan rendering" ON)
option(MINTY_SOLOUD "Enable SoLoud audio" ON)
option(MINTY_BULLET "Enable Bullet physics" ON)
option(MINTY_TRACE "Enable Tracy profiling (Debug-Trace only)" OFF)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Source")

# Glob source and header files
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${SOURCE_DIR}/*.h")
set(MINTY_INCLUDES
    "${MINTY_PATH}/Engine/Source"
)

# Precompiled header
set(PCH_SOURCE "${SOURCE_DIR}/pch.cpp")
set(PCH_HEADER "${SOURCE_DIR}/pch.h")

# Create executable
add_executable(${PROJECT_NAME} 
    ${SOURCES}
    ${HEADERS}
    ${PCH_SOURCE}
    ${PCH_HEADER}
)

# Set precompiled header
target_precompile_headers(${PROJECT_NAME} PRIVATE "${PCH_HEADER}")

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${MINTY_PATH}/Engine/Source
    ${MINTY_PATH}/Libraries/bullet/include
    ${MINTY_PATH}/Libraries/entt/include
    ${MINTY_PATH}/Libraries/glfw/include
    ${MINTY_PATH}/Libraries/glm/include
    ${MINTY_PATH}/Libraries/soloud/include
    ${MINTY_PATH}/Libraries/stb/include
    ${MINTY_PATH}/Libraries/tracy/include
    ${MINTY_PATH}/Libraries/vulkan/include
    ${MINTY_PATH}/Libraries/zlib/include
    ${MINTY_INCLUDES}
)

# Link directories
target_link_directories(${PROJECT_NAME} PRIVATE
    ${MINTY_PATH}/Libraries/vulkan/lib
    ${MINTY_PATH}/Libraries/glfw/lib
    ${MINTY_PATH}/Libraries/zlib/lib
    ${MINTY_PATH}/Libraries/bullet/lib
    $<$<CONFIG:Debug>:${MINTY_PATH}/Engine/Build/Bin/Debug>
    $<$<STREQUAL:$<CONFIG>,Debug-Trace>:${MINTY_PATH}/Engine/Build/Bin/Debug>
    $<$<CONFIG:Release>:${MINTY_PATH}/Engine/Build/Bin/Release>
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    vulkan-1
    glfw3_mt
    Minty
    BulletDynamics
    BulletCollision
    LinearMath
)

# Set runtime library
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:/MTd>
        $<$<STREQUAL:$<CONFIG>,Debug-Trace>:/MTd>
        $<$<CONFIG:Release>:/MT>
    )
    # Ignore conflicting runtime libraries
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:/NODEFAULTLIB:libcmt.lib>
        $<$<STREQUAL:$<CONFIG>,Debug-Trace>:/NODEFAULTLIB:libcmt.lib>
        $<$<CONFIG:Release>:/NODEFAULTLIB:libcmtd.lib>
    )
endif()

# Compiler-specific settings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W3)
endif()

# Preprocessor definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
    UNICODE
    _UNICODE
    $<$<OR:$<CONFIG:Debug>,$<STREQUAL:$<CONFIG>,Debug-Trace>>:_DEBUG>
    $<$<OR:$<CONFIG:Debug>,$<STREQUAL:$<CONFIG>,Debug-Trace>>:MINTY_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
    $<$<CONFIG:Release>:MINTY_RELEASE>
)

if(MINTY_VULKAN)
    target_compile_definitions(${PROJECT_NAME} PRIVATE MINTY_VULKAN)
endif()

if(MINTY_SOLOUD)
    target_compile_definitions(${PROJECT_NAME} PRIVATE MINTY_SOLOUD)
endif()

if(MINTY_BULLET)
    target_compile_definitions(${PROJECT_NAME} PRIVATE MINTY_BULLET)
endif()

if(MINTY_TRACE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE MINTY_TRACE TRACY_ENABLE)
endif()

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/$<CONFIG>
    RUNTIME_OUTPUT_DIRECTORY_DEBUG-TRACE ${CMAKE_BINARY_DIR}/$<CONFIG>
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/$<CONFIG>
)
