#include "helper.h"
#include "helper_arithmetic.h"

/* Возвращает целые цифры указанного Decimal числа; любые дробные цифры
 * отбрасываются, включая конечные нули. */
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int exit_code = 0;
  s21_long_decimal long_decimal = {{0}};
  decimal_bit_3 bit_3;
  s21_decimal_get_bit_3(value, &bit_3);
  s21_long_decimal ten_pows = s21_long_decimal_ten_pows(bit_3.power);
  s21_long_decimal remainder = {{0}};
  from_decimal_to_long_decimal(value, &long_decimal);
  if (bit_3.power != 0) {
    s21_long_decimal result_long =
        s21_long_decimal_binary_div(long_decimal, ten_pows, &remainder);
    // s21_set_sign_long(&result_long, bit_3.sign);
    from_long_decimal_to_decimal(result_long, result);
    s21_set_sign(result, bit_3.sign);
  } else {
    *result = value;
  }
  return exit_code;
}
