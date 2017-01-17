#include "Board.h"
#include "Algorithm.h"
#include "Move.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*
 * Module local iteration counter
 */
static int iterationCount;

/*
 * Recursive function, tries the given move on the given board and all subsequent moves by the Warnsdorf heuristic
 * board: pointer to the Board structure
 * x: x-value of the move
 * y: y-value of the move
 * n: current recursion depth
 * closedTour: whether the tour should be closed or not
 */
bool tryPath(Board* board, unsigned int x, unsigned int y, unsigned int n, bool closedTour)
{
    ++iterationCount;

    unsigned int boardSize = board->boardSize;
    // Set (x|y) to n to mark that we were here
    board_setValue(board, x, y, n);

    // If the iteration counter is greater than the number of fields, we have backtracked and the heuristic has failed
    if(iterationCount == (boardSize*boardSize + 1))
        printf("Warnsdorf failed, resorting to backtracking\n");

    // If the recursion depth is equal to the number of fields, we have found a solution!
    // If we have an open tour, we must subtract one because n starts at 0,
    // If we have a closed tour then we don't subtract anything
    if(n == (boardSize*boardSize - !closedTour))
    {
        return true;
    }

    // This decides if the starting point should be included in the possible move list.
    // That is the case when we are searching for a closed tour and when we are one field before the solution
    bool shouldOfferStart = (closedTour && n == (boardSize * boardSize) - 1);
    MoveList moveList = generateMoveList(board, x, y, shouldOfferStart);
    HeuristicMoveList list = generateHeuristic(board, &moveList, shouldOfferStart);

    // Go through all possible moves, sorted by the heuristic
    for(unsigned int i = 0; i < list.dataCount; ++i)
    {
        HeuristicMove* move = &list.data[i];
        bool result = tryPath(board, move->move.x, move->move.y, n+1, closedTour);
        if(result)
        {
            // We have found a solution in a deeper recursion depth, report that to the calls above us and the knightsTour function
            return true;
        }
    }
    // This branch did not result in a solution, "unvisit" this field and return false
    board_setValue(board, x, y, -1);
    return false;
}

void knightsTour(unsigned int boardSize, unsigned int x, unsigned int y, bool closedTour)
{
    iterationCount = 0;
    Board board;
    board_initialize(&board, boardSize);
    bool result = false;
    if(closedTour)
    {
        result = tryPath(&board, 0, 0, 0, closedTour);
        if(result)
        {
            board_rewriteClosed(&board, x, y);
        }
    }
    else
    {
        result = tryPath(&board, x, y, 0, closedTour);
    }

    if(result)
    {
        board_print(&board);
    }
    else
    {
        printf("%s", "No solution found");
    }
    board_destruct(&board);
}
