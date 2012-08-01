
## Assemble list of source files
file (GLOB libblog_sources *.cc)

## Build the library
add_library (blog ${libblog_sources})
