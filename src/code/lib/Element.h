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

#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>

#include "Common.h"

namespace Blog { // Namespace Blog -- begin

  class Element {

  public:

    //! Format used for storage or serialization
    enum Format {
      //! HTML formatted text
      HTML,
      //! JSON (JavaScript Object Notation)
      JSON,
      //! Simple text with no specific formatting
      TEXT,
      //! XML formatted text
      XML,
      YAML
    };

  private:

    //! Format used for storage or serialization
    Element::Format itsFormat;

  public:

    //! Get the format used for storage or serialization
    inline Element::Format format () {
      return itsFormat;
    }

    /*!
      \brief Write the element to a string, using the specified \c format
      \param format   -- Format used for storage or serialization.
      \return element -- String represenation of the element, using the
              specified \c format.
    */
    virtual std::string write (Element::Format const &format) = 0;

    /*!
      \brief Write the element to the stream \c os, using the specified \c format
      \param format -- Format used for storage or serialization.
      \param os     -- Output stream to which the formatted element is written.
    */
    virtual void write (Element::Format const &format,
			std::ostream &os) = 0;

  };

} // Namespace Blog -- end

#endif

