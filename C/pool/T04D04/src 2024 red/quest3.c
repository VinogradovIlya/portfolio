#include <stdio.h>

int fib(int num);

int main(void) {
    int num;
    if (scanf("%d", &num) != 1 || getchar() != '\n' || num < 0) {
        printf("n/a\n");
    } else {
        int res = fib(num);
        printf("%d\n", res);
    }
    return 0;
}

int fib(int num) {
    if (num <= 1) {
        return num;
    } else {
        return fib(num - 1) + fib(num - 2);
    }
}