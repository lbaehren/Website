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

## Load test driver and enable it
include (CTest)
enable_testing()

##__________________________________________________________
## Installation prefix

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set (CMAKE_INSTALL_PREFIX
    "${PROJECT_SOURCE_DIR}/release" CACHE PATH "Install prefix" FORCE
    )
endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

##__________________________________________________________
## Path to the generated static website

set (INSTALL_PREFIX               "${PROJECT_SOURCE_DIR}/release"   )
set (INSTALL_PREFIX_WEBSITE       "${INSTALL_PREFIX}/website"       )
set (INSTALL_PREFIX_DOCUMENTATION "${INSTALL_PREFIX}/documentation" )
set (PROJECT_UPLOAD_PATH          "/Volumes/webdav/webseiten"       )
set (PROJECT_LIVEDISK_URL         "https://382611-ftp.livedisk.df.eu/webdav")

## ==============================================================================
##
##  System inspection
##
## ==============================================================================

## Project source directories
##
## .                               ...  PROJECT_SOURCE_DIR
## `-- src
##     |-- code                    ...  PROJECT_SOURCE_DIR_CODE
##     |   |-- CMakeModules        ...  PROJECT_CMAKE_MODULE_PATH
##     |   |-- apps
##     |   |-- external
##     |   |-- lib
##     |   |-- scripts
##     |   `-- tests
##     |-- images
##     |-- pages                   ...  PROJECT_SOURCE_DIR_PAGES
##     |   |-- blog                ...  PROJECT_SOURCE_DIR_BLOG
##     |   |-- computing
##     |   |-- development
##     |   |-- photography
##     |   |-- research
##     |   `-- work
##     `-- templates
##

find_path (PROJECT_SOURCE_DIR_CODE
  NAMES lib/BlogConfig.h.in lib/BlogNode.h lib/Timestamp.h
  PATHS ${CMAKE_CURRENT_SOURCE_DIR}
  PATH_SUFFIXES src code src/code
  )
if (NOT PROJECT_SOURCE_DIR_CODE)
  message (SEND_ERROR "Missing code source dir (PROJECT_SOURCE_DIR_CODE)")
endif (NOT PROJECT_SOURCE_DIR_CODE)

find_path (PROJECT_SOURCE_DIR_BLOG
  NAMES upcoming.page archive.page 2012.page 2011.page 2010.page
  PATHS ${CMAKE_CURRENT_SOURCE_DIR}
  PATH_SUFFIXES src pages src/pages src/pages/blog pages/blog blog
  )
if (NOT PROJECT_SOURCE_DIR_BLOG)
  message (SEND_ERROR "Missing blog pages source dir (PROJECT_SOURCE_DIR_BLOG)")
endif (NOT PROJECT_SOURCE_DIR_BLOG)

find_path (PROJECT_SOURCE_DIR_PAGES
  NAMES index.page default.template default.css
  PATHS ${PROJECT_SOURCE_DIR}
  PATH_SUFFIXES src pages src/pages
  )
if (NOT PROJECT_SOURCE_DIR_PAGES)
  message (SEND_ERROR "Missing webpages source dir (PROJECT_SOURCE_DIR_PAGES)")
endif (NOT PROJECT_SOURCE_DIR_PAGES)

set (PROJECT_BINARY_DIR_PAGES ${PROJECT_BINARY_DIR}/src/pages)

##__________________________________________________________
## Custom CMake modules

find_path (PROJECT_CMAKE_MODULE_PATH
  NAMES FindGem.cmake FindRake.cmake
  PATHS ${PROJECT_SOURCE_DIR}
  PATH_SUFFIXES src src/code src/config src/code/CMakeModules
  )

if (PROJECT_CMAKE_MODULE_PATH)
  set (CMAKE_MODULE_PATH ${PROJECT_CMAKE_MODULE_PATH} CACHE PATH
    "CMake module path"
    FORCE
    )
else (PROJECT_CMAKE_MODULE_PATH)
  message (WARNING "Failed to locate custom CMake modules!")
endif (PROJECT_CMAKE_MODULE_PATH)

foreach (_cmakeModule
  Boost
  Git
  Doxygen
  Gem
  Gnuplot
  KWsys
  Rake
  Ruby
  Webgen
  )
  ## Verbosity of module
  string (TOUPPER ${_cmakeModule} _varModule)
  set (${_varModule}_FIND_QUIETLY YES )
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

add_subdirectory (src)

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

message (STATUS "------------------------------------------------------------"    )
message (STATUS "[Website] Configuration summary."                                )
message (STATUS "------------------------------------------------------------ "   )
message (STATUS " System configuration:"                                          )
message (STATUS " .. Processor type .............. = ${CMAKE_SYSTEM_PROCESSOR}"   )
message (STATUS " .. CMake executable ............ = ${CMAKE_COMMAND}"            )
message (STATUS " .. CMake version ............... = ${CMAKE_VERSION}"            )
message (STATUS " .. System name ................. = ${CMAKE_SYSTEM}"             )
message (STATUS " .. C++ compiler ................ = ${CMAKE_CXX_COMPILER}"       )
message (STATUS " .. C compiler .................. = ${CMAKE_C_COMPILER}"         )
message (STATUS " .. size(void*) ................. = ${CMAKE_SIZEOF_VOID_P}"      )
message (STATUS " Project configuration:"                                         )
message (STATUS " .. Version number .............. = ${PROJECT_VERSION}"          )
message (STATUS " .. Installation prefix ......... = ${CMAKE_INSTALL_PREFIX}"     )
message (STATUS " .. Installation prefix Website . = ${INSTALL_PREFIX_WEBSITE}"   )
message (STATUS " .. Pages source directory ...... = ${PROJECT_SOURCE_DIR_PAGES}" )
message (STATUS " .. Blog source directory ....... = ${PROJECT_SOURCE_DIR_BLOG}"  )
message (STATUS " .. Custom CMake modules ........ = ${PROJECT_CMAKE_MODULE_PATH}")
message (STATUS " .. Path to upload location ..... = ${PROJECT_UPLOAD_PATH}"      )
message (STATUS " External tools & packages:"                                     )
message (STATUS " .. Doxygen executable .......... = ${DOXYGEN_EXECUTABLE}"       )
message (STATUS " .. Doxygen version ............. = ${DOXYGEN_VERSION}"          )
message (STATUS " .. Ruby executable ............. = ${RUBY_EXECUTABLE}"          )
message (STATUS " .. Ruby version ................ = ${RUBY_VERSION}"             )
message (STATUS " .. Path to Ruby library ........ = ${RUBY_LIBRARIES}"           )
message (STATUS " .. Include directory ........... = ${RUBY_INCLUDES}"            )
message (STATUS " .. Gem executable .............. = ${GEM_EXECUTABLE}"           )
message (STATUS " .. Gem executable version ...... = ${GEM_VERSION}"              )
message (STATUS " .. Rake executable ............. = ${RAKE_EXECUTABLE}"          )
message (STATUS " .. Rake executable version ..... = ${RAKE_VERSION}"             )
message (STATUS " .. Webgen executable ........... = ${WEBGEN_EXECUTABLE}"        )
message (STATUS " .. Webgen executable version ... = ${WEBGEN_VERSION}"           )
message (STATUS "------------------------------------------------------------ "   )

