

## === Generate Webgen configuration file ===

configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/config.yaml.in
  ${PROJECT_BINARY_DIR}/config.yaml
  )

## === Process project sub-directories ===

## Source code (C/C++)
add_subdirectory (code)

## Layout templates
add_subdirectory (templates)

## Source files for the web pages
add_subdirectory (pages)
