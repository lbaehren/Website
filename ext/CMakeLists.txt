
## === Documentation generation =================================================

if (DOXYGEN_EXECUTABLE)
  
  ## Locate custom stylesheet
  find_file (DOXYGEN_CSS doxygen.css
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}
    )

  configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.config.in
    ${CMAKE_CURRENT_BINARY_DIR}/doxygen.config
    )
  
  add_custom_target (doc
    COMMAND ${DOXYGEN_EXECUTABLE} doxygen.config
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/doxygen.config
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
  
endif (DOXYGEN_EXECUTABLE)

## === Project sub-directories ==================================================

add_subdirectory (BlogTools)

## === Shell scripts ============================================================

find_file (BLOGINDEX_SH
  NAMES blogIndex.sh
  PATHS ${PROJECT_SOURCE_DIR}
  PATH_SUFFIXES ext
  )

find_file (CONVERTENTRIES_SH
  NAMES convertEntries.sh
  PATHS ${PROJECT_SOURCE_DIR}
  PATH_SUFFIXES ext
  )
