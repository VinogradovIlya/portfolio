#include "s21_matrix.h"
#include "s21_matrix_help.h"

/**
 * Checks the equality of two matrices.
 *
 * This function compares two matrices to determine if they are equal.
 * Two matrices are considered equal if they have the same dimensions
 * and all their elements differ by less than a predefined epsilon value.
 *
 * @param A A pointer to the first matrix.
 * @param B A pointer to the second matrix.
 * @return SUCCESS (1) if the matrices are equal, FAILURE (0) otherwise.
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int a_is_init = (A->matrix == NULL && A->rows == 0 && A->columns == 0);
  int b_is_init = (B->matrix == NULL && B->rows == 0 && B->columns == 0);
  if (a_is_init && b_is_init) {
    return SUCCESS;
  }

  if (!A || !B || (A->rows != B->rows) || (A->columns != B->columns)) {
    return FAILURE;
  }

  if (!s21_matrix_valid(A) || !s21_matrix_valid(B)) {
    return FAILURE;
  }

  int stop = 0;
  for (int i = 0; i < A->rows && stop == 0; i++) {
    for (int j = 0; j < A->columns && stop == 0; j++) {
      stop = fabs(A->matrix[i][j] - B->matrix[i][j]) >= EPSILON;
    }
  }

  return (stop == 0) ? SUCCESS : FAILURE;
}