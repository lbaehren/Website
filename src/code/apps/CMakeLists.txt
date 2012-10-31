
## Assemble list of source files

file (GLOB apps_sources *.cc)

foreach (_filename ${apps_sources})

  get_filename_component (_app ${_filename} NAME_WE)

  ## Compiler instructions
  add_executable (${_app} ${_filename})

  ## Linker instructions
  target_link_libraries (${_app} libblog)

  ## Test execution
  add_test (${_app} ${_app})

endforeach (_filename)