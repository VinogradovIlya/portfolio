#include "tests.h"

START_TEST(sum_simple_case) {
  matrix_t a, b, expected, result;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  s21_create_matrix(2, 2, &expected);

  double value_A[4] = {1.0, 2.0, 3.0, 4.0};
  double value_B[4] = {5.0, 6.0, 7.0, 8.0};
  double expected_value[4] = {6.0, 8.0, 10.0, 12.0};

  fill_test(&a, value_A, 2, 2);
  fill_test(&b, value_B, 2, 2);
  fill_test(&expected, expected_value, 2, 2);

  ck_assert_int_eq(s21_sum_matrix(&a, &b, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_zero_matrix) {
  matrix_t a, b, result;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  a.matrix[0][0] = 1;
  a.matrix[1][1] = 2;

  ck_assert_int_eq(s21_sum_matrix(&a, &b, &result), OK);
  ck_assert_double_eq(result.matrix[0][0], 1);
  ck_assert_double_eq(result.matrix[1][1], 2);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_negative_values) {
  matrix_t a, b, result;
  s21_create_matrix(1, 1, &a);
  s21_create_matrix(1, 1, &b);
  a.matrix[0][0] = -2.5;
  b.matrix[0][0] = -3.5;

  ck_assert_int_eq(s21_sum_matrix(&a, &b, &result), OK);
  ck_assert_double_eq(result.matrix[0][0], -6.0);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_incorrect_rows) {
  matrix_t a, b, result;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(3, 2, &b);
  ck_assert_int_eq(s21_sum_matrix(&a, &b, &result), CALC_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(sum_incorrect_cols) {
  matrix_t a, b, result;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 3, &b);
  ck_assert_int_eq(s21_sum_matrix(&a, &b, &result), CALC_ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(sum_null_pointer) {
  matrix_t a;
  s21_create_matrix(2, 2, &a);
  ck_assert_int_eq(s21_sum_matrix(&a, NULL, NULL), ERROR);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(sum_big_matrix) {
  matrix_t a, b, result;
  s21_create_matrix(100, 100, &a);
  s21_create_matrix(100, 100, &b);
  for (int i = 0; i < 100; i++)
    for (int j = 0; j < 100; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = i - j;
    }

  ck_assert_int_eq(s21_sum_matrix(&a, &b, &result), OK);
  ck_assert_double_eq(result.matrix[50][50],
                      a.matrix[50][50] + b.matrix[50][50]);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_self) {
  matrix_t a, result;
  s21_create_matrix(2, 2, &a);
  a.matrix[0][0] = 3;
  a.matrix[1][1] = 3;

  ck_assert_int_eq(s21_sum_matrix(&a, &a, &result), OK);
  ck_assert_double_eq(result.matrix[0][0], 6);
  ck_assert_double_eq(result.matrix[1][1], 6);

  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_empty_matrix) {
  matrix_t a = {0}, b = {0}, result;
  ck_assert_int_eq(s21_sum_matrix(&a, &b, &result), ERROR);
}
END_TEST

START_TEST(sum_result_is_null) {
  matrix_t a, b;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  ck_assert_int_eq(s21_sum_matrix(&a, &b, NULL), ERROR);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(sum_1x1) {
  matrix_t a, b, result, expected;
  s21_create_matrix(1, 1, &a);
  s21_create_matrix(1, 1, &b);
  s21_create_matrix(1, 1, &expected);
  a.matrix[0][0] = 3.0;
  b.matrix[0][0] = 6.0;
  expected.matrix[0][0] = 9.0;

  ck_assert_int_eq(s21_sum_matrix(&a, &b, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], expected.matrix[0][0], EPSILON);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

Suite *sum_matrix_suite(void) {
  Suite *s = suite_create("sum_matrix");
  TCase *tc = tcase_create("sum_tc");

  tcase_add_test(tc, sum_simple_case);
  tcase_add_test(tc, sum_zero_matrix);
  tcase_add_test(tc, sum_negative_values);
  tcase_add_test(tc, sum_incorrect_rows);
  tcase_add_test(tc, sum_incorrect_cols);
  tcase_add_test(tc, sum_null_pointer);
  tcase_add_test(tc, sum_big_matrix);
  tcase_add_test(tc, sum_self);
  tcase_add_test(tc, sum_empty_matrix);
  tcase_add_test(tc, sum_result_is_null);
  tcase_add_test(tc, sum_1x1);

  suite_add_tcase(s, tc);
  return s;
}
