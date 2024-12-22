#include "s21_sprintf.h"
#include "s21_string.h"

char *s21_add_prefix(char *str, params *params) {
  if (params->hash) {
    if (params->spec == 'x' || params->spec == 'p') s21_strncat(str, "0x", 2);
    if (params->spec == 'X') s21_strncat(str, "0X", 2);
    if (params->spec == 'o') s21_strncat(str, "0", 1);
  }
  return str;
}

s21_size_t s21_get_num_char(int num, int upperr_case) {
  char flag = '0';
  switch (num) {
    case 10:
      flag = (char)('a' - upperr_case * 32);
      break;
    case 11:
      flag = (char)('b' - upperr_case * 32);
      break;
    case 12:
      flag = (char)('c' - upperr_case * 32);
      break;
    case 13:
      flag = (char)('d' - upperr_case * 32);
      break;
    case 14:
      flag = (char)('e' - upperr_case * 32);
      break;
    case 15:
      flag = (char)('f' - upperr_case * 32);
      break;
  }
  if (0 <= num && num <= 9) flag = (char)(num + '0');
  return flag;
}

char *s21_number_to_char_unsigned(s21_size_t number, char *result, char *buffer,
                                  int count_zeros, int number_system,
                                  params *params) {
  char *ptr = buffer;
  int num = 0;
  int flag = 0;
  int upper_case = 0;
  if (params->spec == 'X') upper_case = 1;
  if (number != 0) {
    while (number != 0) {
      num = number % number_system;

      *ptr++ = s21_get_num_char(num, upper_case);
      number /= number_system;
    }
  } else if (params->spec == 'p') {
    s21_strncat(result, "(nil)", 5);
    flag = 1;
  } else if (count_zeros == 0 || flag == 0)
    *ptr++ = '0';
  if (flag == 0) {
    while (count_zeros-- > 0) {
      *ptr++ = '0';
    }
    *ptr = '\0';
    s21_reverse_string(result, buffer);
  }
  return result;
}

int s21_get_number_width_unsigned(s21_size_t number, params *params,
                                  int *count_zeros, int number_system) {
  s21_size_t number_copy = number;
  int number_width = 0;
  int only_numbers = 0;
  while (number_copy != 0) {
    only_numbers++;
    number_copy = number_copy / number_system;
  }
  number_width += only_numbers;
  if (number_system == 8 && params->hash) only_numbers += 1;
  if (params->accuracy > only_numbers)
    *count_zeros = params->accuracy - only_numbers;
  number_width += *count_zeros;

  if (number == 0) {
    if (params->accuracy == 0) number_width = 0;
    if (params->accuracy == -1) number_width += 1;
  }
  if (params->hash) {
    if ((number_system == 16) && (number != 0)) number_width += 2;
    if (number_system == 8) number_width += 1;
  }
  if ((number == 0) && (params->spec == 'p')) number_width = 5;
  return number_width;
}

s21_size_t s21_choose_type_unsigned(params *params, va_list *args) {
  s21_size_t number = 0;
  if (params->length == 'l') {
    number = (s21_size_t)va_arg(*args, s21_size_t);
  } else if (params->length == 'h') {
    number = (unsigned short int)va_arg(*args, unsigned int);
  } else {
    number = (unsigned int)va_arg(*args, unsigned int);
  }
  return number;
}

char *s21_format_number_unsigned(char *str, params *params,
                                 unsigned long number, char *string,
                                 int number_width) {
  char *fill_char = " ";
  if (params->zero == 1) fill_char = "0";
  if (params->minus) {
    if (number_width > 0) {
      if (number != 0) {
        s21_add_prefix(str, params);
        str += s21_strlen(str);
      }
      s21_strncat(str, string, s21_strlen(string));
      str += s21_strlen(string);
    }
    str = s21_add_space(str, params->width, number_width, fill_char);
  } else {
    if (s21_strncmp(fill_char, "0", 1) == 0) {
      if (number != 0) s21_add_prefix(str, params);
      str = s21_add_space(str, params->width, number_width, fill_char);
    } else {
      str = s21_add_space(str, params->width, number_width, fill_char);
      if (number != 0) s21_add_prefix(str, params);
    }
    if (number != 0) {
      str += s21_strlen(str);
    }
    if (number_width > 0) {
      s21_strncat(str, string, s21_strlen(string));
      str += s21_strlen(string);
    }
  }

  return str;
}

s21_size_t s21_str_from_u_x_X_o_p(char *str, va_list *args, params params) {
  int res = 0;
  int number_system = 10;
  if (params.spec == 'x' || params.spec == 'X' || params.spec == 'p')
    number_system = 16;
  if (params.spec == 'o') number_system = 8;
  char *ptr = str;
  int count_zeros = 0;
  if (params.plus && params.space) params.space = 0;
  if (params.minus && params.zero) params.zero = 0;
  // if (((number_system == 8) || (number_system == 16)) && params.zero &&
  //     (params.accuracy != -1))
  //   params.zero = 0;
  s21_size_t number;
  if (params.spec == 'p') {
    void *address = va_arg(*args, void *);
    number = (s21_size_t)address;
    params.hash = 1;
  } else {
    number = s21_choose_type_unsigned(&params, args);
  }
  int number_width = s21_get_number_width_unsigned(number, &params,
                                                   &count_zeros, number_system);
  int allocation = s21_choose_allocation(number_width, &params);

  char *result = malloc((allocation + 1) * sizeof(char));
  char *buffer = malloc((allocation + 1) * sizeof(char));

  if (result && buffer) {
    s21_memset(result, 0, allocation + 1);
    s21_memset(buffer, 0, allocation + 1);

    if (number_width > 0) {
      s21_number_to_char_unsigned(number, result, buffer, count_zeros,
                                  number_system, &params);
    }
    ptr =
        s21_format_number_unsigned(ptr, &params, number, result, number_width);
    free(result);
    free(buffer);
    res = s21_strlen(str);
  }
  return res;
}
