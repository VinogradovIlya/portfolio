#include "s21_matrix.h"

/**
 * @brief Copies the content of matrix A to matrix B.
 *
 * This function iterates through all the rows and columns of the matrix A
 * and assigns each element to the corresponding position in matrix B.
 * It's assumed that matrix B has already been created with the same dimensions
 * as matrix A.
 *
 * @param A Pointer to the source matrix to be copied.
 * @param B Pointer to the target matrix where the contents of A will be copied.
 */
void s21_matrix_copy(const matrix_t *A, matrix_t *B) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      B->matrix[i][j] = A->matrix[i][j];
    }
  }
}

/**
 * Initializes a matrix by setting its rows and columns to 0 and its data
 * pointer to NULL.
 *
 * @param matrix A pointer to a matrix_t structure to be initialized.
 * @return SUCCESS (1) if the matrix is successfully initialized, FAILURE (0) if
 * the provided matrix pointer is NULL.
 */
int s21_matrix_init(matrix_t *matrix) {
  if (!matrix) return FAILURE;
  matrix->rows = 0;
  matrix->columns = 0;
  matrix->matrix = NULL;
  return SUCCESS;
}

/**
 * Checks whether the given matrix is valid.
 * A matrix is considered valid if:
 * - The matrix pointer is not null.
 * - The internal matrix data pointer is not null.
 * - The number of rows and columns is greater than 0.
 * - Each row in the matrix is not null.
 *
 * @param matrix A pointer to the matrix_t structure to validate.
 * @return SUCCESS (1) if the matrix is valid, otherwise FAILURE (0).
 */
int s21_matrix_valid(const matrix_t *matrix) {
  if (matrix == NULL) {
    return FAILURE;
  }

  if (matrix->matrix == NULL) {
    return FAILURE;
  }

  if (matrix->rows < 1 || matrix->columns < 1) {
    return FAILURE;
  }

  for (int i = 0; i < matrix->rows; i++) {
    if (matrix->matrix[i] == NULL) return FAILURE;
  }

  return SUCCESS;
}
