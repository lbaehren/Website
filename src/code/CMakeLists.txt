
include_directories (
    ${CMAKE_CURRENT_SOURCE_DIR}/libs
    ${CMAKE_CURRENT_BINARY_DIR}/libs
    ${YAML_INCLUDES}
    ${Boost_INCLUDE_DIR}
    )

## Directories with sources files

add_subdirectory (external)
add_subdirectory (libs)
add_subdirectory (tools)
