#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *result = s21_NULL;
  int flag = 1;

  if (str) {
    while (flag && *str) {
      if (*str == c) {
        result = (char *)str;
        flag = 0;
      }
      str++;
    }
  }

  if (c == '\0') result = (char *)str;
  return result;
}
