#include <stdio.h>

#define H_SIZE 80
#define V_SIZE 25
#define START_BALL_X 40
#define START_BALL_Y 12
#define START_PLATFORM 13
#define LEFT_X 1
#define RIGHT_X 78
#define COUNT 21

void box(int left_coord, int right_coord, int ball_x, int ball_y, int score1, int score2);
int move_rocket1(int left_coord);
int move_rocket2(int right_coord);
int colise_box(int ball_x, int speed_y);
int colise_rocket(int ball_x, int ball_y, int speed, int left_coord, int right_coord);
int player1_win(int ball_x);
int player2_win(int ball_x);

int main() {
    int rock_1_coord = START_PLATFORM;
    int rock_2_coord = START_PLATFORM;

    int ball_x = START_BALL_X;
    int ball_y = START_BALL_Y;
    int speed_right = 1;
    int speed_down = 1;

    int score1 = 0;
    int score2 = 0;

    while (score1 != COUNT && score2 != COUNT) {
        printf("\033[H\033[J");
        box(rock_1_coord, rock_2_coord, ball_x, ball_y, score1, score2);

        rock_1_coord = move_rocket1(rock_1_coord);
        rock_2_coord = move_rocket2(rock_2_coord);

        ball_x += speed_right;
        ball_y += speed_down;
        speed_down = colise_box(ball_y, speed_down);
        speed_right = colise_rocket(ball_x, ball_y, speed_right, rock_1_coord, rock_2_coord);

        score1 += player1_win(ball_x);
        score2 += player2_win(ball_x);
        if (player1_win(ball_x) || player2_win(ball_x)) {
            ball_x = START_BALL_X;
            speed_right *= -1;
        }
    }
    if (score1 == COUNT) {
        printf("Player1 WIN");
    } else if (score2 == COUNT) {
        printf("Player2 WIN");
    }
    return 0;
}

void box(int left_coord, int right_coord, int ball_x, int ball_y, int score1, int score2) {
    for (int y = 0; y < V_SIZE; y++) {      // y v
        for (int x = 0; x < H_SIZE; x++) {  // x ->
            if ((y == 0) || (y == (V_SIZE - 1))) {
                printf("#");
            } else if ((x == ball_x) && (y == ball_y)) {
                printf("*");
            } else if ((x == LEFT_X) &&
                       ((y == left_coord) || (y == left_coord - 1) || (y == left_coord + 1))) {
                printf("|");
            } else if ((x == RIGHT_X) &&
                       ((y == right_coord) || (y == right_coord - 1) || (y == right_coord + 1))) {
                printf("|");
            } else if (x == 0 && y == START_PLATFORM - 1) {
                printf("%d", score1 / 10);
            } else if (x == 0 && y == START_PLATFORM) {
                printf("%d", score1 % 10);
            } else if (x == H_SIZE - 1 && y == START_PLATFORM - 1) {
                printf("%d", score2 / 10);
            } else if (x == H_SIZE - 1 && y == START_PLATFORM) {
                printf("%d", score2 % 10);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int move_rocket1(int left_coord) {
    char symbol = 'w';
    while (symbol != 'a' && symbol != 'z' && symbol != ' ') {
        scanf("%c", &symbol);
    }
    if (symbol == 'a') {
        if (left_coord != 0 + 2) {
            left_coord--;
        }
    } else if (symbol == 'z') {
        if (left_coord != V_SIZE - 3) {
            left_coord++;
        }
    }
    return left_coord;
}

int move_rocket2(int right_coord) {
    char symbol = 'w';
    while ((symbol != 'k') && (symbol != 'm') && (symbol != ' ')) {
        scanf("%c", &symbol);
    }
    if (symbol == 'k') {
        if (right_coord != 0 + 2) {
            right_coord--;
        }
    } else if (symbol == 'm') {
        if (right_coord != V_SIZE - 3) {
            right_coord++;
        }
    }
    return right_coord;
}

int colise_box(int ball_y, int speed) {
    if ((ball_y == 1) || (ball_y == V_SIZE - 2)) {
        speed *= -1;
    }
    return speed;
}

int colise_rocket(int ball_x, int ball_y, int speed, int left_coord, int right_coord) {
    if ((ball_x == LEFT_X) &&
        ((left_coord - 1 == ball_y) || (left_coord == ball_y) || (left_coord + 1 == ball_y))) {
        speed *= -1;
    }
    if ((ball_x == RIGHT_X) &&
        ((right_coord - 1 == ball_y) || (right_coord == ball_y) || (right_coord + 1 == ball_y))) {
        speed *= -1;
    }
    return speed;
}

int player2_win(int ball_x) {
    int res = 0;
    if (ball_x == 0) {
        res = 1;
    }
    return res;
}

int player1_win(int ball_x) {
    int res = 0;
    if (ball_x == RIGHT_X + 1) {
        res = 1;
    }
    return res;
}
