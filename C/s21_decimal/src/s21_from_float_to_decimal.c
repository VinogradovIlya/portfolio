
#include "helper.h"
#include "helper_arithmetic.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int exit_code = 0;
  char s[50];
  s21_decimal dec_max = {{0xffffffff, 0xffffffff, 0xffffffff, 0}},
              decimal = {{0}};
  float float_max = 0;
  s21_from_decimal_to_float(dec_max, &float_max);
  if (fabs(src) > float_max) {
    exit_code = 1;
  } else if (fabs(src) < 1e-28) {
    exit_code = 1;
    if (src == 0.0) exit_code = 0;
    *dst = decimal;
  } else {
    sprintf(s, "%E", src);
    const char *mantissa = strtok(s, "E");
    const char *exponent = strtok(NULL, "E");
    int scale = atoi(exponent);

    int mantisa = (int)(atof(mantissa) * 1000000);

    if (mantisa < 0) {
      s21_set_sign(&decimal, 1);
      mantisa = -mantisa;
    }
    decimal.bits[0] = mantisa;
    if ((scale >= -28) & (scale <= -22)) {
      s21_decimal ten_pows = {{0}};
      s21_set_scale(&decimal, 6);
      s21_long_decimal ten_pows_long = s21_long_decimal_ten_pows(-scale);
      from_long_decimal_to_decimal(ten_pows_long, &ten_pows);
      s21_div(decimal, ten_pows, dst);
    } else {
      scale -= 6;
      if (scale < 0) scale = -scale;
      s21_set_scale(&decimal, scale);
      *dst = decimal;
    }
  }
  return exit_code;
}
