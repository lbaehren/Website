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
    echo " -N | --new           Create a new blog entry."
    echo " -H | --help          Print this help and exit."
    echo " -I | --index         Update index files."
    echo " -L | --list    PATH  List entries in a given directory; if no further argument"
    echo "                      is provided the entries available for publication are"
    echo "                      displayed."
    echo " -P | --publish FILE  Publish an entry. If no further argument is provided"
    echo "                      entries available for publication are listed."
}

#_______________________________________________________________________________
#                                                                  get_timestamp
# Get the timestamp based on the date and time of day.
#
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
#                                                                 get_entry_body

get_entry_body ()
{
    if [ -z $1 ] ; then
        echo ""
    else
        # check if the file path is valid
        if [ -f $1 ] ; then
            cat $1 | sed 1,/"##"/d
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
            varTimeheader=`cat $1 | grep -v "\[" | grep ":" | grep "_" | grep -v "\-r\-" | grep "\-\-" | sed s/_//g`
            echo ${varTimeheader}
        else
            echo ""
        fi
    fi
}

#_______________________________________________________________________________
#                                                         list_of_recent_entries

list_of_recent_entries ()
{
    nofEntries=$1
    tmpFile=entries.txt

    cd ${PATH_BASEDIR}

    for FILE in `ls ${PATH_BASEDIR}`
    {
        if [ -d "$FILE" ]
        then
            find $FILE -name "*.page" | grep -v index | grep -v upcoming >> ${tmpFile}
        fi
    }

    # Sort through the list of entries
    varEntries=`cat ${tmpFile} | tail -n ${nofEntries} | sort -r`
    rm -f ${tmpFile}

    echo ${varEntries}
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
    create_index_file_upcoming > ${PATH_BASEDIR}/${PATH_UPCOMING}/index.page
}

#_______________________________________________________________________________
#                                                     create_index_file_upcoming

create_index_file_upcoming ()
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
#                                                         create_index_file_blog

create_index_file_blog ()
{
    varOutfile=${PATH_BASEDIR}/index.page

    # change into the directory for which to create the index
    cd ${PATH_BASEDIR}

    echo "---"                         > ${varOutfile}
    echo "title: \"Blog\""            >> ${varOutfile}
    echo "in_menu: false"             >> ${varOutfile}
    echo "author: \"Lars Baehren\""   >> ${varOutfile}
    echo "---"                        >> ${varOutfile}
    echo ""                           >> ${varOutfile}
    echo "# {title:} #"               >> ${varOutfile}

    FILES=`list_of_recent_entries $1`

    for FILE in $FILES
    {
        # extract the title of the entry
        varEntry=`get_entry_title ${FILE}`

        echo ""                       >> ${varOutfile}
        echo "**:::**"                >> ${varOutfile}
        echo ""                       >> ${varOutfile}
        echo "### ${varEntry} ###"    >> ${varOutfile}
        echo ""                       >> ${varOutfile}
        get_entry_body ${FILE}        >> ${varOutfile}
    }

    # change back to the base directory
    cd ${PATH_BASEDIR}
}

#_______________________________________________________________________________
#                                                                   list_entries

## List blog entries within a given directory
#
#  @param dir - Directory for which to list the entries
#
list_entries ()
{
    if [ -z $1 ] ; then
        varDirectory=${PATH_UPCOMING}
    else
        varDirectory=$1
    fi

    cd ${PATH_BASEDIR}

    for FILE in `ls ${varDirectory} | grep -v index.page`
    {
        varTitle=`get_entry_title ${varDirectory}/${FILE}`
        varTimeheader=`get_timeheader ${varDirectory}/${FILE}`
        echo " - ${FILE} | ${varTitle} | ${varTimeheader}"
    }
}

#_______________________________________________________________________________
#                                                                  publish_entry

publish_entry ()
{
    if [ -z $1 ] ; then
        echo " -> Entries available for publication:"
        list_entries
    else
        varTitle=`get_entry_title $1`
        varFilename=`get_filename`
        varPath=`date +%Y/%Y-%m`
        varEntry="${varPath}/${varFilename}"
        varTimeheaderSource=`get_timeheader $1`
        varTimeheaderNew=`get_timeheader`
        varTimestamp=`get_timestamp`
        varRecentEntries=15

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

        # Rebuild the blog index
        echo " -> rebuilding blog index pages ..."
        create_index_file_upcoming > ${PATH_BASEDIR}/${PATH_UPCOMING}/index.page
        create_index_file_blog ${varRecentEntries}

        # log publishing of entry via TaskWarrior
        task log pro:website +blog -- "Blog entry: ${varTitle}"
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
varRecentEntries=15

case $1 in
    "-N")
        echo "Creating file for new blog entry ..."
        create_file ${varFilename} "New_entry" ${varTimestamp}
    ;;
    "--new")
        echo "Creating file for new blog entry ..."
        create_file ${varFilename} "New_entry" ${varTimestamp}
    ;;
    "-H")
        print_help
    ;;
    "--help")
        print_help
    ;;
    "-I")
        echo "Updating index file for upcoming entries ..."
        create_index_file_upcoming > ${PATH_BASEDIR}/${PATH_UPCOMING}/index.page
        create_index_file_blog ${varRecentEntries}
    ;;
    "--index")
        echo "Updating index file for upcoming entries ..."
        create_index_file_upcoming > ${PATH_BASEDIR}/${PATH_UPCOMING}/index.page
        create_index_file_blog ${varRecentEntries}
    ;;
    "-L")
        list_entries $2
    ;;
    "--list")
        list_entries $2
    ;;
    "-P")
        publish_entry $2
    ;;
    "--publish")
        publish_entry $2
    ;;
    *)
        print_help
    ;;
esac
