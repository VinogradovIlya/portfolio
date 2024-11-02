#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n) != 0) {
        printf("n/a");
    } else {
        squaring(data, n);
        output(data, n);
    }
    return 0;
}

int input(int *a, int *n) {
    int error = 0;
    // char ch;
    // int validate = scanf("%d%c", n, &ch);
    if ((scanf("%d", n)) == 1 && getchar() != '\n') {
        error = 1;
    } else if (*n > NMAX || *n < 1) {
        error = 1;
    } else {
        for (int *p = a; p - a < *n && error == 0; p++) {
            char ch;
            int validate = scanf("%d%c", p, &ch);
            if (validate != 1 && ch != ' ' && p - a < *n - 1) {
                error = 1;
            } else if (validate != 1 && ch != '\n' && p - a == *n - 1) {
                error = 1;
            }
        }
    }
    return error;
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (i < n - 1) {
            printf("%d ", a[i]);
        } else if (i == n - 1) {
            printf("%d", a[i]);
        }
    }
}

void squaring(int *a, int n) {
    // for (int *p = a; p - a < n; p++) {
    //     *p = *p * *p;
    // }
    // for (int i = 0; i < n; i++) {
    //     *(a+i) = (int)*(a+i) * (int)*(a+i);
    // }
    for (int i = 0; i < n; i++) {
        a[i] = a[i] * a[i];
    }
}
