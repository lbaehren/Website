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

#include "Common.h"

/*!
    \file ScriptSupport.cc
    \ingroup Blog
    \brief A collection of functions to support the existing scripts
    \author Lars Baehren
    \date 2012-10-17
*/

namespace Blog {

  /*!
    \brief Write header of blog index file.
    \param os     -- Stream to which the output will be written.
    \param title  -- Title of the entry.
    \param author -- Author of the entry.
    \param tags   -- Tags for the entry.
   */
  void write_index_header (std::ostream &os,
                           std::string const &title="Blog",
                           std::string const &author="Lars Baehren",
                           std::string const &tags="Blog")
  {
    os << "---"                          << std::endl;
    os << "title: \"" << title << "\""   << std::endl;
    os << "in_menu: false"               << std::endl;
    os << "author: \"" << author << "\"" << std::endl;
    os << "tags: " << tags               << std::endl;
    os << "---"                          << std::endl;
    os << " "                            << std::endl;
    os << "# {title:} #"                 << std::endl;
    os << " "                            << std::endl;
    os << "**:::**"                      << std::endl;
  }

}
