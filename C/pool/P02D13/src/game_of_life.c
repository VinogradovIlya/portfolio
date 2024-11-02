#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define nl 77
#define n0 0
#define m_d 0
#define m_tp 22

void matrix_out(int **matrix, int m, int n);
void matrix_null(int **matrix, int m, int n);
int exist(int **matrix, int i, int j);
void read_config(int **map, int max_row_num, int max_col_num);
void td_board(int l_board);

int main() {
    int m = 23;
    int n = 78;
    FILE *f;
    int **matrix = malloc(m * sizeof(int *));
    for (int i = 0; i < m; ++i) {
        matrix[i] = malloc(n * sizeof(int));
    }
    int **matrix_new = malloc(m * sizeof(int *));
    for (int i = 0; i < m; ++i) {
        matrix_new[i] = malloc(n * sizeof(int));
    }

    int speed = 500000;

    matrix_null(matrix, m, n);
    matrix_null(matrix_new, m, n);
    read_config(matrix, m, n);
    f = freopen("/dev/tty", "r", stdin);

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    while (1) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (1 == exist(matrix, i, j)) {
                    matrix_new[i][j] = 1;
                } else {
                    matrix_new[i][j] = 0;
                }
            }
        }
        char move = getch();
        if ((move == '+') && (speed - 100000 >= 100000)) {
            speed -= 100000;
        }
        if (move == '-' && (speed + 100000 < 1000000)) {
            speed += 100000;
        }

        int count_0 = 0;
        int count_s = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == matrix_new[i][j]) {
                    ++count_s;
                }
                if (matrix_new[i][j] == 0) {
                    ++count_0;
                }
            }
        }

        if (count_0 == 1794 || count_s == 1794 || move == 'q') {
            break;
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                matrix[i][j] = matrix_new[i][j];
            }
        }

        td_board(0);
        matrix_out(matrix, m, n);

        usleep(speed);

        clear();
    }

    for (int i = 0; i < m; ++i) {
        free(matrix[i]);
        free(matrix_new[i]);
    }
    free(matrix);
    free(matrix_new);
    endwin();
    fclose(f);
    return 0;
}

int count(int **matrix, int x, int y) {
    int i0, j0;
    int summ = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i != 0 || j != 0) {
                i0 = (x + i + m_tp) % m_tp;
                j0 = (y + j + nl) % nl;
                summ += matrix[i0][j0];
            }
        }
    }
    return summ;
}

void matrix_out(int **matrix, int m, int n) {
    char c;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == 0) {
                c = ' ';
            } else
                c = '#';
            if (j == 0) {
                printw("|");
            }
            printw("%c", c);
            if (j == n - 1) {
                printw("|\n");
            }
        }
    }
    td_board(0);
    refresh();
}

void matrix_null(int **matrix, int m, int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = 0;
        }
    }
}

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

void read_config(int **map, int max_row_num, int max_col_num) {
    int temp;
    for (int i = 0; i < max_row_num; i++) {
        for (int j = 0; j < max_col_num; j++) {
            scanf("%d ", &temp);
            map[i][j] = temp;
        }
    }
}

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
