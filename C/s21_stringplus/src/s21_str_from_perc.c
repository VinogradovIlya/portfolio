#include "s21_string.h"

s21_size_t s21_str_from_perc(char *str) {
  s21_strncat(str, "%", 2);
  return 1;
}
