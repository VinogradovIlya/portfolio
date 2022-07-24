#include <stdio.h>
#define N 10

void input(int *a, int *n);
void output(int *a, int n);
void sort(int *a, int n);

int main() {
    int n = 10;
    int data[N];
    input(data, &n);
    sort(data, n);
    output(data, n);
    return 0;
}

void input(int *a, int *n) {
//    scanf("%d", n); // otvechaet za kol-vo v massive
    for (int *p = a; p - a < *n; p++) {
        scanf("%d", p);
    }
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        printf("%d ", *p);
    }
}

void sort(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (a[j] > a[j+1]) {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}
