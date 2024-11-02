#include <stdio.h>

#define NMAX 10

int input(int *a);
void qsortRecursive(int *a, int size);
void output(int *a);
int valide(int *a, int n);
void heapSort(int *numbers, int array_size);
void heapSort(int *numbers, int array_size);

int main() {
    int data[10];
    if (input(data) == 1) {
        printf("n/a");
    } else {
        qsortRecursive(data, NMAX);
        output(data);
        printf("\n");
        heapSort(data, NMAX);
        output(data);
    }

    return 0;
}

int input(int *a) {
    int error = 0;
    for (int i = 0; i < 10 && error == 0; i++) {
        char ch;
        int validate = scanf("%d%c", &a[i], &ch);
        if (validate != 1 && ch != ' ' && i < 10 - 1) {
            error = 1;
        } else if (validate != 1 && ch != '\n' && i == 10 - 1) {
            error = 1;
        }
    }
    return error;
}

void output(int *a) {
    for (int i = 0; i < NMAX; i++) {
        printf("%d", a[i]);
        if (i < NMAX - 1) {
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

void siftDown(int *numbers, int root, int bottom) {
    int maxChild;  // индекс максимального потомка
    int done = 0;  // флаг того, что куча сформирована
    // Пока не дошли до последнего ряда
    while ((root * 2 <= bottom) && (!done)) {
        if (root * 2 == bottom) {  // если мы в последнем ряду,
            maxChild = root * 2;   // запоминаем левый потомок
            // иначе запоминаем больший потомок из двух
        } else if (numbers[root * 2] > numbers[root * 2 + 1]) {
            maxChild = root * 2;
        } else {
            maxChild = root * 2 + 1;
        }
        // если элемент вершины меньше максимального потомка
        if (numbers[root] < numbers[maxChild]) {
            int temp = numbers[root];  // меняем их местами
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
        } else {       // иначе
            done = 1;  // пирамида сформирована
        }
    }
}

// Функция сортировки на куче
void heapSort(int *numbers, int array_size) {
    // Формируем нижний ряд пирамиды
    for (int i = (array_size / 2); i >= 0; i--) {
        siftDown(numbers, i, array_size - 1);
    }
    // Просеиваем через пирамиду остальные элементы
    for (int i = array_size - 1; i >= 1; i--) {
        int temp = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = temp;
        siftDown(numbers, 0, i - 1);
    }
}