#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Algorithm.h"

int main()
{
    printf("=== Springerproblem (Team Lidl) ===\n");
    printf("%s", "1. Offener Springerpfad\n");
    printf("%s", "2. Geschlossener Springerpfad\n> ");

    int choice = 0;
    scanf("%d", &choice);

    bool closed;
    if(choice == 1)
        closed = false;
    else if(choice == 2)
        closed = true;

    printf("%s", "Startpunkt im Format %d %d eingeben. Linke obere Ecke ist 0 0\n> ");
    int x, y;
    scanf("%d %d", &x, &y);

    printf("%s", "Brettgroesse angeben. Format: %d\n> ");
    int boardSize;
    scanf("%d", &boardSize);

    knightsTour(boardSize, x, y, closed);
    return 0;
}
