#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "linked_list.h"
#include "mbstrings.h"

/** Updates the game by a single step, and modifies the game information
 * accordingly. Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - width: width of the board.
 *  - height: height of the board.
 *  - snake_p: pointer to your snake struct (not used until part 2!)
 *  - input: the next input.
 *  - growing: 0 if the snake does not grow on eating, 1 if it does.
 */
void update(int* cells, size_t width, size_t height, snake_t* snake_p, enum input_key input, int growing) {
    if (g_game_over == 1) {
        return;
    }
    int* original_pos = (int*)get_first((*snake_p).list);
    void* removed_elem;
    int new_pos;
    // Cases for growing snake cannot double back on itself
    if (length_list(snake_p->list) >= 2 && input == INPUT_DOWN && snake_p->direction == INPUT_UP) {
        input = snake_p->direction;
    }
    else if (length_list(snake_p->list) >= 2 && input == INPUT_LEFT && snake_p->direction == INPUT_RIGHT) {
        input = snake_p->direction;
    }
    else if (length_list(snake_p->list) >= 2 && input == INPUT_UP && snake_p->direction == INPUT_DOWN) {
        input = snake_p->direction;
    }
    else if (length_list(snake_p->list) >= 2 && input == INPUT_RIGHT && snake_p->direction == INPUT_LEFT) {
        input = snake_p->direction;
    }
    if (input == INPUT_NONE) {
        input = snake_p->direction;
    }
    snake_p->direction = INPUT_RIGHT;
    // Regular movement
    if (input == INPUT_DOWN) {
        // Moves the head of the list into a new position and removes the last element from the list
        new_pos = *original_pos + width;
        insert_first(&(*snake_p).list, &new_pos, 4);
        snake_p->direction = INPUT_DOWN;
    }
    else if (input == INPUT_UP) {
        new_pos = *original_pos - width;
        insert_first(&(*snake_p).list, &new_pos, 4);
        snake_p->direction = INPUT_UP;
    }
    else if (input == INPUT_RIGHT) {
        new_pos = *original_pos + 1;
        insert_first(&(*snake_p).list, &new_pos, 4);
        snake_p->direction = INPUT_RIGHT;
    }
    else if (input == INPUT_LEFT) {
        new_pos = *original_pos - 1;
        insert_first(&(*snake_p).list, &new_pos, 4);
        snake_p->direction = INPUT_LEFT;
    }
    // Checking if the new cell position is a wall, food, or snake cell
    if (*(cells + new_pos) == FLAG_WALL) {
        g_game_over = 1;   
        new_pos = *original_pos;
        insert_first(&(*snake_p).list, &new_pos, 4);
        removed_elem = (int*)remove_last(&snake_p->list); 
        free(removed_elem);
    } 
    else if (*(cells + new_pos) == FLAG_FOOD) {
        if (growing == 1) {
            *(cells + new_pos) = FLAG_SNAKE;
        }
        else {
            removed_elem = (int*)remove_last(&snake_p->list);
            *(cells + *(int*)removed_elem) = FLAG_PLAIN_CELL;
            free(removed_elem);
            *(cells + new_pos) = FLAG_SNAKE;
        }
        g_score = g_score + 1;
        place_food(cells, width, height);
    }
    else if (*(cells + new_pos) == FLAG_SNAKE) {
        // If the last cell of the snake is the next position, then don't call game over
        if (*(int*)get_last(snake_p->list) == new_pos) {
            g_game_over = 0;
            removed_elem = (int*)remove_last(&snake_p->list);
            *(cells + *(int*)removed_elem) = FLAG_PLAIN_CELL;
            free(removed_elem);
            *(cells + new_pos) = FLAG_SNAKE;
        } 
        else {
            g_game_over = 1;
        }
    }
    // general movement
    else {
        removed_elem = (int*)remove_last(&snake_p->list);
        *(cells + *(int*)removed_elem) = FLAG_PLAIN_CELL;
        free(removed_elem);
        *(cells + new_pos) = FLAG_SNAKE;
    }
    // `update` should update the board, your snake's data, and global
    // variables representing game information to reflect new state. If in the
    // updated position, the snake runs into a wall or itself, it will not move
    // and global variable g_game_over will be 1. Otherwise, it will be moved
    // to the new position. If the snake eats food, the game score (`g_score`)
    // increases by 1. This function assumes that the board is surrounded by
    // walls, so it does not handle the case where a snake runs off the board.
}

/** Sets a random space on the given board to food.
 * Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - width: the width of the board
 *  - height: the height of the board
 */
void place_food(int* cells, size_t width, size_t height) {
    /* DO NOT MODIFY THIS FUNCTION */
    unsigned food_index = generate_index(width * height);
    if (*(cells + food_index) == FLAG_PLAIN_CELL) {
        *(cells + food_index) = FLAG_FOOD;
    } else {
        place_food(cells, width, height);
    }
    /* DO NOT MODIFY THIS FUNCTION */
}

/** Prompts the user for their name and saves it in the given buffer.
 * Arguments:
 *  - `write_into`: a pointer to the buffer to be written into.
 */
void read_name(char* write_into) {
    // printf("%s", "Name > ");
    // fflush(stdout);
    // int a = read(0, write_into, 1000);
    // if (strlen(write_into) >= 2 && a >= 0) {
    //     fflush(stdout);
    // }
    // else {
    //     while (write_into[0] == '\n') {
    //     printf("%s", "Name Invalid: must be longer than 0 characters. \n");
    //     a = read(0, write_into, 1000);
    //     printf("%s", "Name > ");
    //     }
    // }

    int a = 1;
    while (1) {
        printf("Name > ");
        fflush(stdout);

        a = read(0, write_into, 1000);
        if (write_into[0] == '\n') {
            printf("Name >");
            fflush(stdout);
        }
        else {
            break;
        }
    }
    write_into[a - 1] = '\0';
}

/** Cleans up on game over — should free any allocated memory so that the
 * LeakSanitizer doesn't complain.
 * Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - snake_p: a pointer to your snake struct. (not needed until part 2)
 */
void teardown(int* cells, snake_t* snake_p) {
    free(cells);
    while(length_list(snake_p->list) > 0) {
        void* data_removed = remove_last(&snake_p->list);
        free(data_removed);
    }
    free(snake_p->list);
}
