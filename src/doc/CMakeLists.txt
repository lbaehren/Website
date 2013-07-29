
## === Documentation generation =================================================

if (DOXYGEN_EXECUTABLE)

  ## Configuration variables for Doxygen

  set (DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_INSTALL_PREFIX}/doc")

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
