#ifndef SRC_21_DECIMAL_ARITHMETIC_HELPER_ARITHMETIC_H
#define SRC_21_DECIMAL_ARITHMETIC_HELPER_ARITHMETIC_H

#include "helper.h"
#include "s21_decimal.h"

#define S21_ARITHMETIC_OK 0
#define S21_ARITHMETIC_BIG 1
#define S21_ARITHMETIC_SMALL 2
#define S21_ARITHMETIC_ZERO_DIV 3
#define S21_ARITHMETIC_ERROR 4

s21_long_decimal s21_long_decimal_set_zero(void);
s21_long_decimal s21_long_decimal_zero_five(void);
s21_long_decimal s21_long_decimal_set_one(void);
s21_decimal s21_decimal_set_min(void);
s21_decimal s21_decimal_get_inf(void);

int s21_long_decimal_zero_mantissa(s21_long_decimal value);
int s21_long_decimal_fit_in_decimal(s21_long_decimal value);

s21_long_decimal s21_long_decimal_mult_10(s21_long_decimal value);

s21_long_decimal s21_long_decimal_binary_add(s21_long_decimal value_1,
                                             s21_long_decimal value_2);
s21_long_decimal s21_long_decimal_binary_sub(s21_long_decimal value_1,
                                             s21_long_decimal value_2);
s21_long_decimal s21_long_decimal_binary_mul(s21_decimal value_1,
                                             s21_decimal value_2);
s21_long_decimal s21_long_decimal_binary_div(s21_long_decimal value_1,
                                             s21_long_decimal value_2,
                                             s21_long_decimal *remainder);

s21_long_decimal s21_long_decimal_logic_and(s21_long_decimal value_1,
                                            s21_long_decimal value_2);
s21_long_decimal s21_long_decimal_logic_xor(s21_long_decimal value_1,
                                            s21_long_decimal value_2);
s21_long_decimal s21_long_decimal_logic_not(s21_long_decimal value);

int combo_sing_decimal(int sing_1, int sing_2);
int s21_max_pow(int pow_1, int pow_2);
void s21_long_decimal_normalize(s21_long_decimal *value_1,
                                s21_long_decimal *value_2, int power_1,
                                int power_2);

int add_algorithm(s21_decimal value_1, s21_decimal value_2,
                  decimal_bit_3 bit_3_value_1, decimal_bit_3 bit_3_value_2,
                  s21_decimal *result);
int sub_algorithm(s21_decimal value_1, s21_decimal value_2,
                  decimal_bit_3 bit_3_value_1, decimal_bit_3 bit_3_value_2,
                  s21_decimal *result);
int mul_algorithm(s21_decimal value_1, s21_decimal value_2,
                  decimal_bit_3 bit_3_value_1, decimal_bit_3 bit_3_value_2,
                  s21_decimal *result);
void div_remainder_not_equal_0(s21_long_decimal quotient,
                               s21_long_decimal divisor,
                               s21_long_decimal remainder, s21_decimal *result);
int div_calc_fractional(s21_long_decimal *quotient, s21_long_decimal divisor,
                        s21_long_decimal *remainder);

// void print_switch_ten_pow(void);
s21_long_decimal s21_long_decimal_ten_pows(int pow);

void ten_pows_0_12(s21_long_decimal *value, int pow);
void ten_pows_13_22(s21_long_decimal *value, int pow);
void ten_pows_23_30(s21_long_decimal *value, int pow);
void ten_pows_31_38(s21_long_decimal *value, int pow);

int s21_long_decimal_binary_compare(s21_long_decimal value_1,
                                    s21_long_decimal valeu_2);

int s21_long_decimal_shift_to_decimal(s21_long_decimal value);

void s21_shift_left_more_31(s21_long_decimal *long_decimal, int shift_value);

s21_long_decimal s21_long_decimal_banking_round(s21_long_decimal integer,
                                                s21_long_decimal fractional);

#endif  // SRC_21_DECIMAL_ARITHMETIC_HELPER_ARITHMETIC_H
