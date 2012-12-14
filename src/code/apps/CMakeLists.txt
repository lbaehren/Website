
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

## Additional tests

add_test (blog_title1 blog --title)
add_test (blog_title2 blog --title "My new title")
add_test (blog_title3 blog -T "My new title")
add_test (blog_index1 blog --index-all)
add_test (blog_index2 blog -I)
add_test (blog_title_index blog -T "My new title" -I)
add_test (blog_index_title blog -I -T "My new title")
