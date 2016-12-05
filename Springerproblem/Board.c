#include "Board.h"
#include <stdlib.h>
struct Board
{
    unsigned int boardSize;
    int* data;
};

Board* board_initialize(unsigned int boardSize)
{
    Board* board = (Board*)malloc(sizeof(Board));
    board->boardSize = boardSize;
    board->data = (int*)malloc(board->boardSize * board->boardSize);
    for(unsigned int i = 0; i < board->boardSize*board->boardSize; ++i)
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

void board_setValue(Board* board, unsigned int x, unsigned int y, int value)
{
    board->data[y * board->boardSize + x] = value;
}

unsigned int board_getSize(Board* board)
{
    return board->boardSize;
}
