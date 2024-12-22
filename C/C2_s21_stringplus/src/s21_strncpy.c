#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t size = s21_strlen(src);
  for (s21_size_t i = 0; i < n && i < size; ++i) {
    dest[i] = src[i];
  }
  return dest;
}
