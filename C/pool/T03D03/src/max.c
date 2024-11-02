#include <stdio.h>

int max(int a, int b);

int main(void) {
    int x, y;
    char dot;
    int res;
    res = scanf("%d %d%c", &x, &y, &dot);
    if (res != 2 && dot != '\n') {
        printf("n/a\n");
        return 1;
    }
    max(x, y);

    return 0;
}

int max(int a, int b) {
    if (a > b) {
        printf("%d\n", a);
        return 0;
    } else {
        printf("%d\n", b);
        return 0;
    }
}
