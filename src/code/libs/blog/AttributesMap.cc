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

#include "AttributesMap.h"

namespace blog { // namespace blog -- begin

  // ===========================================================================
  //
  //  Construction
  //
  // ===========================================================================

  //____________________________________________________________________________
  /*!
    \param attributes -- Attributes attached to/describing the image.
  */
  AttributesMap::AttributesMap (std::map<std::string,std::string> const &attributes)
  {
    std::map<std::string,std::string> buffer = attributes;
    std::map<std::string,std::string>::iterator it;

    for (it=buffer.begin(); it!=buffer.end(); ++it) {
      itsAttributes[it->first] = it->second;
    }

  }

  // ===========================================================================
  //
  //  Public methods
  //
  // ===========================================================================

  //____________________________________________________________________________
  //                                                                hasAttribute

  /*!
    \param key     -- Keyword to be searched for amongst the attributes.
    \return status -- Returns \c true of the provided \c key can be found amongst
            the attributes; else \c false is returned.
   */
  bool AttributesMap::hasAttribute (std::string const &key)
  {
    std::map<std::string,std::string>::iterator it = itsAttributes.find(key);

    if (it==itsAttributes.end()) {
      return false;
    } else {
      return true;
    }
  }

  //____________________________________________________________________________
  //                                                               attributeKeys

  std::set<std::string> AttributesMap::attributeKeys ()
  {
    std::map<std::string,std::string>::iterator it;
    std::set<std::string> keys;

    for (it=itsAttributes.begin();it!=itsAttributes.end(); ++it) {
      keys.insert(it->first);
    }
    return keys;
  }

  //____________________________________________________________________________
  //                                                                setAttribute

  /*!
    \param key       -- Keyword for the attribute.
    \param value     -- Value of the attribute.
    \param overwrite -- Overwrite existing entry if it exists?
    \return status   -- Feedback on whether or not a new value for the attribute
                     has been set; if the attribute has been set already and
                     \c overwrite=false, then the provided \c value is not going
                     to be stored.
  */
  bool AttributesMap::setAttribute (std::string const &key,
				    std::string const &value,
				    bool const &overwrite)
  {
    if (hasAttribute(key) && !overwrite) {
      return false;
    } else {
      itsAttributes[key] = value;
    }
    return true;
  }

} // namespace blog -- end
