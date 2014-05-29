#ifndef BLOG_ABOUTME_H
#define BLOG_ABOUTME_H

#include <string>

namespace blog {

    class AboutMe {

    public:

        // === Public data ======================================================

        /// My first name
        std::string myFirstName = "Lars";
        /// My last name
        std::string myLastName = "Baehren";
        /// My occupation
        std::string myOccupation = "Scientific Software Engineer";
        /// My website
        std::string myWebsite = "www.larsbaehren.de";

        // === Public methods ==================================================

        inline std::string name (const bool &reverse=false) {
            if (reverse) {
                return (myLastName + ", " + myFirstName);
            } else {
                return (myFirstName + " " + myLastName);
            }
        }

        inline std::string firstName () {
            return myFirstName;
        }

        inline std::string lastName () {
            return myLastName;
        }

        inline std::string occupation () {
            return myOccupation;
        }

    };  //  class AboutMe - END

};  //  namespace blog - END

#endif
