cmake_minimum_required(VERSION 3.20)

project(Wrapper VERSION 1.0.0 LANGUAGES CXX)

set(TOP ${CMAKE_CURRENT_SOURCE_DIR}/../..)

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Debug-Trace;Release" CACHE STRING "" FORCE)

# Options for features
option(MINTY_VULKAN "Enable Vulkan rendering" ON)
option(MINTY_SOLOUD "Enable SoLoud audio" ON)
option(MINTY_BULLET "Enable Bullet physics" ON)
option(MINTY_TRACE "Enable Tracy profiling (Debug-Trace only)" OFF)

# Set library paths
set(LIBRARIES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Libraries")
set(ENGINE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Engine")

# Source directory
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Source")

# Collect all source files
file(GLOB WRAPPER_SOURCES
    "${SOURCE_DIR}/*.cpp"
)

# Collect all header files
file(GLOB WRAPPER_HEADERS
    "${SOURCE_DIR}/*.h"
)

# Create the executable
add_executable(${PROJECT_NAME}
    ${WRAPPER_SOURCES}
    ${WRAPPER_HEADERS}
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${ENGINE_DIR}/Source
    ${LIBRARIES_DIR}/bullet/include
    ${LIBRARIES_DIR}/entt/include
    ${LIBRARIES_DIR}/glfw/include
    ${LIBRARIES_DIR}/glm/include
    ${LIBRARIES_DIR}/soloud/include
    ${LIBRARIES_DIR}/stb/include
    ${LIBRARIES_DIR}/tracy/include
    ${LIBRARIES_DIR}/vulkan/include
    ${LIBRARIES_DIR}/zlib/include
)

# Preprocessor definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
    UNICODE
    _UNICODE
    $<$<OR:$<CONFIG:Debug>,$<STREQUAL:$<CONFIG>,Debug-Trace>>:_DEBUG>
    $<$<OR:$<CONFIG:Debug>,$<STREQUAL:$<CONFIG>,Debug-Trace>>:MINTY_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
    $<$<CONFIG:Release>:MINTY_RELEASE>
    _CRT_SECURE_NO_WARNINGS # Suppress CRT security warnings
)

# Feature-based definitions
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

# Compiler flags
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W3                     # Warning level 3
        /permissive-            # Standards conformance mode
        /Zc:wchar_t             # wchar_t is a native type
        /Zc:forScope            # Standard C++ for scoping rules
        /Zc:inline              # Remove unreferenced function or data
        /fp:precise             # Precise floating-point model
        /GS                     # Buffer security check
        /sdl                    # Additional security checks
        $<$<OR:$<CONFIG:Debug>,$<STREQUAL:$<CONFIG>,Debug-Trace>>:/MTd> # Multi-threaded debug runtime
        $<$<CONFIG:Release>:/MT> # Multi-threaded release runtime
        $<$<CONFIG:Release>:/O2> # Optimize for speed
        $<$<CONFIG:Release>:/GL> # Whole program optimization
        $<$<OR:$<CONFIG:Debug>,$<STREQUAL:$<CONFIG>,Debug-Trace>>:/Od> # Disable optimization
        $<$<OR:$<CONFIG:Debug>,$<STREQUAL:$<CONFIG>,Debug-Trace>>:/RTC1> # Runtime checks
        $<$<OR:$<CONFIG:Debug>,$<STREQUAL:$<CONFIG>,Debug-Trace>>:/ZI> # Edit and continue debug info
        $<$<OR:$<CONFIG:Debug>,$<STREQUAL:$<CONFIG>,Debug-Trace>>:/JMC> # Just my code debugging
        $<$<CONFIG:Release>:/Zi> # Generate debug info
        $<$<CONFIG:Release>:/MP> # Multi-processor compilation
    )
    
    # Linker flags
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:/LTCG> # Link-time code generation
    )
endif()

# Link directories
target_link_directories(${PROJECT_NAME} PRIVATE
    ${ENGINE_DIR}/Build/Output/$<CONFIG>
    ${LIBRARIES_DIR}/vulkan/lib
    ${LIBRARIES_DIR}/glfw/lib
    ${LIBRARIES_DIR}/bullet/lib/$<CONFIG>
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Minty
    vulkan-1
    glfw3_mt
    BulletCollision
    BulletDynamics
    LinearMath
)

# Output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>"
)

# Print configuration info
message(STATUS "Wrapper Configuration:")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Vulkan: ${MINTY_VULKAN}")
message(STATUS "  SoLoud: ${MINTY_SOLOUD}")
message(STATUS "  Bullet: ${MINTY_BULLET}")
message(STATUS "  Tracy: ${MINTY_TRACE}")
