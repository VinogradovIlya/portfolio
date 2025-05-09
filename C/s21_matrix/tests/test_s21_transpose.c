#include "tests.h"

START_TEST(transpose_square_matrix) {
  matrix_t src, expected, result;
  s21_create_matrix(2, 2, &src);
  s21_create_matrix(2, 2, &expected);

  double values[] = {1, 2, 3, 4};
  double transposed[] = {1, 3, 2, 4};

  fill_test(&src, values, 2, 2);
  fill_test(&expected, transposed, 2, 2);

  ck_assert_int_eq(s21_transpose(&src, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&src);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_rectangular_matrix) {
  matrix_t src, expected, result;
  s21_create_matrix(2, 3, &src);
  s21_create_matrix(3, 2, &expected);

  double values[] = {1, 2, 3, 4, 5, 6};
  double transposed[] = {1, 4, 2, 5, 3, 6};

  fill_test(&src, values, 2, 3);
  fill_test(&expected, transposed, 3, 2);

  ck_assert_int_eq(s21_transpose(&src, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&src);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_single_element) {
  matrix_t src, expected, result;
  s21_create_matrix(1, 1, &src);
  s21_create_matrix(1, 1, &expected);

  src.matrix[0][0] = 42;
  expected.matrix[0][0] = 42;

  ck_assert_int_eq(s21_transpose(&src, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&src);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_empty_matrix) {
  matrix_t src = {0};
  matrix_t result;

  ck_assert_int_eq(s21_transpose(&src, &result), ERROR);
}
END_TEST

START_TEST(transpose_null_matrix) {
  matrix_t *src = NULL;
  matrix_t result;

  ck_assert_int_eq(s21_transpose(src, &result), ERROR);
}
END_TEST

START_TEST(transpose_large_matrix) {
  matrix_t src, result;
  int size = 50;
  s21_create_matrix(size, size, &src);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) src.matrix[i][j] = i * size + j;

  ck_assert_int_eq(s21_transpose(&src, &result), OK);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      ck_assert_double_eq(src.matrix[i][j], result.matrix[j][i]);

  s21_remove_matrix(&src);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_self_check) {
  matrix_t src, result;
  s21_create_matrix(3, 3, &src);

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) src.matrix[i][j] = i == j ? 1 : 0;

  ck_assert_int_eq(s21_transpose(&src, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&src, &result), SUCCESS);

  s21_remove_matrix(&src);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_check_memory_safety) {
  matrix_t src, result;
  s21_create_matrix(10, 5, &src);

  for (int i = 0; i < src.rows; i++)
    for (int j = 0; j < src.columns; j++) src.matrix[i][j] = rand() % 100;

  ck_assert_int_eq(s21_transpose(&src, &result), OK);

  for (int i = 0; i < src.rows; i++)
    for (int j = 0; j < src.columns; j++)
      ck_assert_double_eq_tol(src.matrix[i][j], result.matrix[j][i], 1e-6);

  s21_remove_matrix(&src);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_zero_matrix) {
  matrix_t src, expected, result;
  s21_create_matrix(2, 2, &src);
  s21_create_matrix(2, 2, &expected);

  double zeros[] = {0, 0, 0, 0};
  fill_test(&src, zeros, 2, 2);
  fill_test(&expected, zeros, 2, 2);

  ck_assert_int_eq(s21_transpose(&src, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&src);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

Suite *transpose_suite(void) {
  Suite *s = suite_create("transpose_tc");
  TCase *tc = tcase_create("transpose_tc");

  tcase_add_test(tc, transpose_square_matrix);
  tcase_add_test(tc, transpose_rectangular_matrix);
  tcase_add_test(tc, transpose_single_element);
  tcase_add_test(tc, transpose_empty_matrix);
  tcase_add_test(tc, transpose_null_matrix);
  tcase_add_test(tc, transpose_large_matrix);
  tcase_add_test(tc, transpose_self_check);
  tcase_add_test(tc, transpose_check_memory_safety);
  tcase_add_test(tc, transpose_zero_matrix);

  suite_add_tcase(s, tc);
  return s;
}
