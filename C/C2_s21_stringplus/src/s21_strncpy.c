#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t counter = 0;

  while (src[counter] && counter < n) {
    dest[counter] = src[counter];
    counter++;
  }

  while (counter < n) {
    dest[counter] = '\0';
    counter++;
  }
  return dest;
}
