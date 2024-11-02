#!/bin/bash

cd .. 
echo "файл для замены"
read filename

if [ ! -f $filename ]; then
    echo "no file"
    exit
fi

# Возьмите строку поиска
read -p "Введите строку поиска: " search

# Возьмите строку замены
read -p "Введите строку замены: " replace

if [[ $search != "" && $replace != "" ]]; then
    sed -i '' "s/$search/$replace/" $filename
fi

size=$(wc -c $filename | awk '{print $1}')
data=$(date +"%Y-%m-%d %H:%M")
sha=$(shasum -a 256 $filename | awk '{print $1}')
echo $filename - $size - $data - $sha - sha256 >> /Users/lucienng/T02D02-1/src/files.log