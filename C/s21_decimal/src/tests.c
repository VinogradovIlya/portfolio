#include <check.h>

#include "helper.h"
#include "helper_arithmetic.h"
#include "s21_decimal.h"
// #define DEBUG 1

void test_add(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_add_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_sub(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_sub_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_mul_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_div(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_div_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
/* тесты сравнения */
START_TEST(test_s21_is_less) {
  s21_decimal dec1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal dec2 = {{0x00000001, 0x00000001, 0x00000001, 0x00000000}};
  ck_assert_int_eq(s21_is_less(dec1, dec2), 0);
  ck_assert_int_eq(s21_is_less(dec2, dec1), 1);

  s21_decimal dec3 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal dec4 = {{0x00000001, 0x00000001, 0x00000001, 0x80000000}};
  ck_assert_int_eq(s21_is_less(dec3, dec4), 1);
  ck_assert_int_eq(s21_is_less(dec4, dec3), 0);

  s21_decimal dec5 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal dec6 = {{0x00000001, 0x00000001, 0x00000001, 0x80000000}};
  ck_assert_int_eq(s21_is_less(dec5, dec6), 0);
  ck_assert_int_eq(s21_is_less(dec6, dec5), 1);

  s21_decimal dec7 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00050000}};
  s21_decimal dec8 = {{0x00000001, 0x00000001, 0x00000001, 0x00020000}};
  ck_assert_int_eq(s21_is_less(dec7, dec8), 0);
  ck_assert_int_eq(s21_is_less(dec8, dec7), 1);

  s21_decimal dec9 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80030000}};
  s21_decimal dec10 = {{0x00000001, 0x00000001, 0x00000001, 0x80040000}};
  ck_assert_int_eq(s21_is_less(dec9, dec10), 1);
  ck_assert_int_eq(s21_is_less(dec10, dec9), 0);

  s21_decimal dec11 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00020000}};
  s21_decimal dec12 = {{0x00000001, 0x00000001, 0x00000001, 0x80030000}};
  ck_assert_int_eq(s21_is_less(dec11, dec12), 0);
  ck_assert_int_eq(s21_is_less(dec12, dec11), 1);

  s21_decimal dec13 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal dec14 = {{0xfffffffe, 0xffffffff, 0xffffffff, 0x00000000}};
  ck_assert_int_eq(s21_is_less(dec13, dec14), 0);
  ck_assert_int_eq(s21_is_less(dec14, dec13), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal) {
  s21_decimal dec1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal dec2 = {{0x00000001, 0x00000001, 0x00000001, 0x00000000}};
  ck_assert_int_eq(s21_is_less_or_equal(dec1, dec2), 0);
  ck_assert_int_eq(s21_is_less_or_equal(dec2, dec1), 1);

  s21_decimal dec3 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal dec4 = {{0x00000001, 0x00000001, 0x00000001, 0x80000000}};
  ck_assert_int_eq(s21_is_less_or_equal(dec3, dec4), 1);
  ck_assert_int_eq(s21_is_less_or_equal(dec4, dec3), 0);

  s21_decimal dec5 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal dec6 = {{0x00000001, 0x00000001, 0x00000001, 0x80000000}};
  ck_assert_int_eq(s21_is_less_or_equal(dec5, dec6), 0);
  ck_assert_int_eq(s21_is_less_or_equal(dec6, dec5), 1);

  s21_decimal dec7 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal dec8 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  ck_assert_int_eq(s21_is_less_or_equal(dec7, dec8), 1);

  s21_decimal dec9 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00040000}};
  s21_decimal dec10 = {{0x00000001, 0x00000001, 0x00000001, 0x00030000}};
  ck_assert_int_eq(s21_is_less_or_equal(dec9, dec10), 0);
  ck_assert_int_eq(s21_is_less_or_equal(dec10, dec9), 1);

  s21_decimal dec11 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80020000}};
  s21_decimal dec12 = {{0x00000001, 0x00000001, 0x00000001, 0x80030000}};
  ck_assert_int_eq(s21_is_less_or_equal(dec11, dec12), 1);
  ck_assert_int_eq(s21_is_less_or_equal(dec12, dec11), 0);

  s21_decimal dec13 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00040000}};
  s21_decimal dec14 = {{0x00000001, 0x00000001, 0x00000001, 0x80020000}};
  ck_assert_int_eq(s21_is_less_or_equal(dec13, dec14), 0);
  ck_assert_int_eq(s21_is_less_or_equal(dec14, dec13), 1);
}
END_TEST

START_TEST(test_s21_is_greater) {
  s21_decimal dec1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal dec2 = {{0x00000001, 0x00000001, 0x00000001, 0x00000000}};
  ck_assert_int_eq(s21_is_greater(dec1, dec2), 1);
  ck_assert_int_eq(s21_is_greater(dec2, dec1), 0);

  s21_decimal dec3 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal dec4 = {{0x00000001, 0x00000001, 0x00000001, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(dec3, dec4), 0);
  ck_assert_int_eq(s21_is_greater(dec4, dec3), 1);

  s21_decimal dec5 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal dec6 = {{0x00000001, 0x00000001, 0x00000001, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(dec5, dec6), 1);
  ck_assert_int_eq(s21_is_greater(dec6, dec5), 0);

  s21_decimal dec7 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal dec8 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  ck_assert_int_eq(s21_is_greater(dec7, dec8), 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal) {
  s21_decimal dec1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal dec2 = {{0x00000001, 0x00000001, 0x00000001, 0x00000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(dec2, dec1), 0);

  s21_decimal dec3 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal dec4 = {{0x00000001, 0x00000001, 0x00000001, 0x80000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(dec3, dec4), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(dec4, dec3), 1);

  s21_decimal dec5 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal dec6 = {{0x00000001, 0x00000001, 0x00000001, 0x80000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(dec5, dec6), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(dec6, dec5), 0);

  s21_decimal dec7 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal dec8 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(dec7, dec8), 1);

  s21_decimal dec9 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal dec10 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(dec9, dec10), 1);
  // -26409387498605864508043122005
  s21_decimal dec11 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  s21_set_sign(&dec11, 1);
  // -79228162514264337593543950334
  s21_decimal dec12 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&dec12, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(dec11, dec12), 1);
}
END_TEST

START_TEST(test_s21_is_equal) {
  s21_decimal dec0 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal dec00 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  ck_assert_int_eq(s21_is_equal(dec0, dec00), 1);

  s21_decimal dec1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal dec2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  ck_assert_int_eq(s21_is_equal(dec1, dec2), 0);

  s21_decimal dec3 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00050000}};
  s21_decimal dec4 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00060000}};
  ck_assert_int_eq(s21_is_equal(dec3, dec4), 0);

  s21_decimal dec6 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal dec71 = {{0xfffffffe, 0xffffffff, 0xffffffff, 0x00000000}};
  ck_assert_int_eq(s21_is_equal(dec71, dec6), 0);

  s21_decimal dec9 = {{0, 0, 0, 0}};
  s21_decimal dec10 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(dec9, dec10), 1);

  s21_decimal dec7 = {{0x00000000, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal dec8 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  ck_assert_int_eq(s21_is_equal(dec7, dec8), 1);

  s21_decimal dec11 = {{0x00000000, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal dec12 = {{0x00000000, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_is_equal(dec11, dec12), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal) {
  s21_decimal dec7 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal dec8 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  ck_assert_int_eq(s21_is_not_equal(dec7, dec8), 0);

  s21_decimal dec1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal dec2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 1);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_positive) {
  int src = 10;
  s21_decimal dst;
  s21_decimal expected = {{10, 0, 0, 0}};  // 10

  ck_assert_int_eq(s21_from_int_to_decimal(src, &dst), 0);
  ck_assert_int_eq(dst.bits[0], expected.bits[0]);
  ck_assert_int_eq(dst.bits[1], expected.bits[1]);
  ck_assert_int_eq(dst.bits[2], expected.bits[2]);
  ck_assert_int_eq(dst.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_negative) {
  int src = -10;
  s21_decimal dst;
  s21_decimal expected = {{10, 0, 0, 0x80000000}};  // -10

  ck_assert_int_eq(s21_from_int_to_decimal(src, &dst), 0);
  ck_assert_int_eq(dst.bits[0], expected.bits[0]);
  ck_assert_int_eq(dst.bits[1], expected.bits[1]);
  ck_assert_int_eq(dst.bits[2], expected.bits[2]);
  ck_assert_int_eq(dst.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_negative_min) {
  int src = INT_MIN;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_decimal expected = {{0x80000000, 0, 0, 0x80000000}};  //

  ck_assert_int_eq(s21_from_int_to_decimal(src, &dst), 0);
  ck_assert_int_eq(dst.bits[0], expected.bits[0]);
  ck_assert_int_eq(dst.bits[1], expected.bits[1]);
  ck_assert_int_eq(dst.bits[2], expected.bits[2]);
  ck_assert_int_eq(dst.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_zero) {
  int src = 0;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};  // 0

  ck_assert_int_eq(s21_from_int_to_decimal(src, &dst), 0);
  ck_assert_int_eq(dst.bits[0], expected.bits[0]);
  ck_assert_int_eq(dst.bits[1], expected.bits[1]);
  ck_assert_int_eq(dst.bits[2], expected.bits[2]);
  ck_assert_int_eq(dst.bits[3], expected.bits[3]);
}
END_TEST

/* s21_from_decimal_to_int_positive */

START_TEST(test_s21_from_decimal_to_int_positive_1) {
  int dst = 0;
  s21_decimal src = {{0x80000000, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), 1);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_positive_2) {
  int dst = 0;
  int expected = 134217728;
  s21_decimal src = {{0x08000000, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), 0);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_positive_3) {
  int dst = 0;
  int expected = 134217;
  s21_decimal src = {{0x08000000, 0, 0, 0x00030000}};
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), 0);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_overloaded) {
  int dst = 0;
  s21_decimal src = {{0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0x00030000}};
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), 1);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_negative) {
  int dst = 0;
  int expected = -134217;
  s21_decimal src = {{0x08000000, 0, 0, 0x80030000}};
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), 0);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_negative_overloaded) {
  int dst = 0;
  // int expected = -134217;
  s21_decimal src = {{0x80000001, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), 1);
  // ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_negative_overloaded_2) {
  int dst = 0;
  // int expected = -134217;
  s21_decimal src = {{0x08000001, 0xBBBBBBBB, 0, 0x80000000}};
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), 1);
  // ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_zero) {
  int dst = 0;
  int expected = 0;
  s21_decimal src = {{0x08000001, 0xBBBBBBBB, 0, 0x801C0000}};
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), 0);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_1) {
  s21_decimal dec = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  float dst = 0.0;
  float expected = 7.922816e+28;
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &dst), 0);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_2) {
  s21_decimal dec = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  float dst = 0.0;
  float expected = -7.922816e+28;
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &dst), 0);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_3) {
  s21_decimal dec = {{0xffffffff, 0xffffffff, 0xffffffff, 0x801C0000}};
  float dst = 0.0;
  float expected = -7.922816e+0;
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &dst), 0);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_4) {
  s21_decimal dec = {{0xffffffff, 0, 0, 0x801C0000}};
  float dst = 0.0;
  float expected = -4.294967e-22;
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &dst), 0);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_5) {
  s21_decimal dec = {{0, 0, 0, 0x00000000}};
  float dst = 0.0;
  float expected = 0.0;
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &dst), 0);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_6) {
  s21_decimal dec = {{0x00000001, 0, 0, 0x001C0000}};
  float dst = 0.0;
  float expected = 1e-28;
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &dst), 0);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_7) {
  s21_decimal dec = {{0, 0, 0, 0x801C0000}};
  float dst = 0.0;
  float expected = 0.0;
  ck_assert_int_eq(s21_from_decimal_to_float(dec, &dst), 0);
  ck_assert_int_eq(dst, expected);
}
END_TEST

// START_TEST(test_s21_from_decimal_to_float_8) {
//   s21_decimal dec = {{0, 0, 0, 0x801C0000}};
//   float dst = 0.0;
//   float expected = 0.0;
//   ck_assert_int_eq(s21_from_decimal_to_float(dec, &dst), 0);
//   ck_assert_int_eq(dst, expected);
// }
// END_TEST

// START_TEST(test_s21_from_decimal_to_int_positive) {
//   int dst = 0;
//   s21_decimal src = {{0x80000000, 0, 0, 0}};
//   int expected = 1;  // 10
//   ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), 0);
//   ck_assert_int_eq(dst, expected);
// }
// END_TEST

START_TEST(test_s21_from_float_to_decimal_1) {
  float src = 0.0;
  s21_decimal dst = {{0}};
  s21_decimal expected = {{0}};
  ck_assert_int_eq(s21_from_float_to_decimal(src, &dst), 0);
  ck_assert_int_eq(dst.bits[0], expected.bits[0]);
  ck_assert_int_eq(dst.bits[1], expected.bits[1]);
  ck_assert_int_eq(dst.bits[2], expected.bits[2]);
  ck_assert_int_eq(dst.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_2) {
  float src = 1e-28;
  s21_decimal dst = {{0}};
  s21_decimal expected = {{0x00000001, 0, 0, 0x001C0000}};
  ck_assert_int_eq(s21_from_float_to_decimal(src, &dst), 0);
  ck_assert_int_eq(dst.bits[0], expected.bits[0]);
  ck_assert_int_eq(dst.bits[1], expected.bits[1]);
  ck_assert_int_eq(dst.bits[2], expected.bits[2]);
  ck_assert_int_eq(dst.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_3) {
  float src = 1e-29;
  s21_decimal dst = {{0}};
  s21_decimal expected = {{0}};
  ck_assert_int_eq(s21_from_float_to_decimal(src, &dst), 1);
  ck_assert_int_eq(dst.bits[0], expected.bits[0]);
  ck_assert_int_eq(dst.bits[1], expected.bits[1]);
  ck_assert_int_eq(dst.bits[2], expected.bits[2]);
  ck_assert_int_eq(dst.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_4) {
  float src = -1e-29;
  s21_decimal dst = {{0}};
  s21_decimal expected = {{0}};
  ck_assert_int_eq(s21_from_float_to_decimal(src, &dst), 1);
  ck_assert_int_eq(dst.bits[0], expected.bits[0]);
  ck_assert_int_eq(dst.bits[1], expected.bits[1]);
  ck_assert_int_eq(dst.bits[2], expected.bits[2]);
  ck_assert_int_eq(dst.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_5) {
  float src = 1e+29;
  s21_decimal dst = {{0}};
  // s21_decimal expected = {{0}};
  ck_assert_int_eq(s21_from_float_to_decimal(src, &dst), 1);
  // ck_assert_int_eq(dst.bits[0], expected.bits[0]);
  // ck_assert_int_eq(dst.bits[1], expected.bits[1]);
  // ck_assert_int_eq(dst.bits[2], expected.bits[2]);
  // ck_assert_int_eq(dst.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_6) {
  float src = -1e+29;
  s21_decimal dst = {{0}};
  // s21_decimal expected = {{0}};
  ck_assert_int_eq(s21_from_float_to_decimal(src, &dst), 1);
  // ck_assert_int_eq(dst.bits[0], expected.bits[0]);
  // ck_assert_int_eq(dst.bits[1], expected.bits[1]);
  // ck_assert_int_eq(dst.bits[2], expected.bits[2]);
  // ck_assert_int_eq(dst.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_7) {
  float src = 1.234567e-21;
  s21_decimal dst = {{0}};
  s21_decimal expected = {{0x0012D687, 0, 0, 0x001B0000}};
  ck_assert_int_eq(s21_from_float_to_decimal(src, &dst), 0);
  ck_assert_int_eq(dst.bits[0], expected.bits[0]);
  ck_assert_int_eq(dst.bits[1], expected.bits[1]);
  ck_assert_int_eq(dst.bits[2], expected.bits[2]);
  ck_assert_int_eq(dst.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_8) {
  float src = 1.234567e-27;
  s21_decimal dst = {{0}};
  s21_decimal expected = {{12, 0, 0, 0x001C0000}};
  ck_assert_int_eq(s21_from_float_to_decimal(src, &dst), 0);
  ck_assert_int_eq(dst.bits[0], expected.bits[0]);
  ck_assert_int_eq(dst.bits[1], expected.bits[1]);
  ck_assert_int_eq(dst.bits[2], expected.bits[2]);
  ck_assert_int_eq(dst.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_9) {
  float src = 1.234567e-26;
  s21_decimal dst = {{0}};
  s21_decimal expected = {{123, 0, 0, 0x001C0000}};
  ck_assert_int_eq(s21_from_float_to_decimal(src, &dst), 0);
  ck_assert_int_eq(dst.bits[0], expected.bits[0]);
  ck_assert_int_eq(dst.bits[1], expected.bits[1]);
  ck_assert_int_eq(dst.bits[2], expected.bits[2]);
  ck_assert_int_eq(dst.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_10) {
  float src = 1.234567e-22;
  s21_decimal dst = {{0}};
  s21_decimal expected = {{1234567, 0, 0, 0x001C0000}};
  ck_assert_int_eq(s21_from_float_to_decimal(src, &dst), 0);
  ck_assert_int_eq(dst.bits[0], expected.bits[0]);
  ck_assert_int_eq(dst.bits[1], expected.bits[1]);
  ck_assert_int_eq(dst.bits[2], expected.bits[2]);
  ck_assert_int_eq(dst.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_11) {
  float src = -1.234567e-22;
  s21_decimal dst = {{0}};
  s21_decimal expected = {{1234567, 0, 0, 0x801C0000}};
  ck_assert_int_eq(s21_from_float_to_decimal(src, &dst), 0);
  ck_assert_int_eq(dst.bits[0], expected.bits[0]);
  ck_assert_int_eq(dst.bits[1], expected.bits[1]);
  ck_assert_int_eq(dst.bits[2], expected.bits[2]);
  ck_assert_int_eq(dst.bits[3], expected.bits[3]);
}
END_TEST

/* Тесты truncate */
START_TEST(test_s21_truncate_positive_1) {
  s21_decimal value = {{123456, 0, 0, 0x00030000}};  // 123.456
  s21_decimal result;
  s21_decimal expected = {{123, 0, 0, 0}};  // 123

  ck_assert_int_eq(s21_truncate(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_truncate_positive_2) {
  s21_decimal value = {{0x80000000, 0, 0, 0}};
  s21_decimal result;
  s21_decimal expected = {{0x80000000, 0, 0, 0}};

  ck_assert_int_eq(s21_truncate(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_truncate_negative) {
  s21_decimal value = {{123456, 0, 0, 0x80030000}};  // -123.456
  s21_decimal result;
  s21_decimal expected = {{123, 0, 0, 0x80000000}};  // -123

  ck_assert_int_eq(s21_truncate(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_truncate_zero) {
  s21_decimal value = {{0, 0, 0, 0x00020000}};  // 0.00
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0}};  // 0

  ck_assert_int_eq(s21_truncate(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_truncate_minus_zero) {
  s21_decimal value = {{0, 0, 0, 0x80020000}};  // -0.00
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0x80000000}};  // 0

  ck_assert_int_eq(s21_truncate(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_truncate_big_scale) {
  s21_decimal value = {
      {0, 0, 0XFFFF0000,
       0x001C0000}};  // 79226953588444722964369244160 (29 digits, scale 28)
  s21_decimal result;
  s21_decimal expected = {{0x00000007, 0, 0, 0x00000000}};  // 7

  ck_assert_int_eq(s21_truncate(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST
/* START_TEST(test_s21_is_less_or_equal) { */

// tests for s21_floor:
/* } */
/* END_TEST */

START_TEST(test_s21_floor_positive) {
  s21_decimal value = {{123456, 0, 0, 0x00030000}};  // 123.456
  s21_decimal result;
  s21_decimal expected = {{123, 0, 0, 0}};  // 123
  /* START_TEST(test_s21_is_greater) { */

  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST
/* } */
/* END_TEST */

START_TEST(test_s21_floor_negative) {
  s21_decimal value = {{123456, 0, 0, 0x80030000}};  // -123.456
  s21_decimal result;
  s21_decimal expected = {{124, 0, 0, 0x80000000}};  // -124
  /* START_TEST(test_s21_is_greater_or_equal) { */

  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST
/* } */
/* END_TEST */

START_TEST(test_s21_floor_negative_fractional_0) {
  s21_decimal value = {
      {0x87F0BDC0, 0x1F128130, 0x1027E72F,
       0x80030000}};  // -4999999999999999999999000,000 (28 digits)
  s21_decimal result;
  s21_decimal expected = {{0x24FFFC18, 0x8B0A00A4, 0x422CA,
                           0x80000000}};  // -4999999999999999999999000,000

  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST
/* START_TEST(test_s21_is_equal) { */

START_TEST(test_s21_floor_big_scale) {
  s21_decimal value = {
      {0, 0, 0XFFFF0000,
       0x801C0000}};  // -79226953588444722964369244160 (29 digits, scale 28)
  s21_decimal result;
  s21_decimal expected = {{0x00000008, 0, 0, 0x80000000}};  // -8

  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST
/* } */
/* END_TEST */

// tests for s21_round:

START_TEST(test_s21_round_positive) {
  s21_decimal value = {
      {0xAAAAAAAA, 0xBBBBBBBB, 0XCCCCCCCC,
       0x00030000}};  // 63382530010181687136301525,674 (29 digits)
  s21_decimal result;
  s21_decimal expected = {
      {0x23C131D6, 0xD63427DE, 0X346DC5,
       0x00000000}};  // 63382530010181687136301526 (26 digits)

  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST
/* START_TEST(test_s21_is_not_equal) { */

START_TEST(test_s21_round_positive_0_49) {
  s21_decimal value = {
      {0x87FFFFFF, 0x1F128130, 0X1027E72F,
       0x001C0000}};  // 0.4999999999999999999999999999 (28 digits)
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0x00000000}};  // 0

  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST
/* } */
/* END_TEST */

START_TEST(test_s21_round_positive_0_502) {
  s21_decimal value = {
      {0X88000002, 0x1F128130, 0X1027E72F,
       0x001C0000}};  // 0.5000000000000000000000000002 (28 digits)
  s21_decimal result;
  s21_decimal expected = {{0X00000001, 0, 0, 0x00000000}};  // 0

  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_round_negative) {
  s21_decimal value = {
      {0xAAAAAAAA, 0xBBBBBBBB, 0XCCCCCCCC,
       0x80030000}};  // -63382530010181687136301525,674 (29 digits)
  s21_decimal result;
  s21_decimal expected = {
      {0x23C131D6, 0xD63427DE, 0X346DC5,
       0x80000000}};  // -63382530010181687136301526 (26 digits)

  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_round_zero_1) {
  s21_decimal value = {{0, 0, 0, 0x00000000}};  // 0
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0x00000000}};  // 0

  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_round_zero_2) {
  s21_decimal value = {
      {0, 0xFF, 0, 0x001C0000}};  // 18374686479671623680 (20 digits)
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0x00000000}};  // 0

  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_round_minus_zero) {
  s21_decimal value = {
      {0, 0xFF, 0, 0x801C0000}};  // 18374686479671623680 (20 digits)
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0x80000000}};  // 0

  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// tests for s21_negate:

START_TEST(test_s21_negate_positive) {
  s21_decimal value = {
      {0xAAAAAAAA, 0xBBBBBBBB, 0XCCCCCCCC,
       0x00030000}};  // 63382530010181687136301525,674 (29 digits)
  s21_decimal result;
  s21_decimal expected = {
      {0xAAAAAAAA, 0xBBBBBBBB, 0XCCCCCCCC,
       0x80030000}};  // -63382530010181687136301525,674 (29 digits)

  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_s21_negate_negative) {
  s21_decimal value = {
      {0xAAAAAAAA, 0, 0,
       0x80030000}};  // -63382530010181687136301525,674 (29 digits)
  s21_decimal result;
  s21_decimal expected = {
      {0xAAAAAAAA, 0, 0,
       0x00030000}};  // 63382530010181687136301525,674 (29 digits)

  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST
/* тесты арифметики */
//========================================================================
//========================================================================
// TEST_ADD
START_TEST(test_s21_add_1) {
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x1B0000}};
  s21_set_scale(&decimal1, 27);

  s21_decimal decimal2 = {{0x6, 0x0, 0x0, 0x1C0000}};
  s21_set_scale(&decimal2, 28);

  s21_decimal check = {{0x38, 0x0, 0x0, 0x0}};
  s21_set_scale(&check, 28);

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_add_2) {
  //
  s21_decimal decimal1 = {{0x80000000, 0x0, 0x0, 0x1C0000}};
  //
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x1C0000}};
  //
  s21_decimal check = {{0x0, 0x1, 0x0, 0x1C0000}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_add_3) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&decimal2, 1);

  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_add_4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  s21_set_sign(&decimal2, 1);

  // 71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_add_5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&decimal2, 1);
  s21_set_scale(&decimal2, 1);

  // 71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_add_6) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x0}};
  s21_set_sign(&decimal2, 1);
  s21_set_scale(&decimal2, 1);

  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_add_7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x0}};
  s21_set_sign(&decimal2, 1);
  s21_set_scale(&decimal2, 28);

  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_add_8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

  int check = S21_ARITHMETIC_BIG;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_add_9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x0}};
  s21_set_scale(&decimal2, 28);

  int check = S21_ARITHMETIC_BIG;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_add_10) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&decimal1, 1);

  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x0}};
  s21_set_sign(&decimal2, 1);
  s21_set_scale(&decimal2, 28);

  int check = S21_ARITHMETIC_SMALL;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_add_11) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&decimal1, 1);

  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  s21_set_sign(&decimal2, 1);

  int check = S21_ARITHMETIC_SMALL;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_add_12) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&decimal1, 1);

  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  s21_set_sign(&decimal2, 1);

  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&check, 1);

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_add_13) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&decimal1, 1);

  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};

  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&check, 1);

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_add_14) {
  // -0.0000000000000000000000000010
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x0}};
  s21_set_sign(&decimal1, 1);
  s21_set_scale(&decimal1, 28);

  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  s21_set_sign(&decimal2, 1);

  // -6148914691236517205.0000000000
  s21_decimal check = {{0x8EA6B400, 0x55555554, 0xC6AEA155, 0x0}};
  s21_set_sign(&check, 1);
  s21_set_scale(&check, 10);

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_add_15) {
  // -0.0000000000000000000000000010
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x0}};
  s21_set_sign(&decimal1, 1);
  s21_set_scale(&decimal1, 28);

  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};

  // 6148914691236517205.0000000000
  s21_decimal check = {{0x8EA6B400, 0x55555554, 0xC6AEA155, 0x0}};
  s21_set_scale(&check, 10);

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_add_16) {
  // 1.0000000000000000000000000001
  s21_decimal decimal1 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x0}};
  s21_set_scale(&decimal1, 28);

  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&decimal2, 1);

  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&check, 1);
  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_add_17) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&decimal2, 1);
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  test_add(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_add_18) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1E0000}};

  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  s21_set_sign(&decimal2, 1);

  int check = S21_ARITHMETIC_ERROR;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_add_19) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&decimal1, 1);

  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  s21_set_sign(&decimal2, 1);

  int check = s21_add(decimal1, decimal2, NULL);

  ck_assert_int_eq(4, check);
}

//========================================================================
//========================================================================
// TEST_SUB
START_TEST(test_s21_sub_1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&decimal2, 1);

  int check = S21_ARITHMETIC_BIG;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_sub_2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  test_sub(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_sub_3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  s21_set_sign(&decimal2, 1);

  int check = S21_ARITHMETIC_BIG;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_sub_4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x0}};
  s21_set_scale(&decimal2, 28);

  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_sub_5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

  // 52818775009509558395695966890
  s21_decimal check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  test_sub(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_sub_6) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&decimal1, 1);
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&decimal2, 1);

  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};
  s21_set_sign(&check, 1);

  test_sub(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_sub_7) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  s21_set_sign(&decimal1, 1);

  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

  // -34332203750032298267397517038
  s21_decimal check = {{0xEEEEEEEE, 0x99999999, 0x6EEEEEEE, 0x0}};
  s21_set_sign(&check, 1);

  test_sub(decimal1, decimal2, check);
}
END_TEST

START_TEST(test_s21_sub_8) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // -1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};
  s21_set_sign(&check, 1);

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_s21_sub_9) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  // 71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_s21_sub_10) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&decimal2, 1);
  s21_set_scale(&decimal2, 1);

  int check = S21_ARITHMETIC_BIG;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_sub_11) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  s21_set_sign(&decimal1, 1);

  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&decimal2, 1);

  // 52818775015658473085500828329
  s21_decimal check = {{0xAAAAAAA9, 0xFFFFFFFF, 0xAAAAAAAA, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_s21_sub_12) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  s21_set_sign(&decimal1, 1);

  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  s21_set_sign(&decimal2, 1);

  // -26409387498605864508043122004
  s21_decimal check = {{0x55555554, 0x0, 0x55555555, 0x0}};
  s21_set_sign(&check, 1);

  test_sub(decimal1, decimal2, check);
}
START_TEST(test_s21_sub_13) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  s21_set_sign(&decimal1, 1);

  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  int check = S21_ARITHMETIC_SMALL;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_sub_14) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x1E0000}};
  s21_set_sign(&decimal1, 1);

  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  int check = S21_ARITHMETIC_ERROR;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_sub_15) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  s21_set_sign(&decimal1, 1);

  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  int check = S21_ARITHMETIC_ERROR;

  ck_assert_int_eq(s21_sub(decimal1, decimal2, NULL), check);
}
//========================================================================
//========================================================================
// TEST_MUL
START_TEST(test_s21_mul_1) {
  // 5.0
  s21_decimal decimal1 = {{0x32, 0x0, 0x0, 0x0}};
  s21_set_scale(&decimal1, 1);

  // 4.5
  s21_decimal decimal2 = {{0x2D, 0x0, 0x0, 0x0}};
  s21_set_scale(&decimal2, 1);

  // 22.50
  s21_decimal check = {{0x8CA, 0x0, 0x0, 0x0}};
  s21_set_scale(&check, 2);

  test_mul(decimal1, decimal2, check);
}

START_TEST(test_s21_mul_2) {
  // -7.000000000000025
  s21_decimal decimal1 = {{0x816D8019, 0x18DE76, 0x0, 0x0}};
  s21_set_sign(&decimal1, 1);
  s21_set_scale(&decimal1, 15);

  // -0.000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x0}};
  s21_set_sign(&decimal2, 1);
  s21_set_scale(&decimal2, 15);

  // 0.0000000000000350000000000001
  s21_decimal check = {{0xB9ABE001, 0x13E52, 0x0, 0x0}};
  s21_set_scale(&check, 28);

  test_mul(decimal1, decimal2, check);
}

START_TEST(test_s21_mul_3) {
  // -7.000000000000025
  s21_decimal decimal1 = {{0x816D8019, 0x18DE76, 0x0, 0x0}};
  s21_set_sign(&decimal1, 1);
  s21_set_scale(&decimal1, 15);

  // -0.000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  s21_set_sign(&decimal2, 1);
  s21_set_scale(&decimal2, 15);

  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};
  s21_set_sign(&check, 1);

  test_mul(decimal1, decimal2, check);
}

START_TEST(test_s21_mul_4) {
  // -0.000000000000025
  s21_decimal decimal1 = {{0x19, 0x0, 0x0, 0x0}};
  s21_set_sign(&decimal1, 1);
  s21_set_scale(&decimal1, 16);

  // -0.000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x0}};
  s21_set_sign(&decimal2, 1);
  s21_set_scale(&decimal2, 13);

  // 0
  s21_decimal check = {{0xc, 0x0, 0x0, 0x0}};
  s21_set_scale(&check, 28);

  test_mul(decimal1, decimal2, check);
}

START_TEST(test_s21_mul_5) {
  // 792281625142643.37593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_scale(&decimal1, 14);

  // -792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&decimal2, 1);
  s21_set_scale(&decimal2, 14);

  int check = S21_ARITHMETIC_SMALL;

  test_mul_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_mul_6) {
  // 792281625142643.37593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_scale(&decimal1, 14);

  // 792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_scale(&decimal2, 14);

  int check = S21_ARITHMETIC_BIG;

  test_mul_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_mul_7) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_sign(&decimal1, 1);
  s21_set_scale(&decimal1, 28);

  // 7.8228162514264337593543950335
  s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0x0}};
  s21_set_sign(&decimal2, 1);
  s21_set_scale(&decimal2, 28);

  // 61.978735728724164262422454727
  s21_decimal check = {{0xE07921C7, 0x3FD7ABE1, 0xC8439BCC, 0x0}};
  s21_set_scale(&check, 27);

  test_mul(decimal1, decimal2, check);
}

START_TEST(test_s21_mul_8) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};

  // 26409387504754779197847983445
  s21_decimal check = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

  test_mul(decimal1, decimal2, check);
}

START_TEST(test_s21_mul_9) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  s21_set_sign(&decimal2, 1);

  // -26409387504754779197847983445
  s21_decimal check = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  s21_set_sign(&check, 1);

  test_mul(decimal1, decimal2, check);
}

START_TEST(test_s21_mul_10) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};

  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  s21_set_sign(&decimal2, 1);

  int check = S21_ARITHMETIC_SMALL;

  test_mul_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_mul_11) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x1E0000}};

  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  s21_set_sign(&decimal2, 1);

  int check = S21_ARITHMETIC_ERROR;

  test_mul_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_mul_12) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};

  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  s21_set_sign(&decimal2, 1);

  int check = S21_ARITHMETIC_ERROR;

  ck_assert_int_eq(s21_mul(decimal1, decimal2, NULL), check);
}

START_TEST(test_s21_mul_13) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  s21_set_scale(&decimal1, 28);

  // 7.8228162514264337593543950335
  s21_decimal decimal2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0x1C0000}};
  s21_set_scale(&decimal2, 28);

  // 61.978735728724164262422454727
  s21_decimal check = {{0xE07921C7, 0x3FD7ABE1, 0xC8439BCC, 0x1B0000}};
  s21_set_scale(&check, 27);

  test_mul(decimal1, decimal2, check);
}

//========================================================================
//========================================================================
// TEST_DIV
START_TEST(test_s21_div_1) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};

  // 500
  s21_decimal decimal2 = {{0x1F4, 0x0, 0x0, 0x0}};

  // 0.002
  s21_decimal check = {{0x2, 0x0, 0x0, 0x0}};
  s21_set_scale(&check, 3);

  test_div(decimal1, decimal2, check);
}

START_TEST(test_s21_div_2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_scale(&decimal2, 28);

  // 10000000000000000000000000000
  s21_decimal check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x0}};

  test_div(decimal1, decimal2, check);
}

START_TEST(test_s21_div_3) {
  // 7.9228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_set_scale(&decimal1, 28);

  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // 0.0000000000000000000000000001
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};
  s21_set_scale(&check, 28);

  test_div(decimal1, decimal2, check);
}

START_TEST(test_s21_div_4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  s21_set_sign(&decimal2, 1);
  // -3
  s21_decimal check = {{0x3, 0x0, 0x0, 0x0}};
  s21_set_sign(&check, 1);

  test_div(decimal1, decimal2, check);
}

START_TEST(test_s21_div_5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};

  int check = S21_ARITHMETIC_ZERO_DIV;

  test_div_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_div_6) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // 0
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  s21_set_scale(&decimal2, 28);

  int check = S21_ARITHMETIC_BIG;

  test_div_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_div_7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // 0
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  s21_set_sign(&decimal2, 1);
  s21_set_scale(&decimal2, 28);

  int check = S21_ARITHMETIC_SMALL;

  test_div_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_div_8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, check);
}

START_TEST(test_s21_div_9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // 39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x0}};

  // 1.9999999999999999998915797827
  s21_decimal check = {{0xDF606343, 0x7C4A04C1, 0x409F9CBC, 0x0}};
  s21_set_scale(&check, 28);

  test_div(decimal1, decimal2, check);
}

START_TEST(test_s21_div_10) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x0}};
  s21_set_scale(&decimal2, 28);

  // 20000000000000000000000000000
  s21_decimal check = {{0x20000000, 0x7C4A04C2, 0x409F9CBC, 0x0}};

  test_div(decimal1, decimal2, check);
}

START_TEST(test_s21_div_11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // 0
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1E0000}};
  s21_set_sign(&decimal2, 1);

  int check = S21_ARITHMETIC_ERROR;

  test_div_fail(decimal1, decimal2, check);
}

START_TEST(test_s21_div_12) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  // 0
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  s21_set_sign(&decimal2, 1);
  s21_set_scale(&decimal2, 28);

  int check = S21_ARITHMETIC_ERROR;

  ck_assert_int_eq(s21_div(decimal1, decimal2, NULL), check);
}
/* тесты конвертации */
/* другие тесты */

Suite *suite(void) {
  Suite *s = suite_create("s21_decimal_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_is_less);
  tcase_add_test(tc_core, test_s21_is_less_or_equal);
  tcase_add_test(tc_core, test_s21_is_greater);
  tcase_add_test(tc_core, test_s21_is_greater_or_equal);
  tcase_add_test(tc_core, test_s21_is_equal);
  tcase_add_test(tc_core, test_s21_is_not_equal);

  /*     suite_add_tcase(s, tc_core); */

  tcase_add_test(tc_core, test_s21_from_int_to_decimal_positive);
  tcase_add_test(tc_core, test_s21_from_int_to_decimal_negative);
  tcase_add_test(tc_core, test_s21_from_int_to_decimal_negative_min);
  tcase_add_test(tc_core, test_s21_from_int_to_decimal_zero);

  tcase_add_test(tc_core, test_s21_from_decimal_to_int_positive_1);
  tcase_add_test(tc_core, test_s21_from_decimal_to_int_positive_2);
  tcase_add_test(tc_core, test_s21_from_decimal_to_int_positive_3);
  tcase_add_test(tc_core, test_s21_from_decimal_to_int_overloaded);
  tcase_add_test(tc_core, test_s21_from_decimal_to_int_negative);
  tcase_add_test(tc_core, test_s21_from_decimal_to_int_negative_overloaded);
  tcase_add_test(tc_core, test_s21_from_decimal_to_int_negative_overloaded_2);
  tcase_add_test(tc_core, test_s21_from_decimal_to_int_zero);

  // convert from decimal to float

  tcase_add_test(tc_core, test_s21_from_decimal_to_float_1);
  tcase_add_test(tc_core, test_s21_from_decimal_to_float_2);
  tcase_add_test(tc_core, test_s21_from_decimal_to_float_3);
  tcase_add_test(tc_core, test_s21_from_decimal_to_float_4);
  tcase_add_test(tc_core, test_s21_from_decimal_to_float_5);
  tcase_add_test(tc_core, test_s21_from_decimal_to_float_6);
  tcase_add_test(tc_core, test_s21_from_decimal_to_float_7);

  // convert from float to decimal

  tcase_add_test(tc_core, test_s21_from_float_to_decimal_1);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_2);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_3);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_4);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_5);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_6);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_7);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_8);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_9);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_10);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_11);

  // tcase_add_test(tc_core, test_s21_from_float_to_decimal_9);
  // tcase_add_test(tc_core, test_s21_from_float_to_decimal_10);

  // tcase_add_test(tc_core, s21_from_decimal_to_int_negative);
  // tcase_add_test(tc_core, s21_from_decimal_to_int_negative_min);
  // tcase_add_test(tc_core, s21_from_decimal_to_int_zero);

  tcase_add_test(tc_core, test_s21_truncate_positive_1);
  tcase_add_test(tc_core, test_s21_truncate_positive_2);
  tcase_add_test(tc_core, test_s21_truncate_negative);
  tcase_add_test(tc_core, test_s21_truncate_zero);
  tcase_add_test(tc_core, test_s21_truncate_minus_zero);
  tcase_add_test(tc_core, test_s21_truncate_big_scale);

  tcase_add_test(tc_core, test_s21_floor_positive);
  tcase_add_test(tc_core, test_s21_floor_negative);
  tcase_add_test(tc_core, test_s21_floor_negative_fractional_0);
  tcase_add_test(tc_core, test_s21_floor_big_scale);

  tcase_add_test(tc_core, test_s21_round_positive);
  tcase_add_test(tc_core, test_s21_round_positive_0_49);
  tcase_add_test(tc_core, test_s21_round_positive_0_502);
  tcase_add_test(tc_core, test_s21_round_negative);
  tcase_add_test(tc_core, test_s21_round_zero_1);
  tcase_add_test(tc_core, test_s21_round_zero_2);
  tcase_add_test(tc_core, test_s21_round_minus_zero);

  tcase_add_test(tc_core, test_s21_negate_positive);
  tcase_add_test(tc_core, test_s21_negate_negative);

  // TEST_ADD
  tcase_add_test(tc_core, test_s21_add_1);
  tcase_add_test(tc_core, test_s21_add_2);
  tcase_add_test(tc_core, test_s21_add_3);
  tcase_add_test(tc_core, test_s21_add_4);
  tcase_add_test(tc_core, test_s21_add_5);
  tcase_add_test(tc_core, test_s21_add_6);
  tcase_add_test(tc_core, test_s21_add_7);
  tcase_add_test(tc_core, test_s21_add_8);
  tcase_add_test(tc_core, test_s21_add_9);
  tcase_add_test(tc_core, test_s21_add_10);
  tcase_add_test(tc_core, test_s21_add_11);
  tcase_add_test(tc_core, test_s21_add_12);
  tcase_add_test(tc_core, test_s21_add_13);
  tcase_add_test(tc_core, test_s21_add_14);
  tcase_add_test(tc_core, test_s21_add_15);
  tcase_add_test(tc_core, test_s21_add_16);
  tcase_add_test(tc_core, test_s21_add_17);
  tcase_add_test(tc_core, test_s21_add_18);
  tcase_add_test(tc_core, test_s21_add_19);

  // TEST_SUB
  tcase_add_test(tc_core, test_s21_sub_1);
  tcase_add_test(tc_core, test_s21_sub_2);
  tcase_add_test(tc_core, test_s21_sub_3);
  tcase_add_test(tc_core, test_s21_sub_4);
  tcase_add_test(tc_core, test_s21_sub_5);
  tcase_add_test(tc_core, test_s21_sub_6);
  tcase_add_test(tc_core, test_s21_sub_7);
  tcase_add_test(tc_core, test_s21_sub_8);
  tcase_add_test(tc_core, test_s21_sub_9);
  tcase_add_test(tc_core, test_s21_sub_10);
  tcase_add_test(tc_core, test_s21_sub_11);
  tcase_add_test(tc_core, test_s21_sub_12);
  tcase_add_test(tc_core, test_s21_sub_13);
  tcase_add_test(tc_core, test_s21_sub_14);
  tcase_add_test(tc_core, test_s21_sub_15);

  // TEST_MUL
  tcase_add_test(tc_core, test_s21_mul_1);
  tcase_add_test(tc_core, test_s21_mul_2);
  tcase_add_test(tc_core, test_s21_mul_3);
  tcase_add_test(tc_core, test_s21_mul_4);
  tcase_add_test(tc_core, test_s21_mul_5);
  tcase_add_test(tc_core, test_s21_mul_6);
  tcase_add_test(tc_core, test_s21_mul_7);
  tcase_add_test(tc_core, test_s21_mul_8);
  tcase_add_test(tc_core, test_s21_mul_9);
  tcase_add_test(tc_core, test_s21_mul_10);
  tcase_add_test(tc_core, test_s21_mul_11);
  tcase_add_test(tc_core, test_s21_mul_12);
  tcase_add_test(tc_core, test_s21_mul_13);

  // TEST_DIV
  tcase_add_test(tc_core, test_s21_div_1);
  tcase_add_test(tc_core, test_s21_div_2);
  tcase_add_test(tc_core, test_s21_div_3);
  tcase_add_test(tc_core, test_s21_div_4);
  tcase_add_test(tc_core, test_s21_div_5);
  tcase_add_test(tc_core, test_s21_div_6);
  tcase_add_test(tc_core, test_s21_div_7);
  tcase_add_test(tc_core, test_s21_div_8);
  tcase_add_test(tc_core, test_s21_div_9);
  tcase_add_test(tc_core, test_s21_div_10);
  tcase_add_test(tc_core, test_s21_div_11);
  tcase_add_test(tc_core, test_s21_div_12);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s = suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}

void test_add(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result = {{0, 0, 0, 0}};
  int code = s21_add(decimal1, decimal2, &result);

#if defined(DEBUG)
  printf("---------------------------------\n");
  printf("Tests_add:\n");
  print_decimal(decimal1);
  print_decimal(decimal2);
  printf("\ncheck:\n");
  print_decimal(check);
  printf("\nresult_add:\n");
  print_decimal(result);
  printf("\nresult_Code:%d\n", code);
  printf("---------------------------------\n\n\n");
#endif

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, 0);
}

void test_add_fail(s21_decimal decimal1, s21_decimal decimal2, int check) {
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

#if defined(DEBUG)
  printf("---------------------------------\n");
  printf("Tests_add:\n");
  print_decimal(decimal1);
  print_decimal(decimal2);
  printf("\ncheck_code:%d\n", check);
  printf("\nresult_add:\n");
  print_decimal(result);
  printf("\nresult_Code:%d\n", code);
  printf("---------------------------------\n\n\n");
#endif

  ck_assert_int_eq(code, check);
}

void test_sub(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result = {{0, 0, 0, 0}};
  int code = s21_sub(decimal1, decimal2, &result);

#if defined(DEBUG)
  printf("---------------------------------\n");
  printf("Tests_sub:\n");
  print_decimal(decimal1);
  print_decimal(decimal2);
  printf("\ncheck:\n");
  print_decimal(check);
  printf("\nresult_sub:\n");
  print_decimal(result);
  printf("\nresult_Code:%d\n", code);
  printf("---------------------------------\n\n\n");
#endif

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, 0);
}

void test_sub_fail(s21_decimal decimal1, s21_decimal decimal2, int check) {
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

#if defined(DEBUG)
  printf("---------------------------------\n");
  printf("Tests_sub:_%d\n", number_test);
  print_decimal(decimal1);
  print_decimal(decimal2);
  printf("\ncheck_code:%d\n", check);
  printf("\nresult_sub:\n");
  print_decimal(result);
  printf("\nresult_Code:%d\n", code);
  printf("---------------------------------\n\n\n");
#endif

  ck_assert_int_eq(code, check);
}

void test_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result = {{0, 0, 0, 0}};
  int code = s21_mul(decimal1, decimal2, &result);

#if defined(DEBUG)
  printf("---------------------------------\n");
  printf("Tests_mul:\n");
  print_decimal(decimal1);
  print_decimal(decimal2);
  printf("\ncheck:\n");
  print_decimal(check);
  printf("\nresult_mul:\n");
  print_decimal(result);
  printf("\nresult_Code:%d\n", code);
  printf("---------------------------------\n\n\n");
#endif

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, 0);
}

void test_mul_fail(s21_decimal decimal1, s21_decimal decimal2, int check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

#if defined(DEBUG)
  printf("---------------------------------\n");
  printf("Tests_mul:\n");
  print_decimal(decimal1);
  print_decimal(decimal2);
  printf("\ncheck_code:%d\n", check);
  printf("\nresult_mul:\n");
  print_decimal(result);
  printf("\nresult_Code:%d\n", code);
  printf("---------------------------------\n\n\n");
#endif

  ck_assert_int_eq(code, check);
}

void test_div(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result = {{0, 0, 0, 0}};
  int code = s21_div(decimal1, decimal2, &result);

#if defined(DEBUG)
  printf("---------------------------------\n");
  printf("Tests_div:\n");
  print_decimal(decimal1);
  print_decimal(decimal2);
  printf("\ncheck:\n");
  print_decimal(check);
  printf("\nresult_div:\n");
  print_decimal(result);
  printf("\nresult_Code:%d\n", code);
  printf("---------------------------------\n\n\n");
#endif

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, 0);
}

void test_div_fail(s21_decimal decimal1, s21_decimal decimal2, int check) {
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

#if defined(DEBUG)
  printf("---------------------------------\n");
  printf("Tests_div:\n");
  print_decimal(decimal1);
  print_decimal(decimal2);
  printf("\ncheck_code:%d\n", check);
  printf("\nresult_div:\n");
  print_decimal(result);
  printf("\nresult_Code:%d\n", code);
  printf("---------------------------------\n\n\n");
#endif

  ck_assert_int_eq(code, check);
}
