#!/bin/sh

TEMP_FILE=$(mktemp temp.py)

cat << 'EOF' > $TEMP_FILE
import csv

with (
    open('../ex03/hh_positions.csv', 'r', newline='', encoding='utf-8') as file_input,
    open('hh_uniq_positions.csv', 'w', newline='',encoding='utf-8') as file_out
):
    csv_reader = csv.reader(file_input)
    csv_writer = csv.writer(file_out)
    res = dict()
    for num, row in enumerate(csv_reader):
        if num == 0:
            csv_writer.writerow(['name', 'count'])
        elif row[2] == '-':
            continue
        elif row[2] not in res:
            res.update({row[2]: 1})
        else:
            res[row[2]] += 1
    temp_res = sorted(res.items(), key=lambda x: x[1], reverse=True)
    csv_writer.writerows(temp_res)
EOF

python3 temp.py
rm -f $TEMP_FILE