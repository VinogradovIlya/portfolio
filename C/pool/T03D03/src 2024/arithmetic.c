#include <stdio.h>

int sum(int a, int b);

int mul(int a, int b);

int dif(int a, int b);

int div(int a, int b);

int clear_stdin();

int main(void) {
    int x, y, read_count, is_empty;
    read_count = scanf("%d %d", &x, &y);
    is_empty = clear_stdin();
    if (read_count == 2 && is_empty != 0) {
        if (y == 0) {
            printf("%d %d %d %s\n", sum(x, y), dif(x, y), mul(x, y), "n/a");
        } else {
            printf("%d %d %d %d\n", sum(x, y), dif(x, y), mul(x, y), div(x, y));
        }
    } else {
        printf("n/a\n");
    }
    return 0;
}

int sum(int a, int b) { return a + b; }

int mul(int a, int b) { return a * b; }

int div(int a, int b) { return a / b; }

int dif(int a, int b) { return a - b; }

int clear_stdin() {
    int rv = 1;
    int ch;
    while (1) {
        ch = getchar();
        if (ch == '\n' || ch == EOF) {
            break;
        }
        rv = 0;
    }
    return rv;
}
