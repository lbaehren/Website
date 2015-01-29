
## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

## Name of the project handled by CMake
project (RUBY)

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8.2)

## Enforced CMake policy
cmake_policy (VERSION 2.8.2)

set (PROJECT_VERSION_MAJOR "1")
set (PROJECT_VERSION_MINOR "9")
set (PROJECT_VERSION_PATCH "3")
set (PROJECT_VERSION_TWEAK "p194")

##  Package information
set (RUBY_VERSION_SERIES "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
set (RUBY_VERSION        "${RUBY_VERSION_SERIES}.3-p194" )
set (RUBY_SOURCE_ARCHIVE "ruby-${RUBY_VERSION}.tar.gz" )
set (RUBY_URL            "http://ftp.ruby-lang.org/pub/ruby/${RUBY_VERSION_SERIES}/${RUBY_SOURCE_ARCHIVE}" )
set (RUBY_SVN            "http://svn.ruby-lang.org/repos/ruby/trunk" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (RUBY_FORCE_BUILD    "Force build and installation of package?" NO )
option (RUBY_FROM_REPOS     "Install package from repository?"         NO )
option (RUBY_ENABLE_TESTING "Enable testing and experimental builds?"  YES )

## Handle options

if (RUBY_ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (RUBY_ENABLE_TESTING)

## ==============================================================================
##
##  System inspection
##
## ==============================================================================

## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

if (RUBY_FROM_REPOS)
  set (RUBY_FORCE_BUILD TRUE)
endif (RUBY_FROM_REPOS)

if (NOT RUBY_FOUND OR RUBY_FORCE_BUILD)

  ## Locate source file to build from

  find_file (RUBY_SOURCE ${RUBY_SOURCE_ARCHIVE}
    PATHS ${PROJECT_SOURCE_DIR}
    )

  if (NOT RUBY_SOURCE)
    set (RUBY_SOURCE ${RUBY_URL})
  endif (NOT RUBY_SOURCE)

  ## Build package from source

  if (RUBY_FROM_REPOS)

    ExternalProject_Add (ruby
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      SVN_REPOSITORY ${RUBY_SVN}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${PROJECT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  else (RUBY_FROM_REPOS)

    ExternalProject_Add (ruby
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${RUBY_SOURCE}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${PROJECT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  endif (RUBY_FROM_REPOS)

else (NOT RUBY_FOUND OR RUBY_FORCE_BUILD)

  add_custom_target (ruby
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "[Ruby] Found system-wide installation; skipping rebuild!"
    )

endif (NOT RUBY_FOUND OR RUBY_FORCE_BUILD)
