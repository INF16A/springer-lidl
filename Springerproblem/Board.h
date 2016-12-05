#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

typedef struct Board Board;

Board* board_initialize(unsigned int boardSize);
void board_destruct(Board* board);

Board* board_copy(Board* board);
int board_getValue(Board* board, unsigned int x, unsigned int y);
void board_setValue(Board* board, unsigned int x, unsigned int y, int value);
unsigned int board_getSize(Board* board);

#endif // BOARD_H_INCLUDED
