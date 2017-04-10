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

/* struct clist insert func
   parameters:
		Clist *clist,
		int data,
   return: bool.
*/
bool ClistInsert(Clist *clist, int data);

void ClistShow(Clist *clist);

#endif /* __ALGORITHM_CLIST__H */
