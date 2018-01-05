#ifndef __ALGORITHM_NUMETHOD__H
#define __ALGORITHM_NUMETHOD__H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ROW 3
#define COL 4

void ShowArray(double array[3][2]);

void Gauss(double fac_array[ROW][COL], double con_array[ROW]);

#endif /* __ALGORITHM_NUMTHOD__H */
