#ifndef s21_DECIMAL
#define s21_DECIMAL

#include <limits.h>  // ?
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  int bits[8];
} s21_long_decimal;

typedef struct decimal_bit_3 {
  int empty_1;
  int power;
  int empty_2;
  int sign;
} decimal_bit_3;

int s21_is_less(s21_decimal dec1, s21_decimal dec2);
int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_greater(s21_decimal dec1, s21_decimal dec2);
int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

#endif
