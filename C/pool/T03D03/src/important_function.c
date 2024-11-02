#include <math.h>
#include <stdio.h>
// y = 7e-3 * x^4 + ((22.8 * x^⅓ - 1e3) * x + 3) / (x * x / 2) - x * (10 + x)^(2/x) - 1.01.

int main(void) {
    double x;
    int res;

    res = scanf("%lf", &x);
    if (res != 1 || getchar() != '\n') {
        printf("n/a\n");
        return 0;
    }

    double step1 = (pow(x, (1 / 3)) * 22.8 - 1 * exp(3)) * x + 3;
    double step2 = x * x / 2;
    double step3 = step1 / step2;
    double step4 = pow(x, 4) * 7 * exp(-3);
    double step5 = x * pow((10 + x), (2 / x));
    double step6 = step4 + step3 - step5 - 1.01;
    double result = round(step6);
    printf("%f\n", step6);
    return 0;
}