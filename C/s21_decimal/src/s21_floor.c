#include "helper.h"
#include "helper_arithmetic.h"

/*
Округляет указанное Decimal число до ближайшего целого числа в сторону
отрицательной бесконечности.
*/
int s21_floor(s21_decimal value, s21_decimal *result) {
  int exit_code = 0;
  // if (result == NULL) {
  //   exit_code = 1;
  // } else {
  decimal_bit_3 bit_3;
  s21_long_decimal long_decimal = {{0}}, remainder = {{0}};
  s21_decimal_get_bit_3(value, &bit_3);
  s21_long_decimal ten_pows = s21_long_decimal_ten_pows(bit_3.power);
  from_decimal_to_long_decimal(value, &long_decimal);
  if (bit_3.power != 0) {
    s21_long_decimal result_long =
        s21_long_decimal_binary_div(long_decimal, ten_pows, &remainder);
    if (bit_3.sign == 1) {
      if (!s21_long_decimal_zero_mantissa(remainder)) {
        s21_long_decimal sum = {{0}};
        s21_long_decimal decimal_one = {{1, 0, 0, 0, 0, 0, 0, 0}};
        s21_bitwise_add(result_long, decimal_one, &sum);
        result_long = sum;
      }
    }
    // s21_set_sign_long(&result_long, bit_3.sign);
    from_long_decimal_to_decimal(result_long, result);
    s21_set_sign(result, bit_3.sign);
  }
  // }
  return exit_code;
}
