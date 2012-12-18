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

#include "BlogHelper.h"

namespace Blog {

  std::string get_path_entry (Timestamp const &timestamp)
  {
    std::string path = PROJECT_SOURCE_DIR_BLOG;

    path += "/";
    path += get_filename_entry (timestamp);

    return path;
  }

  /*!
    \param timestamp -- Wrapper for an instance in time.
    \return filename -- The filename for a (new) blog entry.
  */
  std::string get_filename_entry (Timestamp const &timestamp)
  {
    std::string filename;
    Timestamp ts = timestamp;

    filename += ts.ymd();
    filename += "_";
    filename += ts.hourAsString();
    filename += "-";
    filename += ts.minuteAsString();
    filename += ".page";

    return filename;
  }

  /*!
    \param os     -- Stream to which the output will be written.
    \param title  -- Title of the entry.
    \param author -- Author of the entry.
    \param tags   -- Tags for the entry.
    \param inMenu -- Is the generated page to be listed in the menu sidebar?
  */
  void write_header (std::ostream &os,
                     std::string const &title,
                     std::string const &author,
                     std::vector<std::string> const &tags,
                     bool const &inMenu,
                     bool const &forIndex)
  {
    std::string tt;
    std::string in_menu = "false";
    int nofTags = tags.size();

    /* Check if there are tags to be combined */
    if (tags.empty()) {
      tt = "";
    } else{
      tt = tags[0];

      if (nofTags>1) {
        for (int n=1; n<nofTags; ++n) {
          tt += " " + tags[n];
        }
      }
    }

    /* Is the page to be listed in the menu? */
    if (inMenu) {
      in_menu = "true";
    }

    /* Write the header to the output stream */
    os << "---"                          << std::endl;
    os << "title: \""  << title << "\""  << std::endl;
    os << "in_menu: "  << in_menu        << std::endl;
    os << "author: \"" << author << "\"" << std::endl;
    os << "tags: "     << tt             << std::endl;
    os << "---"                          << std::endl;
    os << " "                            << std::endl;

    if (forIndex) {
      os << "## Blog archive | 2012 ##"  << std::endl;
    } else {
      os << "## {title:} ##"             << std::endl;
      os << " "                          << std::endl;

    }
  }

}
