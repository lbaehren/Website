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
    echo " -C | --conver  PATH  Convert entries in PATH from Dokuwiki-based format"
    echo "                      to Webgen page format."
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
#                                                                 get_month_name

get_month_name ()
{
    if [ -z $1 ] ; then
        varName=""
    else
        case $1 in
            "01")
                varName="January"
            ;;
            "02")
                varName="February"
            ;;
            "03")
                varName="March"
            ;;
            "04")
                varName="April"
            ;;
            "05")
                varName="May"
            ;;
            "06")
                varName="June"
            ;;
            "07")
                varName="July"
            ;;
            "08")
                varName="August"
            ;;
            "09")
                varName="September"
            ;;
            "10")
                varName="October"
            ;;
            "11")
                varName="November"
            ;;
            "12")
                varName="December"
            ;;
        esac
    fi

    echo ${varName}
}

#_______________________________________________________________________________
#                                                               get_month_number

get_month_number ()
{
    if [ -z $1 ] ; then
        MON=""
    else
        case $1 in
            Jan) MON=01 ;;
            "January") MON=01 ;;
            Feb) MON=02 ;;
            "February") MON=02 ;;
            Mar) MON=03 ;;
            "March") MON=03 ;;
            Apr) MON=04 ;;
            May) MON=05 ;;
            Jun) MON=06 ;;
            "Jul") MON=07 ;;
            "July") MON=07 ;;
            "Aug") MON=08 ;;
            "August") MON=08 ;;
            "Sep") MON=09 ;;
            "September") MON=09 ;;
            "Oct") MON=10 ;;
            "October") MON=10 ;;
            "Nov") MON=11 ;;
            "November") MON=11 ;;
            "Dec") MON=12 ;;
            "December") MON=12 ;;
        esac
    fi

    echo ${MON}
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

    if [ -z $2 ] ; then
        varTimestamp=`get_timestamp`
    else
        varTimestamp=$2
    fi

    if [ -z $3 ] ; then
        varTimeheader="`date +%a,\ %d.\ %B\ %Y\ --\ %H:%M`"
    else
        varTimeheader=$3
    fi

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
#                                                         create_index_file_year

create_index_file_year ()
{
    varYear=`date +%Y`
    varPage="${varYear}/index.page"

    # === Generate page header ============================

    echo "---"                                        > ${varPage}
    echo "title: \"${varYear}\""                     >> ${varPage}
    echo "routed_title: \"Blog archive ${varYear}\"" >> ${varPage}
    echo "in_menu: false"                            >> ${varPage}
    echo "author: \"Lars Baehren\""                  >> ${varPage}
    echo "---"                                       >> ${varPage}
    echo ""                                          >> ${varPage}
    echo "## Blog archive | {title:} ##"             >> ${varPage}
    echo ""                                          >> ${varPage}

    for varMonth in 01 02 03 04 05 06 07 08 09 10 11 12
    {
        dirMonth="${varYear}/${varMonth}"
        if [ -d ${dirMonth} ] ; then

            varIndexMonth="${dirMonth}/index.page"
            varMonthName=`get_month_name ${varMonth}`

            echo " -> Processing ${varMonthName} ${varYear} ..."

            # === Header section for year index ===========

            echo ""                        >> ${varPage}
            echo "### ${varMonthName} ###" >> ${varPage}
            echo ""                        >> ${varPage}

            # === Page header for month index =============

            echo "---"                                    > ${varIndexMonth}
            echo "title: \"${varMonthName} ${varYear}\"" >> ${varIndexMonth}
            echo "in_menu: false"                        >> ${varIndexMonth}
            echo "author: \"Lars Baehren\""              >> ${varIndexMonth}
            echo "---"                                   >> ${varIndexMonth}
            echo ""                                      >> ${varIndexMonth}
            echo "## Blog archive | {title:} ##"         >> ${varIndexMonth}
            echo ""                                      >> ${varIndexMonth}

            FILES=`find ${dirMonth} -name "${varYear}*.page"`

            for FILE in $FILES
            {
                # extract the title of the entry
                varEntry=`get_entry_title ${FILE}`
                # extract time header line
                varTimeheader=`get_timeheader ${FILE}`
                # set up link pointing to the generated page
                varLink="/blog/`echo $FILE | sed s/".page"/""/`.html"

                echo " * [${varEntry}](${varLink}) \| ${varTimeheader}" >> ${varPage}
                echo " * [${varEntry}](${varLink}) \| ${varTimeheader}" >> ${varIndexMonth}
            }
        fi
    }

    # Create index page in to blog directory
    cat ${varPage} | sed s#"in_menu: false"#"in_menu: true"# | sed s#"Blog archive"#"Blog entries"# > ${varYear}.page
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
#
#  Publish an entry from the collection of 'upcoming' entries.

publish_entry ()
{
    if [ -z $1 ] ; then
        echo " -> Entries available for publication:"
        list_entries
    else
        varTitle=`get_entry_title $1`
        varFilename=`get_filename`
        varPath=`date +%Y/%m`
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
        create_index_file_year

        # log publishing of entry via TaskWarrior
        task log pro:website +blog -- "Blog entry: ${varTitle}"
    fi
}

#_______________________________________________________________________________
#                                                                convert_entries

## Convert entries within a given directory
convert_entries ()
{
    if [ -z $1 ] ; then
        echo " ERROR - no such directory ${1}"
    else
        for FILE in `find $1 -name "*.txt"`
        {
            if [ -f $FILE ] ; then

                # Name of the output file
                varOutfile=`echo $FILE | sed s/".txt"/".page"/`

                # Extract the title
                varTitle=`cat $FILE | grep "=====" | sed s/"====="//g | sed s/" "// | sed s/" *$"//`

                # Extract pubication date
                varDate=`cat ${FILE} | grep -v "${varTitle}" | grep "//" | grep ":" | sed s/"\/\/"//g | grep $1 | grep -v "\[\["`
                tmpDate=( `echo ${varDate} | sed s/"-"//` )
                varDayOfWeek=`echo ${tmpDate[0]} | sed s/"\,"//`
                varDay=`echo ${tmpDate[1]} | sed s/"\."//`
                varMonthName=${tmpDate[2]}
                varMonth=`get_month_number ${varMonthName}`
                varYear=${tmpDate[3]}
                varHourMinute=${tmpDate[4]}

                # Construct timestamp(s)
                varTimestamp="${varYear}-${varMonth}-${varDay}T${varHourMinute}:00.00Z"
                varTimeheader="${varDayOfWeek}, ${varDay} ${varMonthName} ${varYear} -- ${varHourMinute}"

                echo " -> converting $FILE ... ${varOutfile}"
                create_header "VAR_TITLE" "VAR_TIMESTAMP" "VAR_TIMEHEADER" | \
                    sed s/"VAR_TITLE"/"${varTitle}"/ | \
                    sed s/"VAR_TIMESTAMP"/"${varTimestamp}"/ | \
                    sed s/"VAR_TIMEHEADER"/"${varTimeheader}"/ > ${varOutfile}

                # Main text body of entry
                cat ${FILE} | grep -v "=====" | \
                    grep -v "${varDate}" | \
                    grep -v "{{tag" | \
                    grep -v "~~DISCUSSION~~" | \
                    sed s#" //"#" _"# | \
                    sed s#"// "#"_ "# >> ${varOutfile}
            fi
        }
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
        create_index_file_upcoming > ${PATH_BASEDIR}/${PATH_UPCOMING}/index.page
    ;;
    "--new")
        echo "Creating file for new blog entry ..."
        create_file ${varFilename} "New_entry" ${varTimestamp}
        create_index_file_upcoming > ${PATH_BASEDIR}/${PATH_UPCOMING}/index.page
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
        create_index_file_year
    ;;
    "--index")
        echo "Updating index file for upcoming entries ..."
        create_index_file_upcoming > ${PATH_BASEDIR}/${PATH_UPCOMING}/index.page
        create_index_file_blog ${varRecentEntries}
        create_index_file_year
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
    "-C")
        convert_entries $2
    ;;
    "--convert")
        convert_entries $2
    ;;
    "--get_title")
        echo "Function not implemented yet!"
    ;;
    "--get_date")
        echo "Function not implemented yet!"
    ;;
    *)
        print_help
    ;;
esac
