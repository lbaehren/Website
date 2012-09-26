
foreach (script
    blogEntry
    blogIndex
    blogRecent
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

endforeach (script)
