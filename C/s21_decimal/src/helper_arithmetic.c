#include "helper_arithmetic.h"

#include <stdio.h>

#include "helper.h"
#include "s21_decimal.h"

s21_long_decimal s21_long_decimal_set_zero(void) {
  s21_long_decimal result = {{0}};
  return result;
}

s21_long_decimal s21_long_decimal_zero_five(void) {
  s21_long_decimal result = {{0x5, 0, 0, 0, 0, 0, 0, 0x10000}};
  return result;
}

s21_long_decimal s21_long_decimal_set_one(void) {
  s21_long_decimal result = {{1, 0, 0, 0, 0, 0, 0, 0}};
  return result;
}

s21_decimal s21_decimal_set_min(void) {
  s21_decimal result = {{0x1, 0x0, 0x0, 0x1C0000}};

  return result;
}

s21_decimal s21_decimal_get_inf(void) {
  s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  return result;
}
/*Проверяем ноль ли мантиса.
1 - мантиса равна 0.
0 - мантиса не равна 0.
 */
int s21_long_decimal_zero_mantissa(s21_long_decimal value) {
  int rezult = 1;

  for (int i = 0; i < 7 && rezult == 1; i++) {
    if (value.bits[i] != 0) {
      rezult = 0;
    }
  }
  return rezult;
}
/*Проверяем помещается ли long_decimal в decimal.
0 - нет.
1 - да.
*/
int s21_long_decimal_fit_in_decimal(s21_long_decimal value) {
  int result = 1;
  if (value.bits[3] != 0) {
    result = 0;
  }
  if (value.bits[4] != 0) {
    result = 0;
  }
  if (value.bits[5] != 0) {
    result = 0;
  }
  if (value.bits[6] != 0) {
    result = 0;
  }
  return result;
  ;
}
/**combo_sing_decimal
Смотрим какие знаки у чисел, для выбора дальнейшего действия.
1 = - -.
2 = - +.
3 = + -.
4 = + +.
 */
int combo_sing_decimal(int sing_1, int sing_2) {
  int code = 1;
  if (sing_1 && !sing_2) {
    code = 2;
  }
  if (!sing_1 && sing_2) {
    code = 3;
  }
  if (!sing_1 && !sing_2) {
    code = 4;
  }
  return code;
}

s21_long_decimal s21_long_decimal_logic_and(s21_long_decimal value_1,
                                            s21_long_decimal value_2) {
  s21_long_decimal result = s21_long_decimal_set_zero();

  for (unsigned i = 0; i < 7; i++) {
    result.bits[i] = value_1.bits[i] & value_2.bits[i];
  }

  result.bits[7] = value_1.bits[7];
  return result;
}
// Исключающие "или", 1 когда только один из битов 1
s21_long_decimal s21_long_decimal_logic_xor(s21_long_decimal value_1,
                                            s21_long_decimal value_2) {
  s21_long_decimal result = s21_long_decimal_set_zero();
  for (unsigned i = 0; i < 7; i++) {
    result.bits[i] = value_1.bits[i] ^ value_2.bits[i];
  }
  result.bits[7] = value_1.bits[7];
  return result;
}

s21_long_decimal s21_long_decimal_logic_not(s21_long_decimal value) {
  s21_long_decimal result = s21_long_decimal_set_zero();
  for (unsigned i = 0; i < 7; i++) {
    result.bits[i] = ~value.bits[i];
  }
  result.bits[7] = value.bits[7];
  return result;
}

s21_long_decimal s21_long_decimal_mult_10(s21_long_decimal value) {
  s21_long_decimal mult_2 = value, mult_8 = value;
  decimal_bit_3 bit_3 = {0, 0, 0, 0};
  s21_long_decimal_get_bit_3(value, &bit_3);
  s21_shift_left(&mult_2, 1);

  s21_shift_left(&mult_8, 3);

  s21_long_decimal result = s21_long_decimal_binary_add(mult_8, mult_2);

  bit_3.power = bit_3.power + 1;
  s21_long_decimal_set_bit_3(&result, bit_3);

  return result;
}

s21_long_decimal s21_long_decimal_binary_add(s21_long_decimal value_1,
                                             s21_long_decimal value_2) {
  s21_long_decimal result = value_1;
  s21_long_decimal tmp = value_2;

  while (!s21_long_decimal_zero_mantissa(tmp)) {
    s21_long_decimal memory_bit = s21_long_decimal_logic_and(result, tmp);
    s21_shift_left(&memory_bit, 1);
    result = s21_long_decimal_logic_xor(result, tmp);
    tmp = memory_bit;
  }
  return result;
}

s21_long_decimal s21_long_decimal_binary_sub(s21_long_decimal value_1,
                                             s21_long_decimal value_2) {
  s21_long_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};
  value_2 = s21_long_decimal_logic_not(value_2);
  value_2 = s21_long_decimal_binary_add(value_2, one);
  s21_long_decimal result = s21_long_decimal_binary_add(value_1, value_2);
  return result;
}

s21_long_decimal s21_long_decimal_binary_mul(s21_decimal value_1,
                                             s21_decimal value_2) {
  s21_long_decimal result = {{0}};
  s21_long_decimal tmp_value_1 = {{0}};

  from_decimal_to_long_decimal(value_1, &tmp_value_1);

  int max_bit_value_2 = s21_decimal_get_high_bit_not_zero(value_2);

  for (int i = 0; i <= max_bit_value_2; i++) {
    if (s21_get_bit(value_2, i)) {
      result = s21_long_decimal_binary_add(result, tmp_value_1);
    }
    s21_shift_left(&tmp_value_1, 1);
  }

  return result;
}

s21_long_decimal s21_long_decimal_binary_div(s21_long_decimal value_1,
                                             s21_long_decimal value_2,
                                             s21_long_decimal *remainder) {
  s21_long_decimal result = s21_long_decimal_set_zero();
  // Частичный остаток
  s21_long_decimal partial_remainder = value_1;
  // Частное
  s21_long_decimal quotient = s21_long_decimal_set_zero();
  int code_exit = 0;

  // Если делимое 0
  if (s21_long_decimal_zero_mantissa(value_1)) {
    code_exit = 1;
  }

  //  Если делитель больше делимого
  if (s21_long_decimal_binary_compare(value_1, value_2) == -1) {
    code_exit = 1;
    if (remainder != NULL) {
      *remainder = value_1;
    }
  }

  if (!code_exit) {
    int max_bit_1 = s21_long_decimal_get_high_bit_not_zero(value_1);
    int max_bit_2 = s21_long_decimal_get_high_bit_not_zero(value_2);
    int shift = max_bit_1 - max_bit_2;
    // делитель свинутый и тем самым умноженный на 2 в степени сдвига
    s21_long_decimal shifted_divisor = value_2;
    s21_long_set_scale(&shifted_divisor, 0);
    s21_shift_left_more_31(&shifted_divisor, shift);

    int need_sub = 1;
    if (s21_long_decimal_binary_compare(partial_remainder, shifted_divisor) ==
        -1) {
      shift -= 1;
      s21_shift_right(&shifted_divisor, 1);
    }

    while (shift >= 0) {
      s21_shift_left(&quotient, 1);
      if (need_sub == 1) {
        partial_remainder =
            s21_long_decimal_binary_sub(partial_remainder, shifted_divisor);

        s21_set_bit_long(&quotient, 0, 1);
      }
      s21_shift_right(&shifted_divisor, 1);
      if (shift >= 75 && shift <= 80) {
      }
      // Сравнение partial_remainder и shifted_divisor

      if (s21_long_decimal_binary_compare(partial_remainder, shifted_divisor) ==
          -1) {
        // заходим если остаток меньше shifted_divisor
        need_sub = 0;
      } else {
        need_sub = 1;
      }

      --shift;
    }
    if (remainder != NULL) {
      *remainder = partial_remainder;
    }
    result = quotient;
  }
  return result;
}
/*div_remainder_not_equal_0.
Расчитываем остаток от деления и добавляем в quotient.
Расчитываем остаток который не влез.
Округляем результат.
*/
void div_remainder_not_equal_0(s21_long_decimal quotient,
                               s21_long_decimal divisor,
                               s21_long_decimal remainder,
                               s21_decimal *result) {
  int pow_1 = div_calc_fractional(&quotient, divisor, &remainder);

  s21_long_decimal tmp_remainder = {{0}};
  int pow_2 = div_calc_fractional(&tmp_remainder, divisor, &remainder);

  s21_long_set_scale(&tmp_remainder, pow_2);
  s21_long_decimal zero_five = s21_long_decimal_zero_five();
  s21_long_decimal_normalize(&tmp_remainder, &zero_five, pow_2, 1);

  if (s21_long_decimal_binary_compare(tmp_remainder, zero_five) == 0) {
    if (!s21_long_decimal_zero_mantissa(remainder)) {
      s21_decimal tmp_decimal = {{0}};
      from_long_decimal_to_decimal(tmp_remainder, &tmp_decimal);
      s21_add(tmp_decimal, s21_decimal_set_min(), &tmp_decimal);
      from_decimal_to_long_decimal(tmp_decimal, &tmp_remainder);
    }
  }

  quotient = s21_long_decimal_banking_round(quotient, tmp_remainder);
  s21_long_set_scale(&quotient, pow_1);

  from_long_decimal_to_decimal(quotient, result);
}
/*div_calc_fractional.
Рсчитываем остаток от деления сразу плюсуем в quotient.
В remaider обновляем новый остаток, который не помещается в decimal.
Remainder дальше используется для округления.
*/
int div_calc_fractional(s21_long_decimal *quotient, s21_long_decimal divisor,
                        s21_long_decimal *remainder) {
  int pow = 0;
  s21_long_decimal tmp_quotient = *quotient;

  s21_long_decimal tmp_remainder = *remainder;
  int exit_while = 0;

  while (!s21_long_decimal_zero_mantissa(tmp_remainder) && pow < 28 &&
         !exit_while) {
    s21_long_decimal saved_quotient = tmp_quotient;
    s21_long_decimal saved_remainder = tmp_remainder;
    tmp_quotient = s21_long_decimal_mult_10(tmp_quotient);
    tmp_remainder = s21_long_decimal_mult_10(tmp_remainder);
    s21_long_decimal tmp =
        s21_long_decimal_binary_div(tmp_remainder, divisor, &tmp_remainder);
    tmp_quotient = s21_long_decimal_binary_add(tmp_quotient, tmp);

    if (!s21_long_decimal_fit_in_decimal(tmp_quotient)) {
      tmp_quotient = saved_quotient;
      tmp_remainder = saved_remainder;
      exit_while = 1;
    } else {
      pow++;
    }
  }
  *quotient = tmp_quotient;
  *remainder = tmp_remainder;
  return pow;
}

int s21_max_pow(int pow_1, int pow_2) {
  int result = pow_1;
  if (pow_2 > pow_1) {
    result = pow_2;
  }
  return result;
}

void s21_long_decimal_normalize(s21_long_decimal *value_1,
                                s21_long_decimal *value_2, int power_1,
                                int power_2) {
  if (power_1 > power_2) {
    int diff_power = power_1 - power_2;
    while (diff_power) {
      *value_2 = s21_long_decimal_mult_10(*value_2);
      diff_power -= 1;
    }
  }
  if (power_2 > power_1) {
    int diff_power = power_2 - power_1;
    while (diff_power) {
      *value_1 = s21_long_decimal_mult_10(*value_1);
      diff_power -= 1;
    }
  }
}

s21_long_decimal s21_long_decimal_ten_pows(int pow) {
  s21_long_decimal result = s21_long_decimal_set_zero();
  if (pow < 13) {
    ten_pows_0_12(&result, pow);
  }
  if (pow >= 13 && pow < 23) {
    ten_pows_13_22(&result, pow);
  }
  if (pow > 22 && pow < 31) {
    ten_pows_23_30(&result, pow);
  }
  if (pow > 30) {
    ten_pows_31_38(&result, pow);
  }
  return result;
}
void ten_pows_0_12(s21_long_decimal *value, int pow) {
  switch (pow) {
    case 0:
      value->bits[0] = 0x1;
      break;
    case 1:
      value->bits[0] = 0xa;
      break;
    case 2:
      value->bits[0] = 0x64;
      break;
    case 3:
      value->bits[0] = 0x3e8;
      break;
    case 4:
      value->bits[0] = 0x2710;
      break;
    case 5:
      value->bits[0] = 0x186a0;
      break;
    case 6:
      value->bits[0] = 0xf4240;
      break;
    case 7:
      value->bits[0] = 0x989680;
      break;
    case 8:
      value->bits[0] = 0x5f5e100;
      break;
    case 9:
      value->bits[0] = 0x3b9aca00;
      break;
    case 10:
      value->bits[0] = 0x540be400;
      value->bits[1] = 0x2;
      break;
    case 11:
      value->bits[0] = 0x4876e800;
      value->bits[1] = 0x17;
      break;
    case 12:
      value->bits[0] = 0xd4a51000;
      value->bits[1] = 0xe8;
      break;
    default:
      break;
  }
}
void ten_pows_13_22(s21_long_decimal *value, int pow) {
  switch (pow) {
    case 13:
      value->bits[0] = 0x4e72a000;
      value->bits[1] = 0x918;
      break;
    case 14:
      value->bits[0] = 0x107a4000;
      value->bits[1] = 0x5af3;
      break;
    case 15:
      value->bits[0] = 0xa4c68000;
      value->bits[1] = 0x38d7e;
      break;
    case 16:
      value->bits[0] = 0x6fc10000;
      value->bits[1] = 0x2386f2;
      break;
    case 17:
      value->bits[0] = 0x5d8a0000;
      value->bits[1] = 0x1634578;
      break;
    case 18:
      value->bits[0] = 0xa7640000;
      value->bits[1] = 0xde0b6b3;
      break;
    case 19:
      value->bits[0] = 0x89e80000;
      value->bits[1] = 0x8ac72304;
      break;
    case 20:
      value->bits[0] = 0x63100000;
      value->bits[1] = 0x6bc75e2d;
      value->bits[2] = 0x5;
      break;
    case 21:
      value->bits[0] = 0xdea00000;
      value->bits[1] = 0x35c9adc5;
      value->bits[2] = 0x36;
      break;
    case 22:
      value->bits[0] = 0xb2400000;
      value->bits[1] = 0x19e0c9ba;
      value->bits[2] = 0x21e;
      break;
    default:
      break;
  }
}
void ten_pows_23_30(s21_long_decimal *value, int pow) {
  switch (pow) {
    case 23:
      value->bits[0] = 0xf6800000;
      value->bits[1] = 0x2c7e14a;
      value->bits[2] = 0x152d;
      break;
    case 24:
      value->bits[0] = 0xa1000000;
      value->bits[1] = 0x1bcecced;
      value->bits[2] = 0xd3c2;
      break;
    case 25:
      value->bits[0] = 0x4a000000;
      value->bits[1] = 0x16140148;
      value->bits[2] = 0x84595;
      break;
    case 26:
      value->bits[0] = 0xe4000000;
      value->bits[1] = 0xdcc80cd2;
      value->bits[2] = 0x52b7d2;
      break;
    case 27:
      value->bits[0] = 0xe8000000;
      value->bits[1] = 0x9fd0803c;
      value->bits[2] = 0x33b2e3c;
      break;
    case 28:
      value->bits[0] = 0x10000000;
      value->bits[1] = 0x3e250261;
      value->bits[2] = 0x204fce5e;
      break;
    case 29:
      value->bits[0] = 0xa0000000;
      value->bits[1] = 0x6d7217ca;
      value->bits[2] = 0x431e0fae;
      value->bits[3] = 0x1;
      break;
    case 30:
      value->bits[0] = 0x40000000;
      value->bits[1] = 0x4674edea;
      value->bits[2] = 0x9f2c9cd0;
      value->bits[3] = 0xc;
      break;
    default:
      break;
  }
}

void ten_pows_31_38(s21_long_decimal *value, int pow) {
  switch (pow) {
    case 31:
      value->bits[0] = 0x80000000;
      value->bits[1] = 0xc0914b26;
      value->bits[2] = 0x37be2022;
      value->bits[3] = 0x7e;
      break;
    case 32:
      value->bits[1] = 0x85acef81;
      value->bits[2] = 0x2d6d415b;
      value->bits[3] = 0x4ee;
      break;
    case 33:
      value->bits[1] = 0x38c15b0a;
      value->bits[2] = 0xc6448d93;
      value->bits[3] = 0x314d;
      break;
    case 34:
      value->bits[1] = 0x378d8e64;
      value->bits[2] = 0xbead87c0;
      value->bits[3] = 0x1ed09;
      break;
    case 35:
      value->bits[1] = 0x2b878fe8;
      value->bits[2] = 0x72c74d82;
      value->bits[3] = 0x134261;
      break;
    case 36:
      value->bits[1] = 0xb34b9f10;
      value->bits[2] = 0x7bc90715;
      value->bits[3] = 0xc097ce;
      break;
    case 37:
      value->bits[1] = 0xf436a0;
      value->bits[2] = 0xd5da46d9;
      value->bits[3] = 0x785ee10;
      break;
    case 38:
      value->bits[1] = 0x98a2240;
      value->bits[2] = 0x5a86c47a;
      value->bits[3] = 0x4b3b4ca8;
      break;
    default:
      break;
  }
}

/**s21_long_decimal_binary_compare.
Сравнивает побитово, игнорируем степень и знак
  -1 - value_1 меньше value_2.
   0 - value_1 value_2 равны.
   1 - value_1 больше value_2.
*/
int s21_long_decimal_binary_compare(s21_long_decimal value_1,
                                    s21_long_decimal value_2) {
  int result = 0;

  for (int i = LONG_DECIMAL_VALUE_BITS - 1; i >= 0 && result == 0; i--) {
    int bit_1 = s21_get_bit_long(value_1, i);
    int bit_2 = s21_get_bit_long(value_2, i);

    if (bit_1 == 0 && bit_2 == 1) {
      result = -1;
    }
    if (bit_1 == 1 && bit_2 == 0) {
      result = 1;
    }
  }

  return result;
}
// Считаем сколько раз надо поделить на 10, чтобы влезло в decimal
int s21_long_decimal_shift_to_decimal(s21_long_decimal value) {
  int result_shift = 0;

  if (!s21_long_decimal_zero_mantissa(value)) {
    s21_long_decimal max = {
        {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0, 0, 0, 0, 0}};

    s21_long_decimal quotien_of_max =
        s21_long_decimal_binary_div(value, max, NULL);

    while (s21_long_decimal_binary_compare(
               quotien_of_max, s21_long_decimal_ten_pows(result_shift)) >= 0) {
      ++result_shift;
    }
  }
  return result_shift;
}
/*
void print_switch_ten_pow(void) {
  s21_long_decimal dec = s21_long_decimal_set_zero();
  dec.bits[0] = 0x1;
  for (int i = 0; i < 40; i++) {
    printf("case %d:\n", i);
    if (dec.bits[0] != 0) {
      printf(" value->bits[0] = 0x%x;\n", dec.bits[0]);
    }
    if (dec.bits[1] != 0) {
      printf(" value->bits[1] = 0x%x;\n", dec.bits[1]);
    }
    if (dec.bits[2] != 0) {
      printf(" value->bits[2] = 0x%x;\n", dec.bits[2]);
    }
    if (dec.bits[3] != 0) {
      printf(" value->bits[3] = 0x%x;\n", dec.bits[3]);
    }
    if (dec.bits[4] != 0) {
      printf(" value->bits[4] = 0x%x;\n", dec.bits[4]);
    }
    printf(" break;\n");
    dec = s21_long_decimal_mult_10(dec);
  }
}
*/
void s21_shift_left_more_31(s21_long_decimal *long_decimal, int shift_value) {
  while (shift_value > 0) {
    int tmp_shift = 0;
    if (shift_value > 31) {
      tmp_shift = 31;
    } else {
      tmp_shift = shift_value;
    }
    s21_shift_left(long_decimal, tmp_shift);
    shift_value -= 31;
  }
}
/*s21_long_decimal_banking_round.
Банковское округление, на вход целое и дробь раздельно.
Дробная часть которая не влезла.
*/
s21_long_decimal s21_long_decimal_banking_round(s21_long_decimal integer,
                                                s21_long_decimal fractional) {
  s21_long_decimal zero_fife = s21_long_decimal_zero_five();
  s21_long_decimal result = s21_long_decimal_set_zero();

  decimal_bit_3 bit_3_long_decimal = {0, 0, 0, 0};
  s21_long_decimal_get_bit_3(fractional, &bit_3_long_decimal);

  s21_long_decimal_normalize(&zero_fife, &fractional, 1,
                             bit_3_long_decimal.power);

  if (s21_long_decimal_binary_compare(zero_fife, fractional) == 0) {
    if (s21_long_decimal_even(integer)) {
      result = integer;
    } else {
      result = s21_long_decimal_binary_add(integer, s21_long_decimal_set_one());
    }
  }
  if (s21_long_decimal_binary_compare(zero_fife, fractional) == -1) {
    result = s21_long_decimal_binary_add(integer, s21_long_decimal_set_one());
  }
  if (s21_long_decimal_binary_compare(zero_fife, fractional) == 1) {
    result = integer;
  }
  return result;
}
