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

#include <Link.h>

using std::endl;
using Blog::Link;

/*!
  \file LinkTest.cc

  \ingroup Blog

  \brief A collection of test routines for the Blog::Link class
 
  \author Lars B&auml;hren
 
  \date 2012/07/03
*/

//_______________________________________________________________________________
//                                                              test_construction

void test_construction ()
{
  std::cout << "[1] Testing default constructor ..." << endl;
  {
    Link link;
    link.summary();
  }

  std::cout << "[2] Testing argumented constructor ..." << endl;
  {
    Link link ("http://www.google.com");
    link.summary();
  }

  std::cout << "[3] Testing argumented constructor ..." << endl;
  {
    Link link ("http://www.google.com","Google");
    link.summary();
  }

}

//_______________________________________________________________________________
//                                                                           main

int main ()
{
  test_construction ();

  return 0;
}
