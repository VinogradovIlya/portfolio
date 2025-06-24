/**
 * @file s21_tetris_common.h
 * @brief Common definitions and data structures for Tetris game
 * @author Willames
 * @version 1.0
 * @date 2024
 *
 * This file contains common definitions, enumerations and data structures
 * used in both backend and frontend of the Tetris game.
 */

#ifndef S21_TETRIS_COMMON_H
#define S21_TETRIS_COMMON_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

/** @brief Number of rows in the game field */
#define ROWS 20
/** @brief Number of columns in the game field */
#define COLUMNS 10
/** @brief Size of the next piece preview window */
#define PREVIEW_SIZE 4
/** @brief Size of the rotation matrix */
#define ROTATE_SIZE 4
/** @brief Left border of the game field */
#define LEFT (COLS - 12) / 2 - COLUMNS / 2
/** @brief Right border of the game field */
#define RIGHT (COLS - 12) / 2 + COLUMNS / 2 + 1
/** @brief Bottom border of the game field */
#define BOTTOM ROWS + 1

/** @brief Success operation code */
#define GOOD 0
/** @brief Error operation code */
#define ERROR 1
/** @brief Code indicating need to create new tetromino */
#define CREATE_NEW_TETRAMINO 2

/**
 * @brief Game state enumeration
 */
typedef enum {
  GameState_StartScreen, /**< Start screen */
  GameState_Spawn,       /**< New piece spawning */
  GameState_Moving,      /**< Piece moving */
  GameState_GameOver,    /**< Game over */
  GameState_Pause        /**< Game paused */
} GameState_t;

/**
 * @brief User action enumeration
 */
typedef enum {
  UserAction_Left,   /**< Move left */
  UserAction_Right,  /**< Move right */
  UserAction_Down,   /**< Move down */
  UserAction_Rotate, /**< Rotate piece */
  // UserAction_TimerTick /**< Timer tick */
} UserAction_t;

/**
 * @brief Tetromino type enumeration
 */
typedef enum {
  TetrominoType_O,    /**< Square shape */
  TetrominoType_I,    /**< I shape */
  TetrominoType_J,    /**< J shape */
  TetrominoType_L,    /**< L shape */
  TetrominoType_S,    /**< S shape */
  TetrominoType_T,    /**< T shape */
  TetrominoType_Z,    /**< Z shape */
  TetrominoType_Count /**< Number of tetromino types */
} TetrominoType_t;

/**
 * @brief Structure describing a tetromino piece
 */
typedef struct {
  TetrominoType_t type; /**< Type of the piece */
  int rotate;           /**< Current rotation state */
  int x;                /**< X position */
  int y;                /**< Y position */
} Tetromino_t;

/**
 * @brief Structure containing current game state information
 */
typedef struct {
  int field[ROWS][COLUMNS];  /**< Game field */
  Tetromino_t next_piece;    /**< Next piece */
  Tetromino_t current_piece; /**< Current piece */
  int score;                 /**< Current score */
  int high_score;            /**< High score */
  int level;                 /**< Current level */
  int speed;                 /**< Fall speed */
  bool pause;                /**< Pause flag */
  bool game_over;            /**< Game over flag */
} GameInfo_t;

#endif  // S21_TETRIS_COMMON_H
