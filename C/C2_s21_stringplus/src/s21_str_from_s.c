#include "s21_string.h"

s21_size_t s21_str_from_s(char *str, va_list *args, params params) {
  const char *insert_string = va_arg(*args, char *);
  char *insert_string_flags = s21_NULL;
  s21_size_t size_insert_string = s21_strlen(insert_string);

  if (params.accuracy != -1) {
    size_insert_string = params.accuracy;
  }

  if ((s21_size_t)params.width > size_insert_string) {
    insert_string_flags = calloc(params.width + 1, sizeof(char));
  } else {
    insert_string_flags = calloc(size_insert_string + 1, sizeof(char));
  }

  s21_size_t return_size = 0;
  if (insert_string_flags != s21_NULL) {
    s21_size_t count = 0;
    insert_string_flags[count] = '\0';
    if ((s21_size_t)params.width > size_insert_string) {
      if (params.minus) {
        s21_strncat(insert_string_flags, insert_string, size_insert_string);
        count += size_insert_string;
        s21_add_spacebar(insert_string_flags, &count, params,
                         size_insert_string);
        insert_string_flags[count] = '\0';
      } else {
        s21_add_spacebar(insert_string_flags, &count, params,
                         size_insert_string);
        insert_string_flags[count] = '\0';
        s21_strncat(insert_string_flags, insert_string, size_insert_string);
        count += size_insert_string;
      }

    } else {
      s21_strncat(insert_string_flags, insert_string, size_insert_string);
    }
    return_size = s21_strlen(insert_string_flags);
    s21_strncat(str, insert_string_flags, return_size);
  }
  free(insert_string_flags);
  return return_size;
}
