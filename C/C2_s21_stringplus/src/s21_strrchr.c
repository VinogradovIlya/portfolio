#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *result = s21_NULL;
  while (*str) {
    if ((unsigned char)*str == (unsigned char)c) {
      result = (char *)str;
    }
    str++;
  }
  if (c == '\0') result = (char *)str;

  return result;
}
