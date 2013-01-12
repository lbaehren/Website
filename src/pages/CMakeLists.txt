
##_______________________________________________________________________________
## Target: Render the website

## Build instructions
add_custom_target (Website ALL
  COMMAND ${WEBGEN_EXECUTABLE} render
  DEPENDS ${PROJECT_BINARY_DIR}/config.yaml
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  COMMENT "Rendering website from sources ..."
  )
add_dependencies (Website libblog)

## Installation instructions
install(
  DIRECTORY ${PROJECT_BINARY_DIR}/website
  DESTINATION ${CMAKE_INSTALL_PREFIX}
  USE_SOURCE_PERMISSIONS
  )

##_______________________________________________________________________________
## Build the page with the most recent blog entries

if (script_blog_recent AND PROJECT_SOURCE_DIR_BLOG)

  ## Build target
  add_custom_target (recent_blog_entries
    COMMAND ${script_blog_recent}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR_BLOG}
    COMMENT "Generating page with recent blog entries ..."
    )

  ## Dependencies
  add_dependencies (recent_blog_entries blog)
  add_dependencies (Website recent_blog_entries)

endif (script_blog_recent AND PROJECT_SOURCE_DIR_BLOG)

##_______________________________________________________________________________
## Publish the website online

add_custom_target (online
  COMMAND rsync -axuvP ${CMAKE_INSTALL_PREFIX}/website/* ${PROJECT_UPLOAD_PATH}
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "Publishing website - uploading generated pages ..."
  )
