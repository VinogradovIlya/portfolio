#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  int finish = 0;
  const char *p = (const char *)str;
  const char *res = NULL;
  for (s21_size_t i = 0; i < n && finish == 0; i++) {
    if ((unsigned char)p[i] == (unsigned char)c) {
      res = p + i;
      finish = 1;
    }
  }
  return (void *)res;
}
