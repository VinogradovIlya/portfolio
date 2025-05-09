#include "s21_matrix.h"
#include "s21_matrix_help.h"

/**
 * Swaps two rows in a given matrix.
 *
 * @param matrix A pointer to the matrix where rows will be swapped.
 * @param i The index of the first row to be swapped.
 * @param j The index of the second row to be swapped.
 */
void s21_swap_lines(matrix_t *matrix, const int i, const int j) {
  double *temp = matrix->matrix[i];
  matrix->matrix[i] = matrix->matrix[j];
  matrix->matrix[j] = temp;
}

/**
 * Calculates the determinant of a square matrix using Gaussian elimination.
 *
 * @param matrix A pointer to the matrix_t structure representing the matrix
 *               whose determinant is to be calculated. The matrix must be
 *               square (rows == columns).
 * @return The determinant of the matrix as a double. If the matrix is singular
 *         (determinant is zero), returns 0.0.
 */
double s21_gaus(matrix_t *matrix) {
  int sign_factor = 1;
  double det = 1.0;
  for (int i = 0; i < matrix->rows; i++) {
    int pivot_row = i;
    for (int j = i + 1; j < matrix->rows; j++) {
      if (fabs(matrix->matrix[j][i]) > fabs(matrix->matrix[pivot_row][i])) {
        pivot_row = j;
      }
    }
    if (pivot_row != i) {
      s21_swap_lines(matrix, i, pivot_row);
      sign_factor *= -1;
    }
    if (fabs(matrix->matrix[i][i]) <= EPSILON) {
      return 0.0;
    }
    for (int j = i + 1; j < matrix->rows; j++) {
      double factor = matrix->matrix[j][i] / matrix->matrix[i][i];
      for (int k = i; k < matrix->columns; k++) {
        matrix->matrix[j][k] -= factor * matrix->matrix[i][k];
      }
    }
    det *= matrix->matrix[i][i];
  }
  return det * sign_factor;
}

/**
 * Calculates the determinant of the given square matrix.
 * The function validates the input, ensures the matrix is square,
 * and computes the determinant using Gaussian elimination.
 *
 * @param matrix A pointer to the matrix for which the determinant is to be
 * calculated. Must be a valid and square matrix.
 * @param result A pointer to a double variable where the computed determinant
 * value will be stored.
 * @return Returns OK (0) on successful calculation, ERROR (1) for invalid
 * inputs, or CALC_ERROR (2) if the matrix is not square.
 */
int s21_determinant(matrix_t *matrix, double *result) {
  if (!s21_matrix_valid(matrix)) return ERROR;

  if (matrix->rows != matrix->columns) return CALC_ERROR;

  if (!result) return ERROR;

  if (matrix->rows == 1) {
    *result = matrix->matrix[0][0];
  } else if (matrix->rows == 2) {
    *result = matrix->matrix[0][0] * matrix->matrix[1][1] -
              matrix->matrix[0][1] * matrix->matrix[1][0];
  } else {
    matrix_t temp = {0};
    s21_create_matrix(matrix->rows, matrix->columns, &temp);
    s21_matrix_copy(matrix, &temp);
    *result = s21_gaus(&temp);
    s21_remove_matrix(&temp);
  }
  return OK;
}
