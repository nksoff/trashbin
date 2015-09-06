#!/bin/bash

show_usage() {
  echo "Usage: ./photos.sh [--from=FROM] [--to=TO]"
}

show_help() {
  echo "Renames photos in FROM directory accoarding to exif date \n"
  echo "Creates and moves photos in TO directory (TO/<year>/<month>/<date> <time>.jpg)"
  show_usage
}

FROM="."
TO="./result"

while [ "$1" != "" ]; do
  PARAM=`echo $1 | awk -F= '{print $1}'`
  VALUE=`echo $1 | awk -F= '{print $2}'`
  case $PARAM in
    -h | --help)
      show_help
      exit
      ;;
    --from)
      FROM=$VALUE
      ;;
    --to)
      TO=$VALUE
      ;;
    *)
      echo "ERROR: unknown parameter \"$PARAM\""
      show_usage
      exit 1
      ;;
  esac
  shift
done

echo "==== copying from $FROM to $TO ===="

find "$FROM" -path "$TO" -prune -o -type f -iname "*.JPG" | while read f ; do
exifdate=$(exif "$f" | grep Origi | awk '{print $4}' | sed s/'(Origi|'/''/ | sed s/':'/'\ '/g )
exiftime=$(exif "$f" | grep Origi | awk '{print $5}' | sed s/':'/'-'/g)
exifyear="$(echo $exifdate | awk '{print $1}' )"
exifmonth="$(echo $exifdate | awk '{print $2}' )"
exifday="$(echo $exifdate | awk '{print $3}' )"
target="$TO/$exifyear/$exifmonth"

if [ "$target" == "$TO//" ]; then
    target="$TO/trash"
    exifdate=$(echo $f | sed s/'\/'/'-'/g | sed s/'\.'/'-'/g)
    exiftime=""
fi

filename=$(echo $exifdate | sed s/'\ '/'-'/g)
filename="$target/$filename $exiftime.JPG"

mkdir -p  "$target"
cp "$f" "$filename"
done
