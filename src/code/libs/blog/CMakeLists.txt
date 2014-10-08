
## Assemble list of source files
file (GLOB libblog_sources *.h *.cc)

add_library (blog ${libblog_sources})

target_link_libraries (blog dal)

set_target_properties (blog
    PROPERTIES
    LINKER_LANGUAGE CXX
)
