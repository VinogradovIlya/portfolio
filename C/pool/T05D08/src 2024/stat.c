#include <math.h>
#include <stdio.h>

#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);
int valide(int *a, int n);
void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (input(data, &n) != 0) {
        printf("n/a");
    } else if (valide(data, n) != 0) {
        printf("n/a");
    } else {
        output(data, n);
        output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));
    }

    return 0;
}

int input(int *a, int *n) {
    int error = 0;
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
            printf("%d ", *(a + i));
        } else if (i == n - 1) {
            printf("%d\n", *(a + i));
        }
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
    float temp = 0;
    float disp = 0;
    for (int *p = a; p - a < n; p++) {
        disp = pow((*p - mean(a, n)), 2) / n;
        temp += disp;
    }
    return temp;
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %6f %6f", max_v, min_v, mean_v, variance_v);
}

int valide(int *a, int n) {
    // проверка на равномерную дискретную последовательность
    int error = 0;
    int ax = max(a, n);
    int in = min(a, n);
    if (ax - in + 1 != n) {
        error = 1;
    }
    for (int i = 0; i < n - 1 && error == 0; i++) {
        int count = 0;
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) {
                count++;
            }
            if (count != 0) {
                error = 1;
            }
        }
    }
    return error;
}