#include <stdio.h>

int factorial (int num);

int main() {
    int x;
    scanf("%d", &x);
    printf("the factorial of %d is %d\n", x, factorial(x));
}

int factorial(int num){
    if (num == 1)
    return 1;
    else 
    return num * factorial(num-1);
}