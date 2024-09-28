#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

void s21_strlen_test(char *str_test, int expectation);
void s21_strcmp_test(char *s1, char *s2, int expectation);
void s21_strcpy_test(char *s1, int expectation);
void s21_strcat_test(char *s1, char *s2, char *s3, int expectation);

int main() {
#ifdef q1
    s21_strlen_test("abc", 3);
    s21_strlen_test("\0abc", 0);
    s21_strlen_test("", 0);
#endif

#ifdef q2
    s21_strcmp_test("abc", "abc", 0);
    s21_strcmp_test("abc", "abb", 1);
    s21_strcmp_test("", "abc", -1);
#endif

#ifdef q3
    s21_strcmp_test("abc", "abc", 0);
    s21_strcmp_test("abc", "abb", 1);
    s21_strcmp_test("", "abc", -1);
#endif

#ifdef q4
    s21_strcat_test("hello", " world", "hello world", 0);
    s21_strcat_test("hello", "1234", "hello1234", 0);
    s21_strcat_test("", "hello", "hello", 0);
    s21_strcat_test("", "", "hello", 0);
#endif
    return 0;
}

void s21_strlen_test(char *str_test, int expectation) {
    int res = s21_strlen(str_test);
    output(res, expectation);
}

void s21_strcmp_test(char *s1, char *s2, int expectation) {
    int res = s21_strcmp(s1, s2);
    output(res, expectation);
}

void s21_strcpy_test(char *s1, int expectation) {
    char word[s21_strlen(s1)];
    s21_strcpy(word, s1);
    int res = s21_strcmp(word, s1);
    output(res, expectation);
}

void s21_strcat_test(char *s1, char *s2, char *s3, int expectation) {
    char dest[256];
    s21_strcpy(dest, s1);
    s21_strcat(dest, s2);
    int res = s3 == s1 ? 1 : 0;
    output(res, expectation);
}