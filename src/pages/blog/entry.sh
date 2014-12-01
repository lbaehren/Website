#!/bin/bash

PATH_BASEDIR=`pwd`
PATH_UPCOMING=upcoming
EDITOR=atom

# ==============================================================================
#
#  Functions
#
# ==============================================================================

print_help ()
{
    echo "usage: entry.sh [-I|--index] [-P|--publish]"
    echo ""
    echo " -H|--help     Print this help and exit."
    echo " -I|--index    Update index files."
    echo " -P|--publish  Publish an entry."
}

#_______________________________________________________________________________
#                                                                  get_timestamp

get_timestamp ()
{
    echo `date +%Y-%m-%dT%H:%M:%S.00Z`
}

#_______________________________________________________________________________
#                                                                   get_filename

get_filename ()
{
    if [ -z $1 ] ; then
        varFilename="`date +%Y-%m-%d`_`date +%H-%M`.page"
    else
        varFilename=""
    fi

    echo ${varFilename}
}

#_______________________________________________________________________________
#                                                                get_entry_title

get_entry_title ()
{
    if [ -z $1 ] ; then
        echo ""
    else
        # check if the file path is valid
        if [ -f $1 ] ; then
            varTitle=`grep "title: \"" $1 | sed s/"title: \""// | sed s/\"//`
            echo ${varTitle}
        else
            echo ""
        fi
    fi
}

#_______________________________________________________________________________
#                                                                 get_timeheader

## Get the (sub-)header with the expanded date and time of the entry
get_timeheader ()
{
    if [ -z $1 ] ; then
        varTimeheader="`date +%a,\ %d.\ %B\ %Y\ --\ %H:%M`"
        echo ${varTimeheader}
    else
        # check if the file path is valid
        if [ -f $1 ] ; then
            varTimeheader=`cat $1 | grep "_" | grep "\-\-" | sed s/_//g`
            echo ${varTimeheader}
        else
            echo ""
        fi
    fi
}

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
    varTimestamp=`get_timestamp`
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
#                                                         writeHeaderYearArchive

## Create header for contents of year folder
#
#  @param outfile -- File to which the output will be written.
#  @param year    -- Year for which to create the index file.
#  @param month   -- [optional] Month of the year for which to create the index file.
#
create_index_file_header ()
{
    varOutfile=${1}
    varYear=${2}

    if [ -z "$3" ]
        then
        varTitle = "${varYear}"
    else
        varTitle = "${3} ${varYear}"
    fi

    echo "-- Writing header for ${varOutfile} ..."

    echo "---"                                        > ${varOutfile}
    echo "title: ${varTitle}"                        >> ${varOutfile}
    echo "in_menu: false"                            >> ${varOutfile}
    echo "author: \"Lars Baehren\""                  >> ${varOutfile}
    echo "---"                                       >> ${varOutfile}
    echo ""                                          >> ${varOutfile}
    echo "## Blog entries | {title:} ##"             >> ${varOutfile}
    echo ""                                          >> ${varOutfile}
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

    # open the newly created file for further editing
    open -a ${EDITOR} ${varOutfile}

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
    echo "_`get_timeheader`_"
    echo ""

    FILES=`ls *.page | grep -v index`

    for FILE in $FILES
    {
        # extract the title of the entry
        varEntry=`get_entry_title ${FILE}`
        # extract time header line
        varTimeheader=`get_timeheader ${FILE}`
        # set up link pointing to the generated page
        varLink="/blog/${PATH_UPCOMING}/`echo $FILE | sed s/".page"/""/`.html"

        echo " * [${varEntry}](${varLink}) \| ${varTimeheader}"
    }

    # change back to the base directory
    cd ${PATH_BASEDIR}
}

#_______________________________________________________________________________
#                                                                  list_upcoming

list_upcoming ()
{
    cd ${PATH_BASEDIR}

    for FILE in `ls ${PATH_UPCOMING} | grep -v index.page`
    {
        varTitle=`get_entry_title ${PATH_UPCOMING}/${FILE}`
        varTimeheader=`get_timeheader ${PATH_UPCOMING}/${FILE}`
        echo " - ${FILE} | ${varTitle} | ${varTimeheader}"
    }
}

#_______________________________________________________________________________
#                                                                  publish_entry

publish_entry ()
{
    if [ -z $1 ] ; then
        echo " -> Entries available for publication:"
        list_upcoming
    else
        varTitle=`get_entry_title $1`
        varFilename=`get_filename`
        varPath=`date +%Y/%Y-%m`
        varEntry="${varPath}/${varFilename}"
        varTimeheaderSource=`get_timeheader $1`
        varTimeheaderNew=`get_timeheader`
        varTimestamp=`get_timestamp`

        echo " -> Entry \"${varTitle}\" selected for publication"
        echo "    - Source file : $1"
        echo "    - Target file : ${varEntry}"
        echo "    - Time header : ${varTimeheaderSource} -> ${varTimeheaderNew}"

        if [ -d ${varPath} ] ; then
            echo "    - Release directory found."
        else
            echo "    - Release directory missing - creating it now."
            mkdir -p ${varPath}
        fi

        # Parse the input file to replace the time information
        cat $1 | sed s/"`cat $1 | grep \"date: [0-9]*\"`"/"date: ${varTimestamp}"/ | sed s/"${varTimeheaderSource}"/"${varTimeheaderNew}"/ > ${varEntry}
        # Remove the input file
        rm -f $1

        # open the newly created file for further editing
        echo " -> loading published entry into editor for final changes ..."
        open -a ${EDITOR} ${varEntry}

    fi
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
varTimestamp=`get_timestamp`
varFilename=`get_filename`

case $1 in
    "-H")
        print_help
    ;;
    "--help")
        print_help
    ;;
    "-I")
        echo "Updating index file for upcoming entries ..."
        create_index_file > ${PATH_BASEDIR}/${PATH_UPCOMING}/index.page
    ;;
    "-P")
        publish_entry $2
    ;;
    "--publish")
        publish_entry $2
    ;;
    *)
        echo "Creating file for new blog entry ..."
        create_file ${varFilename} "New_entry" ${varTimestamp}
    ;;
esac
