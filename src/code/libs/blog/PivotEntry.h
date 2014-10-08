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

#ifndef PIVOTENTRY_H
#define PIVOTENTRY_H

// Standard library header files
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

namespace Blog {

  /*!
    \class PivotEntry
    \ingroup blog
    \brief Brief description for class PivotEntry
    \author Lars B&auml;hren
    \date 24 Apr 2011
    \test tPivotEntry.cc

    <h3>Prerequisite</h3>

    <ul type="square">
      <li>[start filling in your text here]
    </ul>

    <h3>Synopsis</h3>

    \code
    s:4:"code";i:1400;
    s:4:"date";s:16:"2006-01-25-21-39";
    s:12:"introduction";s:0:"";
    \endcode

    <h3>Example(s)</h3>

  */
  class PivotEntry {

    //! Name of the file to which the entry is written
    std::string itsFilename;
    //! Fields used to store the contents the entry
    std::map<std::string,std::string> itsFields;

  public:

    // === Construction =========================================================

    //! Default constructor
    PivotEntry ();
    //! Argumented constructor
    PivotEntry (std::string const &filename);
    //! Argumented constructor
    PivotEntry (std::map<std::string,std::string> const &fields);
    //! Copy constructor
    PivotEntry (PivotEntry const &other);

    // === Destruction ==========================================================

    //! Destructor
    ~PivotEntry ();

    // === Operators ============================================================

    //! Overloading of the copy operator
    PivotEntry& operator= (PivotEntry const &other);

    // === Parameter access =====================================================

    //! Get the file name
    inline std::string filename () const {
      return itsFilename;
    }

    //! Get blog entry field
    bool getField (std::string &value,
		   std::string const &name);

    //! Set blog entry field
    bool setField (std::string const &name,
		   std::string const &value);

    /*!
      \brief Get the name of the class
      \return className -- The name of the class, PivotEntry.
    */
    inline std::string className () const {
      return "PivotEntry";
    }

    //! Provide a summary of the object's internal parameters and status
    inline void summary () {
      summary (std::cout);
    }

    //! Provide a summary of the object's internal parameters and status
    void summary (std::ostream &os);

    // === Public methods =======================================================

    //! Read entry from file
    bool readFile (std::string const &filename);
    //! Write entry to file
    bool writeFile (std::string const &filename);

    // === Static methods =======================================================

    //! Get the names of the fields used to store the contents of an entry
    static std::set<std::string> fieldNames ();

  private:

    void init ();

    //! Unconditional copying
    void copy (PivotEntry const &other);

    //! Unconditional deletion
    void destroy(void);

  }; // Class PivotEntry -- end

}; // namespace Blog -- end

#endif /* PIVOTENTRY_H */

