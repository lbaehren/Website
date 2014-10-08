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

#ifndef ATTRIBUTESMAP_H
#define ATTRIBUTESMAP_H

#include <iostream>
#include <map>
#include <set>
#include <vector>

namespace Blog { // Namespace Blog -- begin

  /*!
    \class AttributesMap
    \ingroup blog
    \author Lars B&auml;hren
    \date 2012-10-04

    \brief Container encapsulating map of attributes <key,value>
  */
  class AttributesMap {

  protected:

    //! Map with the \c <key,value> pairs of attributes
    std::map<std::string,std::string> itsAttributes;

  public:

    // === Construction =========================================================

    //! Default constructor
    AttributesMap ();

    //! Default constructor
    AttributesMap (std::string const &key,
		   std::string const &val);

    //! Argumented constructor
    AttributesMap (std::map<std::string,std::string> const &attributes);

    //! Copy constructor
    AttributesMap (AttributesMap const &other);

    // === Parameter access =====================================================

    //! Set the value of an attribute attached to the image
    bool setAttribute (std::string const &key,
                       std::string const &value,
                       bool const &overwrite=true);


    // === Public methods =======================================================

    //! Get the attributes attached to/describing the image
    inline std::map<std::string,std::string> attributes () const {
      return itsAttributes;
    }

    //! Get the attribute keywords attached to the image
    std::set<std::string> attributeKeys ();

    //! Is the attribute defined for the image?
    bool hasAttribute (std::string const &key);

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
