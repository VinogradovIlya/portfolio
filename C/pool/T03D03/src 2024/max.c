#include <stdio.h>

int clear_stdin();

int max(int a, int b);

int main(void) {
    int x, y, read_count, is_empty;
    read_count = scanf("%d %d", &x, &y);
    is_empty = clear_stdin();
    if (read_count == 2 && is_empty != 0) {
        printf("%d\n", max(x, y));
    } else {
        printf("n/a\n");
    }
    return 0;
}

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

int max(int a, int b) {
    int res = 0;
    if (a > b) {
        res = a;
    } else {
        res = b;
    }
    return res;
}