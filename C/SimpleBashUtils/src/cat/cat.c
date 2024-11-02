#include "cat.h"

int print_file(char *path);
int parse_args(int argc, char **argv);

int main(int argc, char **argv) {
    if (argc == 1) {
        while (1) {
            char str[100];
            scanf("%s", str);
            printf("%s\n", str);
        }
    } else if (argc != 1) {
        for (int i = 1; i < argc; i++) {
            print_file(argv[i]);
        }
    }

    return 0;
}

int print_file(char *path) {
    int error = 0;
    FILE *f = NULL;
    if ((f = fopen(path, "r")) != NULL) {
        int c = fgetc(f);
        while (c != EOF) {
            putc(c, stdout);
            c = fgetc(f);
        }
        fclose(f);
    } else {
        perror("print_file");
        error = errno;
    }
    return error;
}

int parse_args(int argc, char **argv) {

    return 0;
}