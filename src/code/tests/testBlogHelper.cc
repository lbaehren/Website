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

#include <fstream>
#include <BlogHelper.h>

/*!
  \brief filename -- Name of the output file, to which the header will be
                     written.
  \return status  -- Return status of the function; returns non-zero value
                     in case an error was encountered.
*/
int test_write_headers (std::string const &filename="testBlogHelper.page")
{
  int status = 0;

  // Open output filestream
  std::ofstream outfile (filename.c_str());

  if (!outfile.is_open()) {
    std::cerr << "[testBlogHelper] Failed to open output file "
	      << filename
	      << std::endl;
  }

  try {
  } catch (std::exception &e) {
    std::cerr << "[testBlogHelper] ERROR : " << e.what() << std::endl;
    ++status;
  }

  return status;
}

//_______________________________________________________________________________
//                                                                           main

/*!
  \file testBlogHelper.cc
  \ingroup Blog
  \brief A collection of tests for the Blog helper functions
  \author Lars Baehren
*/
int main ()
{
  int status = 0;

  std::cout << "-- Filename for entry = " << Blog::get_filename_entry() << std::endl;

  status += test_write_headers ();

  return 0;
}
