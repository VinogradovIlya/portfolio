#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define X 80
#define Y 25
#define MID 39
#define RACK_START 12
#define C_EXIT 'b'
#define C_LEFT_UP 'a'
#define C_LEFT_DOWN 'z'
#define C_RIGHT_UP 'k'
#define C_RIGHT_DOWN 'm'
#define C_SKIP ' '
#define BALL_START_Y 12
#define BALL_START_X_LEFT 1
#define BALL_START_X_RIGHT 78
#define MAX_SCORE 21

int rand0_1();
int move_ball(int position, int vector);
int get_command(void);
void printfield(int rack1, int rack2, int ball_x, int ball_y,
                int score1, int score2);

int main(void) {
  int rack1 = RACK_START;
  int rack2 = RACK_START;
  // ball_x (i.e. starting player) will be initialized later via random
  int ball_x;
  int ball_y = BALL_START_Y;
  int is_game_start = 1;
  int ball_vector_x;
  int ball_vector_y;
  int score1 = 0;
  int score2 = 0;

  // ball position initializing
  // left or right player? 0 = left, 1 = right
  ball_x = (rand0_1() == 1) ? BALL_START_X_RIGHT : BALL_START_X_LEFT;

  while (1) {
    int flag;
    printfield(rack1, rack2, ball_x, ball_y, score1, score2);

    // check for win
    if (score1 == MAX_SCORE || score2 == MAX_SCORE) break;

    flag = get_command();
    // check for "end game" char
    if (flag == -1) {
      break;
    }
    if (flag >= 0) {
      // check for "rack1 up" char and check if the rack is not near a border
      if (flag == 1 && rack1 > 2) rack1--;
      // check for "rack1 down" and check if the rack is not near the border
      if (flag == 2 && rack1 < Y - 3) rack1++;
      // check for "rack2 up" and check if the rack is not near a border
      if (flag == 3 && rack2 > 2) rack2--;
      // check for "rack2 down" and check if the rack is not near the border
      if (flag == 4 && rack2 < Y - 3) rack2++;
      // moving the ball
      // check for reaching top and bottom borders and invert y-vector
      if (ball_y == 1 || ball_y == Y - 2) ball_vector_y *= -1;

      // if the ball is in starting position, randomize direction of moving
      if (is_game_start == 1) {
        ball_vector_y = (rand0_1() == 1) ? 1 : -1;
        // if the ball is on the right it should fly to the left and vice versa
        ball_vector_x = (ball_x == BALL_START_X_RIGHT) ? -1 : 1;
        is_game_start = 0;
      } else {
        // check for reaching racks and invert x-vector
        if (ball_x == 1 || ball_x == X - 2) {
          // bouncing from rack - normal bounce, inverting x-vector
          if (abs(ball_y - rack1) <= 1 || abs(ball_y - rack2) <= 1) {
            ball_vector_x *= -1;
          // bouncing from rack - corner bounce, invert both vectors
          } else if (abs(ball_y - rack1) == 2 || abs(ball_y - rack2) == 2) {
            ball_vector_x *= -1;
            ball_vector_y *= -1;
          }
        }
      }

      // check for the goal - if not, move the ball
      if (ball_x == 0) {
        // player 2 scored
        score2++;
        ball_x = BALL_START_X_LEFT;
        ball_y = BALL_START_Y;
        rack1 = RACK_START;
        rack2 = RACK_START;
        is_game_start = 1;
      } else if (ball_x == X - 1) {
        // player 1 scored
        score1++;
        ball_x = BALL_START_X_RIGHT;
        ball_y = BALL_START_Y;
        rack1 = RACK_START;
        rack2 = RACK_START;
        is_game_start = 1;
      } else {
        // move the ball
        ball_x = move_ball(ball_x, ball_vector_x);
        ball_y = move_ball(ball_y, ball_vector_y);
      }
    }
  }
  return 0;
}

int rand0_1() {
  // returns 0 or 1
  srand(time(NULL));
  return rand() % 2;
}

int move_ball(int position, int vector) {
  // vector can be +1 for moving down/right and -1 for moving up/left
  return position + vector;
}

int get_command(void) {
  char c;
  int res;

  c = getchar();
  if (c == C_EXIT) {
    res = -1;
  } else if (c == C_LEFT_UP) {
    res = 1;
  } else if (c == C_LEFT_DOWN) {
    res = 2;
  } else if (c == C_RIGHT_UP) {
    res = 3;
  } else if (c == C_RIGHT_DOWN) {
    res = 4;
  } else if (c == C_SKIP) {
    res = 0;
  } else {
    res = -10;
  }
  return res;
}

void printfield(int rack1, int rack2, int ball_x, int ball_y,
                int score1, int score2) {
  int i, k;
  int is_win;
  // check if there's a win
  is_win = (score1 == MAX_SCORE || score2 == MAX_SCORE) ? 1 : 0;

  // clear field
  printf("\e[1;1H\e[2J");

  for (i = 0; i < Y; i++) {
    for (k = 0; k < X; k++) {
      // print corners
      if ((k == 0 && i == 0) ||
         (k == 0 && i == Y - 1) ||
         (k == X - 1 && i == 0) ||
         (k == X - 1 && i == Y - 1)) {
        printf("*");

      // print top horizontal border with score
      } else if (i == 0) {
        if (k == MID) {
          printf(":");
        } else if (k == MID - 1 || k == MID - 4 ||
                   k == MID + 1 || k == MID + 4) {
          printf(" ");
        } else if (k == MID - 3) {
          printf("%02d", score1);
          k++;
        } else if (k == MID + 2) {
          printf("%02d", score2);
          k++;
        } else {
          printf("=");
        }
      // print bottom horizontal border
      } else if (i == Y - 1) {
        printf("=");
      // print racks (rack1 and rack2 are coordinates of racks' centers)
      } else if ((i == rack1 - 1 && k == 0) || (i == rack2 - 1 && k == X - 1) ||
              (i == rack1 && k == 0) || (i == rack2 && k == X - 1) ||
              (i == rack1 + 1 && k == 0) || (i == rack2 + 1 && k == X - 1)) {
        printf("I");
      // print ball if score != max
      } else if (i == ball_y && k == ball_x && is_win == 0) {
        printf("@");
      // print congratulation
      } else if (is_win == 1 && i == RACK_START && k == 32) {
        printf("PLAYER ");
        printf((score1 == MAX_SCORE) ? "1" : "2");
        printf(" WINS !");
        k += 14;
      // print net
      } else if (k == MID && is_win == 0) {
        printf("|");
      } else {
        printf(" ");
      }
    }

    printf("\n");
  }
}
