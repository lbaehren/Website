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

#include "BlogEntry.h"

namespace blog {

    // =========================================================================
    //
    //  Construction
    //
    // =========================================================================

    BlogEntry::BlogEntry ()
    {
        itsTitle     = "";
        itsText      = "";
        itsAuthor    = "";
        itsTime = dal::Time();
        itsTags.clear();
    }

    /*!
     * \param title     -- Title of the blog entry
     * \param timestamp -- Time of the blog entry
     */
    BlogEntry::BlogEntry (std::string const &title,
                          dal::Time const &timestamp)
    {
        itsTitle     = title;
        itsText      = "";
        itsAuthor    = "";
        itsTime = timestamp;
        itsTags.clear();
    }

    BlogEntry::BlogEntry (std::string const &title,
                          std::string const &text)
    {
        itsTitle     = title;
        itsText      = text;
        itsAuthor    = "";
        itsTime = dal::Time();
        itsTags.clear();
    }

/*!
      \param title     -- Title of the blog entry.
      \param tags      -- Tags attached to the entry.
      \param timestamp -- Time of the blog entry.
    */
    BlogEntry::BlogEntry (std::string const &title,
                          std::vector<std::string> const &tags,
                          dal::Time const &timestamp)
    {
        itsTitle     = title;
        itsText      = "";
        itsAuthor    = "";
        itsTime = timestamp;
        setTags (tags,false);
    }

    // =========================================================================
    //
    //  Public methods
    //
    // =========================================================================

    std::string BlogEntry::path ()
    {
        std::stringstream out;

#ifdef BLOG_WEBSITE_SOURCE_DIR_BLOG
        out << BLOG_WEBSITE_SOURCE_DIR_BLOG;
#else
        out << ".";
#endif
        out << "/" << itsTime.formatAsString("%Y/%Y-%m");

        return out.str();
    }

    //__________________________________________________________________________
    //                                                                  filename

    /*!
      \return filename -- Filename for the blog entry.
    */
    std::string BlogEntry::filename (bool const &fullPath)
    {
        std::string name;

        if (fullPath) {
            name = path() + "/" + filename (itsTime);
        } else {
            name = filename (itsTime);
        }

        return name;
    }

    //__________________________________________________________________________
    //                                                                   summary

    void BlogEntry::summary (std::ostream &os)
    {
        os << "[BlogEntry] Summary of internal parameters." << std::endl;
        os << "-- Title     = " << itsTitle                 << std::endl;
        os << "-- Author    = " << itsAuthor                << std::endl;
        os << "-- Time      = " << itsTime.rfc2822()        << std::endl;
        os << "             = " << itsTime.iso8601()        << std::endl;
        os << "-- Tags      = " << itsTags                  << std::endl;
        os << "-- Filename  = " << filename(false)          << std::endl;
    }

    /*!
     *\param format -- Format used for storage or serialization.
     *\param os     -- Output stream to which the formatted element is written.
     */
    void BlogEntry::write (dal::data::StorageFormat const &format,
                           std::ostream &os)
    {
        switch (format) {
        case dal::data::XML:
          os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"  << std::endl;
          os << "  <entry>"                                   << std::endl;
          os << "    <title>"      << itsTitle   << "</title>"    << std::endl;
          os << "    <author>"     << itsAuthor  << "</author>"   << std::endl;
          os << "    <date>"       << itsTime.iso8601() << "</date>" << std::endl;
          os << "    <created_at>" << itsTime.iso8601() << "</created_at>" << std::endl;
          os << "    <menu></menu>"                           << std::endl;
          os << "    <body>" << itsText <<"</body>"           << std::endl;
          os << "  </entry>"                                  << std::endl;
          break;
      default:
          os << "---"                                << std::endl;
          os << "title: \""    << itsTitle << "\""     << std::endl;
          os << "in_menu: false"                     << std::endl;
          os << "author: \""   << itsAuthor << "\""    << std::endl;
          os << "date: "       << itsTime.iso8601() << std::endl;
          os << "created_at: " << itsTime.iso8601() << std::endl;
          os << "---"                                << std::endl;
          os                                         << std::endl;
          os << "## {title:} ##"                     << std::endl;
          os                                         << std::endl;
          os << "_" << itsTime.formatAsString("%a, %d. %B %Y -- %H:%M") << "_" << std::endl;
          break;
        };
    }

    // =========================================================================
    //
    //  Static methods
    //
    // =========================================================================

    //__________________________________________________________________________
    //                                                                  filename

    std::string BlogEntry::filename (dal::Time const &timestamp)
    {
        std::string name;
        dal::Time ts = timestamp;

        name += ts.ymd();
        name += "_";
        name += ts.hourAsString();
        name += "-";
        name += ts.minuteAsString();
        name += ".page";

        return name;
    }

    //__________________________________________________________________________
    //                                                            header_keyword

    std::string BlogEntry::header_keyword (const std::string& filename,
                                           const std::string& keyword)
    {
        std::string result = "";
        YAML::Node infile = YAML::LoadFile(filename);

        if (infile[keyword]) {
            result = infile[keyword].as<std::string>();
        }

        return result;
    }

}  //  namespace blog - END
