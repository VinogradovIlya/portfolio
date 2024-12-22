#include <stdlib.h>

#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = s21_NULL;
  if (!src || !trim_chars) {
    res = s21_NULL;
  }
  if (src && trim_chars) {
    s21_size_t src_len = s21_strlen(src);

    if (src_len == 0) {
      char *empty_str = (char *)malloc(1);
      if (empty_str) {
        empty_str[0] = '\0';
      }
      res = empty_str;
    } else {
      s21_size_t start_index = 0;
      while (start_index < src_len &&
             s21_strchr(trim_chars, src[start_index])) {
        start_index++;
      }

      s21_size_t end_index = src_len;
      while (end_index > start_index &&
             s21_strchr(trim_chars, src[end_index - 1])) {
        end_index--;
      }

      s21_size_t new_str_len = end_index - start_index;

      res = (char *)malloc(new_str_len + 1);

      s21_strncpy(res, src + start_index, new_str_len);
      res[new_str_len] = '\0';
    }
  }
  return (void *)res;
}