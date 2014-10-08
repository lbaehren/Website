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

#ifndef BLOGENTRY_H
#define BLOGENTRY_H

#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <yaml-cpp/yaml.h>

#include <dal/Time.h>
#include <dal/data/StorageFormat.h>
#include <dal/io/iostream.h>

using namespace dal::io;

namespace Blog { // Namespace Blog -- begin

    /*!
     * \class BlogEntry
     * \ingroup blog
     * \author Lars B&auml;hren
     *
     * \brief Container for elements of a blog entry
     */
    class BlogEntry {

    public:

        // === Construction ====================================================

        /// Default constructor
        BlogEntry ();

        /// Argumented constructor, taking ``title`` as input
        BlogEntry (std::string const &title,
                   dal::Time const &timestamp=dal::Time());

        /// Argumented constructor, taking ``title`` and ``text`` as input
        BlogEntry (std::string const &title,
                   std::string const &text);

        /// Argumented constructor, providing all parameters
        BlogEntry (std::string const &title,
                   std::vector<std::string> const &tags,
                   dal::Time const &timestamp=dal::Time());

        // === Parameter access ================================================

        /// Get the title of the blog entry
        inline std::string title () {
            return itsTitle;
        }

        /// Set the title of the blog entry
        inline void setTitle (const std::string& title) {
            itsTitle = title;
        }

        /// Get the author of the blog entry
        inline std::string author () {
            return itsAuthor;
        }

        /// Set the author of the blog entry
        inline void setAuthor (const std::string& author) {
            itsAuthor = author;
        }

        /// Get the timestamp of the blog entry
        inline dal::Time timestamp () {
            return itsTime;
        }

        /// Set the timestamp of the blog entry
        inline void setTime (dal::Time const &timestamp) {
            itsTime = timestamp;
        }

        /// Get the text of the blog entry
        inline std::string text () {
            return itsText;
        }

        /// Set the text of the blog entry
        inline void setText (const std::string& text) {
            itsText = text;
        }

        /// Get the tags attached to the entry
        inline std::set<std::string> tags () {
            return itsTags;
        }

        /// Set the tags attached to the entry
        inline void setTag (std::string const &tag)
        {
            itsTags.insert(tag);
        }

        /// Set the tags attached to the entry
        inline void setTags (std::vector<std::string> const &tags,
                             bool const &replace=false)
        {
            setTags (tags.begin(),tags.end(),replace);
        }

        /// Set the tags attached to the entry
        inline void setTags (std::set<std::string> const &tags,
                             bool const &append=true)
        {
            setTags (tags.begin(),tags.end(),append);
        }

        // === Public methods ==================================================

        /// Get the path to the new blog entry
        std::string path ();

        /// Get the filename for the blog entry
        std::string filename (bool const &fullPath=false);

        /// Provide a summary of the internal status
        inline void summary () {
            summary (std::cout);
        }

        /// Provide a summary of the internal status to output stream \c os
        void summary (std::ostream &os);

        /// Write the element to the stream \c os, using the specified \c format
        void write (dal::data::StorageFormat const &format,
                    std::ostream &os);

        // === Static methods ==================================================

        /// Get the filename for a blog entry
        static std::string filename (dal::Time const &timestamp);

        /*!
         * \brief  Parse the contents of a blog entry
         * \param  filename -- File with the blog entry.
         * \param  keyword  -- Keyword to extract.
         * \return value    -- Value of the header keyword, empty string
         *                     otherwise.
         */
        static std::string header_keyword (const std::string& filename,
                                           const std::string& keyword);


    private:

        // === Private data ====================================================

        /// Author for the blog entry
        std::string itsAuthor;
        /// Title of the blog entry
        std::string itsTitle;
        /// Time of the blog entry1
        dal::Time itsTime;
        /// Text of the blog entry
        std::string itsText;
        /// Tags attached to the entry
        std::set<std::string> itsTags;

        // === Private methods =================================================

        ///
        bool checkPath (const bool& createPath=false);

        /// Set the tags attached to the entry
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
