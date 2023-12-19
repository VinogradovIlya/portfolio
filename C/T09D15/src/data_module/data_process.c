#include "data_process.h"

#include <math.h>
#include <stdio.h>

int normalization(double *data, int n) {
    int result = 0;
    double max_value = max(data, n);
    double min_value = min(data, n);
    double size = max_value - min_value;

    if (fabs(size) < EPS) {
        for (int i = 0; i < n; i++) {
            data[i] = data[i] / size - min_value / size;
        }
    } else {
        result = 1;
    }

    return result;
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