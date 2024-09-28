#include <math.h>
#include <stdio.h>

double example(double num);

int main(void) {
    double x;
    int digit = scanf("%lf", &x);
    if (digit == 0) {
        printf("n/a\n");
    } else if (x == (double)x) {
        if (isnan(example(x))) {
            printf("n/a\n");
        } else if (isinf(example(x))) {
            printf("n/a\n");
        } else {
            printf("%.1f\n", example(x));
        }
    } else {
        printf("n/a\n");
    }
    return 0;
}

double example(double x) {
    double res = 7e-3 * pow(x, 4) + ((22.8 * pow(x, 1 / 3) - 1e3) * x + 3) / (x * x / 2) -
                 x * pow((10 + x), (2 / x)) - 1.01;
    return res;
}