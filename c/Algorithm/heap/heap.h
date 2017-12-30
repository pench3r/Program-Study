#ifndef __ALGORITHM_HEAP__H
#define __ALGORITHM_HEAP__H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


typedef struct heap_ {
	int len;
	int level;
	int size;
	int *buf;
} Heap;


/* struct heap init func
   prarameters:
		Heap *heap,
		int level,
   return: void.
*/
void HeapInit(Heap *heap, int level);

/* struct heap insert func
   desc:
		insert left node index is: index * 2 + 1;
		insert right node index is: index * 2 + 2;
   parameters:
		Heap *heap,
		int index,
		int data,
   return: bool.
*/
bool HeapInsert(Heap *heap, int index, int data);

/* struct heap show func
   parameters:
		Heap *heap,
   return: void.
*/
void HeapShow(Heap *heap);

#endif /* __ALGORITHM_HEAP__H */
