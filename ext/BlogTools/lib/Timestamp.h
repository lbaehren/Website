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

#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <sstream>

namespace Blog { // Namespace Blog -- begin
  
  /*!
    \class Timestamp
    
    \ingroup Blog
    
    \brief Wrapper for the time information in its various formats
    
    \author Lars B&auml;hren
    
    \date 2006/07/16
    
    \test TimestampTest.cc
    
    <h3>Prerequisite</h3>
    
    <ul type="square">
      <li>C++ : Reference : C Library : 
      <a href="http://www.cplusplus.com/reference/clibrary/ctime/time_t">time_t</a>
      <li>C++ : Reference : C Library : 
      <a href="http://www.cplusplus.com/reference/clibrary/ctime/tm">tm</a>
    </ul>
    
    The underlying time information -- as defined in <tt>time.h</tt>
    \code
    struct tm {
      int     tm_sec;        //  seconds after the minute [0-60]
      int     tm_min;        //  minutes after the hour [0-59]
      int     tm_hour;       //  hours since midnight [0-23]
      int     tm_mday;       //  day of the month [1-31]
      int     tm_mon;        //  months since January [0-11]
      int     tm_year;       //  years since 1900
      int     tm_wday;       //  days since Sunday [0-6]
      int     tm_yday;       //  days since January 1 [0-365]
      int     tm_isdst;      //  Daylight Savings Time flag
      long    tm_gmtoff;     //  offset from CUT in seconds
      char    *tm_zone;      //  timezone abbreviation
    };
    \endcode
    
    The Daylight Saving Time flag (<tt>tm_isdst</tt>) is greater than zero
    if Daylight Saving Time is in effect, zero if Daylight Saving Time is not
    in effect, and less than zero if the information is not available.
    
    The functions <tt>ctime()</tt>, <tt>gmtime()</tt>, and <tt>localtime()</tt>
    all take as an argument a time value representing the time in seconds since
    the Epoch (00:00:00 UTC, January 1, 1970; see time(3)).
    
    The functions <tt>mktime()</tt> and <tt>timegm()</tt> convert the broken-out
    time (in the structure pointed to by *timeptr) into a time value with the
    same encoding as that of the values returned by the time(3) function
    (that is, seconds from the Epoch, UTC).  The <tt>mktime()</tt> function
    interprets the input structure according to the current timezone
    setting (see tzset(3)).  The <tt>timegm()</tt> function interprets the input
    structure as representing Universal Coordinated Time (UTC).
    
    | Format       | Output                          |
    |--------------|---------------------------------|
    | Unix seconds | 1255969060                      |
    | ISO 8601     | 2009-10-19T16:17:40+00:00       |
    | RFC 2822     | Mon, 19 Oct 2009 16:17:40 +0000 |
    | Location     | Greenwich Mean Time             |
    | Day of the week | Monday |

    <h3>Synopsis</h3>
    
    <h3>Example(s)</h3>

    <ul>
      <li>Using timestamps in C/C++
      \code
      #include <time.h>
      #include <stdio.h>
      #include <stdlib.h>
      
      #define SIZE 256
      
      int main (void)
      {
        char buffer[SIZE];
        char *tzone;
        time_t timestamp;
        char* format;
        
        // Get and print timestamp
        timestamp = time(NULL);
        printf("%i\n", (int) timestamp);
        
        // Format string
        format = "%a %e %b %Y %r %Z %n";
        
        // Print time in my default timezone (NZDT)
        strftime(buffer, SIZE, format, localtime(&timestamp));
        fputs(buffer, stdout);
        
        // Print UTC time
        tzone="TZ=UTC";
        putenv(tzone);
        strftime(buffer, SIZE, format, localtime(&timestamp));
        fputs(buffer, stdout);
        
        // Print time is the Eastern USA
        tzone="TZ=EST";
        putenv(tzone);
        strftime(buffer, SIZE, format, localtime(&timestamp));
        fputs(buffer, stdout);
        
        return 0;
      }
      \endcode
      The output of the above program will be something like this:
      \verbatim
      1236296532
      Fri  6 Mar 2009 12:42:12 PM NZDT
      Thu  5 Mar 2009 11:42:12 PM UTC
      Thu  5 Mar 2009 06:42:12 PM EST
      \endverbatim

      <li>By the default the internal time is set to the time at which the object
      was created; thus 
      \code 
      Timestamp ts;
      //
      std::cout << " -- ymd         = " << ts.ymd()         << std::endl;
      std::cout << " -- hms         = " << ts.hms()         << std::endl;
      std::cout << " -- iso8601     = " << ts.iso8601()     << std::endl;
      std::cout << " -- Unix time   = " << ts.timer()       << std::endl;
      \endcode
      will result in something like (keep in mind you'll be running this at
      another instance in time):
      \verbatim
      -- ymd         = 2006-07-18
      -- hms         = 19:05:09
      -- iso8601     = 2006-07-18T19:05:09.00Z
      -- Unix time   = 1153242309
      \endverbatim
      
    </ul>
    
  */
  
  class Timestamp {

  public:

    //! List of months
    enum Month {
      Jan,
      Feb,
      Mar,
      Apr,
      May,
      Jun,
      Jul,
      Aug,
      Sep,
      Oct,
      Nov,
      Dec
    };

  private:
    
    //! Type capable of representing times and support arithmetical operations.
    time_t rawtime_p;

    //! Numerical value for the year
    int itsYear;
    //! Numerical value of the month, [01-12]
    int itsMonth;
    //! Numerical value of the day, [01-31]
    int itsDay;
    //! Numerical value of the hour, [00-23]
    int itsHour;
    //! Numerical value of the minute, [00-59]
    int itsMinute;
    //! Numerical value of the second, [00-59].[...]
    double valSecond_p;

  public:
    
    // === Construction =========================================================
    
    //! Default constructor
    Timestamp ();

    //! Argumented constructor
    Timestamp (int const &year,
	       int const &month,
	       int const &day,
	       int const &hour=0,
	       int const &minute=0,
	       double const &second=0.0);
    
    //! Copy constructor
    Timestamp (Timestamp const &other);
    
    // === Destruction ==========================================================
    
    //! Destructor
    ~Timestamp ();
    
    // === Operators ============================================================
    
    //! Overloading of the copy operator
    Timestamp& operator= (Timestamp const &other); 
    
    // === Parameter access =====================================================
    
    //! Get the numerical value of the year
    inline int year () {
      return itsYear;
    }
    
    //! Set the numerical value of the year
    void setYear (int const &year);
    
    //! Get the numerical value of the month
    inline int month () {
      return itsMonth;
    }
    
    //! Set the numerical value of the month
    void setMonth (int const &month);

    //! Set the numerical value of the month
    void setMonth (Month const &month);
    
    //! Get the numerical value of the day
    inline int day () {
      return itsDay;
    }
    
    //! Set the numerical value of the day
    void setDay (int const &day);

    //! Get the numerical value of the hour of day
    inline int hour () const {
      return itsHour;
    }

    //! Set the numerical value of the hour of day
    void setHour (int const &hour);

    //! Get the numerical value of the minute within the hour
    inline int minute () const {
      return itsMinute;
    }

    //! Set the numerical value of the minute within the hour
    void setMinute (int const &minute);

    //! Get the numerical value of the second within the minute
    int second ();
    
    //! Set the numerical value of the second within the minute
    void setSecond (double const &second);

    //! Get the fraction of a second
    inline double fractionOfSecond () const {
      int fullSecond = floor(valSecond_p);
      return valSecond_p-fullSecond;
    }
    
    /*!
      \brief Provide a summary of the internal status
    */
    inline void summary () {
      summary (std::cout);
    }
    
    /*!
      \brief Provide a summary of the internal status
    */
    void summary (std::ostream &os);    
    
    // === Public methods =======================================================
    
    //! Set to current time
    void setTime ();

    //! Set the time
    void setTime (time_t const &rawtime);
    
    //! Get the name of the day of the week
    std::string dayOfWeek (bool const &longName=false);
    
    /*!
      \brief Get string combining year, month and day
      
      \param sep -- Filling character to be inserted between year/month and
      month/day. By default the filling character is set to
      <tt>-</tt>, such that the returned string will be
      <tt>yyyy-mm-dd</tt>.
      
      \return ymd -- Formatted string including year, month and day.
    */
    std::string ymd (std::string const &sep="-");
    
    /*!
      \brief Get the time of day
      
      \param sep -- Separator inserted between components of the time string;
      by default the string is returned as <tt>hh:mm:ss</tt>
      
      \return timeOfWeek -- The time of the day, consisting of hour, minutes
      and seconds.
    */
    std::string hms (std::string const &sep=":");
    
    //! Retrieve ISO 8601 conform version of the timestamp string
    std::string iso8601 ();

    //! Retrieve RCF 2822 conform version of the timestamp string
    inline std::string rfc2822 () const {
      std::string out (ctime(&rawtime_p));
      return out;
    }

    // === Private methods ======================================================
    
  private:
    
    //! Convert numerical vale to string
    std::string asString (int const &val);
    
    //! Update the value of the raw time (in UNIX seconds)
    void setRawtime ();
    
    //! Unconditional copying
    void copy (Timestamp const &other);
    
    //! Unconditional deletion 
    void destroy(void);
    
  };
  
}

#endif /* TIMESTAMP_H */
