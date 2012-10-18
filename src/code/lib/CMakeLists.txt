
## Assemble list of source files
file (GLOB libblog_sources *.cc)

## Build the library
add_library (libblog ${libblog_sources})

set_target_properties(libblog
  PROPERTIES
  OUTPUT_NAME blog
  )
