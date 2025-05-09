#include "tests.h"

START_TEST(eq_identical_matrices) {
  double values[4] = {1.0, 2.0, 3.0, 4.0};

  matrix_t m1, m2;
  s21_create_matrix(2, 2, &m1);
  s21_create_matrix(2, 2, &m2);
  fill_test(&m1, values, 2, 2);
  fill_test(&m2, values, 2, 2);

  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(eq_different_matrices) {
  double values1[4] = {1.0, 2.0, 3.0, 4.0};
  double values2[4] = {5.0, 6.0, 7.0, 8.0};

  matrix_t m1, m2;
  s21_create_matrix(2, 2, &m1);
  s21_create_matrix(2, 2, &m2);
  fill_test(&m1, values1, 2, 2);
  fill_test(&m2, values2, 2, 2);
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FAILURE);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(eq_different_size_matrices) {
  double values1[4] = {1.0, 2.0, 3.0, 4.0};
  double values2[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

  matrix_t m1, m2;
  s21_create_matrix(2, 2, &m1);
  s21_create_matrix(3, 2, &m2);
  fill_test(&m1, values1, 2, 2);
  fill_test(&m2, values2, 3, 2);

  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FAILURE);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(eq_matrices_with_small_floats) {
  double values1[4] = {0.000001, 0.000002, 0.000003, 0.000004};
  double values2[4] = {0.000001, 0.000002, 0.000003, 0.000004};

  matrix_t m1, m2;
  s21_create_matrix(2, 2, &m1);
  s21_create_matrix(2, 2, &m2);
  fill_test(&m1, values1, 2, 2);
  fill_test(&m2, values2, 2, 2);

  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(eq_matrices_with_inf) {
  double values1[4] = {INFINITY, 2.0, 3.0, 4.0};
  double values2[4] = {INFINITY, 2.0, 3.0, 4.0};

  matrix_t m1, m2;
  s21_create_matrix(2, 2, &m1);
  s21_create_matrix(2, 2, &m2);
  fill_test(&m1, values1, 2, 2);
  fill_test(&m2, values2, 2, 2);

  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(eq_no_valid_matrices) {
  matrix_t m1 = {0}, m2 = {0};
  m1.rows = -1;
  m2.rows = -1;
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FAILURE);
}
END_TEST

START_TEST(eq_no_valid_matrices2) {
  matrix_t m1 = {0}, m2 = {0};
  m1.columns = -1;
  m2.columns = -1;
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FAILURE);
}
END_TEST

START_TEST(eq_empty_matrices) {
  matrix_t m1 = {0}, m2 = {0};
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), SUCCESS);
}
END_TEST

START_TEST(eq_zero_matrices) {
  double values[4] = {0.0, 0.0, 0.0, 0.0};

  matrix_t m1, m2;
  s21_create_matrix(2, 2, &m1);
  s21_create_matrix(2, 2, &m2);
  fill_test(&m1, values, 2, 2);
  fill_test(&m2, values, 2, 2);

  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(eq_identity_matrices) {
  double values[4] = {1.0, 0.0, 0.0, 1.0};

  matrix_t m1, m2;
  s21_create_matrix(2, 2, &m1);
  s21_create_matrix(2, 2, &m2);
  fill_test(&m1, values, 2, 2);
  fill_test(&m2, values, 2, 2);

  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

Suite *eq_matrix_suite(void) {
  Suite *s = suite_create("eq_matrix");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, eq_identical_matrices);
  tcase_add_test(tc, eq_different_matrices);
  tcase_add_test(tc, eq_different_size_matrices);
  tcase_add_test(tc, eq_matrices_with_small_floats);
  tcase_add_test(tc, eq_matrices_with_inf);
  tcase_add_test(tc, eq_no_valid_matrices);
  tcase_add_test(tc, eq_no_valid_matrices2);
  tcase_add_test(tc, eq_empty_matrices);
  tcase_add_test(tc, eq_zero_matrices);
  tcase_add_test(tc, eq_identity_matrices);

  suite_add_tcase(s, tc);
  return s;
}
