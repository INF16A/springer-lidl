#include "Move.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>


void moveList_initialize(MoveList* moveList)
{
    moveList->dataCount = 0;
}

void moveList_push(MoveList* list, Move* move)
{
    if(list->dataCount < 8)
    {
        memcpy(&list->data[list->dataCount++], move, sizeof(Move));
        return;
    }
    assert(!"Out of memory in move list");
}

void heuristicMoveList_initialize(HeuristicMoveList* moveList)
{
    moveList->dataCount = 0;
}

void heuristicMoveList_push(HeuristicMoveList* list, HeuristicMove* move)
{
    if(list->dataCount < 8)
    {
        memcpy(&list->data[list->dataCount++], move, sizeof(HeuristicMove));
        return;
    }
    assert(!"Out of memory in heuristic move list");
}

/*
 * Swaps two heuristic moves deterministically
 */
void swapHeuristic(HeuristicMove* move1, HeuristicMove* move2)
{
    HeuristicMove tmp = *move1;
    *move1 = *move2;
    *move2 = tmp;
}

void heuristicMoveList_sort(HeuristicMoveList* list)
{
    // We need a stable sort, if two possibilities are equal,
    // then they need to be sorted as seen in the generateMoveList function
    // The implemented algorithm is bubble sort whose worst case runtime is O(n^2)
    // But for 8 elements that does not really matter
    for(unsigned int outer = list->dataCount; outer; --outer)
    {
        bool didSwap = false;
        for(unsigned int inner = 0; inner < (outer - 1); ++inner)
        {
            HeuristicMove* current = &list->data[inner];
            HeuristicMove* next = &list->data[inner + 1];
            if(current->neighborCount > next->neighborCount)
            {
                swapHeuristic(current, next);
                didSwap = true;
            }
        }
        if(!didSwap) break;
    }
}

bool checkBounds(Board* board, Move* move)
{
    return move->x >= 0 && move->x < board->boardSize && move->y >= 0 && move->y < board->boardSize;
}

bool checkBoard(Board* board, Move* move, bool shouldOfferStart)
{
    return board_getValue(board, move->x, move->y) == -1 || (shouldOfferStart && board_getValue(board, move->x, move->y) == 0);
}

Move* moveList_get(MoveList* list, unsigned int index)
{
    assert(list->dataCount > index);
    return &list->data[index];
}

MoveList generateMoveList(Board* board, unsigned int x, unsigned int y, bool shouldOfferStart)
{
    MoveList moveList;
    moveList_initialize(&moveList);

    Move move = {x + 1, y + 2};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        moveList_push(&moveList, &move);

    move = (Move){x + 2, y + 1};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        moveList_push(&moveList, &move);

    move = (Move){x + 2, y - 1};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        moveList_push(&moveList, &move);

    move = (Move){x + 1, y - 2};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        moveList_push(&moveList, &move);

    move = (Move){x - 1, y - 2};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        moveList_push(&moveList, &move);

    move = (Move){x - 2, y - 1};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        moveList_push(&moveList, &move);

    move = (Move){x - 2, y + 1};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        moveList_push(&moveList, &move);

    move = (Move){x - 1, y + 2};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        moveList_push(&moveList, &move);

    return moveList;
}

unsigned int generateMoveCount(Board* board, unsigned int x, unsigned int y, bool shouldOfferStart)
{
    unsigned int moveCount = 0;

    Move move = {x + 1, y + 2};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        ++moveCount;

    move = (Move){x + 2, y + 1};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        ++moveCount;

    move = (Move){x + 2, y - 1};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        ++moveCount;

    move = (Move){x + 1, y - 2};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        ++moveCount;

    move = (Move){x - 1, y - 2};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        ++moveCount;

    move = (Move){x - 2, y - 1};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        ++moveCount;

    move = (Move){x - 2, y + 1};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        ++moveCount;

    move = (Move){x - 1, y + 2};
    if(checkBounds(board, &move) && checkBoard(board, &move, shouldOfferStart))
        ++moveCount;

    return moveCount;
}

HeuristicMoveList generateHeuristic(Board* board, MoveList* moveList, bool shouldOfferStart)
{
    HeuristicMoveList heuristicMoveList;
    heuristicMoveList_initialize(&heuristicMoveList);
    for(unsigned int i = 0; i < moveList->dataCount; ++i)
    {
        Move* move = moveList_get(moveList, i);
        unsigned int moveCount = generateMoveCount(board, move->x, move->y, shouldOfferStart);
        // Warnsdorf heuristic: prefer fields with fewer next steps
        HeuristicMove heuristicMove = {{move->x, move->y}, moveCount};
        heuristicMoveList_push(&heuristicMoveList, &heuristicMove);
    }
    // Warnsdorf heuristic: sort by neighbor count
    heuristicMoveList_sort(&heuristicMoveList);
    return heuristicMoveList;
}
