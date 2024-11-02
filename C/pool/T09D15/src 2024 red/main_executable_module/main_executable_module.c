#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "../data_libs/data_stat.h"
#include "../data_module/data_process.h"
#include "../yet_another_decision_module/decision.h"

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
        printf("LOAD DATA...\n");
        input(data, &n, &error);
    }

    if (error == 0) {
        printf("RAW DATA:\n\t");
        output(data, n);

        printf("\nNORMALIZED DATA:\n\t");
        normalization(data, n);
        output(data, n);

        printf("\nSORTED NORMALIZED DATA:\n\t");
        sort(data, n);
        output(data, n);

        printf("\nFINAL DECISION:\n\t");
        if (make_decision(data, n) && error == 0) {
            printf("YES");
            free(data);
        } else {
            printf("NO");
        }
    } else {
        printf("NO");
    }

    return 0;
}
