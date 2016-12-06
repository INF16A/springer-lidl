#include "Move.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

struct Move
{
    unsigned int x;
    unsigned int y;
};

struct HeuristicMove
{
    Move move;
    unsigned int neighbourCount;
};

struct MoveList
{
    Move* data;
    unsigned int dataCount;
    unsigned int allocated;
};

struct HeuristicMoveList
{
    HeuristicMove* data;
    unsigned int dataCount;
    unsigned int allocated;
};

Move* move_initialize(unsigned int x, unsigned int y)
{
    Move* move = malloc(sizeof(Move));
    move->x = x;
    move->y = y;
    return move;
}

void move_destruct(Move* move)
{
    free(move);
}

unsigned int move_getX(Move* move)
{
    return move->x;
}

unsigned int move_getY(Move* move)
{
    return move->y;
}

HeuristicMove* heuristicMove_initialize(Move* move, unsigned int neighbourCount)
{
    HeuristicMove* heuristicMove = malloc(sizeof(HeuristicMove));
    memcpy(&heuristicMove->move, move, sizeof(Move));
    heuristicMove->neighbourCount = neighbourCount;
    return heuristicMove;
}

void heuristicMove_destruct(HeuristicMove* move)
{
    free(move);
}

unsigned int heuristicMove_getX(HeuristicMove* move)
{
    return move->move.x;
}

unsigned int heuristicMove_getY(HeuristicMove* move)
{
    return move->move.y;
}

unsigned int heuristicMove_getCount(HeuristicMove* move)
{
    return move->neighbourCount;
}

MoveList* moveList_initialize()
{
    MoveList* moveList = malloc(sizeof(MoveList));
    if(moveList == NULL)
    {
        perror("malloc failed");
    }
    moveList->allocated = 8;
    moveList->dataCount = 0;
    moveList->data = malloc(sizeof(Move)*8);
    return moveList;
}

void moveList_destruct(MoveList* list)
{
    free(list);
}

void moveList_push(MoveList* list, Move* move)
{
    if(list->dataCount == list->allocated)
    {
        Move* newData = malloc(sizeof(Move) * (list->allocated * 2));
        list->allocated *= 2;
        memcpy(newData, list->data, list->dataCount);
        free(list->data);
        list->data = newData;
    }
    memcpy(&list->data[list->dataCount++], move, sizeof(Move));
}

unsigned int moveList_getCount(MoveList* list)
{
    return list->dataCount;
}

HeuristicMoveList* heuristicMoveList_initialize()
{
    HeuristicMoveList* moveList = (HeuristicMoveList*)malloc(sizeof(HeuristicMoveList));
    moveList->allocated = 8;
    moveList->dataCount = 0;
    moveList->data = malloc(sizeof(HeuristicMove)*8);
    return moveList;
}

void heuristicMoveList_destruct(HeuristicMoveList* list)
{
    free(list);
}

void heuristicMoveList_push(HeuristicMoveList* list, HeuristicMove* move)
{
    if(list->dataCount == list->allocated)
    {
        HeuristicMove* newData = malloc(sizeof(HeuristicMove) * (list->allocated * 2));
        list->allocated *= 2;
        memcpy(newData, list->data, list->dataCount);
        free(list->data);
        list->data = newData;
    }
    memcpy(&list->data[list->dataCount++], move, sizeof(HeuristicMove));
}

int heuristicComparator(const void* elem1, const void* elem2)
{
    const HeuristicMove* heuristic1 = elem1;
    const HeuristicMove* heuristic2 = elem2;
    return heuristic1->neighbourCount - heuristic2->neighbourCount;
}

void swapHeuristic(HeuristicMove* move1, HeuristicMove* move2)
{
    HeuristicMove tmp = *move1;
    *move1 = *move2;
    *move2 = tmp;
}

void heuristicMoveList_sort(HeuristicMoveList* list)
{
    // qsort is not stable...
    // qsort(list->data, list->dataCount, sizeof(HeuristicMove), heuristicComparator);
    for(unsigned int outer = list->dataCount; outer; --outer)
    {
        bool didSwap = false;
        for(unsigned int inner = 0; inner < (outer - 1); ++inner)
        {
            HeuristicMove* current = heuristicMoveList_get(list, inner);
            HeuristicMove* next = heuristicMoveList_get(list, inner + 1);
            if(current->neighbourCount > next->neighbourCount)
            {
                swapHeuristic(current, next);
                didSwap = true;
            }
        }
        if(!didSwap) break;
    }
}

unsigned int heuristicMoveList_getCount(HeuristicMoveList* list)
{
    return list->dataCount;
}

HeuristicMove* heuristicMoveList_get(HeuristicMoveList* list, unsigned int index)
{
    assert(list->dataCount > index);
    return &list->data[index];
}

bool checkBounds(Board* board, Move* move)
{
    return move->x >= 0 && move->x < board_getSize(board) && move->y >= 0 && move->y < board_getSize(board);
}

bool checkBoard(Board* board, Move* move, bool shouldOfferStart)
{
    return board_getValue(board, move_getX(move), move_getY(move)) == -1 || (shouldOfferStart && board_getValue(board, move_getX(move), move_getY(move)) == 0);
}

Move* moveList_get(MoveList* list, unsigned int index)
{
    assert(list->dataCount > index);
    return &list->data[index];
}

MoveList* generateMoveList(Board* board, unsigned int x, unsigned int y, bool shouldOfferStart)
{
    MoveList* moveList = moveList_initialize();

    Move* move = move_initialize(x + 1, y + 2);
    if(checkBounds(board, move) && checkBoard(board, move, shouldOfferStart)) moveList_push(moveList, move);
    move_destruct(move);

    move = move_initialize(x + 2, y + 1);
    if(checkBounds(board, move) && checkBoard(board, move, shouldOfferStart)) moveList_push(moveList, move);
    move_destruct(move);

    move = move_initialize(x + 2, y - 1);
    if(checkBounds(board, move) && checkBoard(board, move, shouldOfferStart)) moveList_push(moveList, move);
    move_destruct(move);

    move = move_initialize(x + 1, y - 2);
    if(checkBounds(board, move) && checkBoard(board, move, shouldOfferStart)) moveList_push(moveList, move);
    move_destruct(move);

    move = move_initialize(x - 1, y - 2);
    if(checkBounds(board, move) && checkBoard(board, move, shouldOfferStart)) moveList_push(moveList, move);
    move_destruct(move);

    move = move_initialize(x - 2, y - 1);
    if(checkBounds(board, move) && checkBoard(board, move, shouldOfferStart)) moveList_push(moveList, move);
    move_destruct(move);

    move = move_initialize(x - 2, y + 1);
    if(checkBounds(board, move) && checkBoard(board, move, shouldOfferStart)) moveList_push(moveList, move);
    move_destruct(move);

    move = move_initialize(x - 1, y + 2);
    if(checkBounds(board, move) && checkBoard(board, move, shouldOfferStart)) moveList_push(moveList, move);
    move_destruct(move);

    return moveList;
}

HeuristicMoveList* generateHeuristic(Board* board, MoveList* moveList, bool shouldOfferStart)
{
    HeuristicMoveList* heuristicMoveList = heuristicMoveList_initialize();
    for(unsigned int i = 0; i < moveList_getCount(moveList); ++i)
    {
        Move* move = moveList_get(moveList, i);
        MoveList* neighbourMoveList = generateMoveList(board, move_getX(move), move_getY(move), shouldOfferStart);
        // Warnsdorf heuristic: prefer fields with fewer next steps
        HeuristicMove* heuristicMove = heuristicMove_initialize(move, moveList_getCount(neighbourMoveList));

        heuristicMoveList_push(heuristicMoveList, heuristicMove);

        heuristicMove_destruct(heuristicMove);
        moveList_destruct(neighbourMoveList);
    }
    // Warnsdorf heuristic: sort by neighbor count
    heuristicMoveList_sort(heuristicMoveList);
    return heuristicMoveList;
}
