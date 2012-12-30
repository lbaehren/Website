
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
