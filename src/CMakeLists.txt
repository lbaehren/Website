

##______________________________________________________________________________
## Generate Webgen configuration file

configure_file (
  ${PROJECT_SOURCE_DIR}/webgen.config.in
  ${PROJECT_BINARY_DIR}/webgen.config
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
