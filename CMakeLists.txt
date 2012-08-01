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

option (ENABLE_TESTING        "Enable CTest test driver?"                     YES )
option (CONFIGURE_VERBOSE     "Increase verbosity during configuration?"      NO  )

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

##____________________________________________________________________
## Standard CMake modules

find_package (Git)
find_package (Doxygen)
find_package (Ruby)

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

##____________________________________________________________________
## Decomposition of Ruby version number

if (RUBY_VERSION)
  ## Convert string to list of numbers
  string (REGEX REPLACE "\\." ";" RUBY_VERSION_LIST ${RUBY_VERSION})
  ## Retrieve individual elements in the list
  list(GET RUBY_VERSION_LIST 0 RUBY_VERSION_MAJOR)
  list(GET RUBY_VERSION_LIST 1 RUBY_VERSION_MINOR)
  list(GET RUBY_VERSION_LIST 2 RUBY_VERSION_PATCH)
endif (RUBY_VERSION)

##____________________________________________________________________
## Find installation of Ruby Gems

find_program (GEM_EXECUTABLE gem
  HINTS ${GEM_ROOT_DIR} ${CMAKE_INSTALL_PREFIX}
  PATH_SUFFIXES bin lib
  )

if (GEM_EXECUTABLE)
  
  execute_process(
    COMMAND ${GEM_EXECUTABLE} --version
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    RESULT_VARIABLE GEM_RESULT_VARIABLE
    OUTPUT_VARIABLE GEM_VERSION
    ERROR_VARIABLE GEM_ERROR_VARIABLE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  
  if (GEM_VERSION)
    ## Convert string to list of numbers
    string (REGEX REPLACE "\\." ";" GEM_VERSION_LIST ${GEM_VERSION})
    ## Retrieve individual elements in the list
    list(GET GEM_VERSION_LIST 0 GEM_VERSION_MAJOR)
    list(GET GEM_VERSION_LIST 1 GEM_VERSION_MINOR)
    list(GET GEM_VERSION_LIST 2 GEM_VERSION_PATCH)
  endif (GEM_VERSION)  
  
endif (GEM_EXECUTABLE)

##____________________________________________________________________
## Find installation of Ruby Rake

find_program (RAKE_EXECUTABLE rake
  HINTS ${RAKE_ROOT_DIR} ${CMAKE_INSTALL_PREFIX}
  PATH_SUFFIXES bin lib
  )

if (RAKE_EXECUTABLE)
  
  execute_process(
    COMMAND ${RAKE_EXECUTABLE} --version
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    RESULT_VARIABLE RAKE_RESULT_VARIABLE
    OUTPUT_VARIABLE RAKE_VERSION
    ERROR_VARIABLE RAKE_ERROR_VARIABLE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  
  if (RAKE_VERSION)
    ## Convert string to list of numbers
    string (REGEX REPLACE "\\." ";" RAKE_VERSION_LIST ${RAKE_VERSION})
    ## Retrieve individual elements in the list
    list(GET RAKE_VERSION_LIST 0 RAKE_VERSION_MAJOR)
    list(GET RAKE_VERSION_LIST 1 RAKE_VERSION_MINOR)
    list(GET RAKE_VERSION_LIST 2 RAKE_VERSION_PATCH)
  endif (RAKE_VERSION)  
  
endif (RAKE_EXECUTABLE)

## ==============================================================================
##
##  Installation location
##
## ==============================================================================

## For a production and development system on one of the server machines the
## installation is done into "/var/local/prometheus". If however development
## (or even just test installation) is carried out on a different system with
## the user/developer not having write permissions to "/var/local" we need to
## move to the installation root to a different point.

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

  set (CMAKE_INSTALL_PREFIX
    "${PROJECT_SOURCE_DIR}/site" CACHE PATH "Website install prefix" FORCE
    )
endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

## ==============================================================================
##
##  Build targets/instructions
##
## ==============================================================================

## Project sub-directories

add_subdirectory (src)

##____________________________________________________________________
## Targets operating from the top-level directory

## Render the website

add_custom_target (Website ALL
  COMMAND rake
  DEPENDS ${PROJECT_SOURCE_DIR}/config.yaml
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )

add_dependencies (Website blog)

set_property (DIRECTORY
  APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
  ${CMAKE_INSTALL_PREFIX}
  ${PROJECT_SOURCE_DIR}/webgen.cache
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
message (STATUS " .. Pages source directory ...... = ${DATA_PAGES_DIR}"          )
message (STATUS " .. Enable CTest test driver? ... = ${ENABLE_TESTING}"          )
message (STATUS " .. Verbose configure? .......... = ${CONFIGURE_VERBOSE}"       )
message (STATUS " Ruby configuration:"                                           )
message (STATUS " .. Ruby executable ............. = ${RUBY_EXECUTABLE}"         )
message (STATUS " .. Ruby version ................ = ${RUBY_VERSION}"            )
message (STATUS " .. Path to Ruby library ........ = ${RUBY_LIBRARY}"            )
message (STATUS " .. Include directory ........... = ${RUBY_INCLUDE_DIRS}"       )
message (STATUS " .. Gem executable .............. = ${GEM_EXECUTABLE}"          )
message (STATUS " .. Gem executable version ...... = ${GEM_VERSION}"             )
message (STATUS " .. Rake executable ............. = ${RAKE_EXECUTABLE}"         )
message (STATUS " .. Rake executable version ..... = ${RAKE_VERSION}"            )
message (STATUS " .. Rails executable ............ = ${RAILS_EXECUTABLE}"        )
message (STATUS " .. Rails executable version .... = ${RAILS_VERSION}"           )
message (STATUS "------------------------------------------------------------ "  )
