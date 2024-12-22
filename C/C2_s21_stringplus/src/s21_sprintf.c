
#include "s21_string.h"

s21_size_t s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  s21_size_t count = 0;
  for (s21_size_t i = 0; i < s21_strlen(format); i++) {
    if (format[i] == '%') {
      params params = {0, 0, 0, 0, 0, 0, -1, '0', '0'};
      i++;
      i = s21_parse_format(i, format, &params, &args);
      if (format[i] == 'n') {
        *(va_arg(args, int *)) = count;
      } else {
        count += s21_parse_spec(str + count, format[i], params, &args);
      }
    } else {
      str[count] = format[i];
      count++;
      str[count] = '\0';
    }
  }
  str[count] = '\0';
  va_end(args);
  return count;
}

#include <stdio.h>
s21_size_t s21_parse_format(s21_size_t i, const char *format, params *params,
                            va_list *args) {
  char *ch;
  while ((ch = s21_strchr("-+ #0", format[i]))) {
    switch (*ch) {
      case '-':
        params->minus = 1;
        break;
      case '+':
        params->plus = 1;
        break;
      case ' ':
        params->space = 1;
        break;
      case '#':
        params->hash = 1;
        break;
      case '0':
        params->zero = 1;
    }
    i++;
  }
  while (s21_strchr("0123456789", format[i])) {
    params->width *= 10;
    params->width += format[i] - 48;
    i++;
  }
  if (format[i] == '*') {
    params->width = va_arg(*args, int);
    i++;
  }
  if (format[i] == '.') {
    i++;
    while (s21_strchr("0123456789", format[i])) {
      if (params->accuracy < 0) params->accuracy = 0;
      params->accuracy *= 10;
      params->accuracy += format[i] - 48;
      i++;
    }
    if (params->accuracy < 0) params->accuracy = 0;
    if (format[i] == '*') {
      params->accuracy = va_arg(*args, int);
      if (params->accuracy < 0) params->accuracy = 0;
      i++;
    }
  }
  if (s21_strchr("hlL", format[i])) {
    params->length = format[i];
    i++;
  }
  return i;
}

s21_size_t s21_parse_spec(char *str, char specificator, params params,
                          va_list *args) {
  s21_size_t size = 0;
  switch (specificator) {
    case 'c':
      size = s21_str_from_c(str, args, params);
      break;
    case 'd':
    case 'i':
      size = s21_str_from_d_i(str, args, params);
      break;
    case 'e':
      // size = s21_str_from_e(str, args, params);
      break;
    case 'f':
      size = s21_str_from_f(str, args, params);
      break;
    case 'g':
    case 'G':
      // size = s21_str_from_g_G(str, args, params);
      break;
    case 's':
      size = s21_str_from_s(str, args, params);
      break;
    case 'u':
      size = s21_str_from_u_x_X_o_p(str, args, params);
      break;
    case 'o':
      params.spec = 'o';
      size = s21_str_from_u_x_X_o_p(str, args, params);
      break;
    case 'x':
      params.spec = 'x';
      size = s21_str_from_u_x_X_o_p(str, args, params);
      break;
    case 'X':
      params.spec = 'X';
      size = s21_str_from_u_x_X_o_p(str, args, params);
      break;
    case 'p':
      params.spec = 'p';
      size = s21_str_from_u_x_X_o_p(str, args, params);
      break;
    case '%':
      size = s21_str_from_perc(str);
      break;
  }
  return size;
}
