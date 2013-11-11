
foreach (script
    blog_entry
    blog_index
    blog_recent
    convertEntries
    )

  ## Convert name of script to variable
  string(TOLOWER ${script} varScript)

  ## Find the file
  find_file(
    script_${varScript}
    ${script}
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}
    DOC "Path to the ${script} script"
    )

  ## Installation instructions
  install (FILES ${script}
    DESTINATION bin
    PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE OWNER_READ GROUP_READ
    )

endforeach (script)

## Generation of statistics

configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/generateStatistics
    ${CMAKE_CURRENT_BINARY_DIR}/generateStatistics
    )

add_custom_target (stats
    COMMAND ./generateStatistics
    COMMAND gnuplot ${CMAKE_CURRENT_SOURCE_DIR}/plotStatistics.gpm
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating blog entry statistics ..."
    )
