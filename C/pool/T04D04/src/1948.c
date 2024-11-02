#include <math.h>
#include <stdio.h>

int isPrime(int num);
int npd(int num);
int division(int num1, int num2);

int main(void) {
    int number;
    int test = scanf("%d", &number);

    if (test != 1 || getchar() != '\n') {
        printf("n/a\n");
        return 0;
    }

    if (number < 0) {
        number *= -1;
        printf("%d", npd(number));
        return 0;
    } else if (number == 0) {
        printf("0\n");
        return 0;
    } else {
        printf("%d", npd(number));
        return 0;
    }
    return 0;
}

// проверка на простое / составное число (возвращает 0/-1)
int isPrime(int num) {
    for (int i = 2; i < num; i++) {
        int count = num;
        do {
            count -= i;
            // если в count появляется ноль, то число не простое
            if (count == 0) {
                return -1;
            }
        } while (count > 0);
    }
    return 0;
}

// деление
int division(int num1, int num2) {
    while (num1 >= 0) {
        num1 -= num2;
    }
    if (num1 == 0) {
        return 0;
    } else {
        return num1 + num2;  // остаток от деления
    }
    return 0;
}

// функция для рассчета простых делителей числа
int npd(int num) {
    int max = 0;
    for (int i = num; i > 1; i--) {
        if (division(num, i) == 0) {
            if (!isPrime(i)) {
                if (i > max) max = i;
            }
        }
    }
    return max;
}