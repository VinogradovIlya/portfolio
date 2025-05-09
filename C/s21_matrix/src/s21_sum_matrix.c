#include "s21_matrix.h"
#include "s21_matrix_help.h"

/**
 * Adds two matrices A and B and stores the result in the supplied result
 * matrix.
 *
 * @param A Pointer to the first matrix to be summed.
 * @param B Pointer to the second matrix to be summed.
 * @param result Pointer to the matrix to store the result of the summation.
 * @return Returns OK (0) if the operation is successful, ERROR (1) if there is
 * an error initializing or validating matrices, or CALC_ERROR (2) if matrix
 * dimensions do not match.
 */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_matrix_init(result)) return ERROR;
  if (!s21_matrix_valid(A) || !s21_matrix_valid(B)) return ERROR;

  if (A->rows != B->rows || A->columns != B->columns) return CALC_ERROR;

  int stop = s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows && stop == 0; i++) {
    for (int j = 0; j < A->columns && stop == 0; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      //      stop = isinf(result->matrix[i][j]) ? 1 : 0; // ?
    }
  }
  return !stop ? OK : ERROR;
}