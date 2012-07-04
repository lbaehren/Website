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

#include "Common.h"
#include "Timestamp.h"

namespace Blog { // Namespace Blog -- begin
  
  /*!
    \class BlogEntry
    \ingroup Blog
    \author Lars B&auml;hren

    \brief Container for elements of a blog entry
  */
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

    //! Argumented constructor, taking \c title as input
    BlogEntry (std::string const &title,
	       Blog::Timestamp const &timestamp=Blog::Timestamp());

    //! Argumented constructor, providing all parameters
    BlogEntry (std::string const &title,
	       Blog::Timestamp const &timestamp,
	       std::vector<std::string> const &tags);

    // === Parameter access =====================================================

    //! Get the title of the blog entry
    inline std::string title () {
      return itsTitle;
    }

    //! Set the title of the blog entry
    void setTitle (std::string const &title) {
      itsTitle = title;
    }

    //! Get the timestamp of the blog entry
    inline Blog::Timestamp timestamp () {
      return itsTimestamp;
    }

    //! Set the timestamp of the blog entry
    void setTimestamp (Blog::Timestamp const &timestamp) {
      itsTimestamp = timestamp;
    }

    // === Public methods =======================================================

    //! Provide a summary of the internal status
    inline void summary () {
      summary (std::cout);
    }
    
    //! Provide a summary of the internal status to output stream \c os
    void summary (std::ostream &os);    

    // === Private methods ======================================================

  private:
    
  };

} // Namespace Blog -- end

#endif
