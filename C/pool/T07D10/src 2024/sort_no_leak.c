#include <stdio.h>
#include <stdlib.h>

int input(int *a, int size);
void qsortRecursive(int *a, int size);
void output(int *a, int size);

int main() {
    int size;
    if (scanf("%d", &size) != 1 && getchar() != '\n') {
        printf("n/a");
    } else {
        int *data = malloc(size * sizeof(int));
        if (input(data, size) == 1) {
            printf("n/a");
        } else {
            qsortRecursive(data, size);
            output(data, size);
            free(data);
        }
    }

    return 0;
}

int input(int *a, int size) {
    int error = 0;
    for (int i = 0; i < size && error == 0; i++) {
        char ch;
        int validate = scanf("%d%c", &a[i], &ch);
        if (validate != 1 && ch != ' ' && i < size - 1) {
            error = 1;
        } else if (validate != 1 && ch != '\n' && i == size - 1) {
            error = 1;
        }
    }
    return error;
}

void output(int *a, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", a[i]);
        if (i < size - 1) {
            printf(" ");
        }
    }
}

void qsortRecursive(int *a, int size) {
    // Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;
    // Центральный элемент массива
    int mid = a[size / 2];
    // Делим массив
    do {
        // Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        // В левой части массива пропускаем(оставляем на месте) элементы, которые
        // меньше центрального
        while (a[i] < mid) {
            i++;
        }
        // В правой части пропускаем элементы, которые больше центрального
        while (a[j] > mid) {
            j--;
        }
        // Меняем элементы местами
        if (i <= j) {
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);
    // Рекурсивные вызовы, если осталось, что сортировать
    if (j > 0) {
        //"Левый кусок"
        qsortRecursive(a, j + 1);
    }
    if (i < size) {
        //"Првый кусок"
        qsortRecursive(&a[i], size - i);
    }
}