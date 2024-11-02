#include <stdio.h>
#define HEIGHT 25
#define WIDTH 80

int draw(int pos_left, int pos_right, int ballx, int bally, int player1, int player2) {
    for (int j = 0; j <= HEIGHT; j++) {
        for (int i = 0; i <= WIDTH; i++)
            if (((i == 0) && (j == 4)) || ((i == WIDTH) && (j == 4)))
                printf("S");
            else if (((i == 0) && (j == 5)) || ((i == WIDTH) && (j == 5)))
                printf("C");
            else if (((i == 0) && (j == 6)) || ((i == WIDTH) && (j == 6)))
                printf("O");
            else if (((i == 0) && (j == 7)) || ((i == WIDTH) && (j == 7)))
                printf("R");
            else if (((i == 0) && (j == 8)) || ((i == WIDTH) && (j == 8)))
                printf("E");
            else if ((i == 0) && (j == 9) && (player1 < 10))
                printf("%d", player1);
            else if ((i == 0) && (j == 9) && (player1 >= 10))
                printf("%d", player1 / 10);
            else if ((i == 0) && (j == 10) && (player1 >= 10))
                printf("%d", player1 % 10);
            else if ((i == WIDTH) && (j == 9) && (player2 < 10))
                printf("%d", player2);
            else if ((i == WIDTH) && (j == 9) && (player2 >= 10))
                printf("%d", player2 / 10);
            else if ((i == WIDTH) && (j == 10) && (player2 >= 10))
                printf("%d", player2 % 10);
            else if ((i == 0) || (i == WIDTH))
                printf("|");
            else if ((j == 0) || ((i == WIDTH || (j == HEIGHT))))
                printf("-");
            else if ((i == 1) && ((j == pos_left - 1) || (j == pos_left) || (j == pos_left + 1)))
                printf("|");
            else if ((i == 79) && ((j == pos_right - 1) || (j == pos_right) || (j == pos_right + 1)))
                printf("|");
            else if ((i == ballx) && (j == bally))
                printf("*");
            else
                printf(" ");
        printf("\n");
    }
    return 0;
}

int movement(int ballx, int bally, int pos_left, int pos_right, int prev_pos) {
    if ((bally == pos_left) && (ballx == 2)) return 0;
    if ((bally == pos_right) && (ballx == 78)) return 1;
    if ((bally == pos_left - 1) && (ballx == 2)) return 2;
    if ((bally == pos_left + 1) && (ballx == 2)) return 3;
    if ((bally == pos_right - 1) && (ballx == 78)) return 4;
    if ((bally == pos_right + 1) && (ballx == 78)) return 5;
    if ((bally == 1) && (prev_pos == 2)) return 3;
    if ((bally == 1) && (prev_pos == 4)) return 5;
    if ((bally == 24) && (prev_pos == 3)) return 2;
    if ((bally == 24) && (prev_pos == 5)) return 4;
    return prev_pos;
}

int main() {
    int pos_left, pos_right, ballx, bally, prev_pos, player1, player2;
    char move;
    player1 = 0;
    player2 = 0;
    pos_left = pos_right = 13;
    ballx = 40;
    bally = 13;
    prev_pos = 1;
    move = ' ';
    while ((player1 < 21) && (player2 < 21)) {
        prev_pos = movement(ballx, bally, pos_left, pos_right, prev_pos);
        if ((move == 'A') || (move == 'Z') || (move == 'K') || (move == 'M') || (move == ' ')) {
            if (prev_pos == 0) {
                ballx++;
            } else if (prev_pos == 1) {
                ballx--;
            } else if (prev_pos == 2) {
                ballx++;
                bally--;
            } else if (prev_pos == 3) {
                ballx++;
                bally++;
            } else if (prev_pos == 4) {
                ballx--;
                bally--;
            } else if (prev_pos == 5) {
                ballx--;
                bally++;
            }
        }
        draw(pos_left, pos_right, ballx, bally, player1, player2);
        if ((scanf("%c", &move) == 1)) {
            if ((move == 'A') && (pos_left != 2)) {
                pos_left -= 1;
            } else if ((move == 'Z') && (pos_left != 23)) {
                pos_left += 1;
            } else if ((move == 'K') && (pos_right != 2)) {
                pos_right -= 1;
            } else if ((move == 'M') && (pos_right != 23))
                pos_right += 1;
            if (ballx <= 1) {
                player2 += 1;
                ballx = 40;
                bally = 13;
                pos_left = pos_right = 13;
            } else if (ballx >= 79) {
                player1 += 1;
                ballx = 40;
                bally = 13;
                pos_left = pos_right = 13;
            }
        }
        printf("\e[1;1H\e[2J");
    }
    if (player1 > player2)
        printf("Игра закончена! Игрок 1 победил.\n");
    else
        printf("Игра закончилась! Игрок 2 победил.\n");
    return 0;
}
