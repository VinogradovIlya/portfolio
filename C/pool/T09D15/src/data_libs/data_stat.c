#include "data_stat.h"

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