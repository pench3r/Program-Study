#ifndef __ALGORITHM_CLIST__H
#define __ALGORITHM_CLIST__H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ClistNode_ {
	int data;
	struct ClistNode_ *next_clist_node;
} ClistNode;

typedef struct Clist_ {
	int size;
	ClistNode *clist_head;
	ClistNode *clist_tail;
} Clist;

/* struct clist init func
   parameters:
		Clist *clist,
   return: void.
*/
void ClistInit(Clist *clist);

/* struct clist insert func, insert node after clist_node. if clist_node is NULL, insert node after head node, else insert node afoter clist_node.
   parameters:
		Clist *clist,
		ClistNode *clist_node,
		int data,
   return: bool.
*/
bool ClistInsertNextNode(Clist *clist,ClistNode *clist_node, int data);

/* struct clist remove func, remove node after clist_node.
   parameters:
		Clist *clist,
		ClistNode *clist_node,
		int *data,
   return: bool.	
*/
bool ClistRemoveNextNode(Clist *clist, ClistNode *clist_node, int *data);

/* struct clist destory func
   parameters:
		Clist *clist,
   return: void.
*/
void ClistDestory(Clist *clist);

void ClistShow(Clist *clist);

#define ClistHeadNode(clist) ((clist)->clist_head)

#define ClistNextNode(clist_node) ((clist_node)->next_clist_node)

#endif /* __ALGORITHM_CLIST__H */
