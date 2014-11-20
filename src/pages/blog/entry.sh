#!/bin/bash

PATH_BASEDIR=`pwd`
PATH_UPCOMING=upcoming

# ==============================================================================
#
#  Functions
#
# ==============================================================================

#_______________________________________________________________________________
#                                                                  create_header

## Create header of a new blog entry
#
#  @param title -- Title of the newly created blog entry.
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

#_______________________________________________________________________________
#                                                                    create_file

## Create a new file
#
#  @param filename -- Name of the newly created file for the blog entry.
#  @param title    -- Title of the newly created blog entry.
#
create_file ()
{
    varFilename=$1
    varTitle=$2

    varOutfile=${PATH_BASEDIR}/${PATH_UPCOMING}/${varFilename}

    # create header for new entry
    create_header ${varTitle} >> ${varOutfile}

    # update the index file
    create_index_file > ${PATH_BASEDIR}/${PATH_UPCOMING}/index.page
}

#_______________________________________________________________________________
#                                                              create_index_file

create_index_file ()
{
    # change into the directory for which to create the index
    cd ${PATH_BASEDIR}/${PATH_UPCOMING}

    echo "---"
    echo "title: \"Upcoming blog entries\""
    echo "in_menu: false"
    echo "author: \"Lars Baehren\""
    echo "---"
    echo ""
    echo "## {title:} ##"
    echo ""
    echo "_`date`_"
    echo ""

    FILES=`ls *.page | grep -v index`

    for FILE in $FILES
    {
        # extract the title of the entry
        varEntry=`grep "title: \"" ${FILE} | sed s/"title: \""// | sed s/\"//`
        # extract time header line
        varTimeheader=`cat ${FILE} | grep "_" | grep "\-\-" | sed s/_//g`
        # set up link pointing to the generated page
        varLink="/blog/${PATH_UPCOMING}/`echo $FILE | sed s/".page"/""/`.html"

        echo " * [${varEntry}](${varLink}) \| ${varTimeheader}"
    }

    # change back to the base directory
    cd ${PATH_BASEDIR}
}

# ==============================================================================
#
#  Main
#
# ==============================================================================

# Time format .... : "2014-08-01T19:09:34.00Z"
# File name ...... : "2014-09-02_20-43.page"
# Time header line : "_Fri, 01. August 2014 -- 19:09_"

varYearMonth=`date +%Y-%m`
varYearMonthDay=`date +%Y-%m-%d`
varHourMinuteSecond=`date +%H:%M:%S`
varTimestamp=`date +%Y-%m-%dT%H:%M:%S.00Z`

varFilename="`date +%Y-%m-%d`_`date +%H-%M`.page"


case $1 in
    "-I")
        echo " - Updating index file for upcoming entries - START"
        create_index_file > ${PATH_BASEDIR}/${PATH_UPCOMING}/index.page
        echo " - Updating index file for upcoming entries - END"
    ;;
    *)
        create_file ${varFilename} "New_entry" ${varTimestamp}
    ;;
esac
