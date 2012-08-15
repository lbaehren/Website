
#include "BlogEntry.h"

namespace Blog { // Namespace Blog -- begin

  // === Construction ===========================================================

  BlogEntry::BlogEntry ()
  {
    itsTitle     = "";
    itsTimestamp = Blog::Timestamp();
    itsTags.clear();
  }

  /*!
    \param title     -- Title of the blog entry
    \param timestamp -- Timestamp of the blog entry
  */
  BlogEntry::BlogEntry (std::string const &title,
			Blog::Timestamp const &timestamp)
  {
    itsTitle     = title;
    itsTimestamp = timestamp;
    itsTags.clear();
  }
  
  /*!
    \param title     -- Title of the blog entry.
    \param timestamp -- Timestamp of the blog entry.
    \param tags      -- Tags attached to the entry.
  */
  BlogEntry::BlogEntry (std::string const &title,
		       Blog::Timestamp const &timestamp,
		       std::vector<std::string> const &tags)
  {
    itsTitle     = title;
    itsTimestamp = timestamp;
    setTags (tags,false);
  }

  // === Public methods =========================================================
  
  void BlogEntry::summary (std::ostream &os)
  {
    os << "[BlogEntry] Summary of internal parameters." << std::endl;
    os << "-- Title     = " << itsTitle                 << std::endl;
    os << "-- Timestamp = " << itsTimestamp.get(Timestamp::RFC2822) << std::endl;
    os << "             = " << itsTimestamp.get(Timestamp::ISO8601) << std::endl;
    os << "-- Tags      = " << itsTags                              << std::endl;
  }

  
} // Namespace Blog -- end
