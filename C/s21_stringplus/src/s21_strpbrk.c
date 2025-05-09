#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;
  int flag = 1;
  if (str1 == s21_NULL || str2 == s21_NULL) {
    flag = 0;
  }

  while (flag && *str1) {
    const char *s = str2;
    while (flag && *s) {
      if (*str1 == *s) {
        result = (char *)str1;
        flag = 0;
      }
      s++;
    }
    str1++;
  }

  return result;
}
