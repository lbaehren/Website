
## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

## Name of the project handled by CMake
project (GEM)

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

## Enforced CMake policy 
cmake_policy (VERSION 2.8)

##  Package information
set (GEM_VERSION_SERIES "1.9")
set (GEM_VERSION        "${GEM_VERSION_SERIES}.3-p194" )
set (GEM_SOURCE_ARCHIVE "gem-${GEM_VERSION}.tar.gz" )
set (GEM_URL            "http://ftp.gem-lang.org/pub/gem/${GEM_VERSION_SERIES}/${GEM_SOURCE_ARCHIVE}" )
set (GEM_SVN            "http://svn.gem-lang.org/repos/gem/trunk" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (GEM_FORCE_BUILD    "Force build and installation of package?" NO )
option (GEM_FROM_REPOS     "Install package from repository?"         NO )
option (GEM_ENABLE_TESTING "Enable testing and experimental builds?"  YES )

## Handle options

if (GEM_ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (GEM_ENABLE_TESTING)

## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

if (GEM_FROM_REPOS)
  set (GEM_FORCE_BUILD TRUE)
endif (GEM_FROM_REPOS)

if (NOT GEM_FOUND OR GEM_FORCE_BUILD)
  
  ## Locate source file to build from
  
  find_file (GEM_SOURCE ${GEM_SOURCE_ARCHIVE}
    PATHS ${PROJECT_SOURCE_DIR}
    )
  
  if (NOT GEM_SOURCE)
    set (GEM_SOURCE ${GEM_URL})
  endif (NOT GEM_SOURCE)
  
  ## Build package from source
  
  if (GEM_FROM_REPOS)
    
    ExternalProject_Add (gem
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      SVN_REPOSITORY ${GEM_SVN}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${PROJECT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )
  
  else (GEM_FROM_REPOS)
    
    ExternalProject_Add (gem
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${GEM_SOURCE}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${PROJECT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )
    
  endif (GEM_FROM_REPOS)
  
else (NOT GEM_FOUND OR GEM_FORCE_BUILD)
  
  add_custom_target (gem
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "[Gem] Found system-wide installation; skipping rebuild!"
    )
  
endif (NOT GEM_FOUND OR GEM_FORCE_BUILD)
