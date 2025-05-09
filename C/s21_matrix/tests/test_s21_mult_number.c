#include "../src/s21_matrix_help.h"
#include "tests.h"

START_TEST(mult_number_basic) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  double values_A[4] = {1.0, 2.0, 3.0, 4.0};
  fill_test(&A, values_A, 2, 2);

  double scalar = 2.0;
  s21_mult_number(&A, scalar, &result);

  double expected[2][2] = {{2.0, 4.0}, {6.0, 8.0}};

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], expected[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_edge_case_zero) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  double values_A[4] = {1.0, 2.0, 3.0, 4.0};
  fill_test(&A, values_A, 2, 2);

  double scalar = 0.0;
  s21_mult_number(&A, scalar, &result);

  double expected[2][2] = {{0.0, 0.0}, {0.0, 0.0}};

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], expected[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_edge_case_negative) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  double values_A[4] = {1.0, 2.0, 3.0, 4.0};
  fill_test(&A, values_A, 2, 2);

  double scalar = -1.0;
  s21_mult_number(&A, scalar, &result);

  double expected[2][2] = {{-1.0, -2.0}, {-3.0, -4.0}};

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], expected[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_edge_case_identity_matrix) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  double values_A[9] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
  fill_test(&A, values_A, 3, 3);

  double scalar = 5.0;
  s21_mult_number(&A, scalar, &result);

  double expected[3][3] = {{5.0, 0.0, 0.0}, {0.0, 5.0, 0.0}, {0.0, 0.0, 5.0}};

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], expected[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_matrix_4_3) {
  matrix_t A, result;
  s21_create_matrix(4, 3, &A);

  double values_A[12] = {
      8.045443250305796,  9.320310659761548, 1.7003517776598671,
      1.7513154645173015, 8.823084738176718, 1.9417351847438997,
      6.963311647704806,  3.038792759413456, 2.206840268937719,
      3.6109712710756514, 9.67735342076212,  9.037491632672484};
  fill_test(&A, values_A, 4, 3);

  double scalar = 7.381627197409966;
  s21_mult_number(&A, scalar, &result);

  double expected[4][3] = {
      {59.3884627116757, 68.79905865440585, 12.551362927138458},
      {12.92755786412558, 65.12872226837804, 14.333165249873435},
      {51.400570642739396, 22.431235280178846, 16.29007214953019},
      {26.65484374363806, 71.43461520964604, 66.7113940321002}};

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], expected[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_empty_matrix) {
  matrix_t A, result;
  s21_matrix_init(&A);
  double scalar = 5.0;

  int status = s21_mult_number(&A, scalar, &result);
  ck_assert_int_eq(status, ERROR);
}

END_TEST

Suite *mult_number_suite(void) {
  Suite *s = suite_create("mult_number");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, mult_number_basic);
  tcase_add_test(tc, mult_number_edge_case_zero);
  tcase_add_test(tc, mult_number_edge_case_negative);
  tcase_add_test(tc, mult_number_edge_case_identity_matrix);
  tcase_add_test(tc, mult_number_empty_matrix);
  tcase_add_test(tc, mult_number_matrix_4_3);

  suite_add_tcase(s, tc);
  return s;
}
