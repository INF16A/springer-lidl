#include "Board.h"
#include <stdlib.h>
#include <stdio.h>
struct Board
{
    unsigned int boardSize;
    int* data;
};

Board* board_initialize(unsigned int boardSize)
{
    Board* board = (Board*)malloc(sizeof(Board));
    board->boardSize = boardSize;
    board->data = (int*)malloc((board->boardSize * board->boardSize)*sizeof(int));
    for(unsigned int i = 0; i < (board->boardSize*board->boardSize); ++i)
    {
        board->data[i] = -1;
    }
    return board;
}

void board_destruct(Board* board)
{
    free(board->data);
    free(board);
}

Board* board_copy(Board* board)
{
    Board* boardCopy = board_initialize(board->boardSize);
    for(unsigned i = 0; i < board->boardSize*board->boardSize; ++i)
    {
        boardCopy->data[i] = board->data[i];
    }
    return boardCopy;
}

int board_getValue(Board* board, unsigned int x, unsigned int y)
{
    return board->data[y * board->boardSize + x];
}

int board_getValueByIndex(Board* board, unsigned int index)
{
    return board->data[index];
}

void board_setValue(Board* board, unsigned int x, unsigned int y, int value)
{
    board->data[y * board->boardSize + x] = value;
}

unsigned int board_getSize(Board* board)
{
    return board->boardSize;
}

const char* board_locationToString(unsigned int x, unsigned int y)
{
    char* buffer = malloc(3);
    buffer[0] = (char)(y + 'A');
    buffer[1] = (char)(x + '0');
    buffer[2] = '\0';
    return buffer;
}

const char* board_indexToString(Board* board, unsigned int index)
{
    return board_locationToString(index%board_getSize(board), index/board_getSize(board));
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
