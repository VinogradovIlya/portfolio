#include <stdio.h>

void Deco();

void Encode();

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("n/a");
    }
    char *symbol = argv[1];
    if (symbol[0] == '1') {
        Deco();
    } else if (symbol[0] == '0') {
        Encode();
    }
    return 0;
}

void Deco() {
    int ch;
    char symb;
    while (1) {
        scanf("%x%c", &ch, &symb);
        if (symb == ' ') {
            printf("%c ", ch);
        } else if (symb == '\n') {
            printf("%c\n", ch);
            break;
        }
    }
}

void Encode() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch != ' ') {
            printf("%02X ", ch);
        }
    }
    printf("\n");
}