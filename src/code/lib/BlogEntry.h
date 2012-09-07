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
#include <set>
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
    //! Text of the blog entry
    std::string itsText;
    //! Tags attached to the entry
    std::set<std::string> itsTags;

  public:

    // === Construction =========================================================

    //! Default constructor
    BlogEntry ();

    //! Argumented constructor, taking \c title as input
    BlogEntry (std::string const &title,
	       Blog::Timestamp const &timestamp=Blog::Timestamp());

    //! Argumented constructor, taking \c title and text as input
    BlogEntry (std::string const &title,
	       std::string const &text);

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

    //! Get the text of the blog entry
    inline std::string text () {
      return itsText;
    }

    //! Set the text of the blog entry
    void setText (std::string const &text) {
      itsText = text;
    }

    //! Get the tags attached to the entry
    inline std::vector<std::string> tags () {
      itsTags;
    }
    
    //! Set the tags attached to the entry
    inline void setTag (std::string const &tag,
			bool const &replace=false)
    {
      std::vector<std::string> tags (1,tag);
      setTags (tags.begin(),tags.end(),replace);
    }
    
    //! Set the tags attached to the entry
    inline void setTags (std::vector<std::string> const &tags,
			 bool const &replace=false)
    {
      setTags (tags.begin(),tags.end(),replace);
    }
    
    //! Set the tags attached to the entry
    inline void setTags (std::set<std::string> const &tags,
			 bool const &append=true)
    {
      setTags (tags.begin(),tags.end(),append);
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

    //! Set the tags attached to the entry
    template <typename T>
    void setTags (T start,
		  T end,
		  bool const &append)
  {
    T it;

    /* Clean current set of tags, if new ones are not being appended */
    if (!append) {
      itsTags.clear();
    }
    /* Store the input values */
    for (it=start; it!=end; ++it) {
      itsTags.insert(*it);
    }
  }

    
  };

} // Namespace Blog -- end

#endif
