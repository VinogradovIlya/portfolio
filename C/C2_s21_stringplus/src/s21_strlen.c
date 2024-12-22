#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  if (str != NULL) {
    while (*str++) {
      length++;
    }
  }
  return length;
}