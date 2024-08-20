# Snake Game
A simple Snake game implemented using SFML (Simple and Fast Multimedia Library). This classic game challenges you to navigate a snake to eat food while avoiding collisions with the walls and the snake's own body. The game supports different difficulty levels and includes a restart feature.

## Features
Difficulty Levels: Start the game with different speeds by passing an argument:
- easy
- medium
- hard
- super-hard
Restart Option: Press R to restart the game without closing the application.
Score Tracking: Your score increases as you eat food and grows longer.
Building and Running
## Prerequisites
Make sure you have SFML installed on your system. You can install SFML using the provided Makefile:

- For Linux use: 
```
make install_linux
```
- For macOS use: 
```
make install_mac
```
## Build the Game
To compile the game, run:
```bash
make
```
## Run the Game
After building, you can run the game with different difficulty levels like this:

```bash
./snake_game easy
```
Replace easy with medium, hard, or super-hard to adjust the game difficulty.

## Controls
- Arrow Keys: Control the direction of the snake.
- Escape: Exit the game.
- R (when game is over): Restart the game with the same difficulty level.

## Makefile
The Makefile includes targets for:

- Building: Compiles the game with SFML libraries.
- Cleaning: Removes the compiled executable.
- Installing SFML: Installs SFML on Linux or macOS.
- Rebuilding: Cleans and rebuilds the project.
