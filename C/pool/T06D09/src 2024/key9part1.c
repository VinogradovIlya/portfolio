/*------------------------------------
        Здравствуй, человек!
        Чтобы получить ключ
        поработай с комментариями.
-------------------------------------*/

#include <stdio.h>

#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int sum_numbers(int *buffer, int length);
int count(int *a, int n, int div);
int find_numbers(int *buffer, int length, int number, int *numbers);

/*------------------------------------
        Функция получает массив данных
        через stdin.
        Выдает в stdout особую сумму
        и сформированный массив
        специальных элементов
        (выбранных с помощью найденной суммы):
        это и будет частью ключа
-------------------------------------*/
int main() {
    int n, data[NMAX];
    if (input(data, &n) != 0 || sum_numbers(data, n) == 0) {
        printf("n/a");
    } else {
        int sum = sum_numbers(data, n);
        printf("%d\n", sum);
        int res[NMAX];
        find_numbers(data, n, sum, res);
    }
    return 0;
}

/*------------------------------------
        Функция должна находить
        сумму четных элементов
        с 0-й позиции.
-------------------------------------*/
int sum_numbers(int *buffer, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0) {
            sum += buffer[i];
        }
    }
    return sum;
}

/*------------------------------------
        Функция должна находить
        все элементы, на которые нацело
        делится переданное число и
        записывает их в выходной массив.
-------------------------------------*/

int find_numbers(int *buffer, int length, int number, int *numbers) {
    int num = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && number % buffer[i] == 0) {
            numbers[num] = buffer[i];
            num++;
        }
    }
    for (int i = 0; i < num; i++) {
        if (i < num - 1) {
            printf("%d ", numbers[i]);
        } else if (i == num - 1) {
            printf("%d", numbers[i]);
        }
    }
    return 0;
}

int count(int *a, int n, int div) {
    int amount;
    for (int i = 0; i < n; i++) {
        if (a[i] != 0 && div % a[i] == 0) {
            amount++;
        }
    }
    return amount;
}

int input(int *a, int *n) {
    int error = 0;
    // char ch;
    // int validate = scanf("%d%c", n, &ch);
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
            printf("%d ", a[i]);
        } else if (i == n - 1) {
            printf("%d", a[i]);
        }
    }
}
