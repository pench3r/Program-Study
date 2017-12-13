#ifndef __ALGORITHM_DLIST__H
#define __ALGORITHM_DLIST__H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct dlistnode_ {
	int data;
	struct dlistnode_ *node_prev;
	struct dlistnode_ *node_next;
} DlistNode;

typedef struct dlist_ {
	int size;
	DlistNode *dlist_head;
	DlistNode *dlist_tail;
} Dlist;

/* struct dlist init func
   parameters:
		Dlist *dlist;
   return: void.
*/
void DlistInit(Dlist *dlist);

/* struct dlist insert next func
   parameters:
		Dlist *dlist,
		DlistNode *dlist_node,
		int data,
   return: bool.
*/
bool DlistInsertNextNode(Dlist *dlist, DlistNode *dlist_node, int data);

/* struct dlist insert prev func
   parameters:
		Dlist *dlist,
		DlistNode *dlist_node,
   return: bool.
*/
bool DlistInsertPrevNode(Dlist *dlist, DlistNode *dlist_node, int data);

/* struct dlist remove next func
   parameters:
		Dlist *dlist,
		DlistNode *dlist_node,
		int *data,
   return: bool.
*/
bool DlistRemoveNextNode(Dlist *dlist, DlistNode *dlist_node, int *data);

/* struct dlist remove prev func
   parameters:
		Dlist *dlist,
		DlistNode *dlist_node,
		int *data,
   return: bool.
*/
bool DlistRemovePrevNode(Dlist *dlist, DlistNode *dlist_node, int *data);



void DlistDestory(Dlist *dlist);

void DlistShow(Dlist *dlist);

#define DlistHeadNode(dlist) ((dlist)->dlist_head)

#define DlistTailNode(dlist) ((dlist)->dlist_tail)

#define NextNode(node) ((node)->node_next)

#endif /* __ALGORITHM_DLIST__H */
