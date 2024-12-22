#include "s21_string.h"

s21_size_t s21_str_from_c(char *str, va_list *args, params params) {
  char *temp_symbol = s21_NULL;

  if (params.width > 1) {
    temp_symbol = calloc(params.width + 1, sizeof(char));
  } else {
    temp_symbol = calloc(2, sizeof(char));
  }
  s21_size_t return_size = 0;
  if (temp_symbol != s21_NULL) {
    s21_size_t count = 0;
    if (params.width > 0) {
      s21_size_t size_insert_string = 1;
      if (params.minus) {
        temp_symbol[count++] = va_arg(*args, int);
        s21_add_spacebar(temp_symbol, &count, params, size_insert_string);
      } else {
        s21_add_spacebar(temp_symbol, &count, params, size_insert_string);
        temp_symbol[count++] = va_arg(*args, int);
      }
      temp_symbol[count] = '\0';

    } else {
      temp_symbol[count++] = va_arg(*args, int);
      temp_symbol[count] = '\0';
    }

    return_size = s21_strlen(temp_symbol);
    s21_strncat(str, temp_symbol, return_size);
  }
  free(temp_symbol);
  return return_size;
}

void s21_add_spacebar(char *temp_string, s21_size_t *count, params params,
                      s21_size_t size_insert_string) {
  if (params.minus) {
    size_insert_string = 0;
  }

  while (*count < (s21_size_t)params.width - size_insert_string) {
    temp_string[*count] = ' ';
    *count += 1;
  }
}
