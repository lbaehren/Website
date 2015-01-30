#-------------------------------------------------------------------------------
# Copyright (c) 2004-2014, Lars Baehren <lbaehren@gmail.com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
#  * Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#-------------------------------------------------------------------------------

## =============================================================================
##
##  CMake project settings
##
## =============================================================================

# Name of the project
project (larsbaehren)

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8.2)

## Enforced CMake policy
cmake_policy (VERSION 2.8.2)

## Project release version (major.minor.patch)
set (PROJECT_VERSION_MAJOR "0" )
set (PROJECT_VERSION_MINOR "1" )
set (PROJECT_VERSION_PATCH "0" )
set (PROJECT_VERSION_SERIES "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
set (PROJECT_VERSION "${PROJECT_VERSION_SERIES}.${PROJECT_VERSION_PATCH}")

## =============================================================================
##
##  Configuration/Build options
##
## =============================================================================

option (VERBOSE_CONFIGURE "Enhanced verbosity during configuration?" NO )
option (WITH_TESTS        "Enable the CTest test driver?"            NO )

##__________________________________________________________
## Handle option: Enable test driver and build test programs?

if (WITH_TESTS)
  include (CTest)
  enable_testing()
endif (WITH_TESTS)

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

## =============================================================================
##
##  System inspection
##
## =============================================================================

## Project source directories
##
## .                               ...  PROJECT_SOURCE_DIR
## `-- src
##     |-- code
##     |   |-- CMakeModules        ...  PROJECT_CMAKE_MODULE_PATH
##     |   `-- external
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

list (INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

foreach (_externalPackage
    Boost
    Git
    Doxygen
    Gem
    Gnuplot
    KWsys
    Rake
    Rsync
    Ruby
    Webgen
    YAML
    )

    ## Convert module name to upper-case
    string (TOUPPER ${_externalPackage} _externalPackageVar)

    ## Verbosity of the script to find the package
    if (VERBOSE_CONFIGURE)
        set (${_externalPackageVar}_FIND_QUIETLY NO)
    else (VERBOSE_CONFIGURE)
        set (${_externalPackageVar}_FIND_QUIETLY YES)
    endif (VERBOSE_CONFIGURE)

    ## Find the package
    find_package (${_externalPackage} REQUIRED)

endforeach (_externalPackage)

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

## =============================================================================
##
##  Build targets/instructions
##
## =============================================================================

##___________________________________________________________________
## Webgen configuration file

configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/webgen.config.in
    ${CMAKE_CURRENT_SOURCE_DIR}/webgen.config
)

find_file (WEBGEN_CONFIG webgen.config
    HINTS ${CMAKE_CURRENT_SOURCE_DIR}
    )

##___________________________________________________________________
## Build the website

add_custom_target (Website ALL
  COMMAND ${WEBGEN_EXECUTABLE} generate
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "Rendering website from sources ..."
  )

##___________________________________________________________________
## Installation instructions

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/out
  DESTINATION ${CMAKE_INSTALL_PREFIX}
  USE_SOURCE_PERMISSIONS
  )

##___________________________________________________________________
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


if (RSYNC_EXECUTABLE)
    add_custom_target (online
        COMMAND ${RSYNC_EXECUTABLE} -axuzP --delete ${PROJECT_SOURCE_DIR}/out/* ${PROJECT_UPLOAD_PATH}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Publishing website - uploading generated pages ..."
        )
else (RSYNC_EXECUTABLE)
  message (STATUS "Unable to publish generated pages - missing rsync!")
endif (RSYNC_EXECUTABLE)

##___________________________________________________________________
## Project sub-directories

add_subdirectory (ext)


## =============================================================================
##
##  Clean-up
##
## =============================================================================

set_property (DIRECTORY
  APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
  ${CMAKE_INSTALL_PREFIX}
  ${PROJECT_SOURCE_DIR}/out
  ${PROJECT_SOURCE_DIR}/tmp
  ${PROJECT_SOURCE_DIR}/webgen.cache
  ${PROJECT_SOURCE_DIR}/webgen.config
  ${PROJECT_SOURCE_DIR}/config.yaml
  )

## =============================================================================
##
##  Configuration summary
##
## =============================================================================

## Display summary of configuration settings

message ( "------------------------------------------------------------"    )
message ( "[Website] Configuration summary."                                )
message ( "------------------------------------------------------------ "   )
message ( " System configuration:"                                          )
message ( " .. Processor type .............. = ${CMAKE_SYSTEM_PROCESSOR}"   )
message ( " .. CMake executable ............ = ${CMAKE_COMMAND}"            )
message ( " .. CMake version ............... = ${CMAKE_VERSION}"            )
message ( " .. System name ................. = ${CMAKE_SYSTEM}"             )
message ( " .. C++ compiler ................ = ${CMAKE_CXX_COMPILER}"       )
message ( " .. C compiler .................. = ${CMAKE_C_COMPILER}"         )
message ( " .. size(void*) ................. = ${CMAKE_SIZEOF_VOID_P}"      )
message ( " Project configuration:"                                         )
message ( " .. Version number .............. = ${PROJECT_VERSION}"          )
message ( " .. Build directory ............. = ${PROJECT_BINARY_DIR}"       )
message ( " .. Installation prefix ......... = ${CMAKE_INSTALL_PREFIX}"     )
message ( " .. Installation prefix Website . = ${INSTALL_PREFIX_WEBSITE}"   )
message ( " .. Webgen configuration file ... = ${WEBGEN_CONFIG}"            )
message ( " .. Pages source directory ...... = ${PROJECT_SOURCE_DIR_PAGES}" )
message ( " .. Blog source directory ....... = ${PROJECT_SOURCE_DIR_BLOG}"  )
message ( " .. Custom CMake modules ........ = ${PROJECT_CMAKE_MODULE_PATH}")
message ( " .. Path to upload location ..... = ${PROJECT_UPLOAD_PATH}"      )
message ( " External tools & packages:"                                     )
message ( " .. Doxygen executable .......... = ${DOXYGEN_EXECUTABLE}"       )
message ( " .. Doxygen version ............. = ${DOXYGEN_VERSION}"          )
message ( " .. Ruby executable ............. = ${RUBY_EXECUTABLE}"          )
message ( " .. Ruby version ................ = ${RUBY_VERSION}"             )
message ( " .. Path to Ruby library ........ = ${RUBY_LIBRARIES}"           )
message ( " .. Include directory ........... = ${RUBY_INCLUDES}"            )
message ( " .. Gem executable .............. = ${GEM_EXECUTABLE}"           )
message ( " .. Gem executable version ...... = ${GEM_VERSION}"              )
message ( " .. Rake executable ............. = ${RAKE_EXECUTABLE}"          )
message ( " .. Rake executable version ..... = ${RAKE_VERSION}"             )
message ( " .. Webgen executable ........... = ${WEBGEN_EXECUTABLE}"        )
message ( " .. Webgen executable version ... = ${WEBGEN_VERSION}"           )
message ( " .. YAML C++ library ............ = ${YAML_LIBRARIES}"           )
message ( "------------------------------------------------------------ "   )
