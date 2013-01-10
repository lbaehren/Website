
file (GLOB test_sources *.cc)

foreach (test_source ${test_sources})

  ## Strip extension from filename
  get_filename_component (testFilename ${test_source} NAME_WE)
  ## Compile
  add_executable (${testFilename} ${test_source})
  ## Link
  target_link_libraries (${testFilename} libblog)
  ## Testing
  add_test (${testFilename} ${testFilename})

endforeach (test_source)
