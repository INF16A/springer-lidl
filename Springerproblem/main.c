#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Algorithm.h"

int main()
{
    printf("=== Knights Tour (Team Lidl) ===\n");
    printf("%s", "1. Open Knights Tour\n");
    printf("%s", "2. Closed Knights Tour\n");
    printf("%s", "3. Open Knights Tour (Starting point chosen by program)\n");
    printf("%s", "4. Closed Knights Tour (Starting point chosen by program)\n> ");

    int choice = 0;
    scanf("%d", &choice);

    if(choice == 1 || choice == 2)
    {
        bool closed = choice == 2;

        printf("%s", "Starting point. Format: %d %d\nLeft upper corner is 0 0\n> ");
        int x, y;
        scanf("%d %d", &x, &y);

        printf("%s", "Board size. Format: %d\n> ");
        int boardSize;
        scanf("%d", &boardSize);

        knightsTour(boardSize, x, y, closed);
    }
    else if(choice == 3 || choice == 4)
    {
        bool closed = choice == 4;
        printf("%s %s (%d|%d)\n", closed ? "Closed" : "Open", "Knights Tour", 0, 0);
        knightsTour(8, 0, 0, closed);
    }
    return 0;
}
