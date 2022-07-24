#include <stdio.h>

int sum(int a, int b);
int mul(int a, int b);
int div(int a, int b);
int diff(int a, int b);

int main(){
    int x, y;
    /*char c;
    if (c != '\n') {
        printf("n/a");
    }
    else {
    scanf("%d %d", &x, &y);
    }*/
    
    if (y != 0) {
        printf("%d %d %d %d\n", sum(x, y), diff(x, y), mul(x, y), div(x, y));
    }
    else {
        printf("%d %d %d %s\n", sum(x, y), diff(x, y), mul(x, y), "n/a");
    }
   
    /*double d;
    scanf("%lf", &d);
    
    if (d != 0) {
        printf("n/a");
    }
    else (d != 0) {
        printf("n/a");
    }*/
}

int sum(int a, int b){
    return a + b;
}

int diff(int a, int b){
    return a - b;
}

int mul(int a, int b){
    return a * b;
}

int div(int a, int b){
    return a / b;
}

