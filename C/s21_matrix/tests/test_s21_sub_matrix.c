#include "tests.h"

START_TEST(s21_sub_matrix_1) {
  matrix_t A = {};
  matrix_t B = {};
  ck_assert_int_eq(s21_sub_matrix(&A, &B, NULL), ERROR);
}
END_TEST

START_TEST(s21_sub_matrix_2) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(5, 5, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sub_matrix_5) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &B);
  s21_create_matrix(5, 5, &eq_matrix);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_sub_matrix_6) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &eq_matrix);
  A.matrix[0][0] = 1, A.matrix[0][1] = 2, A.matrix[0][2] = 3;
  A.matrix[1][0] = 0, A.matrix[1][1] = 4, A.matrix[1][2] = 5;
  A.matrix[2][0] = 0, A.matrix[2][1] = 0, A.matrix[2][2] = 6;
  B.matrix[0][0] = 1, B.matrix[0][1] = 0, B.matrix[0][2] = 0;
  B.matrix[1][0] = 2, B.matrix[1][1] = 0, B.matrix[1][2] = 0;
  B.matrix[2][0] = 3, B.matrix[2][1] = 4, B.matrix[2][2] = 1;
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  eq_matrix.matrix[0][0] = 0, eq_matrix.matrix[0][1] = 2,
  eq_matrix.matrix[0][2] = 3;
  eq_matrix.matrix[1][0] = -2, eq_matrix.matrix[1][1] = 4,
  eq_matrix.matrix[1][2] = 5;
  eq_matrix.matrix[2][0] = -3, eq_matrix.matrix[2][1] = -4,
  eq_matrix.matrix[2][2] = 5;
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(sub_simple_case) {
  matrix_t a, b, expected, result;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  s21_create_matrix(2, 2, &expected);

  double values_a[] = {5, 6, 7, 8};
  double values_b[] = {1, 2, 3, 4};
  double expected_values[] = {4, 4, 4, 4};

  fill_test(&a, values_a, 2, 2);
  fill_test(&b, values_b, 2, 2);
  fill_test(&expected, expected_values, 2, 2);

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_incorrect_rows) {
  matrix_t a, b, result;
  s21_create_matrix(2, 3, &a);
  s21_create_matrix(3, 3, &b);

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &result), CALC_ERROR);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_incorrect_cols) {
  matrix_t a, b, result;
  s21_create_matrix(3, 2, &a);
  s21_create_matrix(3, 3, &b);

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &result), CALC_ERROR);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_negative_values) {
  matrix_t a, b, expected, result;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  s21_create_matrix(2, 2, &expected);

  double values_a[] = {-1, -2, -3, -4};
  double values_b[] = {-4, -3, -2, -1};
  double expected_values[] = {3, 1, -1, -3};

  fill_test(&a, values_a, 2, 2);
  fill_test(&b, values_b, 2, 2);
  fill_test(&expected, expected_values, 2, 2);

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_zero_matrix) {
  matrix_t a, b, expected, result;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  s21_create_matrix(2, 2, &expected);

  double zeros[] = {0, 0, 0, 0};
  fill_test(&a, zeros, 2, 2);
  fill_test(&b, zeros, 2, 2);
  fill_test(&expected, zeros, 2, 2);

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_big_matrix) {
  matrix_t a, b, result;
  s21_create_matrix(100, 100, &a);
  s21_create_matrix(100, 100, &b);

  for (int i = 0; i < 100; i++)
    for (int j = 0; j < 100; j++) {
      a.matrix[i][j] = i + j;
      b.matrix[i][j] = j;
    }

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &result), OK);
  for (int i = 0; i < 100; i++)
    for (int j = 0; j < 100; j++)
      ck_assert_double_eq_tol(result.matrix[i][j], i, 1e-6);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_self) {
  matrix_t a, result;
  s21_create_matrix(3, 3, &a);

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) a.matrix[i][j] = i + j;

  ck_assert_int_eq(s21_sub_matrix(&a, &a, &result), OK);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      ck_assert_double_eq_tol(result.matrix[i][j], 0.0, 1e-6);

  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_null_ptrs) {
  matrix_t *null_matrix = NULL;
  matrix_t res;
  ck_assert_int_eq(s21_sub_matrix(null_matrix, null_matrix, &res), ERROR);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sub_result_rewrite) {
  matrix_t a, b, result;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);

  double values_a[] = {10, 20, 30, 40};
  double values_b[] = {1, 2, 3, 4};
  double expected[] = {9, 18, 27, 36};

  fill_test(&a, values_a, 2, 2);
  fill_test(&b, values_b, 2, 2);

  ck_assert_int_eq(s21_sub_matrix(&a, &b, &result), OK);

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      ck_assert_double_eq_tol(result.matrix[i][j], expected[i * 2 + j], 1e-6);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

Suite *sub_matrix_suite(void) {
  Suite *s = suite_create("sub_tc");
  TCase *tc = tcase_create("sub_tc");

  tcase_add_test(tc, sub_simple_case);
  tcase_add_test(tc, sub_incorrect_rows);
  tcase_add_test(tc, sub_incorrect_cols);
  tcase_add_test(tc, sub_negative_values);
  tcase_add_test(tc, sub_zero_matrix);
  tcase_add_test(tc, sub_big_matrix);
  tcase_add_test(tc, sub_self);
  tcase_add_test(tc, sub_null_ptrs);
  tcase_add_test(tc, sub_result_rewrite);
  tcase_add_test(tc, s21_sub_matrix_1);
  tcase_add_test(tc, s21_sub_matrix_2);
  tcase_add_test(tc, s21_sub_matrix_5);
  tcase_add_test(tc, s21_sub_matrix_6);

  suite_add_tcase(s, tc);
  return s;
}
