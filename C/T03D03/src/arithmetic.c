#include <stdio.h>
// #include <ctype.h>

int sum(int a, int b);
int diff(int a, int b);
int mult(int a, int b);
int div(int a, int b);

int main(void) {
    int x, y;
    char dot;
    int res;
    res = scanf("%d %d%c", &x, &y, &dot);

    // проверка на буквы
    // if (!isdigit(x) || !isdigit(y)) {
    //     printf("n/a\n");
    //     return 0;
    // }
    // проверка на буквы и дробность
    if (res != 2 && dot != '\n') {
        printf("n/a\n");
        return 0;
    }

    // проверка на 0
    if (y != 0 && x != 0) {
        printf("%d %d %d %d\n", sum(x, y), diff(x, y), mult(x, y), div(x, y));
    } else {
        printf("%d %d %d %s\n", sum(x, y), diff(x, y), mult(x, y), "n/a");
    }
    return 0;
}

int sum(int a, int b) { return a + b; }

int diff(int a, int b) { return a - b; }

int mult(int a, int b) { return a * b; }

int div(int a, int b) { return a / b; }