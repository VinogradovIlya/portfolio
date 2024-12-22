#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  const unsigned char *ptr_1 = (const unsigned char *)str1;
  const unsigned char *ptr_2 = (const unsigned char *)str2;
  int flag = 0;
  int diff = 0;
  for (s21_size_t i = 0; (flag == 0) && (i < n); i++) {
    if (*ptr_1 != *ptr_2) {
      diff = *ptr_1 - *ptr_2;
      flag = 1;
    }
    if ((*ptr_1 == '\0') || (*ptr_2 == '\0')) {
      flag = 1;
    }
    ptr_1++;
    ptr_2++;
  }
  return diff;
}
