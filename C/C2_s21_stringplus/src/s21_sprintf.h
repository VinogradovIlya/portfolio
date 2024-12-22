#ifndef s21_SPRINTF_H
#define s21_SPRINTF_H

#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

typedef struct Params {
  int plus, minus, space, hash, zero;
  int width;
  int accuracy;
  char length;
  char spec;
} params;

s21_size_t s21_sprintf(char *str, const char *format, ...);

s21_size_t s21_parse_format(s21_size_t i, const char *format, params *params,
                            va_list *args);

s21_size_t s21_parse_spec(char *str, char specificator, params params,
                          va_list *args);

s21_size_t s21_str_from_c(char *str, va_list *args, params params);

s21_size_t s21_str_from_d_i(char *str, va_list *args, params params);
char *s21_add_sign(char *str, long int number, params *params);
char *s21_add_space(char *str, int total_width, int used_width,
                    char *fill_char);
char *s21_reverse_string(char *dest, const char *src);
int s21_choose_allocation(int number_width, params *params);
char *s21_number_to_char(long int number, char *result, char *buffer,
                         int count_zeros);
int s21_get_number_width(long int number, params *params, int *count_zeros);
long int s21_choose_type(params *params, va_list *args);
char *s21_format_number(char *str, params *params, long number, char *string,
                        int number_width);

s21_size_t s21_str_from_e(char *str, va_list *args, params params);

s21_size_t s21_str_from_E(char *str, va_list *args, params params);

s21_size_t s21_str_from_f(char *str, va_list *args, params params);
void s21_f_spec(char *str, long double number, params params);
void s21_width_flag(char *str, char *buffer, char *prefix, params params);

s21_size_t s21_str_from_g_G(char *str, va_list *args, params params);

s21_size_t s21_str_from_s(char *str, va_list *args, params params);
void s21_add_spacebar(char *temp_string, s21_size_t *count, params params,
                      s21_size_t size_insert_string);

s21_size_t s21_str_from_u_x_X_o_p(char *str, va_list *args, params params);
char *s21_add_prefix(char *str, params *params);
s21_size_t s21_get_num_char(int num, int upperr_case);
char *s21_number_to_char_unsigned(s21_size_t number, char *result, char *buffer,
                                  int count_zeros, int number_system,
                                  params *params);
int s21_get_number_width_unsigned(s21_size_t number, params *params,
                                  int *count_zeros, int number_system);
s21_size_t s21_choose_type_unsigned(params *params, va_list *args);
char *s21_format_number_unsigned(char *str, params *params,
                                 unsigned long number, char *string,
                                 int number_width);

s21_size_t s21_str_from_perc(char *str);

#endif