#!/bin/sh

TEMP_FILE=$(mktemp)
trap 'rm -f $TEMP_FILE' EXIT

cat << 'EOF' > $TEMP_FILE
import csv
def rename(name):
	name = name.lower()
	if 'junior' in name and 'middle' in name:
		name = 'Junior/Middle'
	elif 'senior' in name and 'middle' in name:
		name = 'Middle/Senior'
	elif 'senior' in name:
		name = 'Senior'
	elif 'middle' in name:
		name = 'Middle'
	elif 'junior' in name:
		name = 'Junior'
	else:
		name = '-'
	return name
with (
	open('../ex02/hh_sorted.csv', 'r', newline='') as csvfile,
	open('hh_positions.csv', 'w', newline='') as csvout,
):
	temp = csv.reader(csvfile, delimiter=',')
	upd = []
	for num, line in enumerate(temp):
		if num == 0:
			upd.append(line)
			continue
		line[2] = rename(line[2])
		upd.append(line)
	csvwriter = csv.writer(csvout, delimiter=',')
	csvwriter.writerows(upd)
EOF
python3 $TEMP_FILE