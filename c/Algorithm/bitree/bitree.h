#ifndef __ALGORITHM_BITREE__H
#define __ALGORITHM_BITREE__H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct bitreenode_ {
	int data;
	struct bitreenode_ *node_left;
	struct bitreenode_ *node_right;
} BitreeNode;

typedef struct bitree_ {
	int size;
	BitreeNode *bitree_root;
} Bitree;

/* struct bitree init func
   parameters:
		Bitree *bitree,
   return: void.
*/
void BitreeInit(Bitree *bitree);

/* struct bitree insert left func
   parameters:
		Bitree *bitree,
		BitreeNode *bitree_node,
		int data,
   return: bool.
*/
bool BitreeInsertLeftNode(Bitree *bitree, BitreeNode *bitree_node, int data);

/* struct bitree insert right func
   parameters:
		Bitree *bitree,
		BitreeNode *bitree_node,
		int data,
   return: bool.
*/
bool BitreeInsertRightNode(Bitree *bitree, BitreeNode *bitree_node, int data);

/* struct bitree remove left func
   parameters:
		Bitree *bitree,
		BitreeNode *bitree_node,
		int *data,
   return: bool.
*/
bool BitreeRemoveLeftNode(Bitree *bitree, BitreeNode *bitree_node);

void BitreeShow(Bitree *bitree);

#define BitreeRootNode(bitree) ((bitree)->bitree_root)

#endif /* __ALGORITHM_BITREE__H */
