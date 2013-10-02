
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
## Mount the livedisk

find_program (WEBDAV_EXECUTABLE mount_webdav
  HINTS ${CMAKE_INSTALL_PREFIX}
  PATH_SUFFIXES bin sbin
  )

if (WEBDAV_EXECUTABLE)
    add_custom_target (mount_livedisk
        COMMAND ${WEBDAV_EXECUTABLE} ${PROJECT_LIVEDISK_URL} ${PROJECT_UPLOAD_PATH}
        COMMENT "Mounting livedisk ..."
        )
endif (WEBDAV_EXECUTABLE)

##_______________________________________________________________________________
## Publish the website online

#        -a, --archive               archive mode; equals -rlptgoD (no -H,-A,-X)
#            --no-OPTION             turn off an implied OPTION (e.g. --no-D)
#        -u, --update                skip files that are newer on the receiver
#            --inplace               update destination files in-place
#            --append                append data onto shorter files
#            --append-verify         --append w/old data in file checksum
#        -x, --one-file-system       don't cross filesystem boundaries
#        -p, --perms                 preserve permissions
#            --fileflags             preserve file-flags (aka chflags)

find_program (RSYNC_EXECUTABLE rsync
  HINTS ${CMAKE_INSTALL_PREFIX}
  PATH_SUFFIXES bin
  )

if (RSYNC_EXECUTABLE)

    add_custom_target (online
        COMMAND ${RSYNC_EXECUTABLE} -axuP ${CMAKE_INSTALL_PREFIX}/website/* ${PROJECT_UPLOAD_PATH}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Publishing website - uploading generated pages ..."
        )

else (RSYNC_EXECUTABLE)

  message (STATUS "Unable to publish generated pages - missing rsync!")

endif (RSYNC_EXECUTABLE)
