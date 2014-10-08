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

#include "Link.h"

namespace blog { // namespace blog -- begin

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

  /*!
    \param format -- Format used for storage or serialization.
    \param os     -- Output stream to which the formatted element is written.
  */
  void Link::write (dal::data::StorageFormat const &format,
                    std::ostream &os)
  {
    switch (format) {
    case dal::data::HTML:
      os << "<a href=\"" << itsURL << "\">" << itsTitle << "</a>";
      break;
    case dal::data::JSON:
      os << "{ \"link\": {"
	 << " \"title\": \"" << itsTitle << "\","
	 << " \"url\": \"" << itsURL << "\","
	 << " \"internal\": \"" << itsInternal << "\""
	 << " } }";
      break;
    default:
      break;
    }
  }

  void Link::summary (std::ostream &os)
  {
    os << "[Link] Summary of internal parameters." << std::endl;
    os << "-- Title  ........ = " << itsTitle            << std::endl;
    os << "-- URL  .......... = " << itsURL              << std::endl;
    os << "-- Internal?  .... = " << itsInternal         << std::endl;
  }

} // namespace blog -- end
