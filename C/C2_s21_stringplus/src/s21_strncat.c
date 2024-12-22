#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t size_dest = s21_strlen(dest);
  for (s21_size_t i = 0; i < n; ++i) {
    dest[size_dest + i] = src[i];
  }
  dest[size_dest + n] = '\0';

  return dest;
}
