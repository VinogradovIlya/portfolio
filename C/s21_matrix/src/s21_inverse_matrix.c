#include "s21_matrix.h"
#include "s21_matrix_help.h"

/**
 * Computes the inverse of a given square matrix.
 *
 * @param A Pointer to the input matrix to be inverted. Must be a valid, square
 * matrix.
 * @param result Pointer to the matrix structure that will store the resulting
 * inverse matrix. Memory must be initialized before storing the result.
 * @return OK (0) if the matrix inversion was successful.
 *         ERROR (1) if the input matrix or result pointer is invalid.
 *         CALC_ERROR (2) if the matrix is singular or not square, making
 * inversion impossible.
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!s21_matrix_valid(A)) return ERROR;
  if (A->rows != A->columns) return CALC_ERROR;
  if (!s21_matrix_init(result)) return ERROR;

  matrix_t temp = {0};
  matrix_t temp1 = {0};
  int res = OK;
  double det = 0.0;
  res = s21_determinant(A, &det);
  if (res == OK && fabs(det) > EPSILON) {
    s21_calc_complements(A, &temp);
    s21_transpose(&temp, &temp1);
    res = s21_mult_number(&temp1, 1.0 / det, result);
  } else
    res = CALC_ERROR;
  s21_remove_matrix(&temp1);
  s21_remove_matrix(&temp);

  return res;
}