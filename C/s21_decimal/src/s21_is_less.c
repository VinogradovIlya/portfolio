#include "helper.h"
#include "helper_arithmetic.h"
#include "s21_decimal.h"

/*--------------------------------------------------
  dec1 < dec2
  Возвращаемое значение: 0 — FALSE; 1 — TRUE.
  s21_decimal == NULL ?
  dec1 dec2 s1 s2 s1 > s2 dec1 < dec2
   +    +   0  0     0         -
   +    -   0  1     0         0
   -    +   1  0     1         1
   -    -   1  1     0         -
---------------------------------------------------*/
int s21_is_less(s21_decimal dec1, s21_decimal dec2) {
  int res = 0;
  int s1 = s21_get_sign(dec1);  // 0 -> + | 1 -> -
  int s2 = s21_get_sign(dec2);

  if (s1 != s2) {
    res = s1 > s2;
    /* printf("s1 = %d | s2 = %d | res = %d\n", s1, s2, res); */
    /* printf("1\n"); */
  } else {
    /* нормализация */
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
    int finish = 0, bit1 = 0, bit2 = 0;
    for (int bit = LONG_DECIMAL_VALUE_BITS - 1; bit >= 0 && finish == 0;
         bit--) {
      bit1 = s21_get_bit_long(value_long_1, bit);
      bit2 = s21_get_bit_long(value_long_2, bit);
      if (bit1 != bit2) {
        finish = 1;
      }
    }
    if (s1 == 1) {
      res = bit1 > bit2;
    } else {
      res = bit1 < bit2;
    }
  }
  return res;
}
