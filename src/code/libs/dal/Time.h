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

#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <sstream>
#include <vector>

namespace dal {

    /*!
     * \class Time
     * \brief Wrapper for the time information in its various formats
     * \test TestTime.cc
     * \author Lars B&auml;hren
     * \date 2006-07-16
     *
     * ### Prerequisite
     *
     * - [ISO 8601](http://en.wikipedia.org/wiki/ISO_8601) Data elements and
     *   interchange formats – Information interchange – Representation of dates and times
     * - [A summary of the international standard date and time notation](http://www.cl.cam.ac.uk/~mgk25/iso-time.html)
     * - C++ Reference : C library structures and functions
     *   - [time_t](http://www.cplusplus.com/reference/clibrary/ctime/time_t) (time.h)
     *   - [tm](http://www.cplusplus.com/reference/clibrary/ctime/tm) (time.h)
     *     \param tm_sec    [int]  Seconds after the minute [0-60]
     *     \param tm_min    [int]  Minutes after the hour [0-59]
     *     \param tm_hour   [int]  Hours since midnight [0-23]
     *     \param tm_mday   [int]  Day of the month [1-31]
     *     \param tm_mon    [int]  Months since January [0-11]
     *     \param tm_year   [int]  Years since 1900
     *     \param tm_wday   [int]  Days since Sunday [0-6]
     *     \param tm_yday   [int]  Days since January 1 [0-365]
     *     \param tm_isdst  [int]  The Daylight Saving Time flag (``tm_isdst``)
     *                             is greater than zero if Daylight Saving Time
     *                             is in effect, zero if Daylight Saving Time is
     *                             not in effect, and less than zero if the
     *                             information is not available.
     *     \param tm_gmtoff [long] Offset from CUT in seconds
     *     \param *tm_zone  [char] Timezone abbreviation
     *   - [strftime](http://www.cplusplus.com/reference/ctime/strftime) (time.h) Format time as string
     *   - The functions ``ctime()``, ``gmtime()``, and ``localtime()``
     *     all take as an argument a time value representing the time in seconds since
     *     the Epoch (00:00:00 UTC, January 1, 1970; see time(3)).
     *   - The functions ``mktime()`` and ``timegm()`` convert the broken-out
     *     time (in the structure pointed to by *timeptr) into a time value with the
     *     same encoding as that of the values returned by the time(3) function
     *     (that is, seconds from the Epoch, UTC).  The ``mktime()`` function
     *     interprets the input structure according to the current timezone
     *     setting (see tzset(3)).  The ``timegm()`` function interprets the input
     *     structure as representing Universal Coordinated Time (UTC).
     *
     * ### Notes
     *
     * - While having a method to set the week-number might come in handy at times,
     *   the exact operation of such an assignment is not well defined. Hence in
     *   order to avoid confusion no method ``setWeek()`` is being implemented.
     *
     * ### References
     *
     *  - http://en.cppreference.com/w/c/chrono/tm
     *  - http://www.staff.science.uu.nl/~gent0113/calendar/isocalendar.htm
     *  - http://www.cl.cam.ac.uk/~mgk25/iso-time.html
     */
    class Time {

    public:

        /// Time interval
        enum Intervals {
            /// nof. seconds per minute
            seconds_per_minute = 60,
            /// nof. seconds per hour
            seconds_per_hour   = 3600,
            /// nof. seconds per day
            seconds_per_day    = 86400,
            /// nof. seconds per week
            seconds_per_week   = 604800,
            /// nof. minutes per hour
            minutes_per_hour   = 60,
            /// nof. minutes per day
            minutes_per_day    = 1440,
            /// nof. minutes per week
            minutes_per_week   = 10080,
            /// nof. days per week
            days_per_week      = 7,
            /// nof. months per year
            months_per_year    = 12
        };

        // === Construction ====================================================

        /// Default constructor
        Time () {
            setTime ();
        }

        /// Argumented constructor
        Time (const time_t& rawtime);

        /// Argumented constructor
        Time (int const &year,
                   int const &month,
                   int const &day,
                   int const &hour=0,
                   int const &minute=0,
                   double const &second=0.0);

        /// Copy contructor
        Time (Time const &other) {
            copy (other);
        }

        // === Destruction =====================================================

        /// Destructor
        ~Time ();

        // === Operator overloading ============================================

        /// Assignment operator
        Time& operator= (const Time& other);

        /// Assignment operator
        Time& operator= (const time_t& rawtime);
/*
        /// Binary arithmetic operator for addition
        Time operator+ (const Time& lhs, const time_t& rawtime);

        /// Binary arithmetic operator for substraction
        Time operator- (const Time& lhs, const time_t& rawtime);
*/
        /// Overloading of addition operator.
        Time& operator+= (const time_t& rawtime);

        /// Overloading of substraction operator.
        Time& operator-= (const time_t& rawtime);

        // === Parameter access ================================================

        /// Get time in seconds since the Epoch (00:00:00 UTC, January 1, 1970.
        inline time_t rawtime () {
            return itsRawtime;
        }

        /// Get the numerical value of the year
        inline int year () {
            return itsYear;
        }

        /// Get the numerical value of the year as string
        inline std::string yearAsString () {
            return formatAsString("%Y");
        }

        /// Set the numerical value of the year
        void setYear (int const &year);

        /// Get the numerical value of the month
        inline int month () {
            return itsMonth;
        }

        /// Get the numerical value of the month as string
        inline std::string monthAsString () {
            return formatAsString("%m");
        }

        /// Set the numerical value of the month
        void setMonth (int const &month);

        /// Week of the year
        int week (const bool& isoWeek=true);

        /// Get the week of the year as string
        std::string weekAsString (const bool& isoWeek=true);

        /// Get the numerical value of the day
        inline int day () {
            return itsDay;
        }

        /// Get the numerical value of the day as string
        inline std::string dayAsString () {
            return formatAsString("%d");
        }

        /// Set the numerical value of the day
        void setDay (int const &day);

        /// Get the number of days since Jan 1st
        int dayOfYear ();

        /// Get the numerical value of the hour of day
        inline int hour () const {
            return itsHour;
        }

        /// Get the numerical value of the hour of day as string
        inline std::string hourAsString () {
            return formatAsString("%H");
        }

        /// Set the numerical value of the hour of day
        void setHour (int const &hour);

        /// Get the numerical value of the minute within the hour
        inline int minute () const {
            return itsMinute;
        }

        /// Get the numerical value of the minute within the hour as string
        inline std::string minuteAsString () {
            return formatAsString("%M");
        }

        /// Set the numerical value of the minute within the hour
        void setMinute (int const &minute);

        /// Get the numerical value of the second within the minute
        int second ();

        /// Set the numerical value of the second within the minute
        void setSecond (double const &second);

        /// Get the fraction of a second
        inline double fractionOfSecond () const {
            int fullSecond = floor(itsSecond);
            return itsSecond-fullSecond;
        }

        /// Provide a summary of the internal status
        void summary (std::ostream &os=std::cout);

        // === General public methods ==========================================

        /// Set to current time
        void setTime ();

        /// Set the time
        void setTime (time_t const &rawtime);

        /// Get the name of the month
        std::string nameOfMonth (bool const &fullName=false);

        /// Get the name of the day of the week
        std::string nameOfDay (bool const &fullName=false);

        /// Format time as string
        std::string formatAsString (const std::string& format);

        /*!
         *\brief Get string combining year, month and day
         *
         * \param sep -- Filling character to be inserted between year/month and
         month/day. By default the filling character is set to
         ``-``, such that the returned string will be
         ``yyyy-mm-dd``.
         *
         * \return ymd -- Formatted string including year, month and day.
         */
        std::string ymd (std::string const &sep="-");

        /*!
          \brief Get the time of day
          \param sep -- Separator inserted between components of the time string;
          by default the string is returned as ``hh:mm:ss``
          \return timeOfWeek -- The time of the day, consisting of hour, minutes
          and seconds.
        */
        std::string hms (std::string const &sep=":");

        /// Retrieve ISO 8601 conform version of the timestamp string
        std::string iso8601 (const bool& withTime=true,
                             const bool& withOffset=false);

        /*!
         * \brief Retrieve RFC 2822 conform version of the timestamp string
         * \return timestamp - String with time and date, formated according to
         *                     RFC 2822, e.g. ``Mon, 19 Oct 2009 16:17:40 +0000``
         */
        inline std::string rfc2822 () const {
            std::string out (ctime(&itsRawtime));
            return out;
        }

        /// Get time objects for the days in the week within which this date is located
        inline std::vector<dal::Time> daysOfWeek () {
            return daysOfWeek (itsRawtime);
        }

        // === Public static methods ===========================================

        /// Get time objects for the days in the week within which this date is located
        static std::vector<dal::Time> daysOfCurrentWeek ();

        /// Get time objects for the days in the week within which this date is located
        static std::vector<dal::Time> daysOfWeek (const time_t& rawtime);

    private:

        // === Private data ====================================================

        /// Type capable of representing times and support arithmetical operations.
        time_t itsRawtime;
        // Numerical value for the year
        int itsYear;
        /// Numerical value of the month, [01-12]
        int itsMonth;
        /// Numerical value of the day, [01-31]
        int itsDay;
        /// Numerical value of the hour, [00-23]
        int itsHour;
        /// Numerical value of the minute, [00-59]
        int itsMinute;
        /// Numerical value of the second, [00-59].[...]
        double itsSecond;

        // === Private methods =================================================

        /// Convert numerical vale to string
        std::string asString (int const &val);

        /// Update the value of the raw time (in UNIX seconds)
        void setRawtime ();

        /// Unconditional copying
        void copy (const Time& other);

        /// Unconditional deletion
        void destroy(void);

    };  //  class Time - END

};  //  namespace dal - END

#endif
