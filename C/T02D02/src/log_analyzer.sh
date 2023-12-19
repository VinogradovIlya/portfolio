#!bin/bash

cd ..
read filename

if [ ! -f $filename ]; then
    echo "no file"
    exit
fi

string=$(wc -l < "$filename")
change=$(awk '{print $1}' "$filename" | sort | uniq | wc -l)
newHash=$(awk '{print $4}' "$filename" | sort | uniq -d| wc -l)
echo $string $newHash $change