/*
    Search module for the desired value from data array.

    Returned value must be:
        - "even"
        - ">= mean"
        - "<= mean + 3 * sqrt(variance)"
        - "!= 0"

        OR

        0
*/

#include <math.h>
#include <stdio.h>

#define NMAX 30

int input(int *data, int *n);
int search(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n) != 0) {
        printf("n/a");
    } else {
        printf("%d", search(data, n));
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

int search(int *a, int n) {
    int res = 0;
    int finish = 0;
    double mean_v = mean(a, n);
    double var = variance(a, n);
    for (int i = 0; i < n && finish == 0; i++) {
        if (a[i] != 0 && a[i] % 2 == 0 && a[i] - mean_v <= 3 * sqrt(var) && a[i] > mean_v) {
            res = a[i];
            finish = 1;
        }
    }

    return res;
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