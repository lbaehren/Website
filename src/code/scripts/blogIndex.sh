#!/bin/bash

varExtension=".page"
varOutfile="index.page"

## ==============================================================================
##
##  Function definitions
##
## ==============================================================================

##____________________________________________________________________
##                                                         nameOfMonth
##
##  Get the name of the month from the index/number.
##

nameOfMonth ()
{
  case $1 in
    01)
      varName="January"
    ;;
    02)
      varName="February"
    ;;
    03)
      varName="March"
    ;;
    04)
      varName="April"
    ;;
    05)
      varName="May"
    ;;
    06)
      varName="June"
    ;;
    07)
      varName="July"
    ;;
    08)
      varName="August"
    ;;
    09)
      varName="September"
    ;;
    10)
      varName="October"
    ;;
    11)
      varName="November"
    ;;
    12)
      varName="December"
    ;;
  esac

  echo $varName
}

##____________________________________________________________________
##                                                    writeIndexHeader
##
## Write header of index file; take year as input to generate title.
##
## - year    - Year for which the index is being created.
## - menu    - Add the page to the menu? If unset, the page will be
##             excluded from the index in the sidebar.
## - outfile - Path to the output file to which the index is written.
##

writeIndexHeader ()
{
    _varYear=$1

    ## Command parameter: entry to menu?
    if [ -z "$2" ]
    then
	_varMenu="false"
    else
	_varMenu="true"
    fi

    ## Command parameter: Path to the output file
    if [ -z "$3" ]
    then
	_varOutfile="index.page"
    else
	_varOutfile="$3"
    fi

    echo "Creating index file $_varOutfile ..."

    echo "---"                                > $_varOutfile
    echo "title: Blog | ${_varYear}"         >> $_varOutfile
    echo "in_menu: ${_varMenu}"              >> $_varOutfile
    echo "author: Lars Baehren"              >> $_varOutfile
    echo "---"                               >> $_varOutfile
    echo ""                                  >> $_varOutfile
    echo "## Blog archive | ${_varYear} ##"  >> $_varOutfile
    echo ""                                  >> $_varOutfile
    echo "_contents coming soon..._"         >> $_varOutfile
    echo ""                                  >> $_varOutfile
}

##____________________________________________________________________
##                                                    processDirectory
##
##  Process the blog entries within a given directory.
##

processDirectory ()
{
    echo "-- Processing directory `pwd` ..."

    FILES=`ls *${varExtension} | grep -v index`
    varIndexFileMonth=`pwd`/$varOutfile

    ## Remove existing index file
    rm -f $varIndexFileMonth
    
    for FILE in $FILES
    {
      ## Remove extension to filename ...
      varFilename=`echo $FILE | sed s/.page//`

      ## Extract title of the entry
      varTitle=`grep title: $FILE | grep -v \#\# | sed s/"title: "//`

      ## Extract date & time
      varMonth=`echo ${varFilename:5:2}`
      varDay=`echo ${varFilename:8:2}`
      varHour=`echo ${varFilename:11:2}`
      varMinutes=`echo ${varFilename:14:2}`
      varMonthName=`nameOfMonth $varMonth`
      varTime="$varHour:$varMinutes"
      varDateTime=`grep $varTime $FILE | grep $varYear | grep "_" | sed s/"_"//g`

      ## Link to generated file
      varLink="/blog/$varYear/$varYear-$varMonth/$varFilename.html"

      ## Summary of variables assembled so far
#      echo "--------------"
      echo "-- Filename    = $varFilename"
#      echo "-- Title       = $varTitle"
#      echo "-- Timestamp   = $varDateTime"
#      echo "-- Output file = $varIndexFileMonth"

      ## Generate the index file(s)
      if [[ -e index.page ]]
      then
	  echo "  * [$varTitle]($varLink) | $varDateTime |" >> $varIndexFileMonth
      else 
	  echo "Index file missing - generating header now..."
	  echo "---"                     > $varIndexFileMonth
	  echo "title: Blog | $varMonthName $varYear" >> $varIndexFileMonth
	  echo "in_menu: false"         >> $varIndexFileMonth
	  echo "author: Lars Baehren"   >> $varIndexFileMonth
	  echo "---"                    >> $varIndexFileMonth
	  echo ""                       >> $varIndexFileMonth
	  echo "## {title:} ##"         >> $varIndexFileMonth
	  echo ""                       >> $varIndexFileMonth
	  echo "  * [$varTitle]($varLink) | $varDateTime |" >> $varIndexFileMonth
	  ##
          ## Entry to YYYY/index.page
          ##
	  echo "  * [$varTitle]($varLink) | $varDateTime |" >> $varIndexBlog
	  ##
          ## Entry to YYYY/index.page
          ##
	  echo "  * [$varTitle]($varLink) | $varDateTime |" >> $varIndexYear
      fi
    }

}

## ==============================================================================
##
##  Processing
##
##  src/pages/blog
##  |-- YYYY.page                  ...  varIndexBlog
##  `-- YYYY
##      |-- index.page             ...  varIndexYear
##      |-- YYYY-01
##      |-- YYYY-02
##      |
##      `-- YYYY-12
##
## ==============================================================================

##____________________________________________________________________
## Process command line parameters

if [ -z "$1" ]
then
    echo "Missing command line option - year"
    exit
else
    varYear=$1
fi

##____________________________________________________________________
## Check if the directory is there

if [ -d $varYear ]
then
    echo "Found directory for year $varYear"
    ## Make the current directory the base directory
    varBasedir=`pwd`
else
    echo "Unable to continue - missing directory $varYear"
    exit
fi

## Set up path to the index files created
varIndexBlog=$varBasedir/$varYear.page
varIndexYear=$varBasedir/$varYear/index.page

## Change into the directory ...
cd $varYear

writeIndexHeader $varYear true "$varIndexBlog"
writeIndexHeader $varYear false "$varIndexYear"

for FILE in `ls`
{
    if [ -d $FILE ] 
    then
	## Change into the directory
	cd $FILE
	processDirectory
	cd $varBasedir/$varYear
    fi
}

exit

##____________________________________________________________________
## Run another pass across the index file for clean-up

cat $varOutfile | sed s/" ]"/"]"/g > index.tmp
mv index.tmp $varOutfile
