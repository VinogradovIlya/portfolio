#include "tests.h"

START_TEST(test_valid_3x3_matrix) {
  matrix_t m = {0};
  int code = s21_create_matrix(3, 3, &m);
  ck_assert_int_eq(code, OK);
  ck_assert_ptr_nonnull(m.matrix);
  ck_assert_int_eq(m.rows, 3);
  ck_assert_int_eq(m.columns, 3);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_valid_1x1_matrix) {
  matrix_t m = {0};
  int code = s21_create_matrix(1, 1, &m);
  ck_assert_int_eq(code, OK);
  ck_assert_ptr_nonnull(m.matrix);
  ck_assert_int_eq(m.rows, 1);
  ck_assert_int_eq(m.columns, 1);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_invalid_zero_rows) {
  matrix_t m = {0};
  int code = s21_create_matrix(0, 2, &m);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(test_invalid_zero_columns) {
  matrix_t m = {0};
  int code = s21_create_matrix(2, 0, &m);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(test_invalid_negative_rows) {
  matrix_t m = {0};
  int code = s21_create_matrix(-1, 2, &m);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(test_invalid_negative_columns) {
  matrix_t m = {0};
  int code = s21_create_matrix(2, -1, &m);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(test_null_pointer_result) {
  int code = s21_create_matrix(2, 2, NULL);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(test_large_matrix_creation) {
  matrix_t m = {0};
  int code = s21_create_matrix(10000, 10000, &m);
  ck_assert_int_eq(code, OK);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_allocated_matrix_filled_with_zero) {
  matrix_t m = {0};
  s21_create_matrix(3, 3, &m);
  int all_zero = 1;
  for (int i = 0; i < m.rows; i++)
    for (int j = 0; j < m.columns; j++)
      if (m.matrix[i][j] != 0.0) all_zero = 0;
  ck_assert_int_eq(all_zero, 1);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_matrix_structure_integrity) {
  matrix_t m = {0};
  s21_create_matrix(4, 5, &m);
  ck_assert_int_eq(m.rows, 4);
  ck_assert_int_eq(m.columns, 5);
  ck_assert_ptr_nonnull(m.matrix);
  for (int i = 0; i < m.rows; i++) {
    ck_assert_ptr_nonnull(m.matrix[i]);
  }
  s21_remove_matrix(&m);
  s21_remove_matrix(NULL);
}
END_TEST

Suite *create_matrix_suite(void) {
  Suite *s = suite_create("Create Matrix");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_valid_3x3_matrix);
  tcase_add_test(tc, test_valid_1x1_matrix);
  tcase_add_test(tc, test_invalid_zero_rows);
  tcase_add_test(tc, test_invalid_zero_columns);
  tcase_add_test(tc, test_invalid_negative_rows);
  tcase_add_test(tc, test_invalid_negative_columns);
  tcase_add_test(tc, test_null_pointer_result);
  tcase_add_test(tc, test_large_matrix_creation);
  tcase_add_test(tc, test_allocated_matrix_filled_with_zero);
  tcase_add_test(tc, test_matrix_structure_integrity);

  suite_add_tcase(s, tc);
  return s;
}
