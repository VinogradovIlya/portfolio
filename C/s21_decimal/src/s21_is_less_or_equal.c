#include "helper.h"
#include "s21_decimal.h"

int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2) {
  int res = 0;
  if (s21_is_equal(dec1, dec2)) {
    res = 1;
  } else if (s21_is_less(dec1, dec2)) {
    res = 1;
  }
  return res;
}