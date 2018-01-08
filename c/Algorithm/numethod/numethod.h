#ifndef __ALGORITHM_NUMETHOD__H
#define __ALGORITHM_NUMETHOD__H


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ROW 3
#define COL 3 


typedef struct fract_ {
	int num;
	int deno;
} Fract;

typedef Fract FractArray[ROW];
typedef Fract Fract2Array[ROW][COL];

void DoubleaToFracta_one(double oarray[ROW][COL], FractArray farray);

void DoubleaToFracta2(double darray[ROW][COL], Fract2Array farray);

void Fract2ArrayInit(Fract2Array *array);

void FractAdd(Fract fract1, Fract fract2);

void PrintFract(Fract fract);

void ShowArray(double array[3][3]);

void ShowFract2Array(Fract2Array *array);

void Gauss(double fac_array[ROW][COL], double con_array[ROW], double (*result_array)[ROW]);

#endif /* __ALGORITHM_NUMTHOD__H */
