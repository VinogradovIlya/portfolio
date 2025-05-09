#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);
  char *new_str = (char *)malloc(src_len + str_len + 1);

  if (start_index > src_len) {
    free(new_str);
    new_str = s21_NULL;

  } else {
    s21_memcpy(new_str, src, start_index);
    s21_memcpy(new_str + start_index, str, str_len);

    s21_memcpy(new_str + start_index + str_len, src + start_index,
               src_len - start_index);
    new_str[src_len + str_len] = '\0';
  }

  return new_str;
}
