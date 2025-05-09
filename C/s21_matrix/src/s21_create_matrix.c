#include "s21_matrix.h"

/**
 * Creates a matrix with the specified number of rows and columns, and
 * initializes all elements to zero. The allocated matrix is assigned to the
 * `result` parameter.
 *
 * @param rows The number of rows for the matrix. Must be greater than 0.
 * @param columns The number of columns for the matrix. Must be greater than 0.
 * @param result A pointer to a `matrix_t` structure where the created
 * matrix will be stored. The structure must be allocated by the caller.
 *
 * @return Returns `OK` (0) on success. If `rows` or `columns` are less than 1,
 * or if `result` is NULL, the function returns `ERROR` (1).
 */
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows < 1 || columns < 1 || !result) {
    return ERROR;
  }
  result->rows = rows;
  result->columns = columns;
  result->matrix = (double **)malloc(result->rows * sizeof(double *));
  for (int i = 0; i < result->rows; i++) {
    result->matrix[i] = (double *)calloc(result->columns, sizeof(double));
  }
  return OK;
}