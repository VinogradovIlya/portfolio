#include "s21_sprintf.h"
#include "s21_string.h"

char *s21_add_sign(char *str, long int number, params *params) {
  if (number < 0) {
    s21_strncat(str, "-", 1);
  } else if (params->plus) {
    s21_strncat(str, "+", 1);
  } else if (params->space) {
    s21_strncat(str, " ", 1);
  }
  return str;
}

char *s21_add_space(char *str, int total_width, int used_width,
                    char *fill_char) {
  int fill_number = total_width - used_width;
  for (int i = 0; i < fill_number; i++) {
    s21_strncat(str, fill_char, 1);
  }
  return str;
}

char *s21_reverse_string(char *dest, const char *src) {
  s21_size_t length = s21_strlen(src);
  for (s21_size_t i = 0; i < length; i++) {
    dest[length - 1 - i] = src[i];
  }
  dest[length] = '\0';
  return dest;
}

char *s21_number_to_char(long int number, char *result, char *buffer,
                         int count_zeros) {
  char *ptr = buffer;
  if (number < 0) number = -number;
  if (number != 0) {
    while (number != 0) {
      *ptr++ = (number % 10) + '0';
      number /= 10;
    }
  } else if (count_zeros == 0)
    *ptr++ = '0';

  while (count_zeros-- > 0) {
    *ptr++ = '0';
  }

  *ptr = '\0';
  s21_reverse_string(result, buffer);
  return result;
}

int s21_get_number_width(long int number, params *params, int *count_zeros) {
  long int number_copy = number;
  int number_width = 0;
  if (number_copy < 0) number_copy *= -1;
  int only_numbers = 0;
  // считаем количество цифр
  while (number_copy != 0) {
    only_numbers++;
    number_copy = number_copy / 10;
  }
  number_width += only_numbers;
  // если accuracy > кол-ва цифр, то считаем, сколько добавить нулей.
  if (params->accuracy > only_numbers)
    *count_zeros = params->accuracy - only_numbers;
  number_width += *count_zeros;
  if (number == 0) {
    if (params->accuracy == 0) number_width = 0;
    if (params->accuracy == -1) number_width += 1;
  }
  return number_width;
}

long int s21_choose_type(params *params, va_list *args) {
  long int number;
  if (params->length == 'l') {
    number = (long int)va_arg(*args, long int);
  } else if (params->length == 'h') {
    number = (short int)va_arg(*args, int);
  } else {
    number = (int)va_arg(*args, int);
  }
  return number;
}

int s21_choose_allocation(int number_width, params *params) {
  int allocation;
  if (number_width > params->width) {
    allocation = number_width;
  } else
    allocation = params->width;
  return allocation;
}

char *s21_format_number(char *str, params *params, long number, char *string,
                        int number_width) {
  int sign_width = (number < 0 || params->plus || params->space) ? 1 : 0;
  char *fill_char = " ";
  if (params->zero) fill_char = "0";
  if (params->minus) {
    if (number_width >= 0) {
      str = s21_add_sign(str, number, params);
      if (number_width > 0) {
        s21_strncat(str, string, s21_strlen(string));
        // str += s21_strlen(string);
      }
    }
    str =
        s21_add_space(str, params->width, number_width + sign_width, fill_char);
  } else {
    if (number_width == 0 || !params->zero) {
      str = s21_add_space(str, params->width, number_width + sign_width,
                          fill_char);
      str = s21_add_sign(str, number, params);
    } else {
      str = s21_add_sign(str, number, params);
      str = s21_add_space(str, params->width, number_width + sign_width,
                          fill_char);
    }
    s21_strncat(str, string, s21_strlen(string));
    // str += s21_strlen(string);
  }
  return str;
}

s21_size_t s21_str_from_d_i(char *str, va_list *args, params params) {
  int res = 0;
  char *ptr = str;
  int count_zeros = 0;

  if (params.plus && params.space) params.space = 0;
  long int number = s21_choose_type(&params, args);

  int number_width = s21_get_number_width(number, &params, &count_zeros);

  int allocation = s21_choose_allocation(number_width, &params);

  char *result = malloc((allocation + 1) * sizeof(char));
  char *buffer = malloc((allocation + 1) * sizeof(char));

  if (result && buffer) {
    s21_memset(result, 0, allocation + 1);
    s21_memset(buffer, 0, allocation + 1);

    if (number_width > 0) {
      s21_number_to_char(number, result, buffer, count_zeros);
    }

    ptr = s21_format_number(ptr, &params, number, result, number_width);

    free(result);
    free(buffer);
    res = s21_strlen(str);
  }
  return res;
}
