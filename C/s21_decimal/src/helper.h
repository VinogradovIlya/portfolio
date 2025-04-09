#ifndef SRC_S21_DECIMAL_HELPERS_HELPERS_H_
#define SRC_S21_DECIMAL_HELPERS_HELPERS_H_
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"
#define DECIMAL_VALUE_BITS 96
#define LONG_DECIMAL_VALUE_BITS 224
#define INT_BITS 32

void s21_decimal_get_bit_3(s21_decimal decimal, decimal_bit_3 *decimal_bit_3);
void s21_decimal_set_bit_3(s21_decimal *decimal, decimal_bit_3 bit_3);
void s21_long_decimal_get_bit_3(s21_long_decimal decimal,
                                decimal_bit_3 *decimal_bit_3);
void s21_long_decimal_set_bit_3(s21_long_decimal *decimal, decimal_bit_3 bit_3);
int s21_get_sign(s21_decimal value);
void s21_set_sign(s21_decimal *value, int sign_value);
int s21_get_bit(s21_decimal value, int bit);
int s21_get_bit_long(s21_long_decimal value, int bit);
void s21_set_bit(s21_decimal *decimal, int bit, unsigned value);
void s21_set_bit_long(s21_long_decimal *long_decimal, int bit, unsigned value);
void s21_set_scale(s21_decimal *decimal, int power_value);
void s21_long_set_scale(s21_long_decimal *decimal, int power_value);
int s21_is_zero(s21_decimal decimal);
void s21_shift_left(s21_long_decimal *long_decimal, int shift_value);
void s21_bitwise_add(s21_long_decimal value_1, s21_long_decimal value_2,
                     s21_long_decimal *result);
void s21_mult_by_10(s21_long_decimal long_decimal, s21_long_decimal *result);
void s21_shift_right(s21_long_decimal *long_decimal, int shift_value);
int s21_long_decimal_get_high_bit_not_zero(s21_long_decimal value);
int s21_decimal_get_high_bit_not_zero(s21_decimal value);
s21_decimal s21_abs(s21_decimal value_1);

// Печать
void print_bits(unsigned n);
void print_decimal(s21_decimal decimal);
void print_long_decimal(s21_long_decimal decimal);

// Конвертация
void from_decimal_to_long_decimal(s21_decimal decimal,
                                  s21_long_decimal *long_decimal);
void from_long_decimal_to_decimal(s21_long_decimal long_decimal,
                                  s21_decimal *decimal);
// Коректность
int s21_correct_decimal(s21_decimal decimal);

int s21_long_decimal_even(s21_long_decimal value);

#endif
