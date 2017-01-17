#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include "Board.h"
#include <stdbool.h>

typedef struct Move Move;
typedef struct HeuristicMove HeuristicMove;
typedef struct MoveList MoveList;
typedef struct HeuristicMoveList HeuristicMoveList;

unsigned char move_getX(Move* move);
unsigned char move_getY(Move* move);

unsigned char heuristicMove_getX(HeuristicMove* move);
unsigned char heuristicMove_getY(HeuristicMove* move);
unsigned char heuristicMove_getCount(HeuristicMove* move);

MoveList* moveList_initialize();
void moveList_destruct(MoveList* list);
void moveList_push(MoveList* list, Move* move);
unsigned char moveList_getCount(MoveList* list);
Move* moveList_get(MoveList* list, unsigned char index);

HeuristicMoveList* heuristicMoveList_initialize();
void heuristicMoveList_destruct(HeuristicMoveList* list);
void heuristicMoveList_push(HeuristicMoveList* list, HeuristicMove* move);
void heuristicMoveList_sort(HeuristicMoveList* list);
unsigned char heuristicMoveList_getCount(HeuristicMoveList* list);
HeuristicMove* heuristicMoveList_get(HeuristicMoveList* list, unsigned char index);

MoveList* generateMoveList(Board* board, unsigned char x, unsigned char y, bool shouldOfferStart);
HeuristicMoveList* generateHeuristic(Board* board, MoveList* moveList, bool shouldOfferStart);

#endif // MOVE_H_INCLUDED
