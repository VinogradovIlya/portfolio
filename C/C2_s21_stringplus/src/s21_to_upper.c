#include "s21_string.h"

char _s21_upper(char c);

void *s21_to_upper(const char *str) {
  s21_size_t len = s21_strlen(str);
  char *new_str = s21_NULL;
  if (len != 0) {
    new_str = (char *)malloc(len + 1);
    if (new_str != s21_NULL) {
      s21_strncpy(new_str, str, len);
      new_str[len] = '\0';
      for (s21_size_t i = 0; i < len; i++) {
        new_str[i] = _s21_upper(new_str[i]);
      }
    }
  }

  return new_str;
}

char _s21_upper(char c) {
  if (c >= 'a' && c <= 'z') {
    c = (c - 32);
  }
  return c;
}