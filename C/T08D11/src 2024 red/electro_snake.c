#include <stdio.h>
#include <stdlib.h>

void input(int **a, int n, int *e);
void q_sort(int *mat, int n);
void swap(int *a, int *b);
void sort_vertical(const int *mat, int n, int m, int **result_mat);
void sort_horizontal(const int *mat, int n, int m, int **result_mat);
void output(int **a, int n, int m);

int main() {
    int *mat;
    int n, m, error = 0;

    if (scanf("%d %d", &m, &n) == 2 && m > 0 && n > 0) {
        int nm = n * m;

        input(&mat, nm, &error);
        if (error != 1) {
            q_sort(mat, nm);

            int **vertical_result = malloc(m * sizeof(int *));
            int **horizontal_result = malloc(m * sizeof(int *));
            for (int i = 0; i < m; i++) {
                vertical_result[i] = malloc(n * sizeof(int));
                horizontal_result[i] = malloc(n * sizeof(int));
            }
            sort_vertical(mat, n, m, vertical_result);
            sort_horizontal(mat, n, m, horizontal_result);
            output(vertical_result, n, m);
            printf("\n");
            printf("\n");
            output(horizontal_result, n, m);
            for (int i = 0; i < m; i++) {
                free(vertical_result[i]);
            }
            for (int i = 0; i < m; i++) {
                free(horizontal_result[i]);
            }
            free(vertical_result);
            free(horizontal_result);
            free(mat);
        }
        if (error == 1) {
            printf("n/a");
        }
        return 0;
    }
}

void input(int **mat, int n, int *e) {
    *mat = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &(*mat)[i]) != 1) {
            *e = 1;
        }
    }
}

void q_sort(int *a, int size) {
    // Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;
    // Центральный элемент массива
    int mid = a[size / 2];
    // Делим массив
    do {
        // Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        // В левой части массива пропускаем(оставляем на месте) элементы, которые
        // меньше центрального
        while (a[i] < mid) {
            i++;
        }
        // В правой части пропускаем элементы, которые больше центрального
        while (a[j] > mid) {
            j--;
        }
        // Меняем элементы местами
        if (i <= j) {
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);
    // Рекурсивные вызовы, если осталось, что сортировать
    if (j > 0) {
        //"Левый кусок"
        q_sort(a, j + 1);
    }
    if (i < size) {
        //"Првый кусок"
        q_sort(&a[i], size - i);
    }
}

void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void sort_vertical(const int *mat, int n, int m, int **result_mat) {
    int count = 0;
    for (int j = 0; j < n; j++) {
        if (j % 2 == 0) {
            for (int i = 0; i < m; i++) {
                result_mat[i][j] = mat[count++];
            }
        } else {
            for (int i = m - 1; i >= 0; i--) {
                result_mat[i][j] = mat[count++];
            }
        }
    }
}

void output(int **a, int n, int m) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", a[i][j]);
            if (j != n - 1) {
                printf(" ");
            }
        }
        if (i != m - 1) {
            printf("\n");
        }
    }
}

void sort_horizontal(const int *mat, int n, int m, int **result_mat) {
    int count = 0;
    for (int i = 0; i < m; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < n; j++) {
                result_mat[i][j] = mat[count++];
            }
        } else {
            for (int j = n - 1; j >= 0; j--) {
                result_mat[i][j] = mat[count++];
            }
        }
    }
}