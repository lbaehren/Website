
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
    \param title     -- Title of the blog entry
    \param timestamp -- Timestamp of the blog entry
    \param tags      -- Tags attached to the entry
  */
  BlogEntry::BlogEntry (std::string const &title,
		       Blog::Timestamp const &timestamp,
		       std::vector<std::string> const &tags)
  {
    itsTags.clear();

    itsTitle     = title;
    itsTimestamp = timestamp;
    itsTags      = tags;
  }
  
} // Namespace Blog -- end
