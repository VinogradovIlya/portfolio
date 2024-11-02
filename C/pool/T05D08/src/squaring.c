#include <stdio.h>

#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);
// int test(int count, char end);

int main() {
    int n = 0;
    int count = scanf("%d", &n);
    if (n > 10 || count != 1 || getchar() != '\n') {
        printf("n/a");
        return 0;
    }
    int data[NMAX];

    if (input(data, &n) == -1) {
        printf("n/a");
        return 0;
    }
    squaring(data, n);
    output(data, n);

    return 1;
}

int input(int *a, int *n) {
    int finalRes = 0;
    for (int i = 0; i < *n; i++) {
        if (scanf("%d", (a + i)) != 1 && *(a + i) != (int)*(a + i)) {
            finalRes = -1;
        }
    }
    return finalRes;
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

void squaring(int *a, int n) {
    for (int i = 0; i < n; i++) {
        *(a + i) = (int)*(a + i) * (int)*(a + i);
    }
}

// int test(int count, char end) {
//     int finalRes = 0;
//     if (count != 1 || (end != '\n' && end != ' ')) {
//         printf("n/a");
//         finalRes = -1;
//     }
//     return finalRes;
// }
