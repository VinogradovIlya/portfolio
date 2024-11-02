#include <stdio.h>
#include <stdlib.h>

int input(int *a, int *n);
void output(int *a, int n);
void sort(int *a, int n);

int main(void) {
    int n = 10;
    if (scanf("%d", &n) != 1 || n != (int)n || n < 1) {
        printf("n/a");
        return 1;
    }
    int *ptrN = malloc(n * sizeof(int));

    if (input(ptrN, &n) == 1) {
        return 0;
    }
    sort(ptrN, n);
    output(ptrN, n);
    free(ptrN);

    // return 0;
}

int input(int *a, int *n) {
    for (int i = 0; i < *n; i++) {
        if (scanf("%d", (a + i)) != 1) {
            printf("n/a");
            return 1;
        }
    }
    return 0;
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (i < n - 1) {
            printf("%d ", *(a + i));
        } else if (i == n - 1) {
            printf("%d", *(a + i));
        }
    }
}

// из-за двух вложенных циклов оценка всегда O(n^2)
void sort(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}