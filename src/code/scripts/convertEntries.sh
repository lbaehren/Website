#!/bin/bash

varExtension=".page"

FILES=`ls *.txt`

for FILE in $FILES
{
  ## Remove extension to filename ...
  varFilename=`echo $FILE | sed s/.txt//`
  ## ... and assemble the new name
  varOutfile=$varFilename$varExtension

  ##________________________________________________________
  ## Extract title of the entry

  varTitle=`grep ==== $FILE | sed s/"===== "// | sed s/" ====="//`

  ##________________________________________________________
  ## Extract date & time

  varYear=`echo ${varFilename:0:4}`
  varMonth=`echo ${varFilename:5:2}`
  varDay=`echo ${varFilename:8:2}`
  varHour=`echo ${varFilename:11:2}`
  varMinutes=`echo ${varFilename:14:2}`

  varTime="$varHour:$varMinutes"

  varDateTime=`grep $varTime $FILE | sed s/"\/\/"/"_"/ | sed s/"\/\/"/"_"/`
  
  ##________________________________________________________
  ## Convert file

  echo "Processing file $FILE -> $varOutfile ..."

  echo "---"                > $varOutfile
  echo "title: $varTitle"  >> $varOutfile
  echo "in_menu: false"    >> $varOutfile
  echo "---"               >> $varOutfile
  echo ""                  >> $varOutfile
  echo "## {title:} ##"    >> $varOutfile
  echo ""                  >> $varOutfile
  echo "$varDateTime"      >> $varOutfile

  cat $FILE | grep -v "====" | grep -v $varTime | grep -v "{{tag" >> $varOutfile

  ##________________________________________________________
  ## Remove input file

  rm -f $FILE
}
