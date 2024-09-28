#include <stdio.h>
#include <stdlib.h>

#define ROWS_MAX 100
#define COLUMNS_MAX 100

void output(int **a, int r, int c);
void input(int *error, int *r, int *c);
void input1(int *error, int r, int c, int a[ROWS_MAX][COLUMNS_MAX]);
void input2(int *rows, int *columns, int **p_matrix);

int main(void) {
    int error = 0, move, rows = 0, columns = 0;
    int *p_err = &error;
    if ((scanf("%d", &move)) != 1 || getchar() != '\n') {
        error = 1;
        printf("+++");
    }
    if (error == 0 && move == 1) {
        input(p_err, &rows, &columns);
        if (error != 1) {
            int matrix1[ROWS_MAX][COLUMNS_MAX];
            input1(p_err, rows, columns, matrix1);
        }
        if (error == 1) {
            printf("n/a");
        } else {
            // for (int i = 0; i < rows; i++) {
            //     for (int j = 0; j < columns; j++) {
            //         printf("%d ", matrix1[i][j]);
            //     }
            //     printf("\n");
            // }
        }
    } else if (error == 0 && move == 2) {
        input(p_err, &rows, &columns);
        if (error != 1) {
            int **array = malloc(rows * sizeof(int *));
            for (int i = 0; i < rows; i++) {
                array[i] = malloc(columns * sizeof(int));
            }
            input2(&rows, &columns, array);
        }
    }
}

void output(int **a, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d ", a[i][j]);
        }
    }
}

void input(int *error, int *r, int *c) {
    char ch, ch2;
    if ((scanf("%d%c%d%c", r, &ch, c, &ch2)) != 4 || ch != ' ' || ch2 != '\n' || *r < 1 || *c < 1) {
        *error = 1;
        // printf("%d%c%d%c", *r, ch, *c, ch2);
        // printf("n/a");
    }
}

void input1(int *error, int r, int c, int matrix[ROWS_MAX][COLUMNS_MAX]) {
    for (int i = 0; i < r && *error == 0; i++) {
        for (int j = 0; j < c; j++) {
            int temp;
            char ch;
            int res = scanf("%d%c", &temp, &ch);
            if (((res != 2 || ch != ' ') /*|| temp != (int)temp*/) && j < c - 1) {
                *error = 1;
            } else if (((res != 2 || ch != '\n') /*|| temp != (int)temp*/) && j == c - 1) {
                *error = 1;
            } else {
                matrix[i][j] = temp;
            }
        }
    }
}

void input2(int *rows, int *columns, int **p_matrix) {
    int count = 0;
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *columns; j++) {
            p_matrix[i][j] = count++;
        }
    }
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *columns; j++) {
            printf("%d", p_matrix[i][j]);
        }
    }
    for (int i = 0; i < *rows; i++) {
        free(p_matrix[i]);
    }
    free(p_matrix);
}