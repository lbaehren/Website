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

#ifndef BLOG_APPLICATION_BLOG_ENTRY_H
#define BLOG_APPLICATION_BLOG_ENTRY_H

#include "ApplicationBase.h"


namespace blog {

    /*!
     * @class ApplicationBlogEntry
     * @brief Class implementing functionality of the `blog_entry` application program
     * @ingroup blog
     * @author Lars Baehren
     */
    class ApplicationBlogEntry : public ApplicationBase {

    public:

        // === Public member functions =========================================

        /// Constructor
        ApplicationBlogEntry (int argc, char *argv[]);

        /// Actually run the application
        int run ();
        
    protected:

        // === Protected member functions ======================================

        /*!
         * @brief Set the description of the available command line options
         *
         * The set of available command line options is stored as a
         * `boost::program_options::options_description` container. In order to
         * get an overview of the available options use `--help` when running the
         * program.
         */
        void setOptionsDescription ();

    };

}

#endif
