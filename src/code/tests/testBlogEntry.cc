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

int test_construction ()
{
  std::cout << "\n[BlogEntryTest::test_construction]\n" << std::endl;

  int status = 0;

  std::cout << "[1] Testing default constructor ..." << std::endl;
  try {
    BlogEntry entry;
    entry.summary();
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++ status;
  }

  std::cout << "[2] Testing simple argumented constructor ..." << std::endl;
  try {
    std::string title = "My new blog entry";
    BlogEntry entry (title);
    entry.summary();
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++ status;
  }

  return status;
}

//_______________________________________________________________________________
//                                                                test_parameters

//!  Test acces to the internal parameters
int test_parameters ()
{
  std::cout << "\n[BlogEntryTest::test_parameters]\n" << std::endl;

  int status = 0;

  std::cout << "[1] Testing setTitle() ..." << std::endl;
  try {
    BlogEntry entry;
    std::string title ("Title of the new blog entry");
    // Set the title
    entry.setTitle (title);
    // Get the title
    title = entry.title();
    // Summary
    entry.summary();
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++ status;
  }

  std::cout << "[2] Testing setTags(std::set<T>) ..." << std::endl;
  try {
    BlogEntry entry;
    // Define tags ...
    std::set<std::string> tags;
    tags.insert("Test");
    tags.insert("Blog");
    tags.insert("Computing");
    // ... and store then inside the object
    entry.setTags (tags);
    // Summary
    entry.summary();
    std::cout << "-- BlogEntry::tags() = " << entry.tags() << std::endl;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++ status;
  }

  std::cout << "[3] Testing setTags(std::vector<T>) ..." << std::endl;
  try {
    BlogEntry entry;
    // Define tags ...
    std::vector<std::string> tags;
    tags.push_back("Computing");
    tags.push_back("Test");
    tags.push_back("Blog");
    // ... and store then inside the object
    entry.setTags (tags);
    // Summary
    entry.summary();
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++ status;
  }

  return status;
}

//_______________________________________________________________________________
//                                                                           main

/*!
  \brief Program main function
*/
int main ()
{
  int status = 0;

  status += test_construction ();
  status += test_parameters ();

  return status;
}
