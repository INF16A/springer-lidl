#include "Board.h"
#include <stdlib.h>
#include <stdio.h>

void board_initialize(Board* board, unsigned int boardSize)
{
    board->boardSize = boardSize;
    board->data = (int*)malloc((board->boardSize * board->boardSize)*sizeof(int));

    // Initialize board data with -1 for not visited
    for(unsigned int i = 0; i < (board->boardSize*board->boardSize); ++i)
    {
        board->data[i] = -1;
    }
}

void board_destruct(Board* board)
{
    free(board->data);
}

int board_getValue(Board* board, unsigned int x, unsigned int y)
{
    return board->data[y * board->boardSize + x];
}

void board_setValue(Board* board, unsigned int x, unsigned int y, int value)
{
    board->data[y * board->boardSize + x] = value;
}

void board_print(Board* board)
{
    printf("%s", "|");
    for(unsigned int i = 0; i < board->boardSize; ++i)
    {
        printf("%s", "---");
    }
    puts("|");
    for(unsigned int y = 0; y < board->boardSize; ++y)
    {
        printf("%s", "|");
        for(unsigned int x = 0; x < board->boardSize; ++x)
        {
            int value = board_getValue(board, x, y);
            if(value == -1)
                printf("% 3c", 'x');
            else if(value == board->boardSize*board->boardSize)
                printf("% 3c", 'X');
            else
                printf("% 3d", value);
        }
        printf("%s", "|\n");
    }
    printf("%s", "|");
    for(unsigned int i = 0; i < board->boardSize; ++i)
    {
        printf("%s", "---");
    }
    puts("|");
}

/*
 * A closed path can be converted into a closed path with another starting position by just starting it at another position.
 * We can do that on our calculated board by taking the starting position as our new zero and calculate each cell given by
 * the formula below. This was done because the calculation in some starting positions was really slow.
 */
void board_rewriteClosed(Board* board, unsigned int rx, unsigned int ry)
{
    // Calculate the new values by applying
    // value = value - offset MOD boardsize^2
    int relative = board_getValue(board, rx, ry);
    if(relative == 0) return;
    unsigned int boardSize = board->boardSize*board->boardSize;
    for(unsigned int x = 0; x < board->boardSize; ++x)
    {
        for(unsigned int y = 0; y < board->boardSize; ++y)
        {
            // C modulo returns negative values, but we want it to wrap around
            // We add boardSize again to make sure it will be positive after modulo
            int newVal = (((board_getValue(board, x, y) - relative) % boardSize) + boardSize) % boardSize;
            board_setValue(board, x, y, newVal);
        }
    }
}
