#ifndef __ALGORITHM_NUMETHOD__H
#define __ALGORITHM_NUMETHOD__H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ROW 3
#define COL 3 

typedef double ResultArray[ROW];

typedef struct fract_ {
	int num;
	int deno;
} Fract;

void PrintFract(Fract *fract);

void ShowArray(double array[3][3]);

void ShowResultArray(ResultArray *array, int size);

void Gauss(double fac_array[ROW][COL], double con_array[ROW], double (*result_array)[ROW]);

#endif /* __ALGORITHM_NUMTHOD__H */
