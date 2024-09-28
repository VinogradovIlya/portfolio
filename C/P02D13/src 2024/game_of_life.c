#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define M 23
#define N 78

void matrix_out(int **matrix);
int exist(int **matrix, int i, int j);
void my_read_config(int **map);
void td_board(int l_board);
void setting_speed(int *speed, char move);
void big_cleaning(int **matrix, int **matrix_new);
void create(int **matrix, int **matrix_new);
void my_read(int **matrix, int **matrix_new);
void exit_condition(int *count_1, int *count_0, int **matrix, int **matrix_new);

int main() {
    FILE *f;
    int **matrix = calloc(M, sizeof(int *));
    int **matrix_new = calloc(M, sizeof(int *));
    int speed = 500000;
    create(matrix, matrix_new);
    my_read_config(matrix);
    f = freopen("/dev/tty", "r", stdin);
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    while (1) {
        my_read(matrix, matrix_new);
        char move = getch();
        setting_speed(&speed, move);
        int count_0 = 0;
        int count_1 = 0;
        exit_condition(&count_1, &count_0, matrix, matrix_new);
        if (count_0 == 1794 || count_1 == 1794 || move == 'q') {
            break;
        }

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                matrix[i][j] = matrix_new[i][j];
            }
        }
        td_board(0);
        matrix_out(matrix);
        usleep(speed);
        clear();
    }
    big_cleaning(matrix, matrix_new);
    endwin();
    fclose(f);
    return 0;
}

/*---------------------------------------------------------
Подсчет кол-ва соседей и вывода их суммы
---------------------------------------------------------*/
int count(int **matrix, int x, int y) {
    int i0, j0;
    int summ = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i != 0 || j != 0) {
                i0 = (x + i + M) % M;
                j0 = (y + j + N) % N;
                summ += matrix[i0][j0];
            }
        }
    }
    return summ;
}

/*---------------------------------------------------------
Функция для вывода матрицы
---------------------------------------------------------*/
void matrix_out(int **matrix) {
    char c;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (matrix[i][j] == 0) {
                c = ' ';
            } else
                c = '#';
            if (j == 0) {
                printw("|");
            }
            printw("%c", c);
            if (j == N - 1) {
                printw("|\n");
            }
        }
    }
    td_board(0);
    refresh();
}

/*---------------------------------------------------------
Проверка состояния клетки в зависимости от кол-ва соседей
---------------------------------------------------------*/
int exist(int **matrix, int i, int j) {
    int is;
    int score = count(matrix, i, j);
    if (matrix[i][j] == 0) {
        if (score == 3) {
            is = 1;
        } else {
            is = 0;
        }
    } else {
        if (score == 2 || score == 3) {
            is = 1;
        } else {
            is = 0;
        }
    }
    return is;
}

/*---------------------------------------------------------
Функция для чтения файла
---------------------------------------------------------*/
void my_read_config(int **map) {
    int temp;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d ", &temp);
            map[i][j] = temp;
        }
    }
}

/*---------------------------------------------------------
Вывод верхней и нижней границы поля
---------------------------------------------------------*/
void td_board(int l_board) {
    int r_board = l_board + 80;
    char td_board_s = '-';
    printw(" ");
    for (int i = 0; i < r_board; i++) {
        if (i < l_board) {
            printw(" ");
        }
        if (i - 1 > l_board) {
            printw("%c", td_board_s);
        }
    }
    printw("\n");
}

/*---------------------------------------------------------
Функция для изменения скорости
---------------------------------------------------------*/
void setting_speed(int *speed, char move) {
    if ((move == '=') && (*speed - 100000 >= 100000)) {
        *speed -= 100000;
    }
    if (move == '-' && (*speed + 100000 < 1000000)) {
        *speed += 100000;
    }
}

/*---------------------------------------------------------
Функция для очистки двух матриц
---------------------------------------------------------*/
void big_cleaning(int **matrix, int **matrix_new) {
    for (int i = 0; i < M; ++i) {
        free(matrix[i]);
        free(matrix_new[i]);
    }
    free(matrix);
    free(matrix_new);
}

/*---------------------------------------------------------
Функция для инициализации двух матриц
---------------------------------------------------------*/
void create(int **matrix, int **matrix_new) {
    for (int i = 0; i < M; ++i) {
        matrix[i] = calloc(N, sizeof(int));
    }
    for (int i = 0; i < M; ++i) {
        matrix_new[i] = calloc(N, sizeof(int));
    }
}

/*---------------------------------------------------------
Запись нового поколения в матрицу
---------------------------------------------------------*/
void my_read(int **matrix, int **matrix_new) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (1 == exist(matrix, i, j)) {
                matrix_new[i][j] = 1;
            } else {
                matrix_new[i][j] = 0;
            }
        }
    }
}

/*---------------------------------------------------------
Функция для проверки весь ли экран 0 и 1
---------------------------------------------------------*/
void exit_condition(int *count_1, int *count_0, int **matrix, int **matrix_new) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (matrix[i][j] == matrix_new[i][j]) {
                ++(*count_1);
            }
            if (matrix_new[i][j] == 0) {
                ++(*count_0);
            }
        }
    }
}
