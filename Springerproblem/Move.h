#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include "Board.h"
#include <stdbool.h>

typedef struct Move Move;
typedef struct HeuristicMove HeuristicMove;
typedef struct MoveList MoveList;
typedef struct HeuristicMoveList HeuristicMoveList;

unsigned int move_getX(Move* move);
unsigned int move_getY(Move* move);

unsigned int heuristicMove_getX(HeuristicMove* move);
unsigned int heuristicMove_getY(HeuristicMove* move);
unsigned int heuristicMove_getCount(HeuristicMove* move);

MoveList* moveList_initialize();
void moveList_destruct(MoveList* list);
void moveList_push(MoveList* list, Move* move);
unsigned int moveList_getCount(MoveList* list);
Move* moveList_get(MoveList* list, unsigned int index);

HeuristicMoveList* heuristicMoveList_initialize();
void heuristicMoveList_destruct(HeuristicMoveList* list);
void heuristicMoveList_push(HeuristicMoveList* list, HeuristicMove* move);
void heuristicMoveList_sort(HeuristicMoveList* list);
unsigned int heuristicMoveList_getCount(HeuristicMoveList* list);
HeuristicMove* heuristicMoveList_get(HeuristicMoveList* list, unsigned int index);

MoveList* generateMoveList(Board* board, unsigned int x, unsigned int y, bool shouldOfferStart);
HeuristicMoveList* generateHeuristic(Board* board, MoveList* moveList, bool shouldOfferStart);

#endif // MOVE_H_INCLUDED
