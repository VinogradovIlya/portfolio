#include "s21_matrix.h"
#include "s21_matrix_help.h"

/**
 * Transposes the given matrix A. The rows of matrix A will become the columns
 * of the resulting matrix, and the columns of matrix A will become the rows of
 * the resulting matrix.
 *
 * The result is written into the matrix pointed to by the result parameter. If
 * the function encounters an invalid matrix or fails to allocate memory for the
 * result matrix, an error code is returned.
 *
 * @param A Pointer to the source matrix to be transposed. Must be a valid
 * matrix.
 * @param result Pointer to the matrix where the transposed result will be
 * stored. Must be initialized.
 * @return An integer representing the operation outcome:
 *         - OK (0) if the transpose operation was successful.
 *         - ERROR (1) if an error occurred (e.g., invalid matrix or memory
 * allocation failure).
 */
int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!s21_matrix_init(result)) return ERROR;

  if (!s21_matrix_valid(A)) return ERROR;

  int suc = s21_create_matrix(A->columns, A->rows, result);
  if (!suc) {
    for (int row = 0; row < A->rows; row++) {
      for (int col = 0; col < A->columns; col++) {
        result->matrix[col][row] = A->matrix[row][col];
      }
    }
  }

  return !suc ? OK : ERROR;
}