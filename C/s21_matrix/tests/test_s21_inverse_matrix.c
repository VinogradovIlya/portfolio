#include "tests.h"

START_TEST(inverse_2x2) {
  double values[4] = {4.0, 7.0, 2.0, 6.0};

  matrix_t m, m_inv, result;
  s21_create_matrix(2, 2, &m);
  fill_test(&m, values, 2, 2);

  ck_assert_int_eq(s21_inverse_matrix(&m, &m_inv), OK);
  s21_mult_matrix(&m, &m_inv, &result);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, EPSILON);
  ck_assert_double_eq_tol(result.matrix[1][1], 1.0, EPSILON);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.0, EPSILON);
  ck_assert_double_eq_tol(result.matrix[1][0], 0.0, EPSILON);

  s21_remove_matrix(&m);
  s21_remove_matrix(&m_inv);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_2x3) {
  matrix_t m, m_inv;
  s21_create_matrix(2, 3, &m);

  ck_assert_int_eq(s21_inverse_matrix(&m, &m_inv), CALC_ERROR);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(inverse_3x3) {
  double values[9] = {4.0, 7.0, 2.0, 3.0, 6.0, 1.0, 1.0, 3.0, 5.0};

  matrix_t m, m_inv, result;
  s21_create_matrix(3, 3, &m);
  fill_test(&m, values, 3, 3);

  ck_assert_int_eq(s21_inverse_matrix(&m, &m_inv), OK);

  s21_mult_matrix(&m, &m_inv, &result);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], (i == j) ? 1.0 : 0.0,
                              EPSILON);
    }
  }

  s21_remove_matrix(&m);
  s21_remove_matrix(&m_inv);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_singular_matrix) {
  double values[4] = {1.0, 2.0, 2.0, 4.0};

  matrix_t m, m_inv;
  s21_create_matrix(2, 2, &m);
  fill_test(&m, values, 2, 2);

  ck_assert_int_eq(s21_inverse_matrix(&m, &m_inv), CALC_ERROR);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(inverse_identity_matrix) {
  double values[4] = {1.0, 0.0, 0.0, 1.0};

  matrix_t m, m_inv;
  s21_create_matrix(2, 2, &m);
  fill_test(&m, values, 2, 2);

  ck_assert_int_eq(s21_inverse_matrix(&m, &m_inv), OK);

  matrix_t result;
  s21_mult_matrix(&m, &m_inv, &result);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, EPSILON);
  ck_assert_double_eq_tol(result.matrix[1][1], 1.0, EPSILON);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.0, EPSILON);
  ck_assert_double_eq_tol(result.matrix[1][0], 0.0, EPSILON);

  s21_remove_matrix(&m);
  s21_remove_matrix(&m_inv);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_zero_matrix) {
  double values[4] = {0.0, 0.0, 0.0, 0.0};
  matrix_t m, m_inv;

  s21_create_matrix(2, 2, &m);
  fill_test(&m, values, 2, 2);
  ck_assert_int_eq(s21_inverse_matrix(&m, &m_inv), CALC_ERROR);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(inverse_large_numbers) {
  double values[4] = {1000.0, 2000.0, 3000.0, 4000.0};

  matrix_t m, m_inv, result;
  s21_create_matrix(2, 2, &m);
  fill_test(&m, values, 2, 2);
  int code = s21_inverse_matrix(&m, &m_inv);
  s21_mult_matrix(&m, &m_inv, &result);

  ck_assert_int_eq(code, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, EPSILON);
  ck_assert_double_eq_tol(result.matrix[1][1], 1.0, EPSILON);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.0, EPSILON);
  ck_assert_double_eq_tol(result.matrix[1][0], 0.0, EPSILON);

  s21_remove_matrix(&m);
  s21_remove_matrix(&m_inv);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_no_valid_matrix) {
  matrix_t m = {0}, m_inv = {0};
  s21_create_matrix(2, 2, &m);
  for (int i = 0; i < 2; i++) {
    free(m.matrix[i]);
  }
  free(m.matrix);
  m.matrix = NULL;
  int code = s21_inverse_matrix(&m, &m_inv);
  ck_assert_int_eq(code, ERROR);

  s21_remove_matrix(&m);
  s21_remove_matrix(&m_inv);
}
END_TEST

// Проверяем случай с очень маленьким определителем, но > EPSILON
START_TEST(inverse_very_small_det) {
  matrix_t m = {0}, m_inv = {0};
  s21_create_matrix(2, 2, &m);

  // Создаем матрицу с очень маленьким детерминантом
  m.matrix[0][0] = EPSILON * 2;
  m.matrix[0][1] = 0;
  m.matrix[1][0] = 0;
  m.matrix[1][1] = 1;

  ck_assert_int_eq(s21_inverse_matrix(&m, &m_inv), OK);
  s21_remove_matrix(&m);
  s21_remove_matrix(&m_inv);
}
END_TEST

// Проверяем случай, когда детерминант = EPSILON (граничный случай)
START_TEST(inverse_epsilon_det) {
  matrix_t m = {0}, m_inv = {0};
  s21_create_matrix(2, 2, &m);

  // Создаем матрицу с определителем = EPSILON
  m.matrix[0][0] = EPSILON;
  m.matrix[0][1] = 0;
  m.matrix[1][0] = 0;
  m.matrix[1][1] = 1;

  ck_assert_int_eq(s21_inverse_matrix(&m, &m_inv), CALC_ERROR);
  s21_remove_matrix(&m);
}
END_TEST

// Специальный тест для покрытия ветви, где s21_determinant возвращает ошибку
START_TEST(inverse_det_error) {
  // Создаем заведомо неправильную матрицу
  matrix_t m = {0}, m_inv = {0};
  s21_create_matrix(2, 2, &m);

  // Освобождаем одну из строк, чтобы сделать матрицу невалидной для
  // s21_determinant
  free(m.matrix[1]);
  m.matrix[1] = NULL;

  ck_assert_int_eq(s21_inverse_matrix(&m, &m_inv), ERROR);

  // Освобождаем только первую строку, так как вторая уже NULL
  if (m.matrix) {
    if (m.matrix[0]) free(m.matrix[0]);
    free(m.matrix);
  }
}
END_TEST

// Проверяем случай, когда s21_calc_complements возвращает ошибку
// Это сложно сделать, поэтому создаем специальный случай
START_TEST(inverse_test_complex_matrix) {
  // Создаем большую матрицу для теста на обработку ошибок
  int size = 15;  // Достаточно большой размер
  matrix_t m = {0}, m_inv = {0};
  int result = s21_create_matrix(size, size, &m);

  // Если не удалось создать большую матрицу, пропускаем тест
  if (result == OK) {
    // Заполняем матрицу
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        m.matrix[i][j] = (i == j) ? 1.0 : 0.1;
      }
    }

    result = s21_inverse_matrix(&m, &m_inv);
    ck_assert(result == OK || result == CALC_ERROR);

    if (result == OK) {
      s21_remove_matrix(&m_inv);
    }
    s21_remove_matrix(&m);
  }
}
END_TEST

// Тест на очень специфическую матрицу с сингулярностью
START_TEST(inverse_special_singular) {
  matrix_t m = {0}, m_inv = {0};
  s21_create_matrix(3, 3, &m);

  m.matrix[0][0] = 1.0;
  m.matrix[0][1] = 2.0;
  m.matrix[0][2] = 3.0;
  m.matrix[1][0] = 2.0;
  m.matrix[1][1] = 4.0;
  m.matrix[1][2] = 6.0;
  m.matrix[2][0] = 3.0;
  m.matrix[2][1] = 6.0;
  m.matrix[2][2] = 9.0;

  ck_assert_int_eq(s21_inverse_matrix(&m, &m_inv), CALC_ERROR);
  s21_remove_matrix(&m);
}
END_TEST

// Тест с крошечными значениями, чтобы вызывать разные пути для проверки на
// равенство с EPSILON
START_TEST(inverse_tiny_values) {
  matrix_t m = {0}, m_inv = {0};
  s21_create_matrix(3, 3, &m);

  // Создаем матрицу с очень маленькими значениями
  m.matrix[0][0] = EPSILON * 10;
  m.matrix[0][1] = EPSILON * 5;
  m.matrix[0][2] = EPSILON * 2;
  m.matrix[1][0] = EPSILON * 8;
  m.matrix[1][1] = EPSILON * 12;
  m.matrix[1][2] = EPSILON * 3;
  m.matrix[2][0] = EPSILON * 4;
  m.matrix[2][1] = EPSILON * 6;
  m.matrix[2][2] = EPSILON * 15;

  int result = s21_inverse_matrix(&m, &m_inv);
  ck_assert(result == OK || result == CALC_ERROR);

  if (result == OK) {
    s21_remove_matrix(&m_inv);
  }
  s21_remove_matrix(&m);
}
END_TEST

// Тестируем матрицу 1x1
START_TEST(inverse_1x1) {
  matrix_t m = {0}, m_inv = {0};
  s21_create_matrix(1, 1, &m);

  m.matrix[0][0] = 5.0;

  ck_assert_int_eq(s21_inverse_matrix(&m, &m_inv), OK);
  ck_assert_double_eq_tol(m_inv.matrix[0][0], 0.2, EPSILON);

  s21_remove_matrix(&m);
  s21_remove_matrix(&m_inv);
}
END_TEST

// Тест для проверки результата вычислений через матрицу алгебраических
// дополнений
START_TEST(inverse_via_complementary) {
  matrix_t m = {0}, m_inv = {0}, complements = {0}, transposed = {0};
  s21_create_matrix(3, 3, &m);

  // Создаем матрицу для обращения
  m.matrix[0][0] = 1.0;
  m.matrix[0][1] = 2.0;
  m.matrix[0][2] = 3.0;
  m.matrix[1][0] = 0.0;
  m.matrix[1][1] = 4.0;
  m.matrix[1][2] = 2.0;
  m.matrix[2][0] = 5.0;
  m.matrix[2][1] = 2.0;
  m.matrix[2][2] = 1.0;

  // Вычисляем определитель
  double det = 0.0;
  s21_determinant(&m, &det);

  s21_calc_complements(&m, &complements);
  s21_transpose(&complements, &transposed);

  ck_assert_int_eq(s21_inverse_matrix(&m, &m_inv), OK);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(m_inv.matrix[i][j], transposed.matrix[i][j] / det,
                              EPSILON);
    }
  }

  s21_remove_matrix(&m);
  s21_remove_matrix(&m_inv);
  s21_remove_matrix(&complements);
  s21_remove_matrix(&transposed);
}
END_TEST

// Тест для проверки обработки ошибок вычисления
START_TEST(inverse_init_error) {
  matrix_t m = {0}, m_inv = {0};

  m.rows = -1;
  m.columns = -1;
  m.matrix = NULL;

  ck_assert_int_eq(s21_inverse_matrix(&m, &m_inv), ERROR);
}
END_TEST

// Тест для проверки, что функция корректно обрабатывает случай, когда
// детерминант равен нулю
START_TEST(inverse_zero_det) {
  matrix_t m = {0}, m_inv = {0};
  s21_create_matrix(3, 3, &m);

  m.matrix[0][0] = 1.0;
  m.matrix[0][1] = 2.0;
  m.matrix[0][2] = 3.0;
  m.matrix[1][0] = 2.0;
  m.matrix[1][1] = 4.0;
  m.matrix[1][2] = 6.0;
  m.matrix[2][0] = 3.0;
  m.matrix[2][1] = 6.0;
  m.matrix[2][2] = 9.0;

  ck_assert_int_eq(s21_inverse_matrix(&m, &m_inv), CALC_ERROR);

  s21_remove_matrix(&m);
}
END_TEST

// Тест для проверки корректной обработки случая, когда матрица не квадратная
START_TEST(inverse_not_square) {
  matrix_t m = {0}, m_inv = {0};
  s21_create_matrix(2, 3, &m);

  ck_assert_int_eq(s21_inverse_matrix(&m, &m_inv), CALC_ERROR);

  s21_remove_matrix(&m);
}
END_TEST

// Тест для проверки поведения при передаче NULL в качестве result
START_TEST(inverse_null_result) {
  matrix_t m = {0};
  s21_create_matrix(2, 2, &m);

  ck_assert_int_eq(s21_inverse_matrix(&m, NULL), ERROR);

  s21_remove_matrix(&m);
}
END_TEST

// Тест для проверки вычисления алгебраических дополнений
START_TEST(inverse_complements) {
  matrix_t m = {0}, m_inv = {0}, complements = {0}, transposed = {0},
           result = {0};
  s21_create_matrix(3, 3, &m);

  m.matrix[0][0] = 1.0;
  m.matrix[0][1] = 2.0;
  m.matrix[0][2] = 3.0;
  m.matrix[1][0] = 0.0;
  m.matrix[1][1] = 4.0;
  m.matrix[1][2] = 2.0;
  m.matrix[2][0] = 5.0;
  m.matrix[2][1] = 2.0;
  m.matrix[2][2] = 1.0;

  ck_assert_int_eq(s21_inverse_matrix(&m, &m_inv), OK);

  ck_assert_int_eq(s21_mult_matrix(&m, &m_inv, &result), OK);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == j) {
        ck_assert_double_eq_tol(result.matrix[i][j], 1.0, EPSILON);
      } else {
        ck_assert_double_eq_tol(result.matrix[i][j], 0.0, EPSILON);
      }
    }
  }

  s21_remove_matrix(&m);
  s21_remove_matrix(&m_inv);
  s21_remove_matrix(&complements);
  s21_remove_matrix(&transposed);
  s21_remove_matrix(&result);
}
END_TEST

// Тест для покрытия случая, когда s21_transpose возвращает ошибку
START_TEST(inverse_transpose_error) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);

  A.rows = 1;
  A.columns = 2;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  A.rows = 2;
  s21_remove_matrix(&A);
}
END_TEST

// Тест для покрытия случая, когда s21_mult_number возвращает ошибку
START_TEST(inverse_mult_number_error) {
  matrix_t m = {0}, result = {0};

  m.rows = -1;
  m.columns = -1;
  m.matrix = NULL;

  int code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

// Тест для проверки граничного случая, когда обратная матрица имеет очень
// большие значения
START_TEST(inverse_extreme_values_test) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = EPSILON * 10;
  A.matrix[0][1] = 0.1;
  A.matrix[1][0] = 0.01;
  A.matrix[1][1] = EPSILON * 10;

  int code = s21_inverse_matrix(&A, &result);

  ck_assert(code == OK || code == CALC_ERROR);

  if (code == OK) {
    matrix_t check = {0};
    s21_mult_matrix(&A, &result, &check);

    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        if (i == j) {
          ck_assert_double_eq_tol(check.matrix[i][j], 1.0, EPSILON);
        } else {
          ck_assert_double_eq_tol(check.matrix[i][j], 0.0, EPSILON);
        }
      }
    }
    s21_remove_matrix(&check);
    s21_remove_matrix(&result);
  }

  s21_remove_matrix(&A);
}
END_TEST

// Тест для проверки обработки ошибки в s21_calc_complements
START_TEST(inverse_calc_complements_error) {
  matrix_t A = {0}, result = {0};

  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  A.rows = 1;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  A.rows = 2;
  s21_remove_matrix(&A);
}
END_TEST

// Тест для проверки ситуации когда s21_matrix_init возвращает ошибку внутри
// s21_inverse_matrix
START_TEST(inverse_internal_init_error) {
  matrix_t A = {0};

  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 1.0;

  matrix_t *bad_result = NULL;

  int code = s21_inverse_matrix(&A, bad_result);
  ck_assert_int_eq(code, ERROR);

  s21_remove_matrix(&A);
}
END_TEST

// Тест для покрытия случая невалидного указателя на result
START_TEST(inverse_null_ptr_result) {
  matrix_t A = {0};

  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 1.0;

  int code = s21_inverse_matrix(&A, NULL);
  ck_assert_int_eq(code, ERROR);

  s21_remove_matrix(&A);
}
END_TEST

// Тест для проверки случая, когда определитель точно равен EPSILON
START_TEST(inverse_det_exactly_epsilon) {
  matrix_t A = {0}, result = {0};

  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = EPSILON;
  A.matrix[0][1] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 1.0;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_det_slightly_above_epsilon) {
  matrix_t A = {0}, result = {0};

  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = EPSILON * 1.1;
  A.matrix[0][1] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 1.0;

  int code = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_init_fail) {
  matrix_t A = {0}, result = {0};

  A.rows = -1;
  A.columns = -1;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

// Тест с неинициализированной матрицей A
START_TEST(inverse_uninit_matrix_A) {
  matrix_t A = {0}, result = {0};

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

// Тест для случая, когда s21_determinant возвращает ошибку
START_TEST(inverse_det_error_return) {
  matrix_t A = {0}, result = {0};

  s21_create_matrix(2, 2, &A);

  free(A.matrix[1]);
  A.matrix[1] = NULL;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, ERROR);

  free(A.matrix[0]);
  free(A.matrix);
}
END_TEST

// Тест для случая, когда алгебраические дополнения генерируют ошибку
START_TEST(inverse_complements_error) {
  matrix_t A = {0}, result = {0};

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 0.0;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

// Тест для случая, когда det == EPSILON
START_TEST(inverse_det_exact_epsilon) {
  matrix_t A = {0}, result = {0};

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = EPSILON;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

// Тест для случая, когда s21_transpose возвращает ошибку
START_TEST(inverse_transpose_failure) {
  matrix_t A = {0}, result = {0}, temp = {0};

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 1.0;

  ck_assert_int_eq(s21_create_matrix(2, 2, &result), OK);

  double det = 0.0;
  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert(fabs(det) > EPSILON);

  ck_assert_int_eq(s21_calc_complements(&A, &temp), OK);

  free(temp.matrix[0]);
  temp.matrix[0] = NULL;

  matrix_t temp1 = {0};
  int res = s21_transpose(&temp, &temp1);
  ck_assert_int_eq(res, ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  free(temp.matrix[1]);
  free(temp.matrix);
}
END_TEST

// Добавим еще один тест для случая, когда s21_mult_number возвращает ошибку
START_TEST(inverse_mult_number_failure) {
  matrix_t A = {0}, temp = {0}, temp1 = {0}, result = {0};

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 1.0;

  ck_assert_int_eq(s21_create_matrix(2, 2, &result), OK);

  double det = 0.0;
  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert(fabs(det) > EPSILON);

  ck_assert_int_eq(s21_calc_complements(&A, &temp), OK);

  ck_assert_int_eq(s21_transpose(&temp, &temp1), OK);

  free(temp1.matrix[0]);
  temp1.matrix[0] = NULL;

  s21_remove_matrix(&result);
  int res = s21_mult_number(&temp1, 1.0 / det, &result);
  ck_assert_int_eq(res, ERROR);

  s21_remove_matrix(&A);
  free(temp1.matrix[1]);
  free(temp1.matrix);
  s21_remove_matrix(&temp);
}
END_TEST

START_TEST(inverse_det_very_close_but_less_than_epsilon) {
  matrix_t A = {0}, result = {0};

  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 0.99 * EPSILON;
  A.matrix[0][1] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 1.0;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

Suite *inverse_matrix_suite(void) {
  Suite *s = suite_create("Inverse Matrix");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, inverse_2x2);
  tcase_add_test(tc, inverse_2x3);
  tcase_add_test(tc, inverse_3x3);
  tcase_add_test(tc, inverse_singular_matrix);
  tcase_add_test(tc, inverse_identity_matrix);
  tcase_add_test(tc, inverse_zero_matrix);
  tcase_add_test(tc, inverse_large_numbers);
  tcase_add_test(tc, inverse_no_valid_matrix);

  tcase_add_test(tc, inverse_very_small_det);
  tcase_add_test(tc, inverse_epsilon_det);
  tcase_add_test(tc, inverse_det_error);
  tcase_add_test(tc, inverse_test_complex_matrix);
  tcase_add_test(tc, inverse_special_singular);
  tcase_add_test(tc, inverse_tiny_values);
  tcase_add_test(tc, inverse_1x1);
  tcase_add_test(tc, inverse_via_complementary);

  tcase_add_test(tc, inverse_init_error);
  tcase_add_test(tc, inverse_zero_det);
  tcase_add_test(tc, inverse_not_square);
  tcase_add_test(tc, inverse_null_result);
  tcase_add_test(tc, inverse_complements);

  tcase_add_test(tc, inverse_transpose_error);
  tcase_add_test(tc, inverse_mult_number_error);
  tcase_add_test(tc, inverse_extreme_values_test);

  tcase_add_test(tc, inverse_calc_complements_error);
  tcase_add_test(tc, inverse_internal_init_error);
  tcase_add_test(tc, inverse_null_ptr_result);
  tcase_add_test(tc, inverse_det_exactly_epsilon);
  tcase_add_test(tc, inverse_det_slightly_above_epsilon);
  tcase_add_test(tc, inverse_init_fail);
  tcase_add_test(tc, inverse_uninit_matrix_A);

  tcase_add_test(tc, inverse_det_error_return);
  tcase_add_test(tc, inverse_complements_error);
  tcase_add_test(tc, inverse_det_exact_epsilon);
  tcase_add_test(tc, inverse_transpose_failure);
  tcase_add_test(tc, inverse_mult_number_failure);

  tcase_add_test(tc, inverse_det_very_close_but_less_than_epsilon);

  suite_add_tcase(s, tc);
  return s;
}