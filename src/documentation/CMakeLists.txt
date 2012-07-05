
## === Documentation generation =================================================

if (DOXYGEN_EXECUTABLE)
  
  find_path (DOXYGEN_INPUT_DIR
    NAMES documentation/doxygen.config.in code/CMakeLists.txt
    PATHS ${PROJECT_SOURCE_DIR}
    PATH_SUFFIXES src
    )

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
