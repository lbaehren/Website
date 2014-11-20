#!/bin/bash

PATH_BASEDIR=`pwd`
PATH_UPCOMING=upcoming

# ==============================================================================
#
#  Functions
#
# ==============================================================================

## Create header of a new blog entry
#
#  @param title
#  @param timestamp
#  @param timeheader
#
create_header ()
{
    varTitle=$1
    varHourMinuteSecond=`date +`
    varTimestamp=`date +%Y-%m-%dT%H:%M:%S.00Z`
    varTimeheader="`date +%a,\ %d.\ %B\ %Y\ --\ %H:%M`"

    echo "---"
    echo "title: \"${varTitle}\""
    echo "in_menu: false"
    echo "author: \"Lars Baehren\""
    echo "date: ${varTimestamp}"
    echo "created_at: ${varTimestamp}"
    echo "---"
    echo ""
    echo "## {title:} ##"
    echo ""
    echo "_${varTimeheader}_"
}

## Create a new file
#
#  @param filename
#  @param title
#  @param tmestamp
#
create_file ()
{
    varFilename=$1
    varTitle=$2
    varTimestamp=$3
    varTimeheader=$4

    varOutfile=${PATH_BASEDIR}/${PATH_UPCOMING}/${varFilename}

    echo "Creating new file ${varFilename} ..."
    echo " - Title     = ${varTitle}"
    echo " - Timestamp = ${varTimestamp}"

    # create header for new entry
    create_header ${varTitle} ${varTimestamp} ${varTimeheader} >> ${varOutfile}
}


# ==============================================================================
#
#  Main
#
# ==============================================================================

# Time format .... : "2014-08-01T19:09:34.00Z"
# File name ...... : "2014-09-02_20-43.page"
# Time header line : "_Fri, 01. August 2014 -- 19:09_"

varYear=`date +%Y`
varMonth=`date +%Y`
varYearMonth=`date +%Y-%m`
varYearMonthDay=`date +%Y-%m-%d`
varHourMinuteSecond=`date +%H:%M:%S`
varTimestamp="${varYearMonthDay}T${varHourMinuteSecond}.00Z"

varFilename="`date +%Y-%m-%d`_`date +%H-%M`.page"

# Create new file
create_file ${varFilename} "New_entry" ${varTimestamp} ${varTimeheader}
