#!/bin/bash

varExtension=".page"
varOutfile="index.page"

FILES=`ls *${varExtension} | grep -v index`

##__________________________________________________________
## Remove existing index file

if [[ -e index.page ]]
then
    rm index.page
fi

##__________________________________________________________
## Process entry files

for FILE in $FILES
{

  ## Remove extension to filename ...
  varFilename=`echo $FILE | sed s/.page//`

  ##________________________________________________________
  ## Extract title of the entry

  varTitle=`grep title: $FILE | grep -v \#\# | sed s/"title: "//`

  ##________________________________________________________
  ## Extract date & time

  varYear=`echo ${varFilename:0:4}`
  varMonth=`echo ${varFilename:5:2}`
  varDay=`echo ${varFilename:8:2}`
  varHour=`echo ${varFilename:11:2}`
  varMinutes=`echo ${varFilename:14:2}`

  varTime="$varHour:$varMinutes"

  varDateTime=`grep $varTime $FILE | grep $varYear | sed s/"_"//g`

  ##________________________________________________________
  ## Link to generated file

  varLink="/blog/$varYear/$varYear-$varMonth/$varFilename.html"

  ##________________________________________________________
  ## Summary

  echo "--------------"
  echo "Title     = $varTitle"
  echo "Filename  = $varFilename"
  echo "Timestamp = $varDateTime"

  ##________________________________________________________
  ## Generate index file

  if [[ -e index.page ]]
  then
      echo "  * [$varTitle]($varLink) | $varDateTime |" >> $varOutfile
  else 
      echo "Index file missing - generating header now..."
      echo "---"                     > $varOutfile
      echo "title: Blog | $varYear" >> $varOutfile
      echo "in_menu: false"         >> $varOutfile
      echo "---"                    >> $varOutfile
      echo ""                       >> $varOutfile
      echo "## {title:} ##"         >> $varOutfile
      echo ""                       >> $varOutfile
      echo "  * [$varTitle]($varLink) | $varDateTime |" >> $varOutfile
  fi

}

##____________________________________________________________________
## Run another pass across the index file for clean-up

cat $varOutfile | sed s/" ]"/"]"/g > index.tmp
mv index.tmp $varOutfile