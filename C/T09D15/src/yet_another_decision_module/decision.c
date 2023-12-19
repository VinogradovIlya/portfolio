#include "decision.h"

#include <math.h>
#include <stdio.h>

int make_decision(double *data, int n) {
    int decision = 1;

    double m = mean(data, n);
    double sigma = sqrt(variance(data, n));
    double max_value = max(data, n);
    double min_value = min(data, n);

    decision &= (max_value <= m + 3 * sigma) && (max_value >= m - 3 * sigma) && (m >= GOLDEN_RATIO);

    return decision;
}

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

double max(double *a, int n) {
    double temp = *a;
    for (int i = 0; i < n; i++) {
        if (temp < *(a + i)) {
            temp = *(a + i);
        }
    }
    return temp;
}

double min(double *a, int n) {
    double temp = *a;
    for (int i = 0; i < n; i++) {
        if (temp > *(a + i)) {
            temp = *(a + i);
        }
    }
    return temp;
}