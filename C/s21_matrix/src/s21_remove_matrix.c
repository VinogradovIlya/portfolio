#include "s21_matrix.h"
#include "s21_matrix_help.h"

/**
 * @brief Frees all allocated memory for a matrix and resets its structure.
 *
 * This function is responsible for safely deallocating all dynamically
 * allocated memory associated with the provided matrix_t structure. It also
 * nullifies the pointer to the matrix's row array (matrix), and resets the row
 * (rows) and column (columns) counts to zero, ensuring the matrix structure is
 * in a clean and safe state.
 *
 * @param A A pointer to the matrix_t structure whose memory needs to be
 * cleared. If the pointer A is NULL, the function returns immediately. If
 * A->matrix is NULL (e.g., the matrix was not created or has already been
 * cleared), the function will handle this safely and zero out the rows and
 * columns fields.
 */
void s21_remove_matrix(matrix_t *A) {
  if (A == NULL) return;
  if (A->matrix != NULL && A->rows > 0) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
  }
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}