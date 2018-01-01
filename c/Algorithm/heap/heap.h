#ifndef __ALGORITHM_HEAP__H
#define __ALGORITHM_HEAP__H

#include "../sort/sort.h"
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

/* struct heap insert1 func
   desc:
		insert left node index is: index * 2 + 1;
		insert right node index is: index * 2 + 2;
   parameters:
		Heap *heap,
		int index,
		int data,
   return: bool.
*/
bool HeapInsert1(Heap *heap, int index, int data);

/* struct heap insert func
   parameters:
		Heap *heap,
		int data,
   return: bool.
*/
bool HeapInsert(Heap *heap, int data);

/* struct heap precolate up func
   desc:
		parent node index is: (node_index-1)/2
   parameters:
		Heap *heap,
   return: void.
*/
void HeapPrecolateUp(Heap *heap, int position);

/* struct heap remove func
   parameters:
		Heap *heap,
   return: int.
*/
int HeapRemove(Heap *heap);

/* struct heap precolate down func
   parameters:
		Heap *heap,
		int position,
   return: void.
*/
void HeapPrecolateDown(Heap *heap, int position);

/* struct heap show func
   parameters:
		Heap *heap,
   return: void.
*/
void HeapShow(Heap *heap);

#define NodeParent(node) ((node-1)/2)

#define NodeLeftChild(node) (node*2+1)

#define NodeRightChild(node) (node*2+2)

#endif /* __ALGORITHM_HEAP__H */
