#include <check.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "../../brick_game/tetris/s21_tetris_backend.h"

GameInfo_t game_info;
GameState_t game_state;

void setup(void) { init_backend(&game_info, &game_state); }

void teardown(void) { unlink("record.txt"); }

START_TEST(test_init_backend) {
  GameInfo_t test_info;
  GameState_t test_state;
  init_backend(&test_info, &test_state);

  ck_assert_int_eq(test_state, GameState_StartScreen);
  ck_assert_int_eq(test_info.level, 1);
  ck_assert_int_eq(test_info.score, 0);
  ck_assert_int_eq(test_info.high_score, 0);
  ck_assert_int_eq(test_info.game_over, false);
  ck_assert_int_eq(test_info.pause, false);

  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLUMNS; x++) {
      ck_assert_int_eq(test_info.field[y][x], 0);
    }
  }
}
END_TEST

START_TEST(test_generate_random_tetromino) {
  Tetromino_t piece = generate_random_tetromino();

  ck_assert_int_ge(piece.type, TetrominoType_O);
  ck_assert_int_lt(piece.type, TetrominoType_Count);
  ck_assert_int_eq(piece.rotate, 0);
  ck_assert_int_eq(piece.y, 0);
  ck_assert_int_eq(piece.x, COLUMNS / 2 - 2);
}
END_TEST

START_TEST(test_move_piece) {
  int initial_x = game_info.current_piece.x;
  int result = move_piece(1, 0, &game_info);
  ck_assert_int_eq(result, GOOD);
  ck_assert_int_eq(game_info.current_piece.x, initial_x + 1);

  result = move_piece(-1, 0, &game_info);
  ck_assert_int_eq(result, GOOD);
  ck_assert_int_eq(game_info.current_piece.x, initial_x);

  int initial_y = game_info.current_piece.y;
  result = move_piece(0, 1, &game_info);
  ck_assert_int_eq(result, GOOD);
  ck_assert_int_eq(game_info.current_piece.y, initial_y + 1);
}
END_TEST

START_TEST(test_rotate_piece) {
  int initial_rotation = game_info.current_piece.rotate;
  int result = rotate_piece(&game_info);
  ck_assert_int_eq(result, GOOD);
  ck_assert_int_eq(game_info.current_piece.rotate,
                   (initial_rotation + 1) % ROTATE_SIZE);
}
END_TEST

START_TEST(test_spawn_piece) {
  Tetromino_t next_piece = game_info.next_piece;
  spawn_piece(&game_info);

  ck_assert_int_eq(game_info.current_piece.type, next_piece.type);
  ck_assert_int_eq(game_info.current_piece.rotate, next_piece.rotate);
  ck_assert_int_eq(game_info.current_piece.x, next_piece.x);
  ck_assert_int_eq(game_info.current_piece.y, next_piece.y);
}
END_TEST

START_TEST(test_check_lines) {
  for (int x = 0; x < COLUMNS; x++) {
    game_info.field[ROWS - 1][x] = 1;
  }
  int initial_score = game_info.score;
  check_lines(&game_info);

  for (int x = 0; x < COLUMNS; x++) {
    ck_assert_int_eq(game_info.field[ROWS - 1][x], 0);
  }
  ck_assert_int_gt(game_info.score, initial_score);

  game_info.score = 6000;
  check_lines(&game_info);
  ck_assert_int_eq(game_info.level, 10);
}
END_TEST

START_TEST(test_tetromino_shapes) {
  int form[PREVIEW_SIZE][PREVIEW_SIZE] = {0};
  Tetromino_t piece = {0};

  piece.type = TetrominoType_O;
  get_form_tetromino(piece, form);
  ck_assert_int_eq(form[1][1], 1);
  ck_assert_int_eq(form[1][2], 1);
  ck_assert_int_eq(form[2][1], 1);
  ck_assert_int_eq(form[2][2], 1);

  piece.type = TetrominoType_I;
  get_form_tetromino(piece, form);
  ck_assert_int_eq(form[1][0], 1);
  ck_assert_int_eq(form[1][1], 1);
  ck_assert_int_eq(form[1][2], 1);
  ck_assert_int_eq(form[1][3], 1);

  piece.type = TetrominoType_Z;
  get_form_tetromino(piece, form);
  ck_assert_int_eq(form[0][0], 1);
  ck_assert_int_eq(form[0][1], 1);
  ck_assert_int_eq(form[1][1], 1);
  ck_assert_int_eq(form[1][2], 1);

  piece.type = TetrominoType_S;
  get_form_tetromino(piece, form);
  ck_assert_int_eq(form[0][1], 1);
  ck_assert_int_eq(form[0][2], 1);
  ck_assert_int_eq(form[1][1], 1);
  ck_assert_int_eq(form[1][0], 1);

  piece.type = TetrominoType_J;
  get_form_tetromino(piece, form);
  ck_assert_int_eq(form[0][1], 1);
  ck_assert_int_eq(form[1][1], 1);
  ck_assert_int_eq(form[2][1], 1);
  ck_assert_int_eq(form[2][0], 1);

  piece.type = TetrominoType_L;
  get_form_tetromino(piece, form);
  ck_assert_int_eq(form[0][1], 1);
  ck_assert_int_eq(form[1][1], 1);
  ck_assert_int_eq(form[2][1], 1);
  ck_assert_int_eq(form[2][2], 1);

  piece.type = TetrominoType_T;
  get_form_tetromino(piece, form);
  ck_assert_int_eq(form[1][0], 1);
  ck_assert_int_eq(form[1][1], 1);
  ck_assert_int_eq(form[1][2], 1);
  ck_assert_int_eq(form[2][1], 1);
}
END_TEST

START_TEST(test_possibility_of_movement) {
  int result = possibility_of_movement(1, 0, &game_info);
  ck_assert_int_eq(result, GOOD);

  game_info.current_piece.x = COLUMNS - 1;
  result = possibility_of_movement(1, 0, &game_info);
  ck_assert_int_eq(result, ERROR);

  game_info.current_piece.y = ROWS - 1;
  result = possibility_of_movement(0, 1, &game_info);
  ck_assert_int_eq(result, CREATE_NEW_TETRAMINO);
}
END_TEST

START_TEST(test_game_over) {
  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLUMNS; x++) {
      if (y == 0 && x >= COLUMNS / 2 - 1 && x <= COLUMNS / 2 + 1) {
        game_info.field[y][x] = 0;
      } else {
        game_info.field[y][x] = 1;
      }
    }
  }

  spawn_piece(&game_info);
  ck_assert_int_eq(game_info.game_over, true);
}
END_TEST

START_TEST(test_read_high_score) {
  FILE *f = fopen("record.txt", "w");
  ck_assert_ptr_nonnull(f);
  fprintf(f, "1000");
  fclose(f);

  GameInfo_t test_info;
  GameState_t test_state;
  init_backend(&test_info, &test_state);
  ck_assert_int_eq(test_info.high_score, 1000);

  unlink("record.txt");
}
END_TEST

START_TEST(test_read_user_input) {
  game_state = GameState_StartScreen;

  int result = read_user_input(&game_state, 's');
  ck_assert_int_eq(game_state, GameState_Spawn);

  result = read_user_input(&game_state, 'p');
  ck_assert_int_eq(game_state, GameState_Pause);

  result = read_user_input(&game_state, 'p');
  ck_assert_int_eq(game_state, GameState_Moving);

  result = read_user_input(&game_state, KEY_LEFT);
  ck_assert_int_eq(result, UserAction_Left);

  result = read_user_input(&game_state, KEY_RIGHT);
  ck_assert_int_eq(result, UserAction_Right);

  result = read_user_input(&game_state, KEY_DOWN);
  ck_assert_int_eq(result, UserAction_Down);

  result = read_user_input(&game_state, KEY_UP);
  ck_assert_int_eq(result, UserAction_Rotate);

  result = read_user_input(&game_state, 'q');
  ck_assert_int_eq(game_state, GameState_GameOver);
}
END_TEST

START_TEST(test_handle_user_input) {
  struct timeval last_move_time;
  gettimeofday(&last_move_time, NULL);

  game_state = GameState_Moving;
  game_info.pause = false;
  game_info.game_over = false;
  game_info.current_piece.x = 5;
  game_info.current_piece.y = 0;
  game_info.current_piece.type = TetrominoType_O;
  game_info.current_piece.rotate = 0;

  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLUMNS; x++) {
      game_info.field[y][x] = 0;
    }
  }

  add_current_tetromino_in_field(&game_info);

  handle_user_input(&game_info, &game_state, &last_move_time, KEY_LEFT);
  ck_assert_int_eq(game_info.current_piece.x, 4);

  handle_user_input(&game_info, &game_state, &last_move_time, KEY_RIGHT);
  ck_assert_int_eq(game_info.current_piece.x, 5);

  int old_rotate = game_info.current_piece.rotate;
  handle_user_input(&game_info, &game_state, &last_move_time, KEY_UP);
  ck_assert_int_eq(game_info.current_piece.rotate,
                   (old_rotate + 1) % ROTATE_SIZE);

  handle_user_input(&game_info, &game_state, &last_move_time, 'p');
  ck_assert_int_eq(game_state, GameState_Pause);

  handle_user_input(&game_info, &game_state, &last_move_time, 'p');
  ck_assert_int_eq(game_state, GameState_Moving);

  handle_user_input(&game_info, &game_state, &last_move_time, 'q');
  ck_assert_int_eq(game_state, GameState_GameOver);
}
END_TEST

START_TEST(test_handle_timer_tick) {
  init_backend(&game_info, &game_state);
  game_state = GameState_Moving;
  struct timeval last_move_time;
  gettimeofday(&last_move_time, NULL);

  int initial_y = game_info.current_piece.y;
  struct timespec ts = {0, 200000000};
  nanosleep(&ts, NULL);
  /* usleep(200000); */
  handle_timer_tick(&game_info, &game_state, &last_move_time);
  ck_assert_int_eq(game_info.current_piece.y, initial_y + 1);
  ck_assert_int_eq(game_state, GameState_Moving);

  game_info.level = 5;
  initial_y = game_info.current_piece.y;

  /* usleep(200000); */
  nanosleep(&ts, NULL);
  handle_timer_tick(&game_info, &game_state, &last_move_time);
  ck_assert_int_eq(game_info.current_piece.y, initial_y + 1);

  game_info.current_piece.y = ROWS - 2;
  /* usleep(200000); */
  nanosleep(&ts, NULL);
  handle_timer_tick(&game_info, &game_state, &last_move_time);
  ck_assert_int_eq(game_state, GameState_Spawn);
}
END_TEST

Suite *tetris_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Tetris");
  tc_core = tcase_create("Core");

  tcase_add_checked_fixture(tc_core, setup, teardown);
  tcase_add_test(tc_core, test_init_backend);
  tcase_add_test(tc_core, test_generate_random_tetromino);
  tcase_add_test(tc_core, test_move_piece);
  tcase_add_test(tc_core, test_rotate_piece);
  tcase_add_test(tc_core, test_spawn_piece);
  tcase_add_test(tc_core, test_check_lines);
  tcase_add_test(tc_core, test_tetromino_shapes);
  tcase_add_test(tc_core, test_possibility_of_movement);
  tcase_add_test(tc_core, test_game_over);
  tcase_add_test(tc_core, test_read_high_score);
  tcase_add_test(tc_core, test_read_user_input);
  tcase_add_test(tc_core, test_handle_user_input);
  tcase_add_test(tc_core, test_handle_timer_tick);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = tetris_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
