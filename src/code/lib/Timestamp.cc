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

#include "Timestamp.h"

namespace Blog {
  
  // ============================================================================
  //
  //  Construction
  //
  // ============================================================================

  //_____________________________________________________________________________
  //                                                                    Timestamp
  
  Timestamp::Timestamp ()
  {
    setTime ();
  }

  //_____________________________________________________________________________
  //                                                                    Timestamp
  
  /*!
    \param year   -- Numerical value for the year
    \param month  -- Numerical value of the month, [01-12]
    \param day    -- Numerical value of the day, [01-31]
    \param hour   -- Numerical value of the hour, [00-23]
    \param minute -- Numerical value of the minute, [00-59]
    \param second -- Numerical value of the second, [00-59].[...]
   */
  Timestamp::Timestamp (int const &year,
			int const &month,
			int const &day,
			int const &hour,
			int const &minute,
			double const &second)
  {
    setTime ();
    //
    itsYear    = year;
    itsMonth   = month;
    itsDay     = day;
    itsHour    = hour;
    itsMinute  = minute;
    setSecond(second);
  }
  
  //_____________________________________________________________________________
  //                                                                    Timestamp
  
  Timestamp::Timestamp (Timestamp const &other)
  {
    copy (other);
  }
  
  // ============================================================================
  //
  //  Destruction
  //
  // ============================================================================
  
  Timestamp::~Timestamp ()
  {
    destroy();
  }
  
  void Timestamp::destroy ()
  {;}
  
  // ============================================================================
  //
  //  Operators
  //
  // ============================================================================
  
  //_____________________________________________________________________________
  //                                                                    operator=
  
  /*!
    \param other -- Another Timestamp object from which to create this new one.
  */
  Timestamp& Timestamp::operator= (Timestamp const &other)
  {
    if (this != &other) {
      destroy ();
      copy (other);
    }
    return *this;
  }

  //_____________________________________________________________________________
  //                                                                         copy
  
  /*!
    \param other -- Another Timestamp object from which to make a copy.
  */
  void Timestamp::copy (Timestamp const &other)
  {
    itsRawtime = other.itsRawtime;
    setTime();
  }
  
  // ============================================================================
  //
  //  Parameters
  //
  // ============================================================================

  //_____________________________________________________________________________
  //                                                                      setYear

  void Timestamp::setYear (int const &year)
  {
    itsYear = year;
    setRawtime();
  }

  //_____________________________________________________________________________
  //                                                                     setMonth

  void Timestamp::setMonth (Month const &month)
  {
    int m = 0;

    switch (month) {
    case Timestamp::Jan:
      m = 1;
      break;
    case Timestamp::Feb:
      m = 2;
      break;
    case Timestamp::Mar:
      m = 3;
      break;
    case Timestamp::Apr:
      m = 4;
      break;
    case Timestamp::May:
      m = 5;
      break;
    case Timestamp::Jun:
      m = 6;
      break;
    case Timestamp::Jul:
      m = 7;
      break;
    case Timestamp::Aug:
      m = 8;
      break;
    case Timestamp::Sep:
      m = 9;
      break;
    case Timestamp::Oct:
      m = 10;
      break;
    case Timestamp::Nov:
      m = 11;
      break;
    case Timestamp::Dec:
      m = 12;
      break;
    };
    
    setMonth (m);
  }
  
  //_____________________________________________________________________________
  //                                                                     setMonth

  /*!
    \param month -- The numerical value for the month, [1-12]
  */
  void Timestamp::setMonth (int const &month)
  {
    /* Check if the input value is within the acceptable range. */
    if (month >= 1 && month <= 12) {
      itsMonth = month;
      setRawtime();
    } else {
      eorError ("setMonth", month);
    }
  }

  //_____________________________________________________________________________
  //                                                                       setDay
  
  void Timestamp::setDay (int const &day)
  {
    /* Check if the input value is within the acceptable range. */
    if (day > 0 && day < 32) {
      itsDay = day;
      setRawtime();
    } else {
      eorError ("setDay", day);
    }
  }

  //_____________________________________________________________________________
  //                                                                      setHour
  
  void Timestamp::setHour (int const &hour)
  {
    /* Check if the input value is within the acceptable range. */
    if (hour >= 0 && hour <= 23) {
      itsHour = hour;
      setRawtime();
    } else {
      eorError ("setHour", hour);
    }
  }
  
  //_____________________________________________________________________________
  //                                                                    setMinute
  
  void Timestamp::setMinute (int const &minute)
  {
    /* Check if the input value is within the acceptable range. */
    if (minute >= 0 && minute <= 59) {
      itsMinute = minute;
      setRawtime();
    } else {
      eorError ("setMinute", minute);
    }
  }
  
  //_____________________________________________________________________________
  //                                                                    setSecond
  
  void Timestamp::setSecond (double const &second)
  {
    int fullSecond = floor(second);
    /* Check if the input value is within the acceptable range. */
    if (fullSecond >= 0 && fullSecond <= 59) {
      itsSecond = second;
      setRawtime();
    } else {
      eorError ("setSecond", second);
    }
  }
  
  //_____________________________________________________________________________
  //                                                                      summary
  
  void Timestamp::summary (std::ostream &os)
  {
    os << "[Timestamp] Summary of internal parameters."       << std::endl;
    os << "-- Raw time        = " << itsRawtime               << std::endl;
    os << "-- Offset from GMT = " << offsetFromGMT()         
       << " / "                   << offsetFromGMT(false,":") << std::endl;
    os << "-- Timezone ID     = " << timezone()               << std::endl;
    os << "-- ctime           = " << get(Timestamp::RFC2822)  << std::endl; 
    os << "-- iso8601         = " << get(Timestamp::ISO8601)  << std::endl;
    os << "-- ymd             = " << ymd()                    << std::endl;
    os << "-- hms             = " << hms()                    << std::endl;
  }

  // ============================================================================
  //
  //  Methods
  //
  // ============================================================================

  //_____________________________________________________________________________
  //                                                                     asString

  std::string Timestamp::asString (int const &val)
  {
    std::stringstream out;
    
    if (val < 10) {
      out << "0" << val;
    } else {
      out << val;
    }

    return out.str();
  }

  //_____________________________________________________________________________
  //                                                                      setTime

  void Timestamp::setTime ()
  {
    /* Initialize timestamp to current time */
    time (&itsRawtime);
    /* Store the time information */
    setTime (itsRawtime);
  }
  
  //_____________________________________________________________________________
  //                                                                      setTime
  
  /*!
    \param rawtime - The raw time in UNIX seconds
  */
  void Timestamp::setTime (time_t const &rawtime)
  {
    /* Store the raw time information */
    itsRawtime = rawtime;
    /* Convert time information to time structure */
    struct tm * timeinfo;
    timeinfo = localtime(&rawtime);
    /* Store the time information with the internal variables */
    itsYear    = timeinfo->tm_year+1900;
    itsMonth   = timeinfo->tm_mon+1;
    itsDay     = timeinfo->tm_mday;
    itsHour    = timeinfo->tm_hour;
    itsMinute  = timeinfo->tm_min;
    itsSecond  = timeinfo->tm_sec;
  }

  //_____________________________________________________________________________
  //                                                                     timezone

  std::string Timestamp::timezone ()
  {
    struct tm * timeinfo;
    timeinfo = localtime(&itsRawtime);

    return std::string (timeinfo->tm_zone);
  }

  //_____________________________________________________________________________
  //                                                                offsetFromGMT

  /*!
    \param seconds -- Return the offset in seconds.
    \param sep     -- Separator symbol to be used when return the off as an
           hour/minutes combination, e.g. \c hh:mm
  */
  std::string Timestamp::offsetFromGMT (bool const &seconds,
					std::string const &sep)
  {
    std::string offset;
    struct tm * timeinfo;

    timeinfo = localtime(&itsRawtime);

    if (seconds) {
      offset = asString(timeinfo->tm_gmtoff);
    } else {
      int hours = timeinfo->tm_gmtoff/3600;
      offset    = asString(hours) + sep + "00";
    }
    
    return offset;
  }

  //_____________________________________________________________________________
  //                                                                   setRawtime

  void Timestamp::setRawtime ()
  {
    /* Convert time information to time structure */
    struct tm * timeinfo;
    timeinfo = localtime(&itsRawtime);
    /* Update the value inside the time structure */
    timeinfo->tm_year = itsYear-1900;
    timeinfo->tm_mon  = itsMonth-1;
    timeinfo->tm_mday = itsDay;
    timeinfo->tm_hour = hour();
    timeinfo->tm_min  = minute();
    timeinfo->tm_sec  = second();
    /* Update the value of the raw time */
    itsRawtime = mktime (timeinfo);
  }

  //_____________________________________________________________________________
  //                                                                    dayOfWeek

  /*!
    \param longName -- Return the name of the day in its long format? If set 
           <tt>true</tt> then e.g. in instead of <i>Mon</i> the full name of the
	   day will be return -- in this case <i>Monday</i>.
  */
  std::string Timestamp::dayOfWeek (bool const &longName)
  {
    std::string wday;
    const char* tmp = get(Timestamp::RFC2822).c_str();

    wday += tmp[0];
    wday += tmp[1];
    wday += tmp[2];

    if (longName) {
      if (wday == "Mon") {
	wday = "Monday";
      }
      else if (wday == "Tue") {
	wday = "Tuesday";
      }
      else if (wday == "Wed") {
	wday = "Wednesday";
      }
      else if (wday == "Thu") {
	wday = "Thursday";
      }
      else if (wday == "Friday") {
	wday = "Friday";
      }
      else if (wday == "Sat") {
	wday = "Saturday";
      }
      else {
	wday = "Sunday";
      }
    }

    return wday;
  }

  //_____________________________________________________________________________
  //                                                                          hms

  /*!
    \param sep -- Separator inserted between the individual elements of the
           string. By default <tt>sep=":"</tt>, which will yield
	   <tt>hh:mm:ss</tt>.
  */
  std::string Timestamp::hms (std::string const &sep)
  {
    std::stringstream out;
    
    if (sep == "") {
      out << asString(itsHour)
	  << asString(itsMinute)
	  << asString(itsSecond);
    }
    else {
      out << asString(itsHour) << sep
	  << asString(itsMinute) << sep
	  << asString(itsSecond);
    }

    return out.str();
  }
  
  //_____________________________________________________________________________
  //                                                                          ymd
  
  /*!
    \param sep -- Separator inserted between the individual elements of the
           string. By default <tt>sep="-"</tt>, which will yield
	   <tt>yyyy-mm-dd</tt>.
  */
  std::string Timestamp::ymd (std::string const &sep)
  {
    std::stringstream out;
    
    if (sep == "") {
      out << asString(itsYear)
	  << asString(itsMonth)
	  << asString(itsDay);
    } else {
      out << asString(itsYear) << sep
	  << asString(itsMonth) << sep
	  << asString(itsDay);
    }
    
    return out.str();
  }

  //_____________________________________________________________________________
  //                                                                          get
  
  /*!
    The \c ctime() function adjusts the time value for the current time zone,
    in the same manner as \c localtime().  It returns a pointer to a 26-character
    string of the form:
    \verbatim
    Thu Nov 24 18:22:48 1986\n\0
    \endverbatim
   */
  std::string Timestamp::get (Timestamp::Format const &format)
  {
    std::stringstream out;

    switch (format) {
    case Timestamp::ISO8601:
      out << ymd() << "T" << hms() << ".00Z";
      break;
    case Timestamp::RFC2822:
      std::string tmp (ctime(&itsRawtime));
      tmp.erase (24,1);
      out << tmp;
      break;
    }
    
    return out.str();
  }
  
  // ============================================================================
  //
  //  Static methods
  //
  // ============================================================================
  
  
}
