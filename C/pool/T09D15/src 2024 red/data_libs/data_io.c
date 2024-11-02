#include "data_io.h"

#include <stdio.h>
#include <stdlib.h>

void input(double *data, int *n, int *err) {
    for (int i = 0; i < *n && *err != 1; i++) {
        double temp;
        char ch;
        int validate = scanf("%lf%c", &temp, &ch);
        if ((validate != 2 || ch != ' ') && i < *n - 1) {
            *err = 1;
        } else if ((validate != 2 || ch != '\n') && i == *n - 1) {
            *err = 1;
        } else {
            data[i] = temp;
        }
    }
}

void output(double *data, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2lf", data[i]);
        if (i < n - 1) printf(" ");
    }
}
