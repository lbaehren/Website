
## Include directories

include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  )

## Directories with sources files

add_subdirectory (lib)
add_subdirectory (tests)

