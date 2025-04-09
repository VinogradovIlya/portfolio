#include "helper.h"
#include "helper_arithmetic.h"
#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
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
    switch (combo_sing_decimal(bit_3_1.sign, bit_3_2.sign)) {
      case 1: {
        s21_set_sign(&value_1, 0);
        s21_set_sign(&value_2, 0);
        if (s21_is_greater_or_equal(value_1, value_2)) {
          code = sub_algorithm(value_1, value_2, bit_3_1, bit_3_2, result);
          s21_set_sign(result, 1);
        } else {
          code = sub_algorithm(value_2, value_1, bit_3_2, bit_3_1, result);
          s21_set_sign(result, 0);
        }
      } break;
      case 2: {
        code = add_algorithm(value_1, value_2, bit_3_1, bit_3_2, result);
        s21_set_sign(result, 1);
      } break;
      case 3: {
        code = add_algorithm(value_1, value_2, bit_3_1, bit_3_2, result);
        s21_set_sign(result, 0);
      } break;
      case 4: {
        if (s21_is_greater_or_equal(value_1, value_2)) {
          code = sub_algorithm(value_1, value_2, bit_3_1, bit_3_2, result);
          s21_set_sign(result, 0);
        } else {
          code = sub_algorithm(value_2, value_1, bit_3_2, bit_3_1, result);
          s21_set_sign(result, 1);
        }

      } break;
      default:
        break;
    }
  }
  if (code == S21_ARITHMETIC_BIG && s21_get_sign(*result) == 1) {
    code = S21_ARITHMETIC_SMALL;
  }
  return code;
}

int sub_algorithm(s21_decimal value_1, s21_decimal value_2,
                  decimal_bit_3 bit_3_1, decimal_bit_3 bit_3_2,
                  s21_decimal *result) {
  int code = S21_ARITHMETIC_OK;
  s21_long_decimal value_long_1 = s21_long_decimal_set_zero(),
                   value_long_2 = s21_long_decimal_set_zero();
  from_decimal_to_long_decimal(value_1, &value_long_1);
  from_decimal_to_long_decimal(value_2, &value_long_2);
  s21_long_decimal_normalize(&value_long_1, &value_long_2, bit_3_1.power,
                             bit_3_2.power);
  s21_long_decimal result_long =
      s21_long_decimal_binary_sub(value_long_1, value_long_2);
  int max_pow = s21_max_pow(bit_3_1.power, bit_3_2.power);
  // Дальше идут проверки и запись в decimal
  // Смотрим насколько надо поделить результат, чтобы он влез в decimal
  if (s21_long_decimal_fit_in_decimal(result_long)) {
    from_long_decimal_to_decimal(result_long, result);
    s21_set_scale(result, max_pow);
  } else {
    int pow_of_ten = s21_long_decimal_shift_to_decimal(result_long);

    int res_pow = max_pow - pow_of_ten;

    if (res_pow >= 0) {
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
  }
  return code;
}
