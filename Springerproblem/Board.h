#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

typedef struct Board
{
    unsigned int boardSize;
    int* data;
} Board;

/*
 * Initializes all elements of the Board struct, allocates memory for the board
 */
void board_initialize(Board* board, unsigned int boardSize);

/*
 * Deallocates memory allocated by board_initialize
 */
void board_destruct(Board* board);

/*
 * Returns the value of the board at the location given by x and y. Maps x and y to an array index.
 */
int board_getValue(Board* board, unsigned int x, unsigned int y);

/*
 * Sets a value on the board at location at (x|y). Maps x and y to an array index.
 */
void board_setValue(Board* board, unsigned int x, unsigned int y, int value);

/*
 * Outputs all board values with a border.
 */
void board_print(Board* board);

/*
 * Rewrites a closed board at 0|0 to a board at x|y
 */
void board_rewriteClosed(Board* board, unsigned int x, unsigned int y);

#endif // BOARD_H_INCLUDED
