#include "s21_matrix.h"
#include "s21_matrix_help.h"

/**
 * Multiplies each element of the given matrix by a specified scalar number and
 * stores the result in the output matrix.
 *
 * @param A Pointer to the input matrix to be multiplied. Must be a valid
 * matrix.
 * @param number The scalar value to multiply each matrix element by.
 * @param result Pointer to the resulting matrix where the operation's result
 *        will be stored. Must not be null.
 * @return Returns OK (0) if the operation is successful, or ERROR (1) in case
 *         of invalid input or an issue during matrix creation.
 */
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!s21_matrix_valid(A)) return ERROR;
  if (!result) return ERROR;

  s21_matrix_init(result);
  int suc = s21_create_matrix(A->rows, A->columns, result);
  if (suc == OK) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }

  return (suc == OK) ? OK : ERROR;
}