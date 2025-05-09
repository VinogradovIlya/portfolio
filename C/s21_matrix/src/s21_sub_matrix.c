#include "s21_matrix.h"
#include "s21_matrix_help.h"

/**
 * Subtracts matrix B from matrix A and stores the result in the provided result
 * matrix.
 *
 * @param A A pointer to the first matrix (minuend).
 * @param B A pointer to the second matrix (subtrahend).
 * @param result A pointer to the matrix where the result of the subtraction
 * will be stored.
 * @return Returns:
 *         - OK (0) if the subtraction is completed successfully.
 *         - ERROR (1) if initialization or validation of the matrices fails.
 *         - CALC_ERROR (2) if the matrices have different dimensions.
 */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_matrix_init(result)) return ERROR;

  if (!s21_matrix_valid(A) || !s21_matrix_valid(B)) return ERROR;

  if (A->rows != B->rows || A->columns != B->columns) return CALC_ERROR;

  int stop = s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows && stop == 0; i++) {
    for (int j = 0; j < A->columns && stop == 0; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      //      stop = isinf(result->matrix[i][j]) ? 1 : 0; // ?
    }
  }
  return !stop ? OK : ERROR;
}