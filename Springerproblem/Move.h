#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include "Board.h"
#include <stdbool.h>

/*
 * Move destination, defined by x and y
 */
typedef struct Move
{
    unsigned int x;
    unsigned int y;
} Move;

/*
 * Warnsdorf heuristic: sort the next moves by available neighbors in ascending order
 * This struct holds the data needed by the heuristic.
 * move: An instance of the above Move struct
 * neighborCount: How many further moves are possible for the given move
 */
typedef struct HeuristicMove
{
    Move move;
    unsigned int neighborCount;
} HeuristicMove;

/*
 * Move list holds at maximum 8 moves
 * data: the moves in the MoveList
 * dataCount: how many moves are stored in the data array
 */
typedef struct MoveList
{
    Move data[8];
    unsigned int dataCount;
} MoveList;

/*
 * The heuristic version of the above MoveList
 * data: the heuristic moves in the HeuristicMoveList
 * dataCount: how many heuristic moves are stored in the data array
 */
typedef struct HeuristicMoveList
{
    HeuristicMove data[8];
    unsigned int dataCount;
} HeuristicMoveList;

/*
 * Initializes the move list members
 */
void moveList_initialize(MoveList* moveList);
/*
 * Adds a Move to the end of the move list
 */
void moveList_push(MoveList* list, Move* move);
/*
 * Returns a pointer to a move by index
 */
Move* moveList_get(MoveList* list, unsigned int index);

/*
 * Adds a heuristic move to the heuristic move list
 */
void heuristicMoveList_push(HeuristicMoveList* list, HeuristicMove* move);
/*
 * A stable sort for the heuristic move list in order to implement the Warnsdorf heuristic
 */
void heuristicMoveList_sort(HeuristicMoveList* list);

/*
 * Returns all moves that are possible given the current state of the board and the current position
 */
MoveList generateMoveList(Board* board, unsigned int x, unsigned int y, bool shouldOfferStart);
/*
 * Returns a sorted list of all moves in the move list with their neighbor count
 */
HeuristicMoveList generateHeuristic(Board* board, MoveList* moveList, bool shouldOfferStart);

#endif // MOVE_H_INCLUDED
