#include "s21_tetris_frontend.h"

#include "../../brick_game/tetris/s21_tetris_backend.h"

void init_frontend() {
  initscr();
  cbreak();
  noecho();
  if (has_colors()) {
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    wbkgd(stdscr, COLOR_PAIR(1));
  }
  // nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  curs_set(0);
  timeout(100);
}

void draw_box(const GameInfo_t *game_info) {
  for (int j = LEFT; j <= RIGHT; j++) {
    mvaddch(0, j, j == LEFT || j == RIGHT ? '+' : '-');
    mvaddch(BOTTOM, j, (j == LEFT || j == RIGHT) ? '+' : '-');
  }
  for (int i = 1; i < ROWS + 1; i++) {
    mvaddch(i, LEFT, '|');
    mvaddch(i, RIGHT, '|');
    for (int j = 1; j <= COLUMNS; j++) {
      mvaddch(i, j + LEFT, game_info->field[i - 1][j - 1] ? '#' : ' ');
    }
  }
  mvprintw(1, 14, "TETRIS");
  mvprintw(3, 14, "SCORE: %d", game_info->score);
  mvprintw(5, 14, "HIGH SCORE: %d", game_info->high_score);
  mvprintw(7, 14, "LEVEL: %d", game_info->level);
  mvprintw(9, 14, "NEXT TETROMINO:");
  print_mini_box();
}

void print_lose(const GameInfo_t *game_info) {
  clear();
  box(stdscr, 0, 0);
  mvprintw(1, COLS / 2 - 12, "TETRIS");
  mvprintw(3, COLS / 2 - 12, "YOU LOSE :(");
  mvprintw(5, COLS / 2 - 12, "SCORE: %d", game_info->score);
  mvprintw(7, COLS / 2 - 12, "LEVEL: %d", game_info->level);
  mvprintw(9, COLS / 2 - 12, "Press any key to exit");
  refresh();
  timeout(-1);
  getch();
}

void print_mini_box() {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      if (i == 0 || i == 5 || j == 0 || j == 5)
        mvaddch(10 + i, COLUMNS + 4 + j, '.');
    }
  }
}

void print_in_mini_box(const int form[PREVIEW_SIZE][PREVIEW_SIZE]) {
  for (int i = 0; i < PREVIEW_SIZE; i++) {
    for (int j = 0; j < PREVIEW_SIZE; j++) {
      mvaddch(11 + i, COLUMNS + 5 + j, form[i][j] == 1 ? '#' : ' ');
    }
  }
}

void print_menu() {
  attron(A_BOLD);
  mvprintw(1, (COLS - 12) / 2, "TETRIS");
  attroff(A_BOLD);
  mvprintw(3, (COLS - 12) / 2, "p - pause");
  mvprintw(4, (COLS - 12) / 2, "s - start");
  mvprintw(5, (COLS - 12) / 2, "-> - move left");
  mvprintw(6, (COLS - 12) / 2, "<- - move right");
  mvprintw(7, (COLS - 12) / 2, "v - move down");
  mvprintw(8, (COLS - 12) / 2, "^ - rotate");
  mvprintw(9, (COLS - 12) / 2, "q - quit");
}

void print_pause() {
  attron(A_BOLD);
  mvprintw(1, (COLS - 12) / 2, "TETRIS");
  mvprintw(3, (COLS - 12) / 2, "PAUSE");
  attroff(A_BOLD);
}

void render_game(const GameInfo_t *game_info, GameState_t game_state) {
  box(stdscr, 0, 0);
  if (game_state == GameState_StartScreen) {
    print_menu();
  } else if (game_state == GameState_Pause) {
    print_pause();
  } else {
    draw_box(game_info);
    int preview_form[PREVIEW_SIZE][PREVIEW_SIZE] = {0};
    get_form_tetromino(game_info->next_piece, preview_form);
    print_in_mini_box(preview_form);
  }
}