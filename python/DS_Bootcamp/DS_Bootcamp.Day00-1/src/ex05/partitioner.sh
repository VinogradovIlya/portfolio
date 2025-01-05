#!/bin/sh

#../ex03/hh_positions.csv

rm -f temp.py
TEMP_FILE=$(mktemp).py

cat << 'EOF' > $TEMP_FILE
import csv

with open('../ex03/hh_positions.csv', 'r', newline='', encoding='utf-8') as f:
    csv_reader = list(csv.reader(f, delimiter=','))
    line1 = csv_reader[0]
    titles = set([row[1] for row in csv_reader[1:]])
    for date in titles:
        with open(f'{date}.csv', 'w', newline='', encoding='utf-8') as f_out:
            csv_writer = csv.writer(f_out, delimiter=',')
            csv_writer.writerow(line1)
            f.seek(0)
            rows = [row for row in csv_reader if date == row[1]]
            csv_writer.writerows(rows)
EOF

python3 $TEMP_FILE
rm -f $TEMP_FILE