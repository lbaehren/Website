
## Include directories

include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  )

## Directories with sources files

add_subdirectory (cmake)
add_subdirectory (external)
add_subdirectory (lib)
add_subdirectory (scripts)
add_subdirectory (tests)
add_subdirectory (apps)
