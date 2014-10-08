
# Assemble list of source files
file (GLOB libdal_sources *.h *.cc)

add_library (dal ${libdal_sources})

set_target_properties (dal
    PROPERTIES
    LINKER_LANGUAGE CXX
)
