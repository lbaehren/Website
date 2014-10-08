//------------------------------------------------------------------------------
// Copyright (c) 2006-2014, Lars Baehren <lbaehren@gmail.com>
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

#include <dal/Time.h>

namespace dal {

    // =========================================================================
    //
    //  Construction
    //
    // =========================================================================

    /*!
     * \param rawtime -- Time in seconds since the Epoch (00:00:00 UTC,
     *                   January 1, 1970.
     */
    Time::Time (const time_t& rawtime)
    {
        setTime (rawtime);
    }

    //__________________________________________________________________________
    //                                                                 Time

    /*!
     * \param year   -- Numerical value for the year.
     * \param month  -- Numerical value of the month, [01-12].
     * \param day    -- Numerical value of the day, [01-31].
     * \param hour   -- Numerical value of the hour, [00-23].
     * \param minute -- Numerical value of the minute, [00-59].
     * \param second -- Numerical value of the second, [00-59].[...].
     */
    Time::Time (int const &year,
                          int const &month,
                          int const &day,
                          int const &hour,
                          int const &minute,
                          double const &second)
    {
        itsYear   = year;
        itsMonth  = month;
        itsDay    = day;
        itsHour   = hour;
        itsMinute = minute;
        setSecond(second);
        setRawtime();
    }

    // =========================================================================
    //
    //  Destruction
    //
    // =========================================================================

    Time::~Time ()
    {
        destroy();
    }

    void Time::destroy ()
    {;}

    // =========================================================================
    //
    //  Operators
    //
    // =========================================================================

    //__________________________________________________________________________
    //                                                                 operator=

    Time& Time::operator= (const Time& other)
    {
        if (this != &other) {
            destroy ();
            copy (other);
        }
        return *this;
    }

    //__________________________________________________________________________
    //                                                                 operator=

    Time& Time::operator= (const time_t& rawtime)
    {
        setTime (rawtime);
        return *this;
    }

    //__________________________________________________________________________
    //                                                                 operator+
/*
    Time Time::operator+ (const Time& lhs,
                          const time_t& rawtime)
    {
        Time t (lhs);
        t += rawtime;
        return t;
    }
*/
    //__________________________________________________________________________
    //                                                                operator+=

    /*!
     * \param rawtime - Time-shift in seconds.
     */
    Time& Time::operator+= (const time_t& rawtime)
    {
        time_t newRawtime = itsRawtime + rawtime;
        setTime (newRawtime);
        return *this;
    }

    //__________________________________________________________________________
    //                                                                operator-=

    /*!
     * \param rawtime - Time-shift in seconds.
     */
    Time& Time::operator-= (const time_t& rawtime)
    {
        time_t newRawtime = itsRawtime - rawtime;
        setTime (newRawtime);
        return *this;
    }

    //__________________________________________________________________________
    //                                                                      copy

    void Time::copy (const Time& other)
    {
        itsRawtime = other.itsRawtime;
        itsYear    = other.itsYear;
        itsMonth   = other.itsMonth;
        itsDay     = other.itsDay;
        itsHour    = other.itsHour;
        itsMinute  = other.itsMinute;
        itsSecond  = other.itsSecond;
    }

    // =========================================================================
    //
    //  Parameter access
    //
    // =========================================================================

    //__________________________________________________________________________
    //                                                                   setYear

    void Time::setYear (int const &year)
    {
        itsYear = year;
        setRawtime();
    }

    //__________________________________________________________________________
    //                                                                  setMonth

    /*!
     * \param month -- The numerical value for the month, [1-12]
     */
    void Time::setMonth (int const &month)
    {
        /* Check if the input value is within the acceptable range. */
        if (month >= 1 && month <= 12) {
            itsMonth = month;
            setRawtime();
        } else {
            std::cerr << "[Time::setMonth] Input value rejected - out of range!"
                      << std::endl;
        }
    }

    //__________________________________________________________________________
    //                                                                      week

    /*!
     * \param isoWeek -- Return value as ISO week? _true_ by default.
     */
    int Time::week (const bool& isoWeek)
    {
        return std::atoi(weekAsString(isoWeek).c_str());
    }

    //__________________________________________________________________________
    //                                                                      week

    /*!
     * \param isoWeek -- Return value as ISO week? _true_ by default.
     */
    std::string Time::weekAsString (const bool& isoWeek)
    {
        if (isoWeek) {
            return formatAsString ("%V");
        } else {
            return formatAsString ("%W");
        }
    }

    //__________________________________________________________________________
    //                                                                    setDay

    void Time::setDay (int const &day)
    {
        /* Check if the input value is within the acceptable range. */
        if (day > 0 && day < 32) {
            itsDay = day;
            setRawtime();
        } else {
            std::cerr << "[Time::setDay] Input value rejected - out of range!"
                      << std::endl;
        }
    }

    //__________________________________________________________________________
    //                                                                 dayOfYear

    int Time::dayOfYear ()
    {
        struct tm * timeinfo;
        timeinfo = localtime(&itsRawtime);
        return timeinfo->tm_yday;
    }

    //__________________________________________________________________________
    //                                                                   setHour

    void Time::setHour (int const &hour)
    {
        /* Check if the input value is within the acceptable range. */
        if (hour >= 0 && hour <= 23) {
            itsHour = hour;
            setRawtime();
        } else {
            std::cerr << "[Time::setHour] Input value rejected - out of range!"
                      << std::endl;
        }
    }

    //__________________________________________________________________________
    //                                                                 setMinute

    void Time::setMinute (int const &minute)
    {
        /* Check if the input value is within the acceptable range. */
        if (minute >= 0 && minute <= 59) {
            itsMinute = minute;
            setRawtime();
        } else {
            std::cerr << "[Time::setMinute] Input value rejected - out of range!"
                      << std::endl;
        }
    }

  //____________________________________________________________________________
  //                                                                      second

  int Time::second ()
  {
    int fullSecond = floor(itsSecond);

    return fullSecond;
  }

  //____________________________________________________________________________
  //                                                                   setSecond

  void Time::setSecond (double const &second)
  {
    int fullSecond = floor(second);
    /* Check if the input value is within the acceptable range. */
    if (fullSecond >= 0 && fullSecond <= 59) {
      itsSecond = second;
      setRawtime();
    } else {
      std::cerr << "[Time::setSecond] Input value rejected - out of range!"
		<< std::endl;
    }
  }

  //____________________________________________________________________________
  //                                                                     summary

  void Time::summary (std::ostream &os)
  {
    os << "[Time] Summary of internal parameters." << std::endl;
    os << "-- Raw time    = " << itsRawtime    << std::endl;
    os << "-- ctime       = " << rfc2822();
    os << "-- iso8601     = " << iso8601()     << std::endl;
    os << "-- ymd         = " << ymd()         << std::endl;
    os << "-- hms         = " << hms()         << std::endl;
  }

  // ===========================================================================
  //
  //  Public methods
  //
  // ===========================================================================

  //____________________________________________________________________________
  //                                                                    asString

  std::string Time::asString (int const &val)
  {
    std::stringstream out;

    if (val < 10) {
      out << "0" << val;
    } else {
      out << val;
    }

    return out.str();
  }

  //____________________________________________________________________________
  //                                                                     setTime

  void Time::setTime ()
  {
    /* Initialize Time to current time */
    time (&itsRawtime);
    /* Store the time information */
    setTime (itsRawtime);
  }

  //____________________________________________________________________________
  //                                                                     setTime

  /*!
    \param rawtime - The raw time in UNIX seconds
  */
  void Time::setTime (time_t const &rawtime)
  {
    /* Store the raw time information */
    itsRawtime = rawtime;
    /* Convert time information to time structure */
    struct tm * timeinfo;
    timeinfo = localtime(&rawtime);
    /* Store the time information with the internal variables */
    itsYear          = timeinfo->tm_year+1900;
    itsMonth         = timeinfo->tm_mon+1;
    itsDay           = timeinfo->tm_mday;
    itsHour          = timeinfo->tm_hour;
    itsMinute        = timeinfo->tm_min;
    itsSecond        = timeinfo->tm_sec;
  }

  //____________________________________________________________________________
  //                                                                  setRawtime

  void Time::setRawtime ()
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

    //__________________________________________________________________________
    //                                                            formatAsString

    std::string Time::formatAsString (const std::string& format)
    {
        char buffer [80];
        struct tm * timeinfo;
        timeinfo = localtime(&itsRawtime);

        strftime (buffer, 80, format.c_str(), timeinfo);

        return std::string(buffer);
    }

    //__________________________________________________________________________
    //                                                               nameOfMonth

    std::string Time::nameOfMonth (bool const &fullName)
    {
        if (fullName) {
            return formatAsString("%B");
        } else {
            return formatAsString("%b");
        }
    }

    //__________________________________________________________________________
    //                                                                 nameOfDay

    /*!
     * \param fullName -- Return the name of the day in its long format? If set
     * <tt>true</tt> then e.g. in instead of <i>Mon</i> the full name of the
     * day will be return -- in this case <i>Monday</i>.
    */
    std::string Time::nameOfDay (bool const &fullName)
    {
        if (fullName) {
            return formatAsString("%A");
        } else {
            return formatAsString("%a");
        }
    }

    //__________________________________________________________________________
    //                                                                       hms

    /*!
     * \param sep -- Separator inserted between the individual elements of the
     *        string. By default <tt>sep=":"</tt>, which will yield
     *	   <tt>hh:mm:ss</tt>.
     */
    std::string Time::hms (std::string const &sep)
    {
        if (sep == "") {
            return formatAsString ("%H%M%S");
        }
        else {
            std::stringstream out;
            out << asString(itsHour) << sep
                << asString(itsMinute) << sep
                << asString(itsSecond);
            return out.str();
        }

    }

    //__________________________________________________________________________
    //                                                                       ymd

    /*!
     * \param sep -- Separator inserted between the individual elements of the
     *        string. By default <tt>sep="-"</tt>, which will yield
     *	   <tt>yyyy-mm-dd</tt>.
     */
    std::string Time::ymd (std::string const &sep)
    {
        if (sep == "") {
            return formatAsString ("%Y%m%d");
        } else {
            std::stringstream out;
            out << asString(itsYear) << sep
                << asString(itsMonth) << sep
                << asString(itsDay);
            return out.str();
        }
    }

    //__________________________________________________________________________
    //                                                                   iso8601

    /*!
     * - Date and time values are ordered from the most to the least
     *   significant: year, month (or week), day, hour, minute, second, and
     *   fraction of second. The lexicographical order of the representation
     *   thus corresponds to chronological order, except for date representations
     *   involving negative years. This allows dates to be naturally sorted by,
     *   for example, file systems.
     * - Each date and time value has a fixed number of digits that must be
     *   padded with leading zeros.
     *
     * \param withTime -- Combined output of date and time of day?
     * \param withOffset -- Include time offset from UTC?
     *   - ``true``  = 2014-02-24T23:45:56+00:00
     *   - ``false`` = 2014-02-24T23:45:56Z
     * \return iso -- ISO 8601 conform version of the Time string
     */
    std::string Time::iso8601 (const bool& withTime,
                               const bool& withOffset)
    {
        // Combined output of date and time of day? //
        if (withTime) {
            std::stringstream out;
            out << ymd() << "T" << hms() << ".00";
            // Include time offset from UTC? //
            if (withOffset) {
                out << formatAsString("%z");
            } else {
                out << "Z";
            }
            return out.str();
        } else {
            return formatAsString ("%F");
        }
    }

    // =========================================================================
    //
    //  Static methods
    //
    // =========================================================================

    /*!
     * \todo Allow to provide first day of week as configuration parameter
     */
    std::vector<dal::Time> Time::daysOfCurrentWeek ()
    {
        time_t rawtime;
        time (&rawtime);
        return daysOfWeek (rawtime);
    }

    /*!
     * \todo Allow to provide first day of week as configuration parameter
     * \param rawtime -- Time in seconds since the Epoch (00:00:00 UTC,
     *                   January 1, 1970.
     */
    std::vector<dal::Time> Time::daysOfWeek (const time_t& rawtime)
    {
        // nof. days backwards to start scanning
        int range = 6;
        time_t begin_of_week;
        std::vector<dal::Time> result;

        // Scan for Monday 'range' days backward w.r.t  today
        for (int n=-range; n<=0; n++) {
            Time t (rawtime+n*seconds_per_day);
            // check of the current day is a Monday, marking the begin of the week
            if (t.nameOfDay() == "Mon") {
                begin_of_week = t.rawtime();
            }
        }

        // Set up time objects for the days of the current week
        for (int n=0; n<days_per_week; ++n) {
            result.push_back(dal::Time(begin_of_week + n*seconds_per_day));
        }

        return result;
    }

}  //  namespace dal - END
