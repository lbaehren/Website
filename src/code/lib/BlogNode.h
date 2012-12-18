/***************************************************************************
 *   Copyright (C) 2012                                                    *
 *   Lars B"ahren (lbaehren@gmail.com)                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "BlogConfig.h"

namespace Blog {

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
