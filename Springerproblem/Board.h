#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

typedef struct Board Board;

Board* board_initialize(unsigned int boardSize);
void board_destruct(Board* board);

Board* board_copy(Board* board);
int board_getValue(Board* board, unsigned int x, unsigned int y);
int board_getValueByIndex(Board* board, unsigned int index);
void board_setValue(Board* board, unsigned int x, unsigned int y, int value);
unsigned int board_getSize(Board* board);

const char* board_locationToString(unsigned int x, unsigned int y);
const char* board_indexToString(Board* board, unsigned int index);

void board_print(Board* board);

#endif // BOARD_H_INCLUDED
