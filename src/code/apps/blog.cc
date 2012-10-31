/***************************************************************************
 *   Copyright (C) 2012                                                    *
 *   Lars B"ahren (lbaehren@gmail.com)                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/*!
  \file blog.cc
  \brief Main blog application executable
  \author Lars Baehren
 */

/* Standard header files */
#include <iostream>
#include <math.h>

#include <BlogHelper.h>
#include <BlogEntry.h>

// ==============================================================================
//
//  Program functions
//
// ==============================================================================

// ==============================================================================
//
//  Program main function
//
// ==============================================================================

int main ()
{
  int status           = 0;
  std::string title    = "Test entry";
  std::string author   = "Lars Baehren";
  std::vector<std::string> tags (1,"Development");

  Blog::Timestamp timestamp;
  Blog::BlogEntry entry (title,
			 timestamp,
			 tags);

  /*
   *  Display parameters
   */
  std::cout << "\n[blog] Summary of parameters.\n" << std::endl;
  std::cout << "-- Filename = " << entry.filename() << std::endl;
  std::cout << "-- Filepath = " << entry.path()     << std::endl;
  std::cout << "-- Title    = " << title    << std::endl;
  std::cout << "-- Author   = " << author   << std::endl;
  std::cout << "\n" << std::endl;

  /*
   *  Write header for blog entry
   */
  Blog::write_header (std::cout,
		      title,
		      author,
		      tags);
  
  return status;
}
