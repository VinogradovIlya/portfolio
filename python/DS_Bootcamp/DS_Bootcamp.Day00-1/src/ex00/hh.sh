#!/bin/sh

#data scientist

#import urllib.parse
#
## Исходная строка
#text = "специалист по данным"
#
## Кодирование строки в URL format
#encoded_text = urllib.parse.quote(text)
#print(encoded_text)

#curl -X GET "https://api.hh.ru/vacancies?text=data%20scientist&per_page=20&page=0" -o temp.json
curl -X GET "https://api.hh.ru/vacancies?text=$1%20$2&per_page=20&page=0" -o temp.json

jq . temp.json > hh.json
rm -f temp.json
