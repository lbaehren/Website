
## === [ Configured header file ] ===============================================

configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/BlogConfig.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/BlogConfig.h
  )

## === [ Library build instructions ] ===========================================

## Assemble list of source files
file (GLOB libblog_sources *.cc)

## Build the library
add_library (libblog ${libblog_sources})

set_target_properties(libblog
  PROPERTIES
  OUTPUT_NAME blog
  )
