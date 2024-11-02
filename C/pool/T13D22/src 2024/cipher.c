#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void my_read(FILE *fp);
int file_size(FILE *fp);
void append_to_file(const char *filepath, int *err);

int main() {
    int error = 0, move = 0;
    FILE *fp, *last_name = NULL;
    char name[100];
    while (1) {
        error = 0, move = 0;
        int valid = (scanf("%d", &move));
        if (valid != 1) {
            error = 1;
        } else if (move == -1) {
            break;
        } else if (last_name == NULL) {
            valid = scanf(" %[^\n]", name);
            if (valid != 1) {
                error = 1;
            } else if ((fp = fopen(name, "r")) == NULL) {
                error = 1;
            } else if ((file_size(fp)) == 0 && move == 1) {
                error = 1;
            }
        }
        if (error == 0) {
            if (move == 1) {
                my_read(fp);
                last_name = fp;
            } else if (move == 2) {
                append_to_file(name, &error);
                last_name = NULL;
            }
        }
        if (error == 1) {
            printf("n/a\n");
        }
        scanf("%*[^\n]");
        fclose(fp);
        if (last_name != NULL) {
            fclose(last_name);
        }
    }
    fclose(fp);
    if (last_name != NULL) {
        fclose(last_name);
    }
    return 0;
}

void append_to_file(const char *filepath, int *err) {
    FILE *file = fopen(filepath, "a");
    if (file == NULL) {
        *err = 1;
    }

    char input[256];
    scanf(" %[^\n]", input);

    fprintf(file, "%s\n", input);
    fclose(file);
}

void my_read(FILE *fp) {
    fseek(fp, SEEK_SET, 0);
    char text[256];
    while ((fgets(text, 256, fp)) != NULL) {
        printf("%s", text);
    }
    printf("\n");
}

int file_size(FILE *fp) {
    int file_size = 0;
    while (getc(fp) != EOF) file_size++;
    return file_size;
}
