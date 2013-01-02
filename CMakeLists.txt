## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

## Name of the project handled by CMake
project (Website)

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

## Enforced CMake policy
cmake_policy (VERSION 2.8)

## Project release version (major.minor.patch)
set (PROJECT_VERSION_MAJOR 0 )
set (PROJECT_VERSION_MINOR 1 )
set (PROJECT_VERSION_PATCH 0 )
set (PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

## ==============================================================================
##
##  Configuration/Build options
##
## ==============================================================================

option (ENABLE_TESTING        "Enable CTest test driver?"                  YES )
option (CONFIGURE_VERBOSE     "Increase verbosity during configuration?"   NO  )

##  Installation location
##
## ==============================================================================

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

  set (CMAKE_INSTALL_PREFIX
    "${PROJECT_SOURCE_DIR}/release" CACHE PATH "Install prefix" FORCE
    )
endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

## Path to the generated static website
set (INSTALL_PREFIX               "${PROJECT_SOURCE_DIR}/release"   )
set (INSTALL_PREFIX_WEBSITE       "${INSTALL_PREFIX}/website"       )
set (INSTALL_PREFIX_DOCUMENTATION "${INSTALL_PREFIX}/documentation" )

##__________________________________________________________
## Handle option: Enable CTest test driver?

if (ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (ENABLE_TESTING)

## ==============================================================================
##
##  System inspection
##
## ==============================================================================

## Project source directories

find_path (PROJECT_SOURCE_DIR_CODE
  NAMES lib/BlogConfig.h.in lib/BlogNode.h lib/Timestamp.h
  PATHS ${CMAKE_CURRENT_SOURCE_DIR}
  PATH_SUFFIXES src code src/code
  )

find_path (PROJECT_SOURCE_DIR_BLOG
  NAMES upcoming.page archive.page 2012.page 2011.page 2010.page
  PATHS ${CMAKE_CURRENT_SOURCE_DIR}
  PATH_SUFFIXES src pages src/pages src/pages/blog pages/blog blog
  )

find_path (SOURCE_DIR_PAGES
  NAMES index.page default.template default.css
  PATHS ${PROJECT_SOURCE_DIR}
  PATH_SUFFIXES src pages src/pages
  )

## Custom CMake modules

find_path (LOCAL_CMAKE_MODULE_PATH
  NAMES FindGem.cmake FindRake.cmake
  PATHS ${PROJECT_SOURCE_DIR}
  PATH_SUFFIXES src src/code src/config src/code/CMakeModules
  )

if (LOCAL_CMAKE_MODULE_PATH)
  set (CMAKE_MODULE_PATH ${LOCAL_CMAKE_MODULE_PATH} CACHE PATH
    "CMake module path"
    FORCE
    )
else (LOCAL_CMAKE_MODULE_PATH)
  message (WARNING "Failed to locate custom CMake modules!")
endif (LOCAL_CMAKE_MODULE_PATH)

foreach (_cmakeModule
  Boost
  Git
  Doxygen
  Gem
  KWsys
  Rake
  Ruby
  Webgen
  )
  ## Verbosity of module
  if (NOT CONFIGURE_VERBOSE)
    ## Convert module name to upper-case
    string (TOUPPER ${_cmakeModule} _varModule)
    ##
    set (${_varModule}_FIND_QUIETLY YES )
  endif (NOT CONFIGURE_VERBOSE)
  ## load the module
  find_package (${_cmakeModule})
endforeach (_cmakeModule)

##____________________________________________________________________
## Extract Doxygen version number

if (DOXYGEN_EXECUTABLE)

  execute_process(
    COMMAND ${DOXYGEN_EXECUTABLE} --version
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    RESULT_VARIABLE DOXYGEN_RESULT_VARIABLE
    OUTPUT_VARIABLE DOXYGEN_VERSION
    ERROR_VARIABLE DOXYGEN_ERROR_VARIABLE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )

  if (DOXYGEN_VERSION)
    ## Convert string to list of numbers
    string (REGEX REPLACE "\\." ";" DOXYGEN_VERSION_LIST ${DOXYGEN_VERSION})
    ## Retrieve individual elements in the list
    list(GET DOXYGEN_VERSION_LIST 0 DOXYGEN_VERSION_MAJOR)
    list(GET DOXYGEN_VERSION_LIST 1 DOXYGEN_VERSION_MINOR)
    list(GET DOXYGEN_VERSION_LIST 2 DOXYGEN_VERSION_PATCH)
  endif (DOXYGEN_VERSION)

endif (DOXYGEN_EXECUTABLE)

## ==============================================================================
##
##  Build targets/instructions
##
## ==============================================================================

## Project sub-directories

add_subdirectory (doc)
add_subdirectory (src)

##_______________________________________________________________________________
## Render the website

add_custom_target (Website ALL
  COMMAND ${WEBGEN_EXECUTABLE} render
  DEPENDS ${PROJECT_SOURCE_DIR}/config.yaml
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "Rendering website from sources ..."
  )
add_dependencies (Website libblog)

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
  COMMAND rsync -avE --delete ${INSTALL_PREFIX_WEBSITE}/* /Volumes/webdav/webseiten
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "Publishing website - uploading generated pages ..."
  )

## ==============================================================================
##
##  Clean-up
##
## ==============================================================================

set_property (DIRECTORY
  APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
  ${CMAKE_INSTALL_PREFIX}
  ${PROJECT_SOURCE_DIR}/webgen.cache
  ${PROJECT_SOURCE_DIR}/config.yaml
  )

## ==============================================================================
##
##  Configuration summary
##
## ==============================================================================

## Display summary of configuration settings

message (STATUS "------------------------------------------------------------"   )
message (STATUS "[Website] Configuration summary."                               )
message (STATUS "------------------------------------------------------------ "  )
message (STATUS " System configuration:"                                         )
message (STATUS " .. Processor type .............. = ${CMAKE_SYSTEM_PROCESSOR}"  )
message (STATUS " .. CMake executable ............ = ${CMAKE_COMMAND}"           )
message (STATUS " .. CMake version ............... = ${CMAKE_VERSION}"           )
message (STATUS " .. System name ................. = ${CMAKE_SYSTEM}"            )
message (STATUS " .. C++ compiler ................ = ${CMAKE_CXX_COMPILER}"      )
message (STATUS " .. C compiler .................. = ${CMAKE_C_COMPILER}"        )
message (STATUS " .. size(void*) ................. = ${CMAKE_SIZEOF_VOID_P}"     )
message (STATUS " Project configuration:"                                        )
message (STATUS " .. Version number .............. = ${PROJECT_VERSION}"         )
message (STATUS " .. Installation prefix ......... = ${CMAKE_INSTALL_PREFIX}"    )
message (STATUS " .. Pages source directory ...... = ${SOURCE_DIR_PAGES}"        )
message (STATUS " .. Blog source directory ....... = ${PROJECT_SOURCE_DIR_BLOG}" )
message (STATUS " .. Enable CTest test driver? ... = ${ENABLE_TESTING}"          )
message (STATUS " .. Verbose configure? .......... = ${CONFIGURE_VERBOSE}"       )
message (STATUS " External tools & packages:"                                    )
message (STATUS " .. Doxygen executable .......... = ${DOXYGEN_EXECUTABLE}"      )
message (STATUS " .. Doxygen version ............. = ${DOXYGEN_VERSION}"         )
message (STATUS " .. Ruby executable ............. = ${RUBY_EXECUTABLE}"         )
message (STATUS " .. Ruby version ................ = ${RUBY_VERSION}"            )
message (STATUS " .. Path to Ruby library ........ = ${RUBY_LIBRARIES}"          )
message (STATUS " .. Include directory ........... = ${RUBY_INCLUDES}"           )
message (STATUS " .. Gem executable .............. = ${GEM_EXECUTABLE}"          )
message (STATUS " .. Gem executable version ...... = ${GEM_VERSION}"             )
message (STATUS " .. Rake executable ............. = ${RAKE_EXECUTABLE}"         )
message (STATUS " .. Rake executable version ..... = ${RAKE_VERSION}"            )
message (STATUS " .. Webgen executable ........... = ${WEBGEN_EXECUTABLE}"       )
message (STATUS " .. Webgen executable version ... = ${WEBGEN_VERSION}"          )
message (STATUS "------------------------------------------------------------ "  )
