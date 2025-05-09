
#include "s21_string.h"

void s21_width_flag(char *str, char *buffer, char *prefix, params params) {
  int count_zero = 0;
  if (params.zero) {
    count_zero = params.width - s21_strlen(buffer) - s21_strlen(prefix);
  }
  int count_space =
      params.width - s21_strlen(buffer) - s21_strlen(prefix) - count_zero;

  if (params.minus == 0) {
    for (int i = 0; i < count_space; i++) {
      s21_strncat(str, " ", 1);
    }
  }
  s21_strncat(str, prefix, s21_strlen(prefix));
  for (int i = 0; params.minus == 0 && i < count_zero; i++) {
    s21_strncat(str, "0", 1);
  }
  s21_strncat(str, buffer, s21_strlen(buffer));
  if (params.minus) {
    for (int i = 0; i < count_space; i++) {
      s21_strncat(str, " ", 1);
    }
  }
}

s21_size_t s21_str_from_f(char *str, va_list *args, params params) {
  if (params.length == 'L') {
    long double number = va_arg(*args, long double);
    s21_f_spec(str, number, params);
  } else {
    double number = va_arg(*args, double);
    s21_f_spec(str, (long double)number, params);
  }

  return s21_strlen(str);
}

void s21_f_spec(char *str, long double number, params params) {
  int minus = number < 0 ? 1 : 0;
  number = number < 0 ? -1 * number : number;
  char prefix[2] = "";
  int strlen = 0;
  if (params.plus == 1 && minus == 0) {
    s21_strncat(prefix, "+", 1);
  } else if (minus == 1) {
    s21_strncat(prefix, "-", 1);
  } else if (params.space) {
    s21_strncat(prefix, " ", 1);
  }
  int count_int = 0;
  double num = number;
  while (num >= 1.0) {
    num /= 10;
    count_int++;
  }
  params.accuracy = params.accuracy < 0 ? 6 : params.accuracy;
  char *buffer = calloc(count_int + params.accuracy + 3, sizeof(char));

  long int n =
      params.accuracy == 0 ? (long int)round(number) : (long int)number;
  if (n == 0) count_int = 1;
  while (count_int != 0) {
    buffer[count_int - 1] = (n % 10) + 48;
    n /= 10;
    count_int--;
    strlen++;
  }
  char local_d = (localeconv()->decimal_point)[0];
  if (params.hash || params.accuracy > 0) {
    buffer[strlen] = local_d;
    strlen++;
  }
  if (params.accuracy > 0) {
    long int afterpoint = (long int)round((number - (long int)trunc(number)) *
                                          pow(10, params.accuracy));
    int count_double = params.accuracy;
    while (count_double != 0) {
      buffer[strlen + count_double - 1] = (afterpoint % 10) + 48;
      afterpoint /= 10;
      count_double--;
    }
    strlen += params.accuracy;
  }
  buffer[strlen] = '\0';
  s21_width_flag(str, buffer, prefix, params);
  free(buffer);
}