
#include "ApplicationBlogEntry.h"

namespace blog {

    ApplicationBlogEntry::ApplicationBlogEntry (int argc, char *argv[])
        :ApplicationBase (argc, argv)
    {
        setOptionsDescription();
        bpo::store (bpo::parse_command_line(argc,argv,itsOptionsDescription), itsVariablesMap);
    }

    void ApplicationBlogEntry::setOptionsDescription ()
    {
        itsOptionsDescription.add_options ()
            ("help,H",                                  "Show help messages.")
            ("title,T",    bpo::value<std::string>(),   "Title of the blog entry.")
            ("author,A",   bpo::value<std::string>(),   "Author of the blog entry.")
            ("upcoming,U",  "Do not publish entry, but store as upcoming.")
            ("publish,P",   "Published previously stashed blog entry.")
            ("dry-run,D",   "Dry run for generation of entry - do not create output file.")
            ("index-all,I", "(re-)Index all blog entries.")
            ("get-date",     bpo::value<std::string>(), "Parse blog entry and extract date.")
            ("get-author",   bpo::value<std::string>(), "Parse blog entry and extract author")
            ("get-title",    bpo::value<std::string>(), "Parse blog entry and extract title.")
            ("parse-entry",  bpo::value<std::string>(), "Parse blog entry and extract its components.")
            ;
    }

    int ApplicationBlogEntry::run ()
    {
        return 0;
    }

}
