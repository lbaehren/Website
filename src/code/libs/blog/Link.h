//------------------------------------------------------------------------------
// Copyright (c) 2012-2014, Lars Baehren <lbaehren@gmail.com>
// All Rights Reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//  * Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//------------------------------------------------------------------------------

#ifndef LINK_H
#define LINK_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>

#include <dal/data/StorageFormat.h>

namespace Blog { // Namespace Blog -- begin

  /*!
    \class Link
    \ingroup blog
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
  class Link {

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

    //! Provide a summary of the internal status
    inline void summary () {
      summary (std::cout);
    }

    //! Provide a summary of the internal status to output stream \c os
    void summary (std::ostream &os);

    //! Write the element to the stream \c os, using the specified \c format
    void write (dal::data::StorageFormat const &format,
                std::ostream &os=std::cout);

    // === Private methods ======================================================

  private:

  };

} // Namespace Blog -- end

#endif
