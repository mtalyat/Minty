file(GLOB MINTY_LIBRARY_SUBDIRS LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/*")
set(MINTY_LIBRARY_INCLUDE_DIRS)

foreach(subdir IN LISTS MINTY_LIBRARY_SUBDIRS)
    if(IS_DIRECTORY "${subdir}/Include")
        list(APPEND MINTY_LIBRARY_INCLUDE_DIRS "${subdir}/Include")
    endif()

    if(IS_DIRECTORY "${subdir}/include")
        list(APPEND MINTY_LIBRARY_INCLUDE_DIRS "${subdir}/include")
    endif()
endforeach()

list(REMOVE_DUPLICATES MINTY_LIBRARY_INCLUDE_DIRS)

file(GLOB MINTY_ZLIB_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/ZLib/Source/*.cpp"
)

file(GLOB MINTY_SOLOUD_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/SoLoud/Include/soloud*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SoLoud/Include/dr_impl.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SoLoud/Include/stb_vorbis.cpp"
)

add_library(minty_zlib STATIC ${MINTY_ZLIB_SOURCES})
target_include_directories(minty_zlib PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/ZLib/Include"
)
target_compile_features(minty_zlib PUBLIC cxx_std_${MINTY_CXX_STANDARD})
minty_set_target_output_dirs(minty_zlib Library)
set_target_properties(minty_zlib PROPERTIES
    OUTPUT_NAME "zlib"
)

add_library(minty_stb STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/STB/Source/stb_image.cpp"
)
target_include_directories(minty_stb PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/STB/Include")
target_compile_features(minty_stb PUBLIC cxx_std_${MINTY_CXX_STANDARD})
minty_set_target_output_dirs(minty_stb Library)
set_target_properties(minty_stb PROPERTIES
    OUTPUT_NAME "stb"
)

set(MINTY_LIBRARY_STUB_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/minty_library_stub.cpp")
file(WRITE "${MINTY_LIBRARY_STUB_SOURCE}" "namespace Minty { void _minty_library_stub() {} }\n")

minty_add_layer(
    NAME minty_library
    LAYER Library
    SOURCES
        ${MINTY_SOLOUD_SOURCES}
        "${MINTY_LIBRARY_STUB_SOURCE}"
    PUBLIC_INCLUDE_DIRS
        "${MINTY_SOURCE_ROOT}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
        ${MINTY_LIBRARY_INCLUDE_DIRS}
    PUBLIC_DEPS
        minty_zlib
        minty_stb
)

add_library(Library ALIAS minty_library)
add_library(Libraries ALIAS minty_library)

set_target_properties(minty_library PROPERTIES
    OUTPUT_NAME "MintyLibrary"
)

file(GLOB_RECURSE MINTY_VENDOR_BINARIES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*/Binary/*.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/*/Binary/*.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/*/Binary/*.pdb"
    "${CMAKE_CURRENT_SOURCE_DIR}/*/Binary/*/*.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/*/Binary/*/*.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/*/Binary/*/*.pdb"
)

# set(MINTY_VENDOR_OUTPUT_DIR "${MINTY_ARTIFACTS_DIR}/Library/vendor")

# add_custom_target(minty_library_assets
#     COMMAND ${CMAKE_COMMAND} -E make_directory "${MINTY_VENDOR_OUTPUT_DIR}"
# )

# foreach(binary_file IN LISTS MINTY_VENDOR_BINARIES)
#     add_custom_command(TARGET minty_library_assets POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_if_different "${binary_file}" "${MINTY_VENDOR_OUTPUT_DIR}"
#     )
# endforeach()

# add_dependencies(minty_library minty_library_assets)
