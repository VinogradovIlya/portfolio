#include "s21_string.h"

#include <stdlib.h>

int s21_strlen(char *arr) {
    int i = 0;
    if (!arr) {
        i = 0;
    }
    while (arr && arr[i] && arr[i] != '\0') {
        i++;
    }

    return i;
}

int s21_strcmp(char *s1, char *s2) {
    int res;
    while (*s1 == *s2 && (*s1 != '\0' || *s2 != '\0')) {
        s1++;
        s2++;
    }
    if (*s1 == '\0' && *s2 == '\0') {
        res = 0;
    } else if (*s1 > *s2) {
        res = 1;
    } else if (*s1 < *s2) {
        res = -1;
    }
    return res;
}

char *s21_strcpy(char *s1, char *s2) {
    // while ((*s1++ = *s2++) != '\0')
    //     ;
    unsigned i;
    for (i = 0; s2[i] != '\0'; ++i) s1[i] = s2[i];

    // Ensure trailing null byte is copied
    s1[i] = '\0';

    return s1;
}

void output(int res, int expectation) {
    if (res == expectation) {
        printf("%d %d SUCCESS", expectation, res);
    } else {
        printf("%d %d FAIL", expectation, res);
    }
    printf("\n");
}

char *s21_strcat(char *dest, char *src) {
    char *rdest = dest;

    while (*dest) dest++;
    while ((*dest++ = *src++))
        ;
    return rdest;
}