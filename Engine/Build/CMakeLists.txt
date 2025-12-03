cmake_minimum_required(VERSION 3.20)

project(Minty VERSION 1.0.0 LANGUAGES CXX)

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

# Source directory
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Source")

# Collect all source files
file(GLOB_RECURSE MINTY_SOURCES
    "${SOURCE_DIR}/Minty/*.cpp"
    "${SOURCE_DIR}/Platform/*.cpp"
)

# Collect all header files
file(GLOB_RECURSE MINTY_HEADERS
    "${SOURCE_DIR}/Minty/*.h"
    "${SOURCE_DIR}/Platform/*.h"
    "${SOURCE_DIR}/*.h"
)

# Third-party sources (zlib, SoLoud, Tracy)
set(THIRD_PARTY_SOURCES
    # zlib sources
    "${LIBRARIES_DIR}/zlib/source/adler32.cpp"
    "${LIBRARIES_DIR}/zlib/source/compress.cpp"
    "${LIBRARIES_DIR}/zlib/source/crc32.cpp"
    "${LIBRARIES_DIR}/zlib/source/deflate.cpp"
    "${LIBRARIES_DIR}/zlib/source/gzclose.cpp"
    "${LIBRARIES_DIR}/zlib/source/gzlib.cpp"
    "${LIBRARIES_DIR}/zlib/source/gzread.cpp"
    "${LIBRARIES_DIR}/zlib/source/gzwrite.cpp"
    "${LIBRARIES_DIR}/zlib/source/infback.cpp"
    "${LIBRARIES_DIR}/zlib/source/inffast.cpp"
    "${LIBRARIES_DIR}/zlib/source/inflate.cpp"
    "${LIBRARIES_DIR}/zlib/source/inftrees.cpp"
    "${LIBRARIES_DIR}/zlib/source/trees.cpp"
    "${LIBRARIES_DIR}/zlib/source/uncompr.cpp"
    "${LIBRARIES_DIR}/zlib/source/zutil.cpp"
    
    # SoLoud sources
    "${LIBRARIES_DIR}/soloud/include/dr_impl.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_audiosource.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_bus.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_core_3d.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_core_basicops.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_core_faderops.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_core_filterops.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_core_getters.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_core_setters.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_core_voicegroup.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_core_voiceops.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_fader.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_fft.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_fft_lut.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_file.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_filter.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_miniaudio.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_misc.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_queue.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_thread.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_wav.cpp"
    "${LIBRARIES_DIR}/soloud/include/soloud_wavstream.cpp"
    "${LIBRARIES_DIR}/soloud/include/stb_vorbis.cpp"
    
    # Tracy source
    "${LIBRARIES_DIR}/tracy/TracyClient.cpp"
)

# Third-party headers
file(GLOB ZLIB_HEADERS "${LIBRARIES_DIR}/zlib/include/*.h")
set(TRACY_HEADERS "${LIBRARIES_DIR}/tracy/include/Tracy.hpp")

# Precompiled header
set(PCH_SOURCE "${SOURCE_DIR}/pch.cpp")
set(PCH_HEADER "${SOURCE_DIR}/pch.h")

# Create the static library
add_library(${PROJECT_NAME} STATIC
    ${MINTY_SOURCES}
    ${MINTY_HEADERS}
    ${THIRD_PARTY_SOURCES}
    ${ZLIB_HEADERS}
    ${TRACY_HEADERS}
    ${PCH_SOURCE}
    ${PCH_HEADER}
)

# Set precompiled header
target_precompile_headers(${PROJECT_NAME} PRIVATE "${PCH_HEADER}")

# # Set the precompiled header source to create mode
# set_source_files_properties(${PCH_SOURCE} PROPERTIES
#     COMPILE_FLAGS "/Yc\"pch.h\""
# )

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC
    ${SOURCE_DIR}
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
    
    # Linker flags for release
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:/LTCG> # Link-time code generation
    )
endif()

# Link directories
target_link_directories(${PROJECT_NAME} PUBLIC
    ${LIBRARIES_DIR}/vulkan/lib
    ${LIBRARIES_DIR}/glfw/lib
    ${LIBRARIES_DIR}/bullet/lib/$<CONFIG>
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    vulkan-1
    glfw3_mt
    BulletCollision
    BulletDynamics
    LinearMath
)

# Output directory - match devenv.bat expectations
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>"
)

# Add custom command to generate files
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Generating directory headers..."
    COMMAND python "${TOP}/Tools/Build/generate_directory_headers.py"
        "${SOURCE_DIR}/Minty"
)

# Print configuration info
message(STATUS "Minty Library Configuration:")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Vulkan: ${MINTY_VULKAN}")
message(STATUS "  SoLoud: ${MINTY_SOLOUD}")
message(STATUS "  Bullet: ${MINTY_BULLET}")
message(STATUS "  Tracy: ${MINTY_TRACE}")
