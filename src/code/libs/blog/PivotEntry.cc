//------------------------------------------------------------------------------
// Copyright (c) 2011-2014, Lars Baehren <lbaehren@gmail.com>
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

#include "PivotEntry.h"

namespace blog { // namespace blog -- begin

  // ============================================================================
  //
  //  Construction
  //
  // ============================================================================

  PivotEntry::PivotEntry ()
  {
    init ();
  }


  PivotEntry::PivotEntry (std::string const &filename)
  {
    readFile (filename);
  }

  /*!
    \param other -- Another HDF5Property object from which to create this new
           one.
  */
  PivotEntry::PivotEntry (PivotEntry const &other)
  {
    copy (other);
  }

  // ============================================================================
  //
  //  Destruction
  //
  // ============================================================================

  PivotEntry::~PivotEntry ()
  {
    destroy();
  }

  void PivotEntry::destroy ()
  {;}

  // ============================================================================
  //
  //  Operators
  //
  // ============================================================================

  //_____________________________________________________________________________
  //                                                                    operator=

  /*!
    \param other -- Another PivotEntry object from which to make a copy.
  */
  PivotEntry& PivotEntry::operator= (PivotEntry const &other)
  {
    if (this != &other) {
      destroy ();
      copy (other);
    }
    return *this;
  }

  //_____________________________________________________________________________
  //                                                                         copy

  void PivotEntry::copy (PivotEntry const &other)
  {;}

  // ============================================================================
  //
  //  Parameters
  //
  // ============================================================================

  //_____________________________________________________________________________
  //                                                                     getField

  /*!
    \retval value  -- Value stored inside of the field.
    \param name    -- Name of the field.
    \return status -- Status of the operation; return \e false in case no field
            of the provided \e name exists.
  */
  bool PivotEntry::getField (std::string &value,
			     std::string const &name)
  {
    bool status = true;
    std::map<std::string,std::string>::iterator it = itsFields.find(name);

    if (it==itsFields.end()) {
      status = false;
      value  = "";
    } else {
      value = it->second;
    }

    return status;
  }

  //_____________________________________________________________________________
  //                                                                     setField

  /*!
    \param name  -- Name of the field.
    \param value -- Value stored inside of the field.
  */
  bool PivotEntry::setField (std::string const &name,
			     std::string const &value)
  {
    bool status = true;
    std::set<std::string> names        = fieldNames();
    std::set<std::string>::iterator it = names.find(name);

    if (it==names.end()) {
      status = false;
    } else {
      itsFields[name] = value;
    }

    return status;
  }

  //_____________________________________________________________________________
  //                                                                      summary

  /*!
    \param os -- Output stream to which the summary is written.
  */
  void PivotEntry::summary (std::ostream &os)
  {
    std::map<std::string,std::string>::iterator it;

    os << "[PivotEntry] Summary of internal parameters." << std::endl;

    os << "-- Filename       = " << itsFilename     << std::endl;

    for (it=itsFields.begin(); it!=itsFields.end(); ++it) {
      os << "-- ";
      os.width(14);
      os << it->first << " = " << it->second << std::endl;
    }
  }

  // ============================================================================
  //
  //  Public methods
  //
  // ============================================================================

  bool PivotEntry::readFile (std::string const &filename)
  {
    bool status = true;
    std::string buffer;
    std::ifstream infile;

    infile.open(filename.c_str(), std::ios::in);

    // Start parsing the contents of the input file
    if (infile.is_open()) {
        if (infile.good()) {
            while (! infile.eof() && infile.good() && status) {
                getline (infile,buffer);
            }
        }
    } else {
        std::cerr << "[PivotEntry::readFile] Failed to open file "
                  << filename
                  << std::endl;
        status = false;
    }

    //! Close input file stream
    infile.close();

    return status;
  }

  bool PivotEntry::writeFile (std::string const &filename)
  {
    bool status = true;

    return status;
  }

  // ============================================================================
  //
  //  Private methods
  //
  // ============================================================================

  std::set<std::string> PivotEntry::fieldNames ()
  {
    std::set<std::string> fields;

    fields.insert("code");
    fields.insert("date");
    fields.insert("introduction");
    fields.insert("body");
    fields.insert("category");
    fields.insert("publish_date");
    fields.insert("edit_date");
    fields.insert("title");
    fields.insert("subtitle");
    fields.insert("user");
    fields.insert("convert_lb");
    fields.insert("status");
    fields.insert("allow_comments");
    fields.insert("keywords");
    fields.insert("vialink");
    fields.insert("viatitle");

    return fields;
  }

  // ============================================================================
  //
  //  Private methods
  //
  // ============================================================================

  void PivotEntry::init ()
  {
    itsFilename = "";

    itsFields.clear();

    std::set<std::string> fields = fieldNames();
    std::set<std::string>::iterator it;

    for (it=fields.begin(); it!=fields.end(); ++it) {
      itsFields[(*it)] = "";
    }
  }

} // namespace blog -- end
