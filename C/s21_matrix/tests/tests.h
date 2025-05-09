#include <check.h>
#include <stdio.h>

#include "../src/s21_matrix.h"
#include "../src/s21_matrix_help.h"

void fill_test(matrix_t *m, const double *values, int rows, int cols);

Suite *create_matrix_suite(void);
Suite *determinant_suite(void);
Suite *eq_matrix_suite(void);
Suite *inverse_matrix_suite(void);
Suite *mult_matrix_suite(void);
Suite *mult_number_suite(void);
Suite *remove_matrix_suite(void);
Suite *sub_matrix_suite(void);
Suite *sum_matrix_suite(void);
Suite *transpose_suite(void);
Suite *calc_complements(void);