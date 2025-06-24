#include "s21_tetris_backend.h"

#include <ncurses.h>

void tetromino_o(int form[PREVIEW_SIZE][PREVIEW_SIZE], const int rotation) {
  int tetromino_o[ROTATE_SIZE][PREVIEW_SIZE][PREVIEW_SIZE] = {
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}};
  for (int j = 0; j < PREVIEW_SIZE; j++) {
    for (int k = 0; k < PREVIEW_SIZE; k++) {
      form[j][k] = tetromino_o[rotation % 4][j][k];
    }
  }
}

void tetromino_i(int form[PREVIEW_SIZE][PREVIEW_SIZE], const int rotation) {
  int tetromino_i[ROTATE_SIZE][PREVIEW_SIZE][PREVIEW_SIZE] = {
      {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
      {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}},
      {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}};
  for (int j = 0; j < PREVIEW_SIZE; j++) {
    for (int k = 0; k < PREVIEW_SIZE; k++) {
      form[j][k] = tetromino_i[rotation][j][k];
    }
  }
}

void tetromino_z(int form[PREVIEW_SIZE][PREVIEW_SIZE], const int rotation) {
  int tetromino_z[ROTATE_SIZE][PREVIEW_SIZE][PREVIEW_SIZE] = {
      {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
      {{0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}}};
  for (int j = 0; j < PREVIEW_SIZE; j++) {
    for (int k = 0; k < PREVIEW_SIZE; k++) {
      form[j][k] = tetromino_z[rotation][j][k];
    }
  }
}

void tetromino_s(int form[PREVIEW_SIZE][PREVIEW_SIZE], const int rotation) {
  int tetromino_s[ROTATE_SIZE][PREVIEW_SIZE][PREVIEW_SIZE] = {
      {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
      {{1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}};
  for (int j = 0; j < PREVIEW_SIZE; j++) {
    for (int k = 0; k < PREVIEW_SIZE; k++) {
      form[j][k] = tetromino_s[rotation][j][k];
    }
  }
}

void tetromino_j(int form[PREVIEW_SIZE][PREVIEW_SIZE], const int rotation) {
  int tetromino_j[ROTATE_SIZE][PREVIEW_SIZE][PREVIEW_SIZE] = {
      {{0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
      {{0, 1, 0, 0}, {0, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 0, 0}, {0, 0, 1, 1}, {0, 0, 1, 0}, {0, 0, 1, 0}},
      {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}}};
  for (int j = 0; j < PREVIEW_SIZE; j++) {
    for (int k = 0; k < PREVIEW_SIZE; k++) {
      form[j][k] = tetromino_j[rotation][j][k];
    }
  }
}

void tetromino_l(int form[PREVIEW_SIZE][PREVIEW_SIZE], const int rotation) {
  int tetromino_l[ROTATE_SIZE][PREVIEW_SIZE][PREVIEW_SIZE] = {
      {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
      {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 1, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
      {{0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}}};
  for (int j = 0; j < PREVIEW_SIZE; j++) {
    for (int k = 0; k < PREVIEW_SIZE; k++) {
      form[j][k] = tetromino_l[rotation][j][k];
    }
  }
}

void tetromino_t(int form[PREVIEW_SIZE][PREVIEW_SIZE], const int rotation) {
  int tetromino_t[ROTATE_SIZE][PREVIEW_SIZE][PREVIEW_SIZE] = {
      {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
      {{0, 0, 0, 0}, {0, 0, 1, 0}, {0, 1, 1, 1}, {0, 0, 0, 0}},
      {{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}}};
  for (int j = 0; j < PREVIEW_SIZE; j++) {
    for (int k = 0; k < PREVIEW_SIZE; k++) {
      form[j][k] = tetromino_t[rotation][j][k];
    }
  }
}

void init_backend(GameInfo_t *game_info, GameState_t *game_state) {
  *game_state = GameState_StartScreen;
  srand((unsigned int)time(NULL));
  game_info->level = 1;
  game_info->score = 0;
  game_info->high_score = 0;
  game_info->game_over = false;
  game_info->pause = false;
  memset(game_info->field, 0, sizeof(game_info->field));
  game_info->current_piece = generate_random_tetromino();
  game_info->next_piece = generate_random_tetromino();
  FILE *f = fopen("record.txt", "r");
  if (f) {
    fscanf(f, "%d", &game_info->high_score);
    fclose(f);
  }
}

Tetromino_t generate_random_tetromino() {
  const TetrominoType_t random_type =
      (TetrominoType_t)(rand() % TetrominoType_Count);
  Tetromino_t tetromino;
  tetromino.type = random_type;
  tetromino.rotate = 0;
  tetromino.y = 0;
  tetromino.x = COLUMNS / 2 - 2;
  return tetromino;
}

void spawn_piece(GameInfo_t *game_info) {
  game_info->current_piece = game_info->next_piece;
  game_info->next_piece = generate_random_tetromino();

  int form[PREVIEW_SIZE][PREVIEW_SIZE] = {0};
  get_form_tetromino(game_info->current_piece, form);

  for (int y = 0; y < PREVIEW_SIZE; y++) {
    for (int x = 0; x < PREVIEW_SIZE; x++) {
      int field_y = game_info->current_piece.y + y;
      int field_x = game_info->current_piece.x + x;
      if (form[y][x] && game_info->field[field_y][field_x] && field_y >= 0 &&
          field_y < ROWS && field_x >= 0 && field_x < COLUMNS) {
        game_info->game_over = true;
        return;
      }
    }
  }
}

void add_current_tetromino_in_field(GameInfo_t *game_info) {
  int form[PREVIEW_SIZE][PREVIEW_SIZE] = {0};
  get_form_tetromino(game_info->current_piece, form);

  for (int y = 0; y < PREVIEW_SIZE; y++) {
    for (int x = 0; x < PREVIEW_SIZE; x++) {
      if (form[y][x]) {
        int field_y = y + game_info->current_piece.y;
        int field_x = x + game_info->current_piece.x;

        game_info->field[field_y][field_x] =
            field_y >= 0 && field_y < ROWS && field_x >= 0 && field_x < COLUMNS
                ? 1
                : 0;
      }
    }
  }
}

int move_piece(const int dx, const int dy, GameInfo_t *game_info) {
  int temp_field[ROWS][COLUMNS] = {0};
  memcpy(temp_field, game_info->field, sizeof(temp_field));

  int form[PREVIEW_SIZE][PREVIEW_SIZE] = {0};
  get_form_tetromino(game_info->current_piece, form);
  for (int y = 0; y < PREVIEW_SIZE; y++) {
    for (int x = 0; x < PREVIEW_SIZE; x++) {
      if (form[y][x] && y + game_info->current_piece.y >= 0 &&
          y + game_info->current_piece.y < ROWS &&
          x + game_info->current_piece.x >= 0 &&
          x + game_info->current_piece.x < COLUMNS) {
        temp_field[y + game_info->current_piece.y]
                  [x + game_info->current_piece.x] = 0;
      }
    }
  }

  int result = possibility_of_movement(dx, dy, game_info);
  if (result == GOOD) {
    game_info->current_piece.x += dx;
    game_info->current_piece.y += dy;
    memcpy(game_info->field, temp_field, sizeof(temp_field));
    add_current_tetromino_in_field(game_info);
  } else if (result == CREATE_NEW_TETRAMINO && dy > 0) {
    add_current_tetromino_in_field(game_info);
    check_lines(game_info);
  }
  return result;
}

void check_lines(GameInfo_t *game_info) {
  int lines_cleared = 0;
  for (int y = 0; y < ROWS; y++) {
    int line_full = 1;
    for (int x = 0; x < COLUMNS && line_full; x++) {
      if (!game_info->field[y][x]) {
        line_full = 0;
      }
    }
    lines_cleared += line_full;
    for (int y2 = y; y2 > 0 && line_full; y2--) {
      for (int x = 0; x < COLUMNS; x++) {
        game_info->field[y2][x] = game_info->field[y2 - 1][x];
      }
    }
    for (int x = 0; x < COLUMNS && line_full; x++) {
      game_info->field[0][x] = 0;
    }
  }

  if (lines_cleared == 1) {
    game_info->score += 100;
  } else if (lines_cleared == 2) {
    game_info->score += 300;
  } else if (lines_cleared == 3) {
    game_info->score += 700;
  } else if (lines_cleared == 4) {
    game_info->score += 1500;
  }

  if (game_info->score > game_info->high_score) {
    game_info->high_score = game_info->score;
  }

  game_info->level = 1 + (game_info->score / 600);
  if (game_info->level > 10) {
    game_info->level = 10;
  }
}

int possibility_of_movement(const int dx, const int dy,
                            const GameInfo_t *game_info) {
  int result = GOOD, form[PREVIEW_SIZE][PREVIEW_SIZE] = {0};
  get_form_tetromino(game_info->current_piece, form);
  int new_x = game_info->current_piece.x + dx;
  int new_y = game_info->current_piece.y + dy;
  for (int y = 0; y < PREVIEW_SIZE && !result; y++) {
    for (int x = 0; x < PREVIEW_SIZE && !result; x++) {
      int field_y = y + new_y;
      int field_x = x + new_x;
      if (form[y][x] &&
          (field_x < 0 || field_x >= COLUMNS || field_y >= ROWS) && dy > 0) {
        result = CREATE_NEW_TETRAMINO;
      } else if (form[y][x] &&
                 (field_x < 0 || field_x >= COLUMNS || field_y >= ROWS)) {
        result = ERROR;
      }
      int is_current_piece = 0;
      if (form[y][x] && field_y >= 0 &&
          game_info->field[field_y][field_x] == 1) {
        is_current_piece =
            is_cur_piece(form, is_current_piece, game_info, field_y, field_x);
      }

      if (form[y][x] && field_y >= 0 &&
          game_info->field[field_y][field_x] == 1 && !is_current_piece &&
          dy > 0) {
        result = CREATE_NEW_TETRAMINO;
      } else if (form[y][x] && field_y >= 0 &&
                 game_info->field[field_y][field_x] == 1 && !is_current_piece) {
        result = ERROR;
      }
    }
  }
  return result;
}

int is_cur_piece(int form[PREVIEW_SIZE][PREVIEW_SIZE], int is_current_piece,
                 const GameInfo_t *game_info, int field_y, int field_x) {
  for (int cy = 0; cy < PREVIEW_SIZE && !is_current_piece; cy++) {
    for (int cx = 0; cx < PREVIEW_SIZE && !is_current_piece; cx++) {
      if (form[cy][cx] == 1 && cy + game_info->current_piece.y == field_y &&
          cx + game_info->current_piece.x == field_x) {
        is_current_piece = 1;
      }
    }
  }
  return is_current_piece;
}

int rotate_piece(GameInfo_t *game_info) {
  int old_rotation = game_info->current_piece.rotate;
  int result = GOOD, temp_field[ROWS][COLUMNS] = {0},
      old_form[PREVIEW_SIZE][PREVIEW_SIZE] = {0},
      new_form[PREVIEW_SIZE][PREVIEW_SIZE] = {0};
  memcpy(temp_field, game_info->field, sizeof(temp_field));
  get_form_tetromino(game_info->current_piece, old_form);
  game_info->current_piece.rotate = (old_rotation + 1) % ROTATE_SIZE;
  for (int y = 0; y < PREVIEW_SIZE; y++) {
    for (int x = 0; x < PREVIEW_SIZE; x++) {
      int field_y = y + game_info->current_piece.y;
      int field_x = x + game_info->current_piece.x;
      if (old_form[y][x] && field_y >= 0 && field_y < ROWS && field_x >= 0 &&
          field_x < COLUMNS) {
        temp_field[field_y][field_x] = 0;
      }
    }
  }
  get_form_tetromino(game_info->current_piece, new_form);
  for (int y = 0; y < PREVIEW_SIZE && !result; y++) {
    for (int x = 0; x < PREVIEW_SIZE && !result; x++) {
      int field_y = y + game_info->current_piece.y;
      int field_x = x + game_info->current_piece.x;
      if (new_form[y][x] &&
          (field_x < 0 || field_x >= COLUMNS || field_y >= ROWS)) {
        game_info->current_piece.rotate = old_rotation;
        result = ERROR;
      }
      if (new_form[y][x] && field_y >= 0 && temp_field[field_y][field_x] == 1) {
        game_info->current_piece.rotate = old_rotation;
        result = ERROR;
      }
    }
  }
  memcpy(game_info->field, temp_field, sizeof(temp_field));
  add_current_tetromino_in_field(game_info);
  return GOOD;
}

void get_form_tetromino(const Tetromino_t piece,
                        int form[PREVIEW_SIZE][PREVIEW_SIZE]) {
  for (int y = 0; y < PREVIEW_SIZE; y++) {
    for (int x = 0; x < PREVIEW_SIZE; x++) {
      form[y][x] = 0;
    }
  }
  const int type = piece.type;
  const int rotate = piece.rotate;
  if (type == TetrominoType_O) {
    tetromino_o(form, 0);
  } else if (type == TetrominoType_I) {
    tetromino_i(form, rotate);
  } else if (type == TetrominoType_Z) {
    tetromino_z(form, rotate);
  } else if (type == TetrominoType_S) {
    tetromino_s(form, rotate);
  } else if (type == TetrominoType_J) {
    tetromino_j(form, rotate);
  } else if (type == TetrominoType_L) {
    tetromino_l(form, rotate);
  } else if (type == TetrominoType_T) {
    tetromino_t(form, rotate);
  }
}

int read_user_input(GameState_t *game_state, int ch) {
  switch (ch) {
    case 'p':
      if (*game_state == GameState_Pause) {
        *game_state = GameState_Moving;
      } else if (*game_state != GameState_StartScreen) {
        *game_state = GameState_Pause;
      }
      break;
    case 's':
      if (*game_state == GameState_StartScreen) {
        *game_state = GameState_Spawn;
      }
      break;
    case 'q':
      *game_state = GameState_GameOver;
      break;
  }
  if (*game_state == GameState_Moving) {
    switch (ch) {
      case KEY_LEFT:
        ch = UserAction_Left;
        break;
      case KEY_RIGHT:
        ch = UserAction_Right;
        break;
      case KEY_DOWN:
        ch = UserAction_Down;
        break;
      case KEY_UP:
        ch = UserAction_Rotate;
        break;
    }
  }
  return ch;
}

void handle_timer_tick(GameInfo_t *game_info, GameState_t *game_state,
                       struct timeval *last_move_time) {
  struct timeval current_time;
  gettimeofday(&current_time, NULL);
  long elapsed_ms = (current_time.tv_sec - last_move_time->tv_sec) * 1000 +
                    (current_time.tv_usec - last_move_time->tv_usec) / 1000;

  int drop_speed = 10000 - (game_info->level - 1) * 100;
  if (drop_speed < 1000) drop_speed = 1000;
  int drop_interval = drop_speed / 100;
  if (drop_interval < 1) drop_interval = 1;

  if (*game_state == GameState_Moving && elapsed_ms >= drop_interval) {
    int result = move_piece(0, 1, game_info);
    if (result == CREATE_NEW_TETRAMINO) {
      *game_state = GameState_Spawn;
    }
    gettimeofday(last_move_time, NULL);
  }
}

void handle_user_input(GameInfo_t *game_info, GameState_t *game_state,
                       struct timeval *last_move_time, int ch) {
  const int move = read_user_input(game_state, ch);
  int new_tetr = 0;

  if (move == 'q' || game_info->game_over) {
    *game_state = GameState_GameOver;
  } else if (move == UserAction_Left) {
    new_tetr = move_piece(-1, 0, game_info);
  } else if (move == UserAction_Right) {
    new_tetr = move_piece(1, 0, game_info);
  } else if (move == UserAction_Rotate) {
    rotate_piece(game_info);
  } else if (move == UserAction_Down) {
    new_tetr = move_piece(0, 1, game_info);
    gettimeofday(last_move_time, NULL);
  }

  if (new_tetr == CREATE_NEW_TETRAMINO) {
    *game_state = GameState_Spawn;
  }
}
