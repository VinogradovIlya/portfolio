#!/bin/bash

gcc -Wall -Werror -Wextra -o s21_cat ../cat.c
SUCCESS=0
FAIL=0
COUNTER=0
LEAKS=0

compare_output() {
    output_file="output.txt"
    expected_output_file="expected_output.txt"
    echo "$1" > "$expected_output_file"
    echo "$2" > "$output_file"
    (( COUNTER++ ))
    if diff -q "$expected_output_file" "$output_file" > /dev/null; then
        echo "$3 Passed"
        (( SUCCESS++ ))
    else
        echo "$3 Failed"
        (( FAIL++ ))
    fi
    rm "$output_file" "$expected_output_file"
}

check_leaks() {
    leaks_output=$(leaks -atExit -- ./s21_cat -$1 $2 2>&1)
    if echo "$leaks_output" | grep "Leaks detected:" > /dev/null; then
        (( LEAKS++ ))
        echo "Memory leaks detected for option $1"
    else
        echo "No memory leaks for option $1"
    fi
}

# 1 параметр
for var1 in b e n s t v
do
  expected_output=$(./s21_cat -$var1 $1)
  output=$(cat -$var1 $1)
  compare_output "$expected_output" "$output" "Test cat flags -$var1"
  check_leaks "$var1" "$1"
done

# Test 2: Проверка флага --number
expected_output=$(./s21_cat --number $1)
output=$(./s21_cat -n $1)
compare_output "$expected_output" "$output" "Test cat flags --number"
check_leaks "n" "$1"

# Test 3: Проверка флага --number-nonblank
expected_output=$(./s21_cat --number-nonblank $1)
output=$(cat -b $1)
compare_output "$expected_output" "$output" "Test cat flags --number-nonblank"
check_leaks "b" "$1"

# Test 4: Проверка флага --squeeze-blank
expected_output=$(./s21_cat --squeeze-blank $1)
output=$(cat -s $1)
compare_output "$expected_output" "$output" "Test cat flags --squeeze-blank"
check_leaks "s" "$1"

## Test : Проверка 1 параметра с двумя файлами
for var1 in b e n s t v
do
  expected_output=$(./s21_cat -$var1 $1 $2)
  output=$(cat -$var1 $1 $2)
  compare_output "$expected_output" "$output" "Test cat flags -$var1 with 2 files"
  check_leaks "$var1" "$1 $2"
done

# проверка с ошибками
expected_output=`./s21_cat -og $1`
output=`cat -og $1`
compare_output "$expected_output" "$output" "Test cat flags -og"
check_leaks "og" "$1"

expected_output=`./s21_cat -og djfnvn.txt`
output=`cat -og djfnvn.txt`
compare_output "$expected_output" "$output" "Test cat flags -og"
check_leaks "og" "djfnvn.txt"

rm s21_cat
echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"
echo "LEAKS: $LEAKS"