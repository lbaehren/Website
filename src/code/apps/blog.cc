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
  bool indexAll        = false;
  bool dryRun          = false;
  std::string title    = "Test entry";
  std::string author   = "Lars Baehren";
  std::vector<std::string> tags (1,"Development");

  //__________________________________________________________________
  // Process command line options

  for (int n=0; n<argc; ++n) {
    optionKey = std::string(argv[n]);

    // Option: title
    if (optionKey == "--title" || optionKey == "-T") {
      if (argc>n+1) {
	title = argv[n+1];
      }
    }

    // Option: --dry-run, -D
    if (optionKey == "--dry-run" || optionKey == "-D") {
      dryRun = true;
    }

    // Option: --index-all, -I
    if (optionKey == "--index-all" || optionKey == "-I") {
      indexAll = true;
    }
  }

  //__________________________________________________________________
  // Create object to store new blog entry

  Blog::Timestamp timestamp;
  Blog::BlogEntry entry (title,
			 timestamp,
			 tags);

  //__________________________________________________________________
  // Summary of command line options and blog entry properties

  if (dryRun) {
    std::cout << "\n[blog] Summary of parameters.\n"   << std::endl;
    std::cout << "-- Filepath = "  << entry.path()     << std::endl;
    std::cout << "-- Filename = "  << entry.filename() << std::endl;
    std::cout << "-- Title    = '" << entry.title()    << "'" << std::endl;
    std::cout << "-- Author   = '" << entry.author()   << "'" << std::endl;
    std::cout << "-- Tags     = "  << entry.tags()     << std::endl;
    std::cout << "\n" << std::endl;
  }

  if (dryRun) {
    /* In case of a dry run, do not create output entry file. */
    Blog::write_header (std::cout,
			title,
			author,
			tags);
  } else {
    std::ofstream outfile (entry.filename().c_str());
  }

  return status;
}
