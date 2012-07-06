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

#include "Link.h"

namespace Blog { // Namespace Blog -- begin

  // ============================================================================
  //
  //  Construction
  //
  // ============================================================================

  Link::Link ()
  {
    itsTitle    = "";
    itsURL      = "";
    itsInternal = false;
  }
  
  Link::Link (std::string const &url,
	      std::string const &title,
	      bool const &isInternal)
  {
    itsURL      = url;
    itsInternal = isInternal;

    if (title.empty()) {
      itsTitle = url;
    } else {
      itsTitle = title;
    }
  }
  
  // ============================================================================
  //
  //  Parameter access
  //
  // ============================================================================


  // ============================================================================
  //
  //  Public methods
  //
  // ============================================================================
  
  std::string Link::write (Element::Format const &format)
  {
    std::stringstream link;

    switch (format) {
    case Element::HTML:
      link << "<a href=\"" << itsURL << "\">" << itsTitle << "</a>";
      break;
    case Element::JSON:
      link << "{ \"link\": {"
	   << " \"title\": \"" << itsTitle << "\","
	   << " \"url\": \"" << itsURL << "\","
	   << " \"internal\": \"" << itsInternal << "\""
	   << " } }";
      break;
    default:
      break;
    }

    return link.str();
  }

  void Link::write (Element::Format const &format,
		    std::ostream &os)
  {
    os << write (format);
  }

  void Link::summary (std::ostream &os)
  {
    os << "[Link] Summary of internal parameters." << std::endl;
    os << "-- Title  ........ = " << itsTitle            << std::endl;
    os << "-- URL  .......... = " << itsURL              << std::endl;
    os << "-- Internal?  .... = " << itsInternal         << std::endl;
    os << "-- HTML formatting = " << write(Element::HTML) << std::endl;
    os << "-- JSON formatting = " << write(Element::JSON) << std::endl;
  }

} // Namespace Blog -- end
