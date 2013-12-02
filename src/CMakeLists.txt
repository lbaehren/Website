

##______________________________________________________________________________
## Generate Webgen configuration file ===

configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/config.yaml.in
  ${PROJECT_BINARY_DIR}/config.yaml
  )

##______________________________________________________________________________
## Process project sub-directories

## Doumentation
add_subdirectory (doc)

## Source code (C/C++)
add_subdirectory (code)

## Layout templates
add_subdirectory (templates)

## Source files for the web pages
add_subdirectory (pages)

##______________________________________________________________________________
## Target dependencies

add_dependencies (Website libblog)

if (GNUPLOT_EXECUTABLE)
  add_dependencies (blog stats)
endif ()
