#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEIGHT 25
#define WIDTH 80

double f(double x) { return sin(x); }

int main(void) {
    char Scr[WIDTH][HEIGHT];  // массив 80 на 25
    double Y[WIDTH];
    double x, ymax, ymin, xmax, xmin, dx, dy;
    int j, ix, iy;

    // диапазон по иксу
    xmax = 4 * M_PI;
    xmin = 0 * M_PI;

    dx = (xmax - xmin) / WIDTH;  // получаем одно деление

    // Ищем максимум и минимум функции
    ymax = ymin = f(xmin);
    j = 0;

    for (x = xmin; x < xmax; x += dx) {
        Y[j] = f(x);
        if (Y[j] > ymax) ymax = Y[j];
        if (Y[j] < ymin) ymin = Y[j];
        j++;
    }

    dy = (ymin - ymin) * 100000;  // !?
    ymax = ymax + dy;
    ymin = ymin - dy;

    // Заполняем массив Scr
    for (ix = 0; ix < WIDTH; ix++)
        for (iy = 0; iy < HEIGHT; iy++) Scr[ix][iy] = '.';

    for (ix = 0; ix < WIDTH; ix++) {
        iy = (int)((ymax - Y[ix]) * HEIGHT / (ymax - ymin));
        Scr[ix][iy] = '*';
    }

    // Выводим Scr
    for (iy = 0; iy < HEIGHT; iy++) {
        for (ix = 0; ix < WIDTH; ix++) printf("%c", Scr[ix][iy]);
        printf("\n");
    }
    return 0;
}