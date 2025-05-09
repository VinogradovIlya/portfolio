#include "tests.h"

START_TEST(mult_matrix_both_invalid_internal) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  A.matrix = NULL;
  A.rows = -1;
  A.columns = -1;
  B.matrix = NULL;
  B.rows = 0;
  B.columns = 0;

  int code = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(mult_valid_matrices) {
  matrix_t A, B, result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);

  double values_A[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double values_B[6] = {7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
  fill_test(&A, values_A, 2, 3);
  fill_test(&B, values_B, 3, 2);

  int code = s21_mult_matrix(&A, &B, &result);

  double expected[2][2] = {{58.0, 64.0}, {139.0, 154.0}};

  ck_assert_int_eq(code, OK);

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], expected[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_valid_matrices2) {
  matrix_t A, B;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);

  double values_A[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double values_B[6] = {7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
  fill_test(&A, values_A, 2, 3);
  fill_test(&B, values_B, 3, 2);

  int code = s21_mult_matrix(&A, &B, NULL);

  ck_assert_int_eq(code, ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_incompatible_sizes) {
  matrix_t A, B, result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);

  double values_A[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double values_B[6] = {7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
  fill_test(&A, values_A, 2, 3);
  fill_test(&B, values_B, 2, 3);

  int code = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_zero_matrices) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  double values_A[4] = {0.0, 0.0, 0.0, 0.0};
  double values_B[4] = {0.0, 0.0, 0.0, 0.0};
  fill_test(&A, values_A, 2, 2);
  fill_test(&B, values_B, 2, 2);

  int code = s21_mult_matrix(&A, &B, &result);

  double expected[2][2] = {{0.0, 0.0}, {0.0, 0.0}};

  ck_assert_int_eq(code, OK);
  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], expected[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_identity_matrix) {
  matrix_t A, I, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &I);

  double values_A[4] = {1.0, 2.0, 3.0, 4.0};
  fill_test(&A, values_A, 2, 2);

  double values_I[4] = {1.0, 0.0, 0.0, 1.0};
  fill_test(&I, values_I, 2, 2);

  int code = s21_mult_matrix(&A, &I, &result);

  ck_assert_int_eq(code, OK);

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], A.matrix[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&I);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_scalar_matrix) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  double values_A[4] = {1.0, 2.0, 3.0, 4.0};
  fill_test(&A, values_A, 2, 2);

  int code = s21_mult_matrix(&A, &A, &result);

  double expected[2][2] = {{7.0, 10.0}, {15.0, 22.0}};

  ck_assert_int_eq(code, OK);

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], expected[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_square_matrix) {
  matrix_t A, B, result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  double values_A[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  double values_B[9] = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
  fill_test(&A, values_A, 3, 3);
  fill_test(&B, values_B, 3, 3);

  int code = s21_mult_matrix(&A, &B, &result);

  double expected[3][3] = {
      {30.0, 24.0, 18.0}, {84.0, 69.0, 54.0}, {138.0, 114.0, 90.0}};

  ck_assert_int_eq(code, OK);

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], expected[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_large_matrix) {
  matrix_t A, B, result;
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &B);

  double values_A[25] = {1.0,  2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,  9.0,
                         10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
                         19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0};
  double values_B[25] = {25.0, 24.0, 23.0, 22.0, 21.0, 20.0, 19.0, 18.0, 17.0,
                         16.0, 15.0, 14.0, 13.0, 12.0, 11.0, 10.0, 9.0,  8.0,
                         7.0,  6.0,  5.0,  4.0,  3.0,  2.0,  1.0};
  fill_test(&A, values_A, 5, 5);
  fill_test(&B, values_B, 5, 5);

  int code = s21_mult_matrix(&A, &B, &result);

  double expected[5][5] = {{175.0, 160.0, 145.0, 130.0, 115.0},
                           {550.0, 510.0, 470.0, 430.0, 390.0},
                           {925.0, 860.0, 795.0, 730.0, 665.0},
                           {1300.0, 1210.0, 1120.0, 1030.0, 940.0},
                           {1675.0, 1560.0, 1445.0, 1330.0, 1215.0}};

  ck_assert_int_eq(code, OK);

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], expected[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_rectangular_matrices) {
  matrix_t A, B, result;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 4, &B);

  double values_A[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double values_B[8] = {7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0};
  fill_test(&A, values_A, 3, 2);
  fill_test(&B, values_B, 2, 4);

  int code = s21_mult_matrix(&A, &B, &result);

  double expected[3][4] = {{29.0, 32.0, 35.0, 38.0},
                           {65.0, 72.0, 79.0, 86.0},
                           {101.0, 112.0, 123.0, 134.0}};

  ck_assert_int_eq(code, OK);

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], expected[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_large_values_matrix) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  double values_A[4] = {100000.0, 200000.0, 300000.0, 400000.0};
  double values_B[4] = {500000.0, 600000.0, 700000.0, 800000.0};
  fill_test(&A, values_A, 2, 2);
  fill_test(&B, values_B, 2, 2);

  int code = s21_mult_matrix(&A, &B, &result);

  double expected[2][2] = {{190000000000.0, 220000000000.0},
                           {430000000000.0, 500000000000.0}};

  ck_assert_int_eq(code, OK);

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], expected[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

Suite *mult_matrix_suite(void) {
  Suite *s = suite_create("mult_matrix");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, mult_matrix_both_invalid_internal);
  tcase_add_test(tc, mult_valid_matrices);
  tcase_add_test(tc, mult_valid_matrices2);
  tcase_add_test(tc, mult_incompatible_sizes);
  tcase_add_test(tc, mult_zero_matrices);
  tcase_add_test(tc, mult_identity_matrix);
  tcase_add_test(tc, mult_scalar_matrix);
  tcase_add_test(tc, mult_square_matrix);
  tcase_add_test(tc, mult_large_matrix);
  tcase_add_test(tc, mult_large_values_matrix);
  tcase_add_test(tc, mult_rectangular_matrices);

  suite_add_tcase(s, tc);
  return s;
}
