#include "Board.h"
#include <stdlib.h>
#include <stdio.h>
struct Board
{
    unsigned char boardSize;
    char* data;
};

Board* board_initialize(unsigned char boardSize)
{
    Board* board = (Board*)malloc(sizeof(Board));
    board->boardSize = boardSize;
    board->data = (char*)malloc((board->boardSize * board->boardSize)*sizeof(char));
    for(unsigned char i = 0; i < (board->boardSize*board->boardSize); ++i)
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

char board_getValue(Board* board, unsigned char x, unsigned char y)
{
    return board->data[y * board->boardSize + x];
}

char board_getValueByIndex(Board* board, unsigned char index)
{
    return board->data[index];
}

void board_setValue(Board* board, unsigned char x, unsigned char y, char value)
{
    board->data[y * board->boardSize + x] = value;
}

unsigned char board_getSize(Board* board)
{
    return board->boardSize;
}

const char* board_locationToString(unsigned char x, unsigned char y)
{
    char* buffer = malloc(3);
    buffer[0] = (char)(y + 'A');
    buffer[1] = (char)(x + '0');
    buffer[2] = '\0';
    return buffer;
}

const char* board_indexToString(Board* board, unsigned char index)
{
    return board_locationToString(index%board_getSize(board), index/board_getSize(board));
}

void board_print(Board* board)
{
    out("|");
    for(unsigned char i = 0; i < board->boardSize; ++i)
    {
        out("---");
    }
    outln("|");
    for(unsigned char y = 0; y < board->boardSize; ++y)
    {
        out("|");
        for(unsigned char x = 0; x < board->boardSize; ++x)
        {
            char value = board_getValue(board, x, y);
            if(value == -1) {
                out("  x");
            }
            else {
              out(" ");
              if (value < 10)
                out(" ");
              outInt(value);
            }
        }
        out("|\n");
    }
    out("|");
    for(unsigned char i = 0; i < board->boardSize; ++i)
    {
        out("---");
    }
    outln("|");
}
