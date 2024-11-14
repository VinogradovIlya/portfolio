#!/bin/bash

gcc -Wall -Werror -Wextra -o s21_cat ../cat.c

echo `./s21_cat $1`

# Test 1: Проверка флага -n
expected_output=`./s21_cat -n $1`
output=`cat -n $1`
if [[ "$output" == "$expected_output" ]]; then
    echo "Test cat flags -n Passed"
else
    echo "Test cat flags -n Failed"
    echo `cat -n $1`
    echo `./s21_cat -n $1`
fi

# Test 2: Проверка флага -e
expected_output=`./s21_cat -e $1`
output=`cat -e $1`
if [[ "$output" == "$expected_output" ]]; then
    echo "Test cat flags -e Passed"
else
    echo "Test cat flags -e Failed"
fi

# Test 3: Проверка флага -b
expected_output=`./s21_cat -b $1`
output=`cat -b $1`
if [[ "$output" == "$expected_output" ]]; then
    echo "Test cat flags -b Passed"
else
    echo "Test cat flags -b Failed"
    echo `cat -b $1`
    echo `./s21_cat -b $1`
fi

# Test 4: Проверка флага -s
expected_output=`./s21_cat -s $1`
output=`cat -s $1`
if [[ "$output" == "$expected_output" ]]; then
    echo "Test cat flags -s Passed"
else
    echo "Test cat flags -s Failed"
fi

# Test 5: Проверка флага -t
expected_output=`./s21_cat -t $1`
output=`cat -t $1`
if [[ "$output" == "$expected_output" ]]; then
    echo "Test cat flags -t Passed"
else
    echo "Test cat flags -t Failed"
fi

# Test 6: Проверка флага --number
expected_output=`./s21_cat --number $1`
output=`./s21_cat -n $1`
if [[ "$output" == "$expected_output" ]]; then
    echo "Test cat flags -number Passed"
else
    echo "Test cat flags --number Failed"
    echo `./s21_cat --number $1`
    echo `cat -n $1`
fi

# Test 7: Проверка флага --number-nonblank
expected_output=`./s21_cat --number-nonblank $1`
output=`cat -b $1`
if [[ "$output" == "$expected_output" ]]; then
    echo "Test cat flags --number-nonblank Passed"
else
    echo "Test cat flags --number-nonblank Failed"
    echo `./s21_cat --number-nonblank $1`
    echo `cat -b $1`
fi

# Test 8: Проверка флага --squeeze-blank
expected_output=`./s21_cat --squeeze-blank $1`
output=`cat -s $1`
if [[ "$output" == "$expected_output" ]]; then
    echo "Test cat flags --squeeze-blank Passed"
else
    echo "Test cat flags --squeeze-blank Failed"
    echo `./s21_cat --squeeze-blank $1`
    echo `cat -s $1`
fi

## Test 9: Проверка флага -E
expected_output=`./s21_cat -E $1`
output=`cat -ev $1`
if [[ "$output" == "$expected_output" ]]; then
    echo "Test cat flags -E Passed"
else
    echo "Test cat flags -E Failed"
fi

# Test 10: Проверка флага -T
expected_output=`./s21_cat -T $1`
output=`cat -tv $1`
if [[ "$output" == "$expected_output" ]]; then
    echo "Test cat flags -T Passed"
else
    echo "Test cat flags -T Failed"
fi


## Test 11:
#expected_output=`./s21_cat -n < 'text1' 'text2' '\0'`
#output=`cat -n  < 'text1' 'text2' '\0'`
#if [[ "$output" == "$expected_output" ]]; then
#    echo "Test cat flags -T Passed"
#else
#    echo "Test cat flags -T Failed"
#fi
#echo "---"

rm s21*