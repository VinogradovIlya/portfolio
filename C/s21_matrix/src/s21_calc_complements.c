#include "s21_matrix.h"
#include "s21_matrix_help.h"

/**
 * @brief Computes the minor of a matrix element by removing the specified row
 * and column and calculating the determinant of the resulting submatrix.
 *
 * The minor of an element in a matrix is the determinant of the submatrix that
 * remains after removing the element's row and column. This function calculates
 * the minor for a given row and column in the input matrix.
 *
 * @param A Pointer to the input matrix from which the minor will be calculated.
 *           This matrix must be valid and properly initialized.
 * @param row The row index of the element for which the minor is being
 * calculated. This index must be within the range of the matrix rows.
 * @param column The column index of the element for which the minor is being
 * calculated. This index must be within the range of the matrix columns.
 * @param result Pointer to store the calculated minor (determinant of the
 * submatrix). This memory location must be valid for storing the result.
 */
void s21_minor(const matrix_t *A, const int row, const int column,
               double *result) {
  matrix_t temp;
  s21_create_matrix(A->rows - 1, A->columns - 1, &temp);

  int temp_i = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == row) continue;
    int temp_j = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == column) continue;
      temp.matrix[temp_i][temp_j] = A->matrix[i][j];
      temp_j++;
    }
    temp_i++;
  }

  s21_determinant(&temp, result);
  s21_remove_matrix(&temp);
}

/**
 * @brief Calculates the matrix of algebraic complements for a given square
 * matrix.
 *
 * This function computes the matrix of algebraic complements for a given input
 * matrix A and stores the result in the provided result matrix. The matrix of
 * algebraic complements is a square matrix where each element is calculated as
 * the signed determinant of the minor matrix obtained by removing one row and
 * one column from the original matrix.
 *
 * The function performs the following steps:
 * 1. Checks if the input matrix A is valid.
 * 2. Ensures that the input matrix is square.
 * 3. Initializes the result matrix.
 * 4. If the matrix has a single element (1 x 1), sets the result matrix to 1.
 * 5. For larger matrices, computes the algebraic complements using determinants
 * of minors and their respective signs.
 *
 * @param A Pointer to the input square matrix from which complements are
 * calculated.
 * @param result Pointer to the matrix where the computed complements will be
 * stored.
 * @return Returns OK (0) on success or ERROR (1) in case of invalid input or
 * memory allocation failure.
 *
 * Preconditions:
 *  - The input matrix A must be valid and initialized.
 *  - The result matrix should not be pre-initialized; it will be allocated
 * internally.
 *
 * Postconditions:
 *  - The result matrix is modified to contain the matrix of algebraic
 * complements.
 *  - The input matrix A remains unmodified.
 */
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!s21_matrix_valid(A)) return ERROR;

  if (A->rows != A->columns) return ERROR;

  if (!s21_matrix_init(result)) return ERROR;

  s21_create_matrix(A->rows, A->columns, result);

  if (A->rows == 1) {
    result->matrix[0][0] = 1;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        double minor;
        s21_minor(A, i, j, &minor);
        result->matrix[i][j] = ((i + j) % 2 == 0 ? 1.0 : -1.0) * minor;
      }
    }
  }

  return OK;
}
