#!/bin/sh

input_file="../ex01/hh.csv"
output_file="hh_sorted.csv"
temp_file1=$(mktemp)
temp_file2=$(mktemp)

echo '"id","created_at","name","has_test","alternate_url"' > "$output_file"

head -n 1 "$input_file" > header.csv
tail -n +2 "$input_file" | sort -t, -k2 > "$temp_file1"

cat header.csv "$temp_file1" > "$output_file"

head -n 1 "$input_file" > header.csv
tail -n +2 "$input_file" | sort -t, -k1 > "$temp_file2"

cat header.csv "$temp_file2" > "$output_file"

rm header.csv "$temp_file1" "$temp_file2"