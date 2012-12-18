
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

  std::string BlogEntry::path ()
  {
    std::stringstream out;
    
    out << PROJECT_SOURCE_DIR_BLOG;
    out << "/";
    out <<  itsTimestamp.year();
    out << "/";
    out <<  itsTimestamp.year() << "-" << itsTimestamp.month();

    return out.str();
  }

  //_____________________________________________________________________________
  //                                                                     filename

  /*!
    \return filename -- Filename for the blog entry.
  */
  std::string BlogEntry::filename (bool const &fullPath)
  {
    std::string name;

    if (fullPath) {
      name = path() + "/" + filename (itsTimestamp);
    } else {
      name = filename (itsTimestamp);
    }

    return name;
  }

  //_____________________________________________________________________________
  //                                                                      summary

  void BlogEntry::summary (std::ostream &os)
  {
    os << "[BlogEntry] Summary of internal parameters." << std::endl;
    os << "-- Title     = " << itsTitle                 << std::endl;
    os << "-- Timestamp = " << itsTimestamp.get(Timestamp::RFC2822) << std::endl;
    os << "             = " << itsTimestamp.get(Timestamp::ISO8601) << std::endl;
    os << "-- Tags      = " << itsTags                              << std::endl;
  }

   /*!
      \param format -- Format used for storage or serialization.
      \param os     -- Output stream to which the formatted element is written.
    */
   void BlogEntry::write (Element::Format const &format,
                         std::ostream &os)
  {
    switch (format) {
      case Element::XML:
       os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"  << std::endl;
       os << "  <entry>"                                   << std::endl;
       os << "    <title>" << itsTitle   << "</title>"     << std::endl;
       os << "    <author>" << itsAuthor << "</author>"    << std::endl;
       os << "    <menu></menu>"                           << std::endl;
       os << "    <body>" << itsText <<"</body>"           << std::endl;
       os << "  </entry>"                                  << std::endl;
    };
  }

  // === Static methods =========================================================
  
  std::string BlogEntry::filename (Timestamp const &timestamp)
  {
    std::string name;
    Timestamp ts = timestamp;
    
    name += ts.ymd();
    name += "_";
    name += ts.hourAsString();
    name += "-";
    name += ts.minuteAsString();
    name += ".page";
    
    return name;
  }

} // Namespace Blog -- end
