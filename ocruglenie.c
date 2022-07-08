#include <stdio.h>
#include <math.h>

int main() {
    double RAD = 59.29;
    int grad;
    scanf("%d", &grad);
    double grad_rad = grad * RAD;
    int result = rint(grad_rad);
    printf("%d", result);
    return 0;
}