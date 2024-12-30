#include "s21_string.h"

s21_size_t s21_strcspn(const char *str, const char *reject) {
  const char *p, *q;
  int finish = 0;
  s21_size_t res = s21_strlen(str);
  for (p = str; *p && finish == 0; p++) {
    for (q = reject; *q && finish == 0; q++) {
      if (*p == *q) {
        res = p - str;
        finish = 1;
      }
    }
  }

  return res;
}
