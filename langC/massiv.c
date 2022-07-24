#include <stdio.h>
#include <math.h>

int main() {
    int N = 6;
    int A[N]; // вместо [N] может быть число
    int i;
    for (i = 0; i<N; i++){
        printf("A[%d] = ", i);
        scanf("%d", &A[i]);
    }
    for (i = 5; i >= 0; i--){
        printf("%d ", A[i]);
    }
    return 0;
}