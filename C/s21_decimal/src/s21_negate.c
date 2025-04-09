#include "helper.h"
#include "helper_arithmetic.h"

/* Возвращает результат умножения указанного Decimal на -1 */
int s21_negate(s21_decimal value, s21_decimal *result) {
  int exit_code = 0;
  // if (result == NULL) {
  // //   exit_code = 1;
  // } else {
  *result = value;
  int sign = s21_get_sign(value);
  if (sign) {
    result->bits[3] &= ~0x80000000;
  } else {
    result->bits[3] |= 0x80000000;
  }
  // }
  return exit_code;
}
