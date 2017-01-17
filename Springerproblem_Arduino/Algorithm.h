#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED

#include <stdbool.h>
#include "Board.h"
#include "Output.h"

typedef struct Result Result;
typedef struct ResultPath ResultPath;

Result* result_initialize(bool status, Board* board);
void result_destruct(Result* result);

bool result_getStatus(Result* result);
void result_setStatus(Result* result, bool status);

Board* result_getBoard(Result* result);
void result_setBoard(Result* result, Board* board);

ResultPath* resultPath_initialize(Result* result);
void resultPath_destruct(ResultPath* path);
const char* resultPath_toString(ResultPath* path);

Result* knightsTour(unsigned char boardSize, unsigned char x, unsigned char y, bool closedTour);

#endif // ALGORITHM_H_INCLUDED
