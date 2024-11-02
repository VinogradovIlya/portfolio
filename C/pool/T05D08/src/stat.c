#include <math.h>
#include <stdio.h>

#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

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
    output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));

    return 1;
}

int input(int *a, int *n) {
    int finalRes = 0;
    for (int i = 0; i < *n; i++) {
        if (scanf("%d", (a + i)) != 1 && *(a + i) != (int)*(a + i)) {
            finalRes = -1;
        }
    }
    //     finalRes = -1;
    // }
    return finalRes;
}

// void output(int *a, int n) {
//     for (int i = 0; i < n; i++) {
//         printf("%d", *(a + i));
//     }
// }

int max(int *a, int n) {
    int max;
    for (int *p = a; p - a < n; p++) {
        max = *a;
        if (*p > max) {
            max = *p;
        }
    }
    return max;
}

int min(int *a, int n) {
    int min;
    for (int *p = a; p - a < n; p++) {
        min = *a;
        if (*p < min) {
            min = *p;
        }
    }
    return min;
}

double mean(int *a, int n) {
    float sum = 0;
    for (int *p = a; p - a < n; p++) {
        sum += *p;
    }
    float mean = 0;
    mean = sum / n;
    return mean;
}

double variance(int *a, int n) {
    float rrrr = 0;
    float disp = 0;
    for (int *p = a; p - a < n; p++) {
        disp = pow((*p - mean(a, n)), 2) / n;
        rrrr += disp;
    }
    return rrrr;
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %6f %6f", max_v, min_v, mean_v, variance_v);
}