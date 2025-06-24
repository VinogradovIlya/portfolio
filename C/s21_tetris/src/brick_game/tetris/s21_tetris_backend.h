/**
 * @file s21_tetris_backend.h
 * @brief Tetris game backend
 * @author Willames
 * @version 1.0
 * @date 2024
 *
 * This file contains function declarations for Tetris game logic,
 * including piece management, collision detection, and scoring.
 */

#ifndef S21_TETRIS_H
#define S21_TETRIS_H

#include "../../s21_tetris_common.h"

/**
 * @brief Initialize game backend
 * @param game_info Pointer to game information structure
 * @param game_state Pointer to current game state
 */
void init_backend(GameInfo_t *game_info, GameState_t *game_state);

/**
 * @brief Generate a random tetromino piece
 * @return Structure containing information about the new piece
 */
Tetromino_t generate_random_tetromino();

/**
 * @brief Spawn a new piece in the game
 * @param game_info Pointer to game information structure
 */
void spawn_piece(GameInfo_t *game_info);

/**
 * @brief Get tetromino shape as a matrix
 * @param piece Structure containing piece information
 * @param form Matrix to store the piece shape
 */
void get_form_tetromino(const Tetromino_t piece,
                        int form[PREVIEW_SIZE][PREVIEW_SIZE]);

/**
 * @brief Get O tetromino shape
 * @param form Matrix to store the piece shape
 * @param rotation Current rotation state
 */
void tetromino_o(int form[PREVIEW_SIZE][PREVIEW_SIZE], const int rotation);

/**
 * @brief Get I tetromino shape
 * @param form Matrix to store the piece shape
 * @param rotation Current rotation state
 */
void tetromino_i(int form[PREVIEW_SIZE][PREVIEW_SIZE], const int rotation);

/**
 * @brief Get Z tetromino shape
 * @param form Matrix to store the piece shape
 * @param rotation Current rotation state
 */
void tetromino_z(int form[PREVIEW_SIZE][PREVIEW_SIZE], const int rotation);

/**
 * @brief Get S tetromino shape
 * @param form Matrix to store the piece shape
 * @param rotation Current rotation state
 */
void tetromino_s(int form[PREVIEW_SIZE][PREVIEW_SIZE], const int rotation);

/**
 * @brief Get J tetromino shape
 * @param form Matrix to store the piece shape
 * @param rotation Current rotation state
 */
void tetromino_j(int form[PREVIEW_SIZE][PREVIEW_SIZE], const int rotation);

/**
 * @brief Get L tetromino shape
 * @param form Matrix to store the piece shape
 * @param rotation Current rotation state
 */
void tetromino_l(int form[PREVIEW_SIZE][PREVIEW_SIZE], const int rotation);

/**
 * @brief Get T tetromino shape
 * @param form Matrix to store the piece shape
 * @param rotation Current rotation state
 */
void tetromino_t(int form[PREVIEW_SIZE][PREVIEW_SIZE], const int rotation);

/**
 * @brief Move current piece
 * @param dx Horizontal movement
 * @param dy Vertical movement
 * @param game_info Pointer to game information structure
 * @return Operation result code (GOOD, ERROR, or CREATE_NEW_TETRAMINO)
 */
int move_piece(const int dx, const int dy, GameInfo_t *game_info);

/**
 * @brief Add current piece to game field
 * @param game_info Pointer to game information structure
 */
void add_current_tetromino_in_field(GameInfo_t *game_info);

/**
 * @brief Check if piece movement is possible
 * @param dx Horizontal movement
 * @param dy Vertical movement
 * @param game_info Pointer to game information structure
 * @return 1 if movement is possible, 0 if not
 */
int possibility_of_movement(const int dx, const int dy,
                            const GameInfo_t *game_info);

/**
 * @brief Check and clear completed lines
 * @param game_info Pointer to game information structure
 */
void check_lines(GameInfo_t *game_info);

/**
 * @brief Rotate current piece
 * @param game_info Pointer to game information structure
 * @return Operation result code (GOOD or ERROR)
 */
int rotate_piece(GameInfo_t *game_info);

/**
 * @brief Check if block belongs to current piece
 * @param form Piece shape matrix
 * @param is_current_piece Current piece flag
 * @param game_info Pointer to game information structure
 * @param field_y Field Y coordinate
 * @param field_x Field X coordinate
 * @return 1 if block belongs to current piece, 0 if not
 */
int is_cur_piece(int form[PREVIEW_SIZE][PREVIEW_SIZE], int is_current_piece,
                 const GameInfo_t *game_info, int field_y, int field_x);

/**
 * @brief Read user input and convert it to game action
 * @param game_state Pointer to current game state
 * @param ch Input character from getch()
 * @return User action code (UserAction_Left, UserAction_Right, etc.)
 *
 * This function processes raw input from getch() and converts it to game
 * actions based on the current game state. It handles pause, start, and game
 * over commands, as well as movement and rotation controls when the game is in
 * Moving state.
 */
int read_user_input(GameState_t *game_state, int ch);

/**
 * @brief Handle timer tick event
 * @param game_info Pointer to game information structure
 * @param game_state Pointer to current game state
 * @param last_move_time Pointer to time of last piece movement
 *
 * This function handles the timer tick event, which is responsible for
 * automatic piece movement and game state updates based on time.
 */
void handle_timer_tick(GameInfo_t *game_info, GameState_t *game_state,
                       struct timeval *last_move_time);

/**
 * @brief Handle user input
 * @param game_info Pointer to game information structure
 * @param game_state Pointer to current game state
 * @param last_move_time Pointer to time of last piece movement
 * @param ch Input character from getch()
 *
 * This function processes user input and updates game state accordingly.
 * It handles movement, rotation, pause, and game exit commands.
 * The input character is passed directly from getch() to avoid
 * multiple calls to the input function.
 */
void handle_user_input(GameInfo_t *game_info, GameState_t *game_state,
                       struct timeval *last_move_time, int ch);

#endif  // S21_TETRIS_H
