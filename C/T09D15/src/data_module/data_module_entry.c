#include <stdio.h>
#include <stdlib.h>

#include "data_process.h"

int main(void) {
    double temp;
    if (scanf("%lf", &temp) != 1 || temp != (int)temp) {
        printf("ERROR");
        return 1;
    }
    int n = temp;
    double *data = malloc(n *sizeof(double));

    if (input(data, n) == -1) {
        printf("ERROR");
        free(data);
        return 1;
    }

    if (normalization(data, n)) {
        output(data, n);
        free(data);
        return 0;
    } else {
        printf("ERROR");
        free(data);
        return 1;
    }
    free(data);
    return 0;
}
