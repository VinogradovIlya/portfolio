#include "helper.h"
#include "helper_arithmetic.h"

/* Округляет Decimal до ближайшего целого числа. */
int s21_round(s21_decimal value, s21_decimal *result) {
  int exit_code = 0;
  s21_long_decimal long_decimal = {{0}}, remainder_1 = {{0}},
                   remainder_2 = {{0}};
  decimal_bit_3 bit_3;
  s21_decimal_get_bit_3(value, &bit_3);
  if (bit_3.power != 0) {
    s21_long_decimal ten_pows = s21_long_decimal_ten_pows(bit_3.power - 1);
    s21_long_decimal ten = s21_long_decimal_ten_pows(1);
    from_decimal_to_long_decimal(value, &long_decimal);
    s21_long_decimal div =
        s21_long_decimal_binary_div(long_decimal, ten_pows, &remainder_1);
    if (s21_long_decimal_binary_compare(div, ten) == -1 &&
        !s21_long_decimal_zero_mantissa(div)) {
      remainder_2 = div;
      div = s21_long_decimal_binary_div(div, ten, &remainder_1);
    } else {
      div = s21_long_decimal_binary_div(div, ten, &remainder_2);
    }
    s21_long_decimal sum = {{0}};
    if (remainder_2.bits[0] >= 5) {
      s21_long_decimal decimal_one = {{1, 0, 0, 0, 0, 0, 0, 0}};
      s21_bitwise_add(div, decimal_one, &sum);
    } else {
      sum = div;
    }
    from_long_decimal_to_decimal(sum, result);
    s21_set_sign(result, bit_3.sign);
  } else {
    *result = value;
  }
  return exit_code;
}
