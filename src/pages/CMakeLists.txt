
##_______________________________________________________________________________
## Render the website

add_custom_target (Website ALL
  COMMAND ${WEBGEN_EXECUTABLE} render
  DEPENDS ${PROJECT_SOURCE_DIR}/config.yaml
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "Rendering website from sources ..."
  )
add_dependencies (Website blog)

##_______________________________________________________________________________
## Build the page with the most recent blog entries

if (script_blogrecent AND BLOG_SOURCE_DIR)
  ## Build target
  add_custom_target (recent_blog_entries
    COMMAND ${script_blogrecent}
    WORKING_DIRECTORY ${BLOG_SOURCE_DIR}
    COMMENT "Generating page with recent blog entries ..."
    )
  ## Dependencies
  add_dependencies (recent_blog_entries blog)
  add_dependencies (Website recent_blog_entries)
endif (script_blogrecent AND BLOG_SOURCE_DIR)

##_______________________________________________________________________________
## Publish the website online

add_custom_target (online
  COMMAND rsync -avE --delete ${WEBSITE_INSTALL_PREFIX}/* bahren@dop131:/export/home/bahren/public_html
  DEPENDS ${WEBSITE_INSTALL_PREFIX}/index.html
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "Publishing website - uploading generated pages ..."
  )
add_dependencies (online Website)

