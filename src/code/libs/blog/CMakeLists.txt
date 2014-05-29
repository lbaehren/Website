
if (CMAKE_COMPILER_IS_GNUCXX)
    if (${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 4.7)
        set (CMAKE_CXX_FLAGS "-fPIC -std=c++0x")
    else ()
        set (CMAKE_CXX_FLAGS "-fPIC -std=c++11")
    endif ()
else (CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "C++ compiler is other than GNU")
    set (CMAKE_CXX_FLAGS "-std=c++11")
endif (CMAKE_COMPILER_IS_GNUCXX)

## Assemble list of source files
file (GLOB libblog_sources *.h *.cc)

add_library (blog ${libblog_sources})

set_target_properties (blog
    PROPERTIES
    LINKER_LANGUAGE CXX
)
