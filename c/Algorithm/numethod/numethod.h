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

/* struct fract arithmetical
   include: add, multi, div
*/
Fract FractAdd(Fract f1, Fract f2);

Fract FractMul(Fract f1, Fract f2);

Fract FractDiv(Fract f1, Fract f2);

/* common multiple func */
int CommonMulti(int a, int b);

/* common divisor func */
int CommonDivisor(int a, int b);

/* simplify fract func */
// Fract FractSimplify(Fract f1);

void DoubleaToFracta_one(double oarray[ROW][COL], FractArray farray);

void DoubleaToFracta2(double darray[ROW][COL], Fract2Array farray);

void Fract2ArrayInit(Fract2Array *array);

void PrintFract(Fract fract);

void ShowArray(double array[3][3]);

void ShowFract2Array(Fract2Array *array);

void Gauss(double fac_array[ROW][COL], double con_array[ROW], double (*result_array)[ROW]);

#define MAX(x, y) ((x) > (y) ? (x) : (y))

#endif /* __ALGORITHM_NUMTHOD__H */
