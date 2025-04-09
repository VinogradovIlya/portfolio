#include "helper.h"
#include "helper_arithmetic.h"
#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = S21_ARITHMETIC_OK;
  if (!result) {
    code = S21_ARITHMETIC_ERROR;
  }
  if (!s21_correct_decimal(value_1) || !s21_correct_decimal(value_2)) {
    code = S21_ARITHMETIC_ERROR;
  }
  if (s21_is_zero(value_2) && code == S21_ARITHMETIC_OK) {
    code = S21_ARITHMETIC_ZERO_DIV;
    *result = s21_decimal_get_inf();
  }
  if (code == S21_ARITHMETIC_OK) {
    decimal_bit_3 bit_3_1 = {0, 0, 0, 0};
    decimal_bit_3 bit_3_2 = {0, 0, 0, 0};
    s21_decimal_get_bit_3(value_1, &bit_3_1);
    s21_decimal_get_bit_3(value_2, &bit_3_2);
    s21_long_decimal value_long_1 = s21_long_decimal_set_zero(),
                     value_long_2 = s21_long_decimal_set_zero(),
                     remainder = s21_long_decimal_set_zero();
    from_decimal_to_long_decimal(value_1, &value_long_1);
    from_decimal_to_long_decimal(value_2, &value_long_2);
    s21_long_decimal_normalize(&value_long_1, &value_long_2, bit_3_1.power,
                               bit_3_2.power);
    s21_long_decimal result_long =
        s21_long_decimal_binary_div(value_long_1, value_long_2, &remainder);
    if (s21_long_decimal_fit_in_decimal(result_long)) {
      div_remainder_not_equal_0(result_long, value_long_2, remainder, result);

      if (bit_3_1.sign != bit_3_2.sign) {
        s21_set_sign(result, 1);
      } else {
        s21_set_sign(result, 0);
      }

    } else {
      if (bit_3_1.sign != bit_3_2.sign) {
        code = S21_ARITHMETIC_SMALL;
      } else {
        code = S21_ARITHMETIC_BIG;
      }
      *result = s21_decimal_get_inf();
    }
  }
  return code;
}