#include "data_io.h"

#include <stdio.h>

int input(double *a, int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%lf", a + i) != 1 || *(a + i) != (double)*(a + i)) {
            return 1;
        }
    }
    return 0;
}

void output(double *a, int n) {
    for (int i = 0; i < n; i++) {
        if (i < n - 1) {
            printf("%.2f ", *(a + i));
        } else if (i == n - 1) {
            printf("%.2f", *(a + i));
        }
    }
}