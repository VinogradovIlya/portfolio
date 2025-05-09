#include "tests.h"

void fill_test(matrix_t *m, const double *values, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m->matrix[i][j] = values[i * cols + j];
    }
  }
}

int main(void) {
  int failed_total = 0;
  int checks_total = 0;

  Suite *suites[] = {create_matrix_suite(),
                     determinant_suite(),
                     eq_matrix_suite(),
                     inverse_matrix_suite(),
                     mult_matrix_suite(),
                     mult_number_suite(),
                     sum_matrix_suite(),
                     sub_matrix_suite(),
                     calc_complements(),
                     transpose_suite(),
                     NULL};

  for (int i = 0; suites[i] != NULL; i++) {
    SRunner *sr = srunner_create(suites[i]);
    srunner_run_all(sr, CK_NORMAL);
    failed_total += srunner_ntests_failed(sr);
    checks_total += srunner_ntests_run(sr);
    srunner_free(sr);
  }

  printf("\n========================================\n");
  printf("TOTAL: Checks: %d, Failures: %d, Errors: 0\n", checks_total,
         failed_total);
  printf("========================================\n");

  return (failed_total == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
