#include <stdio.h>
#include <math.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v,
                   int min_v,
                   double mean_v,
                   double variance_v);

int main() {
    int n, data[NMAX];
    input(data, &n);
    output(data, n);
    output_result(max(data, n),
                  min(data, n),
                  mean(data, n),
                  variance(data, n));
    return 0;
}

int input(int *a, int *n) {
    scanf("%d", n);
    for (int *p = a; p - a < *n; p++) {
        scanf("%d", p);
    }
    return 0;
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        printf("%d ", *p);
    }
}

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
        disp = pow((*p - mean(a,n)), 2) / n;
        rrrr += disp;
}
    return rrrr;
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("\n%d %d %6f %6f", max_v, min_v, mean_v, variance_v);
}
