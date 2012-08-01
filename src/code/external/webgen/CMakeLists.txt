
## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

## Name of the project handled by CMake
project (WEBGEN)

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

## Enforced CMake policy 
cmake_policy (VERSION 2.8)

##  Package information
set (WEBGEN_VERSION        "0.5.14" )
set (WEBGEN_SOURCE_ARCHIVE "webgen-${WEBGEN_VERSION}.tgz" )
set (WEBGEN_URL            "http://files.rubyforge.vm.bytemark.co.uk/webgen/${WEBGEN_SOURCE_ARCHIVE}" )
set (WEBGEN_GIT            "git://rubyforge.org/webgen.git" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (WEBGEN_FORCE_BUILD    "Force build and installation of package?" NO )
option (WEBGEN_FROM_REPOS     "Install package from repository?"         YES )
option (WEBGEN_ENABLE_TESTING "Enable testing and experimental builds?"  YES )

## Handle options

if (WEBGEN_ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (WEBGEN_ENABLE_TESTING)

## ==============================================================================
##
##  System inspection
##
## ==============================================================================

find_program (WEBGEN_EXECUTABLE webgen
  HINTS ${WEBGEN_ROOT_DIR} ${CMAKE_INSTALL_PREFIX}
  PATH_SUFFIXES bin lib
  )

if (WEBGEN_EXECUTABLE)
  set (WEBGEN_FOUND TRUE)
endif (WEBGEN_EXECUTABLE)

## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

if (NOT WEBGEN_FOUND OR WEBGEN_FORCE_BUILD)
  
  ## Locate source file to build from
  
  find_file (WEBGEN_SOURCE ${WEBGEN_SOURCE_ARCHIVE}
    PATHS ${PROJECT_SOURCE_DIR}
    )
  
  if (NOT WEBGEN_SOURCE)
    set (WEBGEN_SOURCE ${WEBGEN_URL})
  endif (NOT WEBGEN_SOURCE)
  
  ## Build package from source
  
  if (WEBGEN_FROM_REPOS)
    
    ExternalProject_Add (webgen
      PREFIX ${PROJECT_BINARY_DIR}
      #--Download step--------------
      DOWNLOAD_DIR download
      SOURCE_DIR source
      GIT_REPOSITORY ${WEBGEN_GIT}
      #--Configure step-------------
      CONFIGURE_COMMAND ruby setup.rb config
      #--Build step-----------------
      BUILD_COMMAND ruby setup.rb setup
      BUILD_IN_SOURCE 1
      #--Install step---------------
      INSTALL_DIR ${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} ruby setup.rb install
      )
  
  else (WEBGEN_FROM_REPOS)
    
    ExternalProject_Add (webgen
      PREFIX ${PROJECT_BINARY_DIR}
      #--Download step--------------
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${WEBGEN_URL}
      #--Configure step-------------
      CONFIGURE_COMMAND ruby setup.rb config
      #--Build step-----------------
      BUILD_COMMAND ruby setup.rb setup
      BUILD_IN_SOURCE 1
      #--Install step---------------
      INSTALL_DIR ${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} ruby setup.rb install
      )
    
  endif (WEBGEN_FROM_REPOS)
  
else (NOT WEBGEN_FOUND OR WEBGEN_FORCE_BUILD)
  
  add_custom_target (webgen
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "[webgen] Found system-wide installation; skipping rebuild!"
    )
  
endif (NOT WEBGEN_FOUND OR WEBGEN_FORCE_BUILD)
