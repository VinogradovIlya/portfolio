#include "tests.h"

START_TEST(det_1x1) {
  double values[1][1] = {{5.0}};

  matrix_t m = {0};
  s21_create_matrix(1, 1, &m);
  fill_test(&m, (double *)values, 1, 1);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 5.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_2x2_simple) {
  double values[2][2] = {{1.0, 2.0}, {3.0, 4.0}};

  matrix_t m = {0};
  s21_create_matrix(2, 2, &m);
  fill_test(&m, (double *)values, 2, 2);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, -2.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_2x2_zero) {
  double values[2][2] = {{0.0, 0.0}, {0.0, 0.0}};

  matrix_t m = {0};
  s21_create_matrix(2, 2, &m);
  fill_test(&m, (double *)values, 2, 2);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 0.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_2x2_negative) {
  double values[2][2] = {{-1.0, -2.0}, {-3.0, -4.0}};

  matrix_t m = {0};
  s21_create_matrix(2, 2, &m);
  fill_test(&m, (double *)values, 2, 2);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, -2.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_2x2_large) {
  double values[2][2] = {{1e10, 2e10}, {3e10, 4e10}};

  matrix_t m = {0};
  s21_create_matrix(2, 2, &m);
  fill_test(&m, (double *)values, 2, 2);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, -2e20, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_3x3_simple) {
  double values[3][3] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};

  matrix_t m = {0};
  s21_create_matrix(3, 3, &m);
  fill_test(&m, (double *)values, 3, 3);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 0.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_3x3_nonzero) {
  double values[3][3] = {{2.0, 4.0, 6.0}, {1.0, 3.0, 5.0}, {0.0, 2.0, 4.0}};

  matrix_t m = {0};
  s21_create_matrix(3, 3, &m);
  fill_test(&m, (double *)values, 3, 3);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 0.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_3x3_zero_row) {
  double values[3][3] = {{1.0, 2.0, 3.0}, {0.0, 0.0, 0.0}, {7.0, 8.0, 9.0}};

  matrix_t m = {0};
  s21_create_matrix(3, 3, &m);
  fill_test(&m, (double *)values, 3, 3);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 0.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_3x3_zero_diag) {
  double values[3][3] = {{0.0, 2.0, 3.0}, {4.0, 0.0, 6.0}, {7.0, 8.0, 0.0}};

  matrix_t m = {0};
  s21_create_matrix(3, 3, &m);
  fill_test(&m, (double *)values, 3, 3);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 180.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_3x3_mixed_signs) {
  double values[3][3] = {{1.0, -2.0, 3.0}, {-4.0, 5.0, -6.0}, {7.0, -8.0, 9.0}};

  matrix_t m = {0};
  s21_create_matrix(3, 3, &m);
  fill_test(&m, (double *)values, 3, 3);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 0.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_3x3_float) {
  double values[3][3] = {{1.5, 2.5, 3.5}, {4.5, 5.5, 6.5}, {7.5, 8.5, 9.5}};

  matrix_t m = {0};
  s21_create_matrix(3, 3, &m);
  fill_test(&m, (double *)values, 3, 3);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 0.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_3x3_small) {
  double values[3][3] = {
      {1e-10, 2e-10, 3e-10}, {4e-10, 5e-10, 6e-10}, {7e-10, 8e-10, 9e-10}};

  matrix_t m = {0};
  s21_create_matrix(3, 3, &m);
  fill_test(&m, (double *)values, 3, 3);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 0.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_3x3_random1) {
  double values[3][3] = {{2.0, 5.0, 7.0}, {6.0, 3.0, 4.0}, {5.0, -2.0, -3.0}};

  matrix_t m = {0};
  s21_create_matrix(3, 3, &m);
  fill_test(&m, (double *)values, 3, 3);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, -1.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_4x4) {
  double values[4][4] = {{1.0, 0.0, 2.0, -1.0},
                         {3.0, 0.0, 0.0, 5.0},
                         {2.0, 1.0, 4.0, -3.0},
                         {1.0, 0.0, 5.0, 0.0}};

  matrix_t m = {0};
  s21_create_matrix(4, 4, &m);
  fill_test(&m, (double *)values, 4, 4);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 30.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_4x4_zero_col) {
  double values[4][4] = {{1.0, 0.0, 2.0, 3.0},
                         {4.0, 0.0, 5.0, 6.0},
                         {7.0, 0.0, 8.0, 9.0},
                         {10.0, 0.0, 11.0, 12.0}};

  matrix_t m = {0};
  s21_create_matrix(4, 4, &m);
  fill_test(&m, (double *)values, 4, 4);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 0.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_4x4_precision) {
  double values[4][4] = {{0.1, 0.2, 0.3, 0.4},
                         {0.5, 0.6, 0.7, 0.8},
                         {0.9, 1.0, 1.1, 1.2},
                         {1.3, 1.4, 1.5, 1.6}};

  matrix_t m = {0};
  s21_create_matrix(4, 4, &m);
  fill_test(&m, (double *)values, 4, 4);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 0.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_4x4_random2) {
  double values[4][4] = {{1.0, 2.0, 3.0, 4.0},
                         {5.0, 6.0, 7.0, 8.0},
                         {9.0, 10.0, 11.0, 12.0},
                         {13.0, 14.0, 15.0, 16.0}};

  matrix_t m = {0};
  s21_create_matrix(4, 4, &m);
  fill_test(&m, (double *)values, 4, 4);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 0.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_5x5_diag) {
  double values[5][5] = {{2.0, 0.0, 0.0, 0.0, 0.0},
                         {0.0, 3.0, 0.0, 0.0, 0.0},
                         {0.0, 0.0, 4.0, 0.0, 0.0},
                         {0.0, 0.0, 0.0, 5.0, 0.0},
                         {0.0, 0.0, 0.0, 0.0, 6.0}};

  matrix_t m = {0};
  s21_create_matrix(5, 5, &m);
  fill_test(&m, (double *)values, 5, 5);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 720.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_5x5_sparse) {
  double values[5][5] = {{1.0, 0.0, 0.0, 0.0, 2.0},
                         {0.0, 3.0, 0.0, 4.0, 0.0},
                         {0.0, 0.0, 5.0, 0.0, 0.0},
                         {0.0, 6.0, 0.0, 7.0, 0.0},
                         {8.0, 0.0, 0.0, 0.0, 9.0}};

  matrix_t m = {0};
  s21_create_matrix(5, 5, &m);
  fill_test(&m, (double *)values, 5, 5);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 105.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_5x5_large) {
  double values[5][5] = {{1e6, 2e6, 3e6, 4e6, 5e6},
                         {6e6, 7e6, 8e6, 9e6, 1e7},
                         {1e7, 2e7, 3e7, 4e7, 5e7},
                         {6e7, 7e7, 8e7, 9e7, 1e8},
                         {1e8, 2e8, 3e8, 4e8, 5e8}};

  matrix_t m = {0};
  s21_create_matrix(5, 5, &m);
  fill_test(&m, (double *)values, 5, 5);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 0.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_not_square) {
  double values[2][3] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};

  matrix_t m = {0};
  s21_create_matrix(2, 3, &m);
  fill_test(&m, (double *)values, 2, 3);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), CALC_ERROR);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_null_matrix) {
  matrix_t m = {NULL, 0, 0};
  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), ERROR);
}
END_TEST

START_TEST(det_null_pointer) {
  ck_assert_int_eq(s21_determinant(NULL, NULL), ERROR);
}
END_TEST

START_TEST(det_1x1_zero) {
  double values[1][1] = {{0.0}};

  matrix_t m = {0};
  s21_create_matrix(1, 1, &m);
  fill_test(&m, (double *)values, 1, 1);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 0.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_2x2_one_zero) {
  double values[2][2] = {{1.0, 0.0}, {0.0, 1.0}};

  matrix_t m = {0};
  s21_create_matrix(2, 2, &m);
  fill_test(&m, (double *)values, 2, 2);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 1.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_3x3_identity) {
  double values[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};

  matrix_t m = {0};
  s21_create_matrix(3, 3, &m);
  fill_test(&m, (double *)values, 3, 3);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 1.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_4x4_upper_triangular) {
  double values[4][4] = {{1.0, 2.0, 3.0, 4.0},
                         {0.0, 5.0, 6.0, 7.0},
                         {0.0, 0.0, 8.0, 9.0},
                         {0.0, 0.0, 0.0, 10.0}};

  matrix_t m = {0};
  s21_create_matrix(4, 4, &m);
  fill_test(&m, (double *)values, 4, 4);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 400.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_5x5_lower_triangular) {
  double values[5][5] = {{1.0, 0.0, 0.0, 0.0, 0.0},
                         {2.0, 3.0, 0.0, 0.0, 0.0},
                         {4.0, 5.0, 6.0, 0.0, 0.0},
                         {7.0, 8.0, 9.0, 10.0, 0.0},
                         {11.0, 12.0, 13.0, 14.0, 15.0}};

  matrix_t m = {0};
  s21_create_matrix(5, 5, &m);
  fill_test(&m, (double *)values, 5, 5);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 2700.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_3x3_permutation) {
  double values[3][3] = {{0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0}};

  matrix_t m = {0};
  s21_create_matrix(3, 3, &m);
  fill_test(&m, (double *)values, 3, 3);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, -1.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_4x4_alternating_signs) {
  double values[4][4] = {{1.0, -1.0, 1.0, -1.0},
                         {1.0, 1.0, -1.0, -1.0},
                         {1.0, -1.0, -1.0, 1.0},
                         {1.0, 1.0, 1.0, 1.0}};

  matrix_t m = {0};
  s21_create_matrix(4, 4, &m);
  fill_test(&m, (double *)values, 4, 4);

  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, -16.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_nan_matrix) {
  matrix_t m = {0};
  s21_create_matrix(2, 2, &m);
  m.matrix[0][0] = NAN;
  m.matrix[0][1] = 2.0;
  m.matrix[1][0] = 3.0;
  m.matrix[1][1] = 4.0;
  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert(isnan(det));
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_inf_matrix) {
  matrix_t m = {0};
  s21_create_matrix(2, 2, &m);
  m.matrix[0][0] = INFINITY;
  m.matrix[0][1] = 2.0;
  m.matrix[1][0] = 3.0;
  m.matrix[1][1] = 4.0;
  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert(isinf(det));
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_big_values) {
  double values[4] = {1e8, 2e8, 3e8, 4e8};
  matrix_t m = {0};
  s21_create_matrix(2, 2, &m);
  fill_test(&m, values, 2, 2);
  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, -2e16, EPSILON);  // с допуском из-за float
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(det_lower_triangular) {
  double values[9] = {2.0, 0.0, 0.0, 4.0, 3.0, 0.0, 1.0, 5.0, 6.0};
  matrix_t m = {0};
  s21_create_matrix(3, 3, &m);
  fill_test(&m, values, 3, 3);
  double det = 0;
  ck_assert_int_eq(s21_determinant(&m, &det), OK);
  ck_assert_double_eq_tol(det, 36.0, EPSILON);
  s21_remove_matrix(&m);
}
END_TEST

Suite *determinant_suite(void) {
  Suite *s = suite_create("Determinant");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, det_1x1);
  tcase_add_test(tc, det_2x2_simple);
  tcase_add_test(tc, det_2x2_zero);
  tcase_add_test(tc, det_2x2_negative);
  tcase_add_test(tc, det_2x2_large);
  tcase_add_test(tc, det_3x3_simple);
  tcase_add_test(tc, det_3x3_nonzero);
  tcase_add_test(tc, det_3x3_zero_row);
  tcase_add_test(tc, det_3x3_zero_diag);
  tcase_add_test(tc, det_3x3_mixed_signs);
  tcase_add_test(tc, det_3x3_float);
  tcase_add_test(tc, det_3x3_small);
  tcase_add_test(tc, det_3x3_random1);
  tcase_add_test(tc, det_4x4);
  tcase_add_test(tc, det_4x4_zero_col);
  tcase_add_test(tc, det_4x4_precision);
  tcase_add_test(tc, det_4x4_random2);
  tcase_add_test(tc, det_5x5_diag);
  tcase_add_test(tc, det_5x5_sparse);
  tcase_add_test(tc, det_5x5_large);
  tcase_add_test(tc, det_not_square);
  tcase_add_test(tc, det_null_matrix);
  tcase_add_test(tc, det_null_pointer);
  tcase_add_test(tc, det_1x1_zero);
  tcase_add_test(tc, det_2x2_one_zero);
  tcase_add_test(tc, det_3x3_identity);
  tcase_add_test(tc, det_4x4_upper_triangular);
  tcase_add_test(tc, det_5x5_lower_triangular);
  tcase_add_test(tc, det_3x3_permutation);
  tcase_add_test(tc, det_4x4_alternating_signs);
  tcase_add_test(tc, det_nan_matrix);
  tcase_add_test(tc, det_inf_matrix);
  tcase_add_test(tc, det_big_values);
  tcase_add_test(tc, det_lower_triangular);

  suite_add_tcase(s, tc);
  return s;
}
