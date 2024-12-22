#include "s21_string.h"

int s21_memcmp(const void *s1, const void *s2, s21_size_t num) {
  const unsigned char *ptr_1 = (const unsigned char *)s1;
  const unsigned char *ptr_2 = (const unsigned char *)s2;
  int diff = 0;
  for (s21_size_t i = 0; (diff == 0) && i < num; i++) {
    if (*ptr_1 != *ptr_2) {
      diff = (*ptr_1 - *ptr_2);
    }
    ptr_1++;
    ptr_2++;
  }
  return diff;
}
