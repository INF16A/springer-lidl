#include "Algorithm.h"
#include "Move.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int iterationCount;

struct Result
{
    bool status;
    Board* board;
};

struct ResultPath
{
    unsigned int length;
    char* data;
};

Result* result_initialize(bool status, Board* board)
{
    Result* result = malloc(sizeof(Result));
    result->status = status;
    result->board = board;
    return result;
}

void result_destruct(Result* result)
{
    free(result);
}

bool result_getStatus(Result* result)
{
    return result->status;
}

void result_setStatus(Result* result, bool status)
{
    result->status = status;
}

Board* result_getBoard(Result* result)
{
    return result->board;
}

void result_setBoard(Result* result, Board* board)
{
    result->board = board;
}

ResultPath* resultPath_initialize(Result* result)
{
    ResultPath* path = malloc(sizeof(ResultPath));

    unsigned int boardSize = board_getSize(result->board);
    path->length = 3 * (boardSize * boardSize);
    path->data = malloc(path->length);
    memset(path->data, '\x20', path->length);

    for(unsigned int pathIndex = 0; pathIndex < boardSize*boardSize; ++pathIndex)
    {
        for(unsigned int boardIndex = 0; boardIndex < boardSize*boardSize; ++boardIndex)
        {
            if(board_getValueByIndex(result->board, boardIndex) == pathIndex)
                memcpy(&path->data[3*pathIndex], board_indexToString(result->board, boardIndex), 2);
        }
    }
    path->data[path->length - 1] = '\0';
    return path;
}

void resultPath_destruct(ResultPath* path)
{
    free(path->data);
    free(path);
}

const char* resultPath_toString(ResultPath* path)
{
    return path->data;
}

Result* tryPath(Board* board, unsigned int x, unsigned int y, unsigned int n, bool closedTour)
{
    ++iterationCount;

    unsigned int boardSize = board_getSize(board);
    board_setValue(board, x, y, n);

    if(iterationCount == (boardSize*boardSize + 1))
        printf("Warnsdorf failed, resorting to backtracking\n");

    /*
    board_print(board);
    printf("%d %d\n", n, iterationCount);
    system("pause");
    */
    if(closedTour)
    {
        if(n == (boardSize*boardSize))
            return result_initialize(true, board);
    } else {
        if(n == (boardSize*boardSize - 1))
            return result_initialize(true, board);
    }

    bool shouldOfferStart = (closedTour && n == (boardSize * boardSize) - 1);
    MoveList* moveList = generateMoveList(board, x, y, shouldOfferStart);
    HeuristicMoveList* list = generateHeuristic(board, moveList, shouldOfferStart);

    for(unsigned int i = 0; i < heuristicMoveList_getCount(list); ++i)
    {
        Board* boardCopy = board_copy(board);
        HeuristicMove* move = heuristicMoveList_get(list, i);
        Result* result = tryPath(boardCopy, heuristicMove_getX(move), heuristicMove_getY(move), n+1, closedTour);
        if(result_getStatus(result))
        {
            heuristicMoveList_destruct(list);
            moveList_destruct(moveList);
            board_destruct(board);
            return result;
        }
        board_destruct(boardCopy);
        result_destruct(result);
    }

    heuristicMoveList_destruct(list);
    moveList_destruct(moveList);
    return result_initialize(false, NULL);
}

Result* knightsTour(unsigned int boardSize, unsigned int x, unsigned int y, bool closedTour)
{
    iterationCount = 0;
    Board* board = board_initialize(boardSize);
    Result* result = tryPath(board, x, y, 0, closedTour);
    if(result_getStatus(result))
    {
        /*ResultPath* path = resultPath_initialize(result);
        printf("%s", resultPath_toString(path));
        resultPath_destruct(path);*/
        board_print(result->board);
    }
    else
    {
        printf("%s", "No solution found");
    }
    return result;
}
