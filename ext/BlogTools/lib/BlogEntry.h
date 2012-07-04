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

#ifndef BLOGENTRY_H
#define BLOGENTRY_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>

#include "Timestamp.h"

namespace Blog { // Namespace Blog -- begin

  class BlogEntry {

    //! Title of the blog entry
    std::string itsTitle;
    //! Timestamp of the blog entry
    Blog::Timestamp itsTimestamp;
    //! Tags attached to the entry
    std::vector<std::string> itsTags;

  public:

    // === Construction =========================================================

    //! Default constructor
    BlogEntry ();

    //! Argumented constructor, taking \e title as input
    BlogEntry (std::string const &title,
	       Blog::Timestamp const &timestamp=Blog::Timestamp());

    // === Parameter access =====================================================

    //! Get the title of the blog entry
    inline std::string title () {
      return itsTitle;
    }

    //! Set the title of the blog entry
    void setTitle (std::string const &title) {
      itsTitle = title;
    }

  };

} // Namespace Blog -- end

#endif
