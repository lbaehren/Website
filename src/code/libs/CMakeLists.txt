
## =============================================================================
##
## Compiler settings
##
## =============================================================================

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

## =============================================================================
##
## Libraries build instruction
##
## =============================================================================

foreach (_module dal blog )

    ## Process configured header file
    find_file(${_module}Config ${_module}_config.h.in
        HINTS ${CMAKE_CURRENT_SOURCE_DIR}/${_module}
    )

    if (${_module}Config)
        configure_file (
            ${${_module}Config}
            ${CMAKE_CURRENT_BINARY_DIR}/${_module}/${_module}_config.h
            )
    endif (${_module}Config)

    ## Get list of source files for the library
    file (GLOB_RECURSE lib${_module}_sources
        ${_module}/*.h
        ${_module}/*.cc
        ${_module}/*/*.h
        ${_module}/*/*.cc
        )

    if (lib${_module}_sources)

        ## Compiler instructions
        add_library (${_module} ${lib${_module}_sources})

        install (
            TARGETS ${_module}
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            )

        target_link_libraries (${_module} ${YAML_LIBRARIES})

        install (
            DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${_module} DESTINATION include
            FILES_MATCHING PATTERN "*.h"
            )

    endif (lib${_module}_sources)

endforeach (_module)

## Module dependencies

target_link_libraries (blog dal)
