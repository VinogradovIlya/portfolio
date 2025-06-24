/**
 * @file s21_tetris_frontend.h
 * @brief Tetris game frontend based on ncurses
 * @author Willames
 * @version 1.0
 * @date 2024
 *
 * This file contains function declarations for displaying the game
 * in terminal using the ncurses library.
 */

#ifndef S21_TETRIS_FRONTEND_H
#define S21_TETRIS_FRONTEND_H

#include "../../s21_tetris_common.h"

/**
 * @brief Initialize frontend
 *
 * Initializes ncurses library and configures display settings
 */
void init_frontend();

/**
 * @brief Draw game field
 * @param game_info Pointer to game information structure
 */
void draw_box(const GameInfo_t *game_info);

/**
 * @brief Display main menu
 */
void print_menu();

/**
 * @brief Display pause screen
 */
void print_pause();

/**
 * @brief Display next piece
 * @param x X coordinate for display
 * @param y Y coordinate for display
 * @param game_info Pointer to game information structure
 */
void print_next_tetromino(const int x, const int y,
                          const GameInfo_t *game_info);

/**
 * @brief Draw preview box for next piece
 */
void print_mini_box();

/**
 * @brief Display piece in preview window
 * @param form Matrix containing piece shape
 */
void print_in_mini_box(const int form[PREVIEW_SIZE][PREVIEW_SIZE]);

/**
 * @brief Display game over screen
 * @param game_info Pointer to game information structure
 */
void print_lose(const GameInfo_t *game_info);

/**
 * @brief Render the game state
 * @param game_info Pointer to game information structure
 * @param game_state Current game state
 *
 * This function renders the current game state, including the game field,
 * current piece, score, and other game information.
 */
void render_game(const GameInfo_t *game_info, GameState_t game_state);

#endif  // S21_TETRIS_FRONTEND_H
