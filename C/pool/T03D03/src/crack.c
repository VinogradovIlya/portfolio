#include <stdio.h>

void crack(double x, double y);

int main(void) {
    double x, y;
    int res = scanf("%lf %lf", &x, &y);
    if (res != 2 && getchar() != '\n') {
        printf("n/a\n");
        return 0;
    }

    crack(x, y);
    return 0;
}

void crack(double x, double y) {
    double a = x * x;
    double b = y * y;
    if (a + b <= 25) {
        printf("GOTCHA\n");
    } else {
        printf("MISS\n");
    }
}