#include "brick_game/tetris/s21_tetris_backend.h"
#include "gui/cli/s21_tetris_frontend.h"

int main() {
  init_frontend();
  GameInfo_t game_info = {0};
  GameState_t game_state = {0};
  init_backend(&game_info, &game_state);
  struct timeval last_move_time;
  gettimeofday(&last_move_time, NULL);
  while (game_state != GameState_GameOver && !game_info.game_over) {
    if (game_state == GameState_Spawn) {
      spawn_piece(&game_info);
      add_current_tetromino_in_field(&game_info);
      game_state = GameState_Moving;
    }

    handle_timer_tick(&game_info, &game_state, &last_move_time);

    render_game(&game_info, game_state);
    int ch = getch();
    handle_user_input(&game_info, &game_state, &last_move_time, ch);
    erase();
    doupdate();
    struct timeval tv = {0, 50000};
    select(0, NULL, NULL, NULL, &tv);
  }
  print_lose(&game_info);
  FILE *f = fopen("record.txt", "w");
  if (f) {
    fprintf(f, "%d", game_info.high_score);
    fclose(f);
  }
  endwin();
  return 0;
}
