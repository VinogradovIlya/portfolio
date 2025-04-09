#include "helper.h"
#include "helper_arithmetic.h"
#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = S21_ARITHMETIC_OK;
  if (!result) {
    code = S21_ARITHMETIC_ERROR;
  }
  if (!s21_correct_decimal(value_1) || !s21_correct_decimal(value_2)) {
    code = S21_ARITHMETIC_ERROR;
  }
  if (code == S21_ARITHMETIC_OK) {
    decimal_bit_3 bit_3_1 = {0, 0, 0, 0};
    decimal_bit_3 bit_3_2 = {0, 0, 0, 0};
    s21_decimal_get_bit_3(value_1, &bit_3_1);
    s21_decimal_get_bit_3(value_2, &bit_3_2);

    code = mul_algorithm(value_1, value_2, bit_3_1, bit_3_2, result);
    if (bit_3_1.sign != bit_3_2.sign) {
      s21_set_sign(result, 1);
    } else {
      s21_set_sign(result, 0);
    }
  }
  if (code == S21_ARITHMETIC_BIG && s21_get_sign(*result) == 1) {
    code = S21_ARITHMETIC_SMALL;
  }
  return code;
}

int mul_algorithm(s21_decimal value_1, s21_decimal value_2,
                  decimal_bit_3 bit_3_value_1, decimal_bit_3 bit_3_value_2,
                  s21_decimal *result) {
  int code = S21_ARITHMETIC_OK;
  s21_long_decimal result_long = s21_long_decimal_binary_mul(value_1, value_2);
  int pow_of_ten = s21_long_decimal_shift_to_decimal(result_long);

  int res_pow = bit_3_value_1.power + bit_3_value_2.power - pow_of_ten;

  if (res_pow >= 0) {
    if (res_pow > 28) {
      s21_long_decimal tmp = result_long;
      int tmp_pow = res_pow;
      while (tmp_pow > 28) {
        tmp = s21_long_decimal_binary_div(tmp, s21_long_decimal_ten_pows(1),
                                          NULL);
        --tmp_pow;
      }
      pow_of_ten = res_pow - tmp_pow + pow_of_ten;
      res_pow = tmp_pow;
    }
    s21_long_decimal remainder = s21_long_decimal_set_zero();
    s21_long_decimal power_ten = s21_long_decimal_ten_pows(pow_of_ten);
    result_long =
        s21_long_decimal_binary_div(result_long, power_ten, &remainder);

    s21_long_set_scale(&remainder, pow_of_ten);
    result_long = s21_long_decimal_banking_round(result_long, remainder);
    s21_long_set_scale(&result_long, res_pow);

    from_long_decimal_to_decimal(result_long, result);
  } else {
    code = S21_ARITHMETIC_BIG;
    *result = s21_decimal_get_inf();
  }

  return code;
}