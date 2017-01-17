#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "Output.h"

typedef struct Board Board;

Board* board_initialize(unsigned char boardSize);
void board_destruct(Board* board);

Board* board_copy(Board* board);
char board_getValue(Board* board, unsigned char x, unsigned char y);
char board_getValueByIndex(Board* board, unsigned char index);
void board_setValue(Board* board, unsigned char x, unsigned char y, char value);
unsigned char board_getSize(Board* board);

const char* board_locationToString(unsigned char x, unsigned char y);
const char* board_indexToString(Board* board, unsigned char index);

void board_print(Board* board);

#endif // BOARD_H_INCLUDED
