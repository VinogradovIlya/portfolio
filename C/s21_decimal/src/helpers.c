#include "./helper.h"
#include "s21_decimal.h"

void s21_decimal_get_bit_3(s21_decimal decimal, decimal_bit_3 *decimal_bit_3) {
  decimal_bit_3->empty_1 = decimal.bits[3] & 0xFFFF;
  decimal_bit_3->empty_2 = (decimal.bits[3] & 0x7F000000) >> 24;
  decimal_bit_3->power = (decimal.bits[3] & 0xFF0000) >> 16;
  unsigned sign_bit = decimal.bits[3];
  decimal_bit_3->sign = (sign_bit >> 31) & 1;
}

/*void s21_decimal_set_bit_3(s21_decimal *decimal, decimal_bit_3 bit_3) {
  unsigned sign_bit = bit_3.sign;
  decimal->bits[3] = (bit_3.empty_1 & 0xFFFF) | ((bit_3.power & 0xFF) << 16) |
                     ((bit_3.empty_2 & 0x7) << 24) | ((sign_bit & 1) << 31);
}*/

void s21_long_decimal_get_bit_3(s21_long_decimal decimal,
                                decimal_bit_3 *decimal_bit_3) {
  decimal_bit_3->empty_1 = decimal.bits[7] & 0xFFFF;
  decimal_bit_3->empty_2 = (decimal.bits[7] & 0x7F000000) >> 24;
  decimal_bit_3->power = (decimal.bits[7] & 0xFF0000) >> 16;
  unsigned sign_bit = decimal.bits[7];
  decimal_bit_3->sign = (sign_bit >> 31) & 1;
}

void s21_long_decimal_set_bit_3(s21_long_decimal *decimal,
                                decimal_bit_3 bit_3) {
  unsigned sign_bit = bit_3.sign;
  decimal->bits[7] = (bit_3.empty_1 & 0xFFFF) | ((bit_3.power & 0xFF) << 16) |
                     ((bit_3.empty_2 & 0x7) << 24) | ((sign_bit & 1) << 31);
}

int s21_get_sign(s21_decimal value) {
  int sign = (value.bits[3] & 0x80000000) == 0 ? 0 : 1;
  return sign;
}

void s21_set_sign(s21_decimal *value, int sign_value) {
  if (sign_value) {
    value->bits[3] |= 0x80000000;
  } else {
    value->bits[3] &= ~0x80000000;
  }
}

int s21_get_bit(s21_decimal value, int bit) {
  int result = -1;
  // if (bit >= 0 && bit <= (DECIMAL_VALUE_BITS - 1)) {
  int index = bit / 32;
  int position = bit % 32;
  unsigned bits = value.bits[index];
  result = (bits >> position) & 1;
  // }
  // else
  //   printf("Invalid argument");
  return result;
}

int s21_get_bit_long(s21_long_decimal value, int bit) {
  int result = -1;
  // if (bit >= 0 && bit <= (LONG_DECIMAL_VALUE_BITS - 1)) {
  int index = bit / 32;
  int position = bit % 32;
  unsigned bits = value.bits[index];
  result = (bits >> position) & 1;
  // }
  // else
  //   printf("Invalid argument");
  return result;
}

/*void s21_set_bit(s21_decimal *decimal, int bit, unsigned value) {
  if (bit >= 0 && bit <= (DECIMAL_VALUE_BITS - 1) &&
      (value == 1 || value == 0)) {
    int index = bit / 32;
    int position = bit % 32;
    if (value)
      decimal->bits[index] |= 1U << position;
    else
      decimal->bits[index] &= ~(1U << position);
  } else
    printf("Invalid arguments");
}*/

void s21_set_bit_long(s21_long_decimal *long_decimal, int bit, unsigned value) {
  // if (bit >= 0 && (bit <= LONG_DECIMAL_VALUE_BITS - 1) &&
  //     (value == 1 || value == 0)) {
  int index = bit / 32;
  int position = bit % 32;
  if (value)
    long_decimal->bits[index] |= 1U << position;
  else
    long_decimal->bits[index] &= ~(1U << position);
  // }
  // else
  //   printf("Invalid arguments");
}

void s21_set_scale(s21_decimal *decimal, int power_value) {
  if (power_value >= 0 && power_value <= 28) {
    decimal->bits[3] &= ~(0xFF << 16);
    decimal->bits[3] |= power_value << 16;
  }
  // else
  //   printf("Invalid power_value\n");
}

void s21_long_set_scale(s21_long_decimal *long_decimal, int power_value) {
  if (power_value >= 0 && power_value <= 100) {
    long_decimal->bits[7] &= ~(0xFF << 16);
    long_decimal->bits[7] |= power_value << 16;
  }
  // else
  //   printf("Invalid power_value\n");
}

int s21_is_zero(s21_decimal decimal) {
  return (decimal.bits[0] == 0 && decimal.bits[1] == 0 && decimal.bits[2] == 0)
             ? 1
             : 0;
}

void s21_shift_left(s21_long_decimal *long_decimal, int shift_value) {
  if (shift_value < 32 && shift_value > 0) {
    unsigned memory = 0;
    for (int i = 0; i < LONG_DECIMAL_VALUE_BITS / INT_BITS; ++i) {
      unsigned temp = long_decimal->bits[i];
      unsigned temp_long = long_decimal->bits[i];
      temp_long <<= shift_value;
      temp_long |= memory;
      long_decimal->bits[i] = temp_long;
      memory = temp >> (32 - shift_value);
    }
  }
  // else
  //   printf("invalid shift_value\n");
}

void s21_shift_right(s21_long_decimal *long_decimal, int shift_value) {
  if (shift_value < 32 && shift_value > 0) {
    unsigned memory = 0;
    for (int i = LONG_DECIMAL_VALUE_BITS / INT_BITS; i >= 0; i--) {
      unsigned temp = long_decimal->bits[i];
      // тут другая запись, так как правый сдвиг для знаковых по другому
      // работает
      long_decimal->bits[i] = temp >> shift_value;
      long_decimal->bits[i] |= memory;
      memory = temp << (32 - shift_value);
    }
  }
  // else
  //   printf("invalid shift_value\n");
}

void s21_bitwise_add(s21_long_decimal value_1, s21_long_decimal value_2,
                     s21_long_decimal *result) {
  unsigned memory = 0;
  for (int i = 0; i < LONG_DECIMAL_VALUE_BITS - 1; i++) {
    unsigned result_bit =
        s21_get_bit_long(value_1, i) + s21_get_bit_long(value_2, i) + memory;
    memory = result_bit / 2;
    s21_set_bit_long(result, i, result_bit % 2);
  }
}

// void s21_bitwise_add(s21_long_decimal value_1, s21_long_decimal value_2,
//                      s21_long_decimal *result) {
//   unsigned int memory = 0;
//   for (int i = 0; i < 7; i++) {
//     unsigned int sum = value_1.bits[i] + value_2.bits[i] + memory;
//     memory = (sum < value_1.bits[i] || sum < value_2.bits[i]);
//     result->bits[i] = sum;
//   }
// }

/*void s21_mult_by_10(s21_long_decimal long_decimal, s21_long_decimal *result) {
  s21_long_decimal mult_by_2 = long_decimal, mult_by_8 = long_decimal;
  s21_shift_left(&mult_by_2, 1);
  s21_shift_left(&mult_by_8, 3);
  s21_bitwise_add(mult_by_2, mult_by_8, result);
}*/
/*
void print_long_decimal(s21_long_decimal decimal) {
  printf("====Long++++Decimal====\n");
  for (int i = 0; i < 8; i++) {
    printf("bits[%d]:", i);
    print_bits(decimal.bits[i]);
  }
}
*/
// void print_decimal(s21_decimal decimal) {
//   printf("====Decimal====\n");
//   for (int i = 0; i < 4; i++) {
//     printf("bits[%d]:", i);
//     print_bits(decimal.bits[i]);
//   }
// }

// void print_bits(unsigned n) {
//   int bits = sizeof(n) * 8;
//   for (int i = bits - 1; i >= 0; i--) {
//     unsigned bit = (n >> i) & 1;
//     printf("%u", bit);
//     if (i % 4 == 0) {
//       printf(" ");
//     }
//   }
//   printf("\n");
// }

void from_decimal_to_long_decimal(s21_decimal decimal,
                                  s21_long_decimal *long_decimal) {
  for (int i = 0; i < 3; i++) {
    long_decimal->bits[i] = decimal.bits[i];
  }
  long_decimal->bits[7] = decimal.bits[3];

  for (int i = 3; i < 7; i++) {
    long_decimal->bits[i] = 0;
  }
}

void from_long_decimal_to_decimal(s21_long_decimal long_decimal,
                                  s21_decimal *decimal) {
  decimal->bits[0] = long_decimal.bits[0];
  decimal->bits[1] = long_decimal.bits[1];
  decimal->bits[2] = long_decimal.bits[2];
  decimal->bits[3] = long_decimal.bits[7];
}

int s21_correct_decimal(s21_decimal decimal) {
  int code = 1;
  decimal_bit_3 bit_3;
  s21_decimal_get_bit_3(decimal, &bit_3);
  if (bit_3.empty_1 > 0 || bit_3.empty_2 > 0) {
    code = 0;
  }
  if (code == 1 && bit_3.power > 28) {
    code = 0;
  }
  return code;
}

int s21_long_decimal_get_high_bit_not_zero(s21_long_decimal value) {
  int result = -1;

  for (int i = 223; i >= 0 && result == -1; i--) {
    if (s21_get_bit_long(value, i)) {
      result = i;
    }
  }

  return result;
}

int s21_decimal_get_high_bit_not_zero(s21_decimal value) {
  int result = -1;

  for (int i = 95; i >= 0 && result == -1; i--) {
    if (s21_get_bit(value, i)) {
      result = i;
    }
  }

  return result;
}
/*Проверяем на четность.
1 - четное.
0 - нечетное.
*/
int s21_long_decimal_even(s21_long_decimal value) {
  int result = 1;
  if (value.bits[0] & 1) {
    result = 0;
  }
  return result;
}

s21_decimal s21_abs(s21_decimal value_1) {
  s21_decimal result = value_1;
  s21_set_sign(&result, 0);
  return result;
}