# Tetris Game

A classic Tetris game implementation in C using the ncurses library.

## Features

- Classic Tetris gameplay
- Score tracking and high score
- Level progression
- Next piece preview
- Pause functionality

## Controls

- Left Arrow: Move piece left
- Right Arrow: Move piece right
- Down Arrow: Move piece down
- Up Arrow: Rotate piece
- P: Pause game
- Q: Quit game

## Building

To build the game, run:

```bash
make install
```

This will create the game executable in the `game` directory.

## Running

After building, run the game with:

```bash
cd game
./s21_tetris
```

## Documentation

To generate documentation, run:

```bash
make dvi
```

Then open `doc/html/index.html` in your web browser.

## Project Structure

- `src/brick_game/tetris/` - Game logic and backend
- `src/gui/cli/` - Terminal user interface using ncurses
- `src/` - Common definitions and main game loop

## Dependencies

- gcc compiler
- ncurses library
- make utility

## Author

- Willames 