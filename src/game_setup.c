#include "game_setup.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Some handy dandy macros for decompression
#define E_CAP_HEX 0x45
#define E_LOW_HEX 0x65
#define S_CAP_HEX 0x53
#define S_LOW_HEX 0x73
#define W_CAP_HEX 0x57
#define W_LOW_HEX 0x77
#define DIGIT_START 0x30
#define DIGIT_END 0x39

/** Initializes the board with walls around the edge of the board.
 *
 * Modifies values pointed to by cells_p, width_p, and height_p and initializes
 * cells array to reflect this default board.
 *
 * Returns INIT_SUCCESS to indicate that it was successful.
 *
 * Arguments:
 *  - cells_p: a pointer to a memory location where a pointer to the first
 *             element in a newly initialized array of cells should be stored.
 *  - width_p: a pointer to a memory location where the newly initialized
 *             width should be stored.
 *  - height_p: a pointer to a memory location where the newly initialized
 *              height should be stored.
 */
enum board_init_status initialize_default_board(int** cells_p, size_t* width_p,
                                                size_t* height_p) {
    *width_p = 20;
    *height_p = 10;
    int* cells = malloc(20 * 10 * sizeof(int));
    *cells_p = cells;
    for (int i = 0; i < 20 * 10; i++) {
        cells[i] = FLAG_PLAIN_CELL;
    }

    // Set edge cells!
    // Top and bottom edges:
    for (int i = 0; i < 20; ++i) {
        cells[i] = FLAG_WALL;
        cells[i + (20 * (10 - 1))] = FLAG_WALL;
    }
    // Left and right edges:
    for (int i = 0; i < 10; ++i) {
        cells[i * 20] = FLAG_WALL;
        cells[i * 20 + 20 - 1] = FLAG_WALL;
    }

    // Add snake
    cells[20 * 2 + 2] = FLAG_SNAKE;

    return INIT_SUCCESS;
}

/** Initialize variables relevant to the game board.
 * Arguments:
 *  - cells_p: a pointer to a memory location where a pointer to the first
 *             element in a newly initialized array of cells should be stored.
 *  - width_p: a pointer to a memory location where the newly initialized
 *             width should be stored.
 *  - height_p: a pointer to a memory location where the newly initialized
 *              height should be stored.
 *  - snake_p: a pointer to your snake struct (not used until part 2!)
 *  - board_rep: a string representing the initial board. May be NULL for
 * default board.
 */
enum board_init_status initialize_game(int** cells_p, size_t* width_p,
                                       size_t* height_p, snake_t* snake_p,
                                       char* board_rep) {
    // TODO: implement!
    int status;
    // Initializes all global variables (snake is set to cell value that's 3 down and 3 over)
    g_game_over = 0;
    g_score = 0;
    snake_p->direction = INPUT_RIGHT;
    if (board_rep != NULL) {
        node_t* head_list = NULL;
        int position = 34;
        insert_first(&head_list, &position, 4);
        (*snake_p).list = head_list;
        status = decompress_board_str(cells_p, width_p, height_p, snake_p, board_rep);
        // free(head_list->data);
        // free(head_list);
    }
    else {
        // snake_p->x = 2;
        // snake_p->y = 2;
        node_t* head_list = NULL;
        int position = 42;
        insert_first(&head_list, &position, 4);
        (*snake_p).list = head_list;
        status = initialize_default_board(cells_p, width_p, height_p);
    }
    if (status == INIT_SUCCESS) {
        place_food(*cells_p, *width_p, *height_p);
    }
    return status;
}

// Checks that there is only one snake ("S") present in the board string
int check_snake_number(char* compressed) {
    int snake_count = 0;
    int i = 0;
    while(compressed[i] != '\0') {
        if(compressed[i] == 'S' && compressed[i + 1] == '1') {
            snake_count++;
        }
        i++;
    }
    if (snake_count != 1) {
        return 0;
    }
    return 1;
}

// Stores the index of where we are when populating the cells array
int cells_index_pointer = 0;

// Iterates through the entire board string and populates the cells array

int populate_board(char* compressed, int* cells, size_t* width, size_t* height, snake_t* snake_p) {
    
    size_t delimiter_count = 0;
    // Loop through entire board string
    for(size_t i = 0; i < strlen(compressed); i++) {
        if (compressed[i] == '|') {
            delimiter_count += 1;
        }
    }
    if (delimiter_count != *height) {
        return 2;
    }
    if (compressed[0] != 'B') {
        return 3;
    }
    const char delimiter[2] = "|";
    
    // Stores the string representing each row
    char* token;
    token = strtok(compressed, delimiter);  
    token = strtok(NULL, delimiter);
    // Stores the index to which cell needs to be filled in the board array
    long cells_index = 0;

    // Looping through the entire decompressed board string
    while (token != NULL) {
        char* previousChar;
        char* pointer = token;
        int row_capacity = *width;
        int row_counter = 0;

        // Looping through each individual row
        while (*pointer) {
            int num_cells = 0;
            // If pointer is at a digit
            if (isdigit(*pointer) > 0) {
                num_cells = strtol(pointer, &pointer, 10);
            }
            // If pointer is NOT at a digit
            else {
                if (*pointer != 'W' && *pointer != 'E' && *pointer != 'S') {
                    return 3;
                }
                else {
                    previousChar = pointer;
                    pointer += 1;
                }
            }
            if (!strncmp(previousChar, "S", 1)) {
                int i;
                for(i = cells_index; i < cells_index + num_cells; i++) {
                    cells[i] = FLAG_SNAKE;
                }
                // Sets the data in the head of the linked list equal to the cell value
                // snake_p->x = (i % *width) - 1;
                // snake_p->y = (i / *width);
            }
            else if (!strncmp(previousChar, "E", 1)) {
                for(int i = cells_index; i < cells_index + num_cells; i++) {
                    cells[i] = FLAG_PLAIN_CELL;
                }
            }
            else if (!strncmp(previousChar, "W", 1)) {
                for(int i = cells_index; i < cells_index + num_cells; i++) {
                    cells[i] = FLAG_WALL;
                }
            }
            cells_index += num_cells;
            row_counter += num_cells;
        }
            if (row_counter != row_capacity) {
                return 2;
            }
        token = strtok(NULL, delimiter);
    }
    return 1;
}

/** Takes in a string `compressed` and initializes values pointed to by
 * cells_p, width_p, and height_p accordingly. Arguments:
 *      - cells_p: a pointer to the pointer representing the cells array
 *                 that we would like to initialize.
 *      - width_p: a pointer to the width variable we'd like to initialize.
 *      - height_p: a pointer to the height variable we'd like to initialize.
 *      - snake_p: a pointer to your snake struct (not used until part 2!)
 *      - compressed: a string that contains the representation of the board.
 * Note: We assume that the string will be of the following form:
 * B24x80|E5W2E73|E5W2S1E72... To read it, we scan the string row-by-row
 * (delineated by the `|` character), and read out a letter (E, S or W) a number
 * of times dictated by the number that follows the letter.
 */
enum board_init_status decompress_board_str(int** cells_p, size_t* width_p,
                                            size_t* height_p, snake_t* snake_p,
                                            char* compressed) {
        
    
    char* x_location = strchr(compressed, (int)'x');
    char* pipe_location = strchr(compressed, (int)'|');
    char str2 [pipe_location - x_location + 1];
    int i;
    for(i = 0; i < pipe_location - x_location - 1; i++) {
        str2[i] = *(x_location + 1 + i);
    }
    str2[i] = '\0';
    *width_p = atoi(str2);

    char* B_location = strchr(compressed, (int)'B');
    char* x_new_location = strchr(compressed, (int)'x');
    char str1 [x_new_location - B_location + 1];
    int j;
    for(j = 0; j < x_new_location - B_location - 1; j++) {
        str1[j] = *(B_location + 1 + j);
    }
    str1[j] = '\0';
    *height_p = atoi(str1);

    *cells_p = malloc(*height_p * *width_p * sizeof(int));
    
    if (check_snake_number(compressed) == 0) {
        return INIT_ERR_WRONG_SNAKE_NUM;
    }
    int result = populate_board(compressed, *cells_p, width_p, height_p, snake_p);
    if (result == 3) {
        return INIT_ERR_BAD_CHAR;
    }
    else if (result == 2) {
        return INIT_ERR_INCORRECT_DIMENSIONS;
    }
    return INIT_SUCCESS;
}