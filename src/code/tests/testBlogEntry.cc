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

/* Standard header files */
#include <iostream>
#include <math.h>

#include <BlogEntry.h>

using std::endl;
using Blog::BlogEntry;
using Blog::Timestamp;

/*!
  \file BlogEntryTest.cc

  \ingroup Blog

  \brief A collection of test routines for the Blog::BlogEntry class
 
  \author Lars B&auml;hren
 
  \date 2012/07/03
*/

//_______________________________________________________________________________
//                                                              test_construction

void test_construction ()
{
  std::cout << "\n[BlogEntryTest::test_construction]\n" << std::endl;

  std::cout << "[1] Testing default constructor ..." << endl;
  {
    BlogEntry entry;
    entry.summary();
  }

  std::cout << "[2] Testing simple argumented constructor ..." << endl;
  {
    std::string title = "My new blog entry";
    BlogEntry entry (title);
    entry.summary();
  }
}

//_______________________________________________________________________________
//                                                                test_parameters

//!  Test acces to the internal parameters
void test_parameters ()
{
  std::cout << "\n[BlogEntryTest::test_parameters]\n" << std::endl;

  std::set<std::string> tags;
  tags.insert("Test");
  tags.insert("Blog");
  tags.insert("Computing");

  BlogEntry entry;
  entry.summary();

  std::cout << "[1] Accessing title ..." << std::endl;
  {
    std::string title ("Title of the new blog entry");
    // Set the title
    entry.setTitle (title);
    // Get the title
    title = entry.title();
    // Summary
    entry.summary();
  }

  std::cout << "[2] Accessing tags ..." << std::endl;
  {
    std::string tag ("Test");
    // Set the tag
    entry.setTag (tag);
    entry.setTag ("Blog");
    // ... and show the result
    entry.summary();
    // Replace the tags ...
    entry.setTags(tags,false);
    // ... and show the result
    entry.summary();
  }
}

//_______________________________________________________________________________
//                                                                           main

int main ()
{
  test_construction ();
  test_parameters ();

  return 0;
}
