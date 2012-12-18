
## === Build instructions =======================================================

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

  ## Installation instructions
  install (
    TARGETS ${_app}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )

endforeach (_filename)

## === Additional testing instructions ==========================================

## Always pass along "-D" option for a dry run
add_test (blog_title1      blog -D --title)
add_test (blog_title2      blog -D --title "My new title")
add_test (blog_title3      blog -D -T "My new title")
add_test (blog_index1      blog -D --index-all)
add_test (blog_index2      blog -D -I)
add_test (blog_title_index blog -D -T "My new title" -I)
add_test (blog_index_title blog -D -I -T "My new title")
