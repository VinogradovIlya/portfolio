#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define H_SIZE 80
#define V_SIZE 25
#define START_BALL_X 40
#define START_BALL_Y 12
#define START_PLATFORM 13
#define LEFT_X 1
#define RIGHT_X 78
#define COUNT 1

void draw(int left_coord, int right_coord, int ball_x, int ball_y, int score1, int score2);
int move_rocket1(char symbol, int left_coord);
int move_rocket2(char symbol, int right_coord);
int colise_box(int ball_x, int speed_y);
int colise_rocket(int ball_x, int ball_y, int speed, int left_coord, int right_coord);
int player1_win(int ball_x);
int player2_win(int ball_x);
int speed_game(char symbol, int speed);

int main() {
    int speed = 100000;
    initscr();
    noecho();
    halfdelay(1);
    int rock_1_coord = START_PLATFORM;
    int rock_2_coord = START_PLATFORM;
    int ball_x = START_BALL_X;
    int ball_y = START_BALL_Y;
    int speed_right = 1;
    int speed_down = 1;
    int score1 = 0;
    int score2 = 0;
    while (score1 != COUNT && score2 != COUNT) {
        draw(rock_1_coord, rock_2_coord, ball_x, ball_y, score1, score2);
        char symbol = getch();
        speed = speed_game(symbol, speed);
        rock_1_coord = move_rocket1(symbol, rock_1_coord);
        rock_2_coord = move_rocket2(symbol, rock_2_coord);
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
        move(0, 0);
        refresh();
        usleep(speed);
    }
    endwin();
    if (score1 == COUNT) {
        printf("Player1 WIN");
    } else if (score2 == COUNT) {
        printf("Player2 WIN");
    }
    return 0;
}

void draw(int left_coord, int right_coord, int ball_x, int ball_y, int score1, int score2) {
    for (int y = 0; y < V_SIZE; y++) {      // y v
        for (int x = 0; x < H_SIZE; x++) {  // x ->
            if ((y == 0) || (y == (V_SIZE - 1))) {
                printw("#");
            } else if ((x == ball_x) && (y == ball_y)) {
                printw("*");
            } else if ((x == LEFT_X) &&
                       ((y == left_coord) || (y == left_coord - 1) || (y == left_coord + 1))) {
                printw("|");
            } else if ((x == RIGHT_X) &&
                       ((y == right_coord) || (y == right_coord - 1) || (y == right_coord + 1))) {
                printw("|");
            } else if (x == 0 && y == START_PLATFORM - 1) {
                printw("%d", score1 / 10);
            } else if (x == 0 && y == START_PLATFORM) {
                printw("%d", score1 % 10);
            } else if (x == H_SIZE - 1 && y == START_PLATFORM - 1) {
                printw("%d", score2 / 10);
            } else if (x == H_SIZE - 1 && y == START_PLATFORM) {
                printw("%d", score2 % 10);
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }
}

int move_rocket1(char symbol, int left_coord) {
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

int move_rocket2(char symbol, int right_coord) {
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

int speed_game(char symbol, int speed) {
    if (symbol == '=' && (speed - 100000 >= 100000)) {
        speed -= 100000;
    } else if (symbol == '-' && (speed + 100000 < 1000000)) {
        speed += 100000;
    }
    return speed;
}