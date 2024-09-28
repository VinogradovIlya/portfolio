#include "data_stat.h"

double max(double *a, int n) {
    double max = *a;
    for (int i = 0; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

double min(double *a, int n) {
    double min = *a;
    for (int i = 0; i < n; i++) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return min;
}

double mean(double *a, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    float mean = sum / n;
    return mean;
}

double variance(double *a, int n) {
    float temp = 0;
    for (int i = 0; i < n; i++) {
        temp += pow((a[i] - mean(a, n)), 2) / n;
    }
    return temp;
}

void swap(double *arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void sort(double *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) swap(arr, j, j + 1);
        }
    }
}
// void sort(double *a, int size) {
// // Указатели в начало и в конец массива
// int i = 0;
// int j = size - 1;
// // Центральный элемент массива
// int mid = a[size / 2];
// // Делим массив
// do {
//     // Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
//     // В левой части массива пропускаем(оставляем на месте) элементы, которые
//     // меньше центрального
//     while (a[i] < mid) {
//         i++;
//     }
//     // В правой части пропускаем элементы, которые больше центрального
//     while (a[j] > mid) {
//         j--;
//     }
//     // Меняем элементы местами
//     if (i <= j) {
//         double tmp = a[i];
//         a[i] = a[j];
//         a[j] = tmp;
//         i++;
//         j--;
//     }
// } while (i <= j);
// // Рекурсивные вызовы, если осталось, что сортировать
// if (j > 0) {
//     //"Левый кусок"
//     sort(a, j + 1);
// }
// if (i < size) {
//     //"Првый кусок"
//     sort(&a[i], size - i);
// }
// }