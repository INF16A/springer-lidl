#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED

#include <stdbool.h>

/*
 * Solve a knights tour for a given board size, start position and whether it should be closed
 */
void knightsTour(unsigned int boardSize, unsigned int x, unsigned int y, bool closedTour);

#endif // ALGORITHM_H_INCLUDED
