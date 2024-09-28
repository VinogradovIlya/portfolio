#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "data_process.h"

int main() {
    double *data;
    int n, error = 0;
    char ch;
    int validate = scanf("%d%c", &n, &ch);
    if (validate != 2 || ch != '\n') {
        error = 1;
    } else if (n <= 1) {
        error = 1;
    } else {
        data = malloc(n * sizeof(double));
        // Don`t forget to allocate memory !
        input(data, &n, &error);
    }

    if (normalization(data, n) && error != 1) {
        output(data, n);
    } else {
        printf("ERROR");
    }
    if (error != 1) {
        free(data);
    }
}
