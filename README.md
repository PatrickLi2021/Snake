# Snake

## Overview:
This project is a terminal-based re-creation of Snake, a famous early computer game widely cloned and reproduced. This project involves a basic playable verison of the game with customizable levels, modifiable playing fields, and standard scorekeeping. This version adheres to the following rules:

- The snake moves around a rectangular playing field bordered by walls, and with some optional internal walls.
- The player uses the arrow keys to change the snake's direction.
- Food appears at random locations on the playing field, and if the snake's head hits the food, the snake eats it. The player's score then increases by 1 and new food appears elsewhere
- When the snake runs into a wall or its own body, it dies and the game is over.

## Project Structure:
Below is an outline of all the files that are provided along with a brief description:

In `snake/src/`:
- `common.h`: Contains definitions for the `input_key` enum and `snake` struct, declarations for global variables defined in `common.c`, and function headers for `common.c`
- `game_over.h`: Contains function headers for `game_over.c`
- `game_setup.h`: Contains the definition for the `board_init_status` enum and function headers for `game_setup.c`
- `game.h`: Contains function headers for `game.c`
- `linked_list.h`: Contains the definition for the `node` struct and function headers for `linked_list.h`
- `mbstrings.h`: Contains function headers for `mbstrings.c`
- `render.h`: Contains fuction headers for `render.c`
- `snake.c`: Contains support functions and main code for gameplay

In `snake/test/`
- `traces.json`: Contains all of the traces (i.e. test cases) that a working implementation should pass

## Overview:

### Game Data:
The game board has certain dimensions, may contain walls, and will have a snake. The game supports user-created levels whose board dimensions may differ. The snake's position is also accessible via global metadata based on arrow key inputs from the user. The width and height of the board are global variables (`size_t width` and `size_t height`). `cells` is what is used to represent the actual game board. For this representation, an array of integers is used.

The game state variables are stored as `int g_game_over` and `int g_score`. These are defined at the top of `common.c`.

### Game Loop:
Many computer games are designed around the idea of a core game loop that repeats over an dover until the game reaches a "game over" state (in this case, it is indicated by the `g_game_over` global variable). Our game loop is

1. Wait (for some specified amount of time) for user input
2. Retrieve user input
3. Update the game state based on user input
4. Render the new game state to the screen

Part of these actions are handled by the following 3 functions:

- `usleep(useconds_t usec)`: A library function that suspends execution for a given amount of time, measured in microseconds
- `update(int* cells, size_t width, size_t height, snake_t* snake_p, enum input_key input, int growing)`: The update function that updates the game state based on the user's input
- `render_game(int* cells, size_t width, size_t height)`: A fucntion that renders the given game state into a visual game that appears in the terminal

### Game Board Decompression:
As stated previously, the game has support for loading user-specified board layouts as a command line argument. An example of this would be 

`W80|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W1E78W1|W80`

where `W` represents a wall, `E` represents empty space, `S` represents the snake, and the vertical bars are delimiters between each row of the game board. The game has implemented error handling for incorrect board strings that are passed into the command line (i.e. bad characters, incorrect dimensions, multiple snakes, etc.)

### Snake Representation:
The growing snake is represented as a pointer to a linked list of coordinates, which allows the program to extend/trim the list as the snake moves. On each iteration, one block is added to the head of the snake while one block is removed from the end of the snake. The linked list essentially stores the snake's current position and the `update` function handles the new structure.
