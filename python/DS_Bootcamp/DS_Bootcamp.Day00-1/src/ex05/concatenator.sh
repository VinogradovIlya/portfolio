#!/bin/sh

rm -f *.py
TEMP_FILE=$(mktemp).py

INPUT_FILE="$1"

cat << 'EOF' > "$TEMP_FILE"
import csv
import os

files = [f for f in os.listdir() if not f.endswith(('.py', '.sh'))]

final_data = []
for file in files:
    with open(file, 'r', newline='', encoding='utf-8') as f:
        reader = list(csv.reader(f))
        if not final_data:
            final_data.append(reader[0])

        for row in reader[1:]:
            final_data.append(row)

final_data[1:] = sorted(final_data[1:], key=lambda x: (x[0], x[1]))
with open('res.csv', 'w', newline='', encoding='utf-8') as w:
    writer = csv.writer(w)
    writer.writerows(final_data)
EOF

python3 "$TEMP_FILE"

if [ -f "$INPUT_FILE" ]; then
    echo "Сравниваю с $INPUT_FILE ..."
    if diff res.csv "$INPUT_FILE" > /dev/null
    then
        echo "Файлы идентичны"
    else
        echo "Файлы различаются"
    fi
else
    echo "Файл для сравнения не найден: $INPUT_FILE "
fi
rm -f *.csv "$TEMP_FILE"