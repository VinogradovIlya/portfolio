#ifndef S21_MATRIX_HELP_H
#define S21_MATRIX_HELP_H

#include "s21_matrix.h"

int s21_matrix_init(matrix_t *matrix);
int s21_matrix_valid(const matrix_t *matrix);
void s21_matrix_copy(const matrix_t *A, matrix_t *B);

#endif  // S21_MATRIX_HELP_H
