#include "s21_matrix.h"
#include "s21_matrix_help.h"

/**
 * Performs matrix multiplication on two given matrices and stores the result in
 * the provided result matrix. The function assumes that the result matrix is
 * already initialized and that the dimensions of the matrices are compatible
 * for multiplication (i.e., the number of columns in the first matrix equals
 * the number of rows in the second matrix).
 *
 * @param matrix1 Pointer to the first input matrix (left operand in the
 * multiplication).
 * @param matrix2 Pointer to the second input matrix (right operand in the
 * multiplication).
 * @param result Pointer to the matrix where the multiplication result is
 * stored. Must be preallocated.
 */
void multiply_matrix(matrix_t *matrix1, matrix_t *matrix2, matrix_t *result);

/**
 * Multiplies two matrices A and B and stores the result in the matrix result.
 *
 * @param A Pointer to the first input matrix of type matrix_t. Must be
 * initialized and valid.
 * @param B Pointer to the second input matrix of type matrix_t. Must be
 * initialized and valid.
 * @param result Pointer to the resultant matrix of type matrix_t where the
 * result of the multiplication will be stored. Must be a valid memory location.
 * @return Returns OK (0) if the operation is successfully performed, ERROR (1)
 * if invalid inputs or initialization issues occur, CALC_ERROR (2) if matrix
 * dimensions do not allow multiplication.
 */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_matrix_valid(A) && !s21_matrix_valid(B)) return ERROR;

  if (!s21_matrix_init(result)) return ERROR;

  if (A->columns != B->rows) return CALC_ERROR;

  int suc = s21_create_matrix(A->rows, B->columns, result);
  if (!suc) {
    multiply_matrix(A, B, result);
  }

  return (!suc) ? OK : CALC_ERROR;
}

/**
 * Performs the multiplication of two matrices and stores the result in the
 * provided result matrix. Assumes that the matrices are valid and compatible
 * for multiplication.
 *
 * @param matrix1 A pointer to the first matrix (multiplicand).
 * @param matrix2 A pointer to the second matrix (multiplier).
 * @param result A pointer to the resulting matrix where the product is stored.
 */
void multiply_matrix(matrix_t *matrix1, matrix_t *matrix2, matrix_t *result) {
  for (int i = 0; i < matrix1->rows; i++) {
    for (int j = 0; j < matrix2->columns; j++) {
      for (int k = 0; k < matrix1->columns; k++) {
        result->matrix[i][j] += matrix1->matrix[i][k] * matrix2->matrix[k][j];
      }
    }
  }
}