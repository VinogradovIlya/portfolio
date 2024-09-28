#include <math.h>
#ifndef DATA_STAT_H
#define DATA_STAT_H

double max(double *data, int n);
double min(double *data, int n);
double mean(double *data, int n);
double variance(double *data, int n);
void swap(double *arr, int i, int j);
void sort(double *arr, int size);

#endif
