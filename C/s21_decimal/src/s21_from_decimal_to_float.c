#include "helper.h"
#include "helper_arithmetic.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int exit_code = 0;
  decimal_bit_3 bit_3;
  s21_decimal_get_bit_3(src, &bit_3);
  double a = 0.0;
  for (int i = 0; i < DECIMAL_VALUE_BITS; i++) {
    if (s21_get_bit(src, i) == 1) {
      a += pow(2.0, i);
    }
  }
  for (int i = 0; i < bit_3.power; i++) {
    a /= 10.0;
  }
  if (bit_3.sign == 1) {
    a = -a;
  }
  *dst = a;
  return exit_code;
}
