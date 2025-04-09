#include "helper.h"
#include "helper_arithmetic.h"
#include "s21_decimal.h"

int s21_is_equal(s21_decimal dec1, s21_decimal dec2) {
  /* dec1 == dec2 */
  /* Возвращаемое значение: 0 — FALSE; 1 — TRUE. */
  /* s21_decimal == NULL ? */
  int res = 1;
  int s1 = s21_get_sign(dec1);  // 0 -> + | 1 -> -
  int s2 = s21_get_sign(dec2);
  int z1 = s21_is_zero(dec1);
  int z2 = s21_is_zero(dec2);
  if (z1 == 1 && z2 == 1) {
    s1 = 0;
    s2 = 0;
  }
  if (s1 != s2) {
    res = 0;
  } else {
    decimal_bit_3 dec_bit_1 = {0, 0, 0, 0};
    decimal_bit_3 dec_bit_2 = {0, 0, 0, 0};
    s21_decimal_get_bit_3(dec1, &dec_bit_1);
    s21_decimal_get_bit_3(dec2, &dec_bit_2);
    s21_long_decimal value_long_1 = {{0}};
    s21_long_decimal value_long_2 = {{0}};
    from_decimal_to_long_decimal(dec1, &value_long_1);
    from_decimal_to_long_decimal(dec2, &value_long_2);
    s21_long_decimal_normalize(&value_long_1, &value_long_2, dec_bit_1.power,
                               dec_bit_2.power);
    for (int bit = LONG_DECIMAL_VALUE_BITS - 1; bit >= 0 && res == 1; bit--) {
      int bit1 = s21_get_bit_long(value_long_1, bit);
      int bit2 = s21_get_bit_long(value_long_2, bit);
      if (bit1 != bit2) {
        res = 0;
      }
    }
  }
  return res;
}
