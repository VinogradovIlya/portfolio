#include "helper.h"
#include "helper_arithmetic.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int exit_code = 0;
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }
  if (src < 0) {
    s21_set_sign(dst, 1);
    if (src == INT_MIN) {
      dst->bits[0] = (unsigned int)(-(src + 1)) + 1;
    } else {
      dst->bits[0] = -src;
    }
  } else {
    dst->bits[0] = src;
  }
  return exit_code;
}
