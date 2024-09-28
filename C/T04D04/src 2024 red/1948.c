#include <stdio.h>

int div(int num1, int num2);

int IsSimple(int num);

int Validate();

int main() {
    int res = 0;
    int test_num, error;
    char ch;
    int input = scanf("%d%c", &test_num, &ch);
    //    int validate = Validate();
    if (input != 2 || ch != '\n') {
        error = 1;
    }

    if (test_num < 0) {
        test_num *= -1;
    }

    if (test_num == 0) {
        error = 1;
    } else if (test_num == 1) {
        res = 1;
    } else if (test_num == 2) {
        res = 2;
    } else if (IsSimple(test_num) == 1) {
        res = test_num;
    } else {
        for (int i = 2; i <= test_num; i++) {
            int temp = div(test_num, i);
            if (temp > res && IsSimple(temp) == 1) {
                res = temp;
            }
        }
    }

    if (error == 1) {
        printf("n/a\n");
    } else {
        printf("%d\n", res);
    }

    return 0;
}

int div(int n, int n2) {
    int res;
    int finish = 0;
    int count = 0;
    if (n - n2 < 0) {
        res = 0;
        finish = 1;
    }
    while (finish == 0) {
        n -= n2;
        count++;
        if (n == 0) {
            res = count;
            finish = 1;
        } else if (n < 0) {
            res = 0;
            finish = 1;
        }
    }
    return res;
}

int IsSimple(int n) {
    int res = 1;
    for (int i = 2; i < n; i++) {
        if (div(n, i) != 0) {
            res = 0;
            break;
        }
    }
    return res;
}

int Validate() {
    int validate = 1;
    int ch;
    while (1) {
        ch = getchar();
        if (ch == '\n' || ch == EOF) {
            break;
        }
        validate = 0;
    }
    return validate;
}