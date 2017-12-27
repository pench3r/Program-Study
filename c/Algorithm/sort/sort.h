/* sort algorithm header file */
#ifndef __ALGORITHM_SORT__H
#define __ALGORITHM_SORT__H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* insertion sort version 1 func
   parameters:
		int array[],
		int size,
   return: void.
*/
void InsertSort_1(int array[], int size);

/* recursive insertion sort version 2 func
   parameters:
		int array[],
		int size,
   return: void.
*/
void RecursiveInsertSort(int array[], int size);

/* tail recursive insertion sort func
   parameters:
		int array[],
		int tmp[],
		int tmp_size,
		int array_size,
   return: int *.
*/
int * TailRecursiveInsertSort(int array[], int tmp[], int tmp_size, int array_size);

/* quick sort func
   parameters:
		int array[],
		int left,
		int right,
   return: void.
*/
void QuickSort(int array[], int left, int right);

/* array show func
   parameters:
		int array[],
		int size,
   return: void.
*/
void ArrayShow(int array[], int size);

/* array data swp func
   parameters:
		int *x,
		int *y,
   return: void.
*/
void ArrayDataSwap(int *x, int *y);

#endif /* __ALGORITHM_SORT__H */
