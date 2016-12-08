#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Algorithm.h"

int main()
{
    printf("=== Knights Tour (Team Lidl) ===\n");
    printf("%s", "1. Open Knights Tour\n");
    printf("%s", "2. Closed Knights Tour\n> ");

    int choice = 0;
    scanf("%d", &choice);

    bool closed;
    if(choice == 1)
        closed = false;
    else if(choice == 2)
        closed = true;

    printf("%s", "Starting point. Format: %d %d\nLeft upper corner is 0 0\n> ");
    int x, y;
    scanf("%d %d", &x, &y);

    printf("%s", "Board size. Format: %d\n> ");
    int boardSize;
    scanf("%d", &boardSize);

    knightsTour(boardSize, x, y, closed);
    return 0;
}
