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

#ifndef LINK_H
#define LINK_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>

#include "Element.h"

namespace Blog { // Namespace Blog -- begin
  
  /*!
    \class Link
    \ingroup Blog
    \author Lars B&auml;hren
    \date 2012-07-05

    \brief Container encapsulating the components of a link

    JSON model representing a Link:
    \verbatim
    { "link": { "title": "<title>",
                "url": "<url>",
                "is_internal": "<internal>" } 
    }
    \endverbatim
  */
  class Link : public Element {

    //! Display title of the link
    std::string itsTitle;
    //! URL of the link
    std::string itsURL;
    //! Is the link internal? This might trigger special treatment with a parser
    bool itsInternal;

  public:

    // === Construction =========================================================

    //! Default constructor
    Link ();

    //! Argumented constructor
    Link (std::string const &url,
	  std::string const &title="",
	  bool const &isInternal=false);

    // === Parameter access =====================================================

    //! Get the display title of the link
    inline std::string title () {
      return itsTitle;
    }

    //! Set the display title of the link
    void setTitle (std::string const &title) {
      itsTitle = title;
    }

    //! Get the URL of the link
    inline std::string url () {
      return itsURL;
    }

    //! Set the UR of the link
    void setURL (std::string const& url,
		 bool const &isInternal=false)
    {
      itsURL      = url;
      itsInternal = isInternal;
    }

    // === Public methods =======================================================

    //! Write the element to a string, using the specified \c format
    std::string write (Element::Format const &format);

    void write (Element::Format const &format,
		std::ostream &os);
    
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
