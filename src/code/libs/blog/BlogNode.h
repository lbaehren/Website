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

#include <blog/blog_config.h>

namespace blog {

  //! Type of the node in the blog structure
  enum NodeType {
    //! Node is a directory
    Directory,
    //! Note is an entry file
    Entry,
    //! Note is an index file
    Index
  };

  /*!
    \class BlogNode
    \brief Base class for a node in the blog
    \ingroup blog
    \author Lars Baehren
  */
  class BlogNode {

  protected:

    //! Type of the node
    NodeType itsType;

  public:

    // === Construction =========================================================

    //! (Argumented) Constructor
    BlogNode (NodeType const type=Entry);

    // === Parameter access =====================================================

    //! Get the type of the node
    inline NodeType nodeType () {
      return itsType;
    }

    // === Static methods =======================================================

    static std::string nodeTypeName (NodeType const type);

  };

}
