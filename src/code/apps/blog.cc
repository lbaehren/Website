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
#include <fstream>
#include <iostream>
#include <math.h>

#include <BlogHelper.h>
#include <BlogEntry.h>

// ==============================================================================
//
//  Program functions
//
// ==============================================================================

int edit_entry ()
{
  return 0;
}

// ==============================================================================
//
//  Program main function
//
// ==============================================================================

int main (int argc, char *argv[])
{
  int status           = 0;
  std::string optionKey;
  std::string title    = "Test entry";
  std::string author   = "Lars Baehren";
  std::vector<std::string> tags (1,"Development");
  bool indexAll = false;

  // === Process command line input ===

  for (int n=0; n<argc; ++n) {
    optionKey = std::string(argv[n]);

    // Option: title
    if (optionKey == "--title" || optionKey == "-T") {
      if (argc>n+1) {
	title = argv[n+1];
      }
    }

    // Option: --index-all, -I
    if (optionKey == "--index-all" || optionKey == "-I") {
      indexAll = true;
    }
  }

  // === Create object to store blog entry data ===

  Blog::Timestamp timestamp;
  Blog::BlogEntry entry (title,
			 timestamp,
			 tags);

  /*
   *  Display parameters
   */
  std::cout << "\n[blog] Summary of parameters.\n"  << std::endl;
  std::cout << "-- Filepath = "  << entry.path()     << std::endl;
  std::cout << "-- Filename = "  << entry.filename() << std::endl;
  std::cout << "-- Title    = '" << title            << "'" << std::endl;
  std::cout << "-- Author   = '" << author           << "'" << std::endl;
  std::cout << "\n" << std::endl;

  /*
   *  Open output file-stream
   */
  // std::ofstream outfile (entry.filename().c_str());

  /*
   *  Write header for blog entry
   */
  Blog::write_header (std::cout,
		      title,
		      author,
		      tags);

  return status;
}
