# +-----------------------------------------------------------------------------+
# |   Copyright (C) 2011                                                        |
# |   Lars B"ahren (lbaehren@gmail.com)                                         |
# |                                                                             |
# |   This program is free software; you can redistribute it and/or modify      |
# |   it under the terms of the GNU General Public License as published by      |
# |   the Free Software Foundation; either version 2 of the License, or         |
# |   (at your option) any later version.                                       |
# |                                                                             |
# |   This program is distributed in the hope that it will be useful,           |
# |   but WITHOUT ANY WARRANTY; without even the implied warranty of            |
# |   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             |
# |   GNU General Public License for more details.                              |
# |                                                                             |
# |   You should have received a copy of the GNU General Public License         |
# |   along with this program; if not, write to the                             |
# |   Free Software Foundation, Inc.,                                           |
# |   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                 |
# +-----------------------------------------------------------------------------+

# - Check for the presence of RUBY
#
# The following variables are set when RUBY is found:
#  RUBY_FOUND      = Set to true, if all components of RUBY
#                         have been found.
#  RUBY_INCLUDES   = Include path for the header files of RUBY
#  RUBY_LIBRARIES  = Link these to use RUBY
#  RUBY_LFLAGS     = Linker flags (optional)

if (NOT RUBY_FOUND)
    
  if (NOT RUBY_ROOT_DIR)
    set (RUBY_ROOT_DIR ${CMAKE_INSTALL_PREFIX})
  endif (NOT RUBY_ROOT_DIR)
  
  ##_____________________________________________________________________________
  ## Check for the header files
  
  find_path (RUBY_INCLUDES ruby.h
    HINTS ${RUBY_ROOT_DIR} /opt/local
    PATH_SUFFIXES include lib lib/ruby lib/ruby/1.8/i686-darwin10
    )
  
  ##_____________________________________________________________________________
  ## Check for the library
  
  find_library (RUBY_LIBRARIES ruby
    HINTS ${RUBY_ROOT_DIR} /opt/local
    PATH_SUFFIXES lib
    )
  
  ##_____________________________________________________________________________
  ## Check for the executable
  
  find_program (RUBY_EXECUTABLE ruby
    HINTS ${RUBY_ROOT_DIR} /opt/local
    PATH_SUFFIXES bin
    )
  
  ##_____________________________________________________________________________
  ## Ruby version number
  
  if (RUBY_EXECUTABLE)
    execute_process(
      COMMAND ${RUBY_EXECUTABLE} --version
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      RESULT_VARIABLE RUBY_RESULT_VARIABLE
      OUTPUT_VARIABLE RUBY_VERSION
      ERROR_VARIABLE RUBY_ERROR_VARIABLE
      OUTPUT_STRIP_TRAILING_WHITESPACE
      )
  endif (RUBY_EXECUTABLE)
  
  if (RUBY_VERSION)
    string (REGEX REPLACE "ruby " "" RUBY_VERSION ${RUBY_VERSION})
  endif (RUBY_VERSION)
  
  ##_____________________________________________________________________________
  ## Actions taken when all components have been found
  
  if (RUBY_INCLUDES AND RUBY_LIBRARIES)
    set (RUBY_FOUND TRUE)
  else (RUBY_INCLUDES AND RUBY_LIBRARIES)
    set (RUBY_FOUND FALSE)
    if (NOT RUBY_FIND_QUIETLY)
      if (NOT RUBY_INCLUDES)
	message (STATUS "Unable to find RUBY header files!")
      endif (NOT RUBY_INCLUDES)
      if (NOT RUBY_LIBRARIES)
	message (STATUS "Unable to find RUBY library files!")
      endif (NOT RUBY_LIBRARIES)
    endif (NOT RUBY_FIND_QUIETLY)
  endif (RUBY_INCLUDES AND RUBY_LIBRARIES)
  
  if (RUBY_FOUND)
    if (NOT RUBY_FIND_QUIETLY)
      message (STATUS "Found components for RUBY")
      message (STATUS "RUBY_ROOT_DIR  = ${RUBY_ROOT_DIR}")
      message (STATUS "RUBY_INCLUDES  = ${RUBY_INCLUDES}")
      message (STATUS "RUBY_LIBRARIES = ${RUBY_LIBRARIES}")
    endif (NOT RUBY_FIND_QUIETLY)
  else (RUBY_FOUND)
    if (RUBY_FIND_REQUIRED)
      message (FATAL_ERROR "Could not find RUBY!")
    endif (RUBY_FIND_REQUIRED)
  endif (RUBY_FOUND)
  
  ##_____________________________________________________________________________
  ## Mark advanced variables
  
  mark_as_advanced (
    RUBY_INCLUDES
    RUBY_LIBRARIES
    )
  
endif (NOT RUBY_FOUND)
