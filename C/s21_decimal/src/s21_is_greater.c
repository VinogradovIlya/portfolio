#include "helper.h"
#include "s21_decimal.h"

int s21_is_greater(s21_decimal dec1, s21_decimal dec2) {
  return !(s21_is_less_or_equal(dec1, dec2));
}
