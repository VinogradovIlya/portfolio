#include "tests.h"

START_TEST(calc_complements_1x1) {
  matrix_t A = {0}, result = {0}, expected = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5;

  s21_create_matrix(1, 1, &expected);
  expected.matrix[0][0] = 1;

  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_2x2) {
  matrix_t A = {0}, result = {0}, expected = {0};
  double data[4] = {1, 2, 3, 4};
  double expected_data[4] = {4, -3, -2, 1};

  s21_create_matrix(2, 2, &A);
  fill_test(&A, data, 2, 2);

  s21_create_matrix(2, 2, &expected);
  fill_test(&expected, expected_data, 2, 2);

  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_zero_matrix) {
  matrix_t A = {0}, result = {0}, expected = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_negative_values) {
  matrix_t A = {0}, result = {0}, expected = {0};
  double data[9] = {-1, -2, -3, -4, -5, -6, -7, -8, -9};
  double expected_data[9] = {-3, 6, -3, 6, -12, 6, -3, 6, -3};

  s21_create_matrix(3, 3, &A);
  fill_test(&A, data, 3, 3);

  s21_create_matrix(3, 3, &expected);
  fill_test(&expected, expected_data, 3, 3);

  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_identity_matrix) {
  matrix_t A = {0}, result = {0}, expected = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = A.matrix[1][1] = A.matrix[2][2] = 1;

  s21_create_matrix(3, 3, &expected);
  expected.matrix[0][0] = expected.matrix[1][1] = expected.matrix[2][2] = 1;

  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_rectangular_matrix) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 3, &A);

  ck_assert_int_eq(s21_calc_complements(&A, &result), ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_null_matrix) {
  matrix_t A = {0}, result = {0};
  A.rows = 0;
  A.columns = 0;
  A.matrix = NULL;

  ck_assert_int_eq(s21_calc_complements(&A, &result), ERROR);
}
END_TEST

START_TEST(calc_complements_null_data) {
  matrix_t A = {NULL, 3, 3}, result = {0};
  ck_assert_int_eq(s21_calc_complements(&A, &result), ERROR);
}
END_TEST

START_TEST(calc_complements_4x4) {
  matrix_t A = {0}, result = {0}, expected = {0};
  double data[16] = {2, 2, 3, 4, 5, 1, 2, 3, 6, 6, 7, 8, 0, 5, 6, 5};
  double expected_data[16] = {10.0, 17,  10, -29, -8, 28, -40, 20,
                              -2,   -29, 30, -7,  0,  16, -32, 16};

  s21_create_matrix(4, 4, &A);
  fill_test(&A, data, 4, 4);

  s21_create_matrix(4, 4, &expected);
  fill_test(&expected, expected_data, 4, 4);

  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_float_values) {
  matrix_t A = {0}, result = {0}, expected = {0};
  double data[9] = {1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5};
  double expected_data[9] = {-3, 6, -3, 6, -12, 6, -3, 6, -3};

  s21_create_matrix(3, 3, &A);
  fill_test(&A, data, 3, 3);

  s21_create_matrix(3, 3, &expected);
  fill_test(&expected, expected_data, 3, 3);

  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

Suite *calc_complements(void) {
  Suite *s = suite_create("calc_complements");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, calc_complements_1x1);
  tcase_add_test(tc, calc_complements_2x2);
  tcase_add_test(tc, calc_complements_zero_matrix);
  tcase_add_test(tc, calc_complements_negative_values);
  tcase_add_test(tc, calc_complements_identity_matrix);
  tcase_add_test(tc, calc_complements_rectangular_matrix);
  tcase_add_test(tc, calc_complements_null_matrix);
  tcase_add_test(tc, calc_complements_null_data);
  tcase_add_test(tc, calc_complements_4x4);
  tcase_add_test(tc, calc_complements_float_values);

  suite_add_tcase(s, tc);
  return s;
}