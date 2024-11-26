#!/bin/bash

if [ "$#" -ne 2 ]; then
  echo "Usage: $0 <test_file> <patterns_file>"
  exit 1
fi

TEST_FILE=$1
PATTERNS_FILE=$2
gcc -Wall -Werror -Wextra -o s21_grep ../grep.c
RED='\033[0;31m'
GREEN='\033[0;92m'
NC='\033[0m'
TOTAL=0
SUC=0
FAIL=0
LEAKS=0

check_result() {
  let "TOTAL += 1"
  if diff -q <(echo "$1") <(echo "$2") &> /dev/null; then
    echo -e "Test ${TOTAL} ${GREEN}PASSED${NC}"
    let "SUC += 1"
  else
    echo -e "Test ${TOTAL} ${RED}FAILED${NC}"
    echo 'grep'
    echo $1
    echo 's21_grep'
    echo $2
    let "FAIL += 1"
  fi
}

check_leaks() {
    leaks_output=$(leaks -atExit -- ./s21_grep -$1 $2 $3 $4 2>&1)
    if echo "$leaks_output" | grep "Leaks detected:" > /dev/null; then
        (( LEAKS++ ))
        echo "Memory leaks detected for option $1"
    else
        echo "No memory leaks for option $1"
    fi
}

# -v: выведет все строки, не содержащие "Hello"     1
EXPECTED=$(grep -v "Hello" "$TEST_FILE")
ACTUAL=$(./s21_grep -v "Hello" "$TEST_FILE")
check_result "$EXPECTED" "$ACTUAL"
check_leaks "-v" "Hello" "$TEST_FILE"

# -c: выведет количество строк, содержащих "World"  2
EXPECTED=$(grep -c "World" "$TEST_FILE")
ACTUAL=$(./s21_grep -c "World" "$TEST_FILE")
check_result "$EXPECTED" "$ACTUAL"
check_leaks "-c" "World" "$TEST_FILE"

# -l: покажет имя файла, содержащего "Test case"   3
echo "Test case" > temp_test_file.txt
EXPECTED=$(grep -l "Test case" "$TEST_FILE" temp_test_file.txt)
ACTUAL=$(./s21_grep -l "Test case" "$TEST_FILE" temp_test_file.txt)
check_result "$EXPECTED" "$ACTUAL"
check_leaks "-l" "Test case" "$TEST_FILE" "temp_test_file.txt"
rm temp_test_file.txt

# -n: выведет строки, содержащие "line", вместе с номерами строк       4
EXPECTED=$(grep -n "line" "$TEST_FILE")
ACTUAL=$(./s21_grep -n "line" "$TEST_FILE")
check_result "$EXPECTED" "$ACTUAL"
check_leaks "-n" "line" "$TEST_FILE"

# -i: игнорирует регистр символов при поиске "hello"                   5
EXPECTED=$(grep -i "hello" "$TEST_FILE")
ACTUAL=$(./s21_grep -i "hello" "$TEST_FILE")
check_result "$EXPECTED" "$ACTUAL"
check_leaks "-i" "hello" "$TEST_FILE"

# -h: скрывает имена файлов в выводе                                   6
cp "$TEST_FILE" test_file_copy.txt
EXPECTED=$(grep -h "test" "$TEST_FILE" test_file_copy.txt)
ACTUAL=$(./s21_grep -h "test" "$TEST_FILE" test_file_copy.txt)
check_result "$EXPECTED" "$ACTUAL"
check_leaks "-h" "test" "$TEST_FILE" test_file_copy.txt
rm test_file_copy.txt

# -s: подавит ошибки, если файл не найден                             7
EXPECTED=$(grep -s "test" missing_file.txt 2>/dev/null)
ACTUAL=$(./s21_grep -s "test" missing_file.txt 2>/dev/null)
check_result "$EXPECTED" "$ACTUAL"
check_leaks "-s" "test" "$TEST_FILE" test_file_copy.txt


# -f: будет искать шаблоны из patterns.txt в test_file.txt            8
EXPECTED=$(grep -f "$PATTERNS_FILE" "$TEST_FILE")
ACTUAL=$(./s21_grep -f "$PATTERNS_FILE" "$TEST_FILE")
check_result "$EXPECTED" "$ACTUAL"
check_leaks "-f" "$PATTERNS_FILE" "$TEST_FILE"


# -o: выведет только совпадающие части строк, соответствующие 'o..'   9
EXPECTED=$(grep -o 'o..' "$TEST_FILE")
ACTUAL=$(./s21_grep -o 'o..' "$TEST_FILE")
check_result "$EXPECTED" "$ACTUAL"
check_leaks "-o" "o.." "$TEST_FILE"

# -e: регистрозависимый поиск "Example"                               10
EXPECTED=$(grep -e "Example" "$TEST_FILE")
ACTUAL=$(./s21_grep -e "Example" "$TEST_FILE")
check_result "$EXPECTED" "$ACTUAL"
check_leaks "-e" "Example" "$TEST_FILE"

# Комбинации флагов
# -vi: выведет все строки, не содержащие "hello" игнорируя регистр    11
EXPECTED=$(grep -vi "hello" "$TEST_FILE")
ACTUAL=$(./s21_grep -vi "hello" "$TEST_FILE")
check_result "$EXPECTED" "$ACTUAL"
check_leaks "-vi" "hello" "$TEST_FILE"

# -cv: выведет количество строк, не содержащих "Example"              12
EXPECTED=$(grep -cv "Example" "$TEST_FILE")
ACTUAL=$(./s21_grep -cv "Example" "$TEST_FILE")
check_result "$EXPECTED" "$ACTUAL"
check_leaks "-cv" "Example" "$TEST_FILE"

# -in: вывведет строки содержащие "test" вместе с номерами строк не учитывая регистр      13
EXPECTED=$(grep -in "test" "$TEST_FILE")
ACTUAL=$(./s21_grep -in "test" "$TEST_FILE")
check_result "$EXPECTED" "$ACTUAL"
check_leaks "-in" "test" "$TEST_FILE"

# -lh: покажет имя файла, содержащего "example" без отображения самих строк               14
echo "example" > temp_test_file.txt
EXPECTED=$(grep -lh "example" "$TEST_FILE" temp_test_file.txt)
ACTUAL=$(./s21_grep -lh "example" "$TEST_FILE" temp_test_file.txt)
check_result "$EXPECTED" "$ACTUAL"
check_leaks "-lh" "example" "$TEST_FILE" "temp_test_file.txt"
rm temp_test_file.txt

# -sh: скрывает ошибки и имена файлов                                                     15
EXPECTED=$(grep -sh "test" missing_file.txt 2>/dev/null)
ACTUAL=$(./s21_grep -sh "test" missing_file.txt 2>/dev/null)
check_result "$EXPECTED" "$ACTUAL"
check_leaks "-sh" "test" "$TEST_FILE" "temp_test_file.txt"


# -nf: покажет номер строк содержащих шаблоны из patterns.txt                             16
EXPECTED=$(grep -nf "$PATTERNS_FILE" "$TEST_FILE")
ACTUAL=$(./s21_grep -nf "$PATTERNS_FILE" "$TEST_FILE")
check_result "$EXPECTED" "$ACTUAL"
check_leaks "-nf" "$PATTERNS_FILE" "$TEST_FILE"


# -e и -f: будет искать шаблоны из patterns.txt и "Example"                               17
EXPECTED=$(grep -e "Example" -f "$PATTERNS_FILE" "$TEST_FILE")
ACTUAL=$(./s21_grep -e "Example" -f "$PATTERNS_FILE" "$TEST_FILE")
check_result "$EXPECTED" "$ACTUAL"
check_leaks "-e" "Example" "-f" "$PATTERNS_FILE" "$TEST_FILE"

# Резюме тестов
echo -e "FAIL ${RED}$FAIL${NC}"
echo -e "SUCCES ${GREEN}$SUC${NC}"
echo -e "TOTAL $TOTAL"
echo -e "LEAKS $LEAKS"
rm -rf s21_grep