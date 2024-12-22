#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *res = s21_NULL;
  for (const char *h = haystack; *h && res == s21_NULL; h++) {
    const char *temp_h = h;
    const char *n = needle;

    while (*n && *temp_h == *n) {
      temp_h++;
      n++;
    }

    if (!*n) {
      res = (char *)h;
    }
  }
  return res;
}
