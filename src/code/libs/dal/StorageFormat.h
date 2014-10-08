//------------------------------------------------------------------------------
// Copyright (c) 2014, Lars Baehren <lbaehren@gmail.com>
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

/*!
 * \file StorageFormat.h
 * \ingroup dal
 * \brief Format used for storage of data
 * \author Lars Baehren
 * \date 2014-03-20
 */

#ifndef DAL_DATA_STORAGEFORMAT_H
#define DAL_DATA_STORAGEFORMAT_H

namespace dal {

    namespace data {

        /// Format used for storage of data
        enum StorageFormat {
            /// Flexible Image Transport System (FITS)
            FITS,
            /// Hierarchical Data Format, version 5 (HDF5)
            HDF5,
            /// Hypertext Markup Language (HTML)
            HTML,
            /// JSON
            JSON,
            /// Network Common Data Form (NetCDF)
            NETCDF,
            /// SQLite database engine
            SQLITE,
            /// Plain text (no specific formatting)
            TEXT,
            /// Extensible Markup Language (XML)
            XML,
            /// YAML Ain't Markup Language (YAML)
            YAML
        };

    };  //  namespace data - END

};  //  namespace dal - END

#endif
