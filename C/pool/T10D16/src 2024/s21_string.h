#include <stdio.h>
#ifndef S21_STRING
#define S21_STRING

int s21_strlen(char *arr);
int s21_strcmp(char *s1, char *s2);
char *s21_strcpy(char *s1, char *s2);
char *s21_strcat(char *dest, char *src);
void output(int res, int expectation);

#endif