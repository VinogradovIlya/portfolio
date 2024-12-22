#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *result = s21_NULL;
  unsigned char uc = (unsigned char)c;
  int flag = 1;
  s21_size_t len_str = s21_strlen(str);

  while (len_str != 0 && flag) {
    if (*(str + len_str - 1) == uc) {
      result = (char *)(str + len_str - 1);
      flag = 0;
    }
    len_str--;
  }

  return result;
}
