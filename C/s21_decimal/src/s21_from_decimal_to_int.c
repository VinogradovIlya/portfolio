#include "helper.h"
#include "helper_arithmetic.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int exit_code = 0;
  s21_decimal truncate = {{0}};

  s21_truncate(src, &truncate);
  if (truncate.bits[1] != 0 || truncate.bits[2] != 0) {
    exit_code = 1;
  } else {
    if (s21_get_sign(src) == 0) {  // if positive
      if ((unsigned)truncate.bits[0] > (unsigned)INT_MAX) {
        exit_code = 1;
      } else {
        *dst = (int)truncate.bits[0];
      }
    } else {
      // if negative
      if ((unsigned)truncate.bits[0] > (unsigned)INT_MAX + 1) {
        exit_code = 1;
      } else {
        *dst = -(int)truncate.bits[0];
      }
    }
  }
  return exit_code;
}
