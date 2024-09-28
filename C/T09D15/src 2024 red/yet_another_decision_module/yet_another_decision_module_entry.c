#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "decision.h"

int main() {
    double *data;
    int n, error = 0;
    char ch;
    int validate = scanf("%d%c", &n, &ch);
    if (validate != 2 || ch != '\n') {
        error = 1;
    } else if (n < 1) {
        error = 1;
    } else {
        data = malloc(n * sizeof(double));
        // Don`t forget to allocate memory !
        input(data, &n, &error);
    }

    if (make_decision(data, n) && error == 0) {
        printf("YES");
        free(data);
    } else {
        printf("NO");
    }
}
