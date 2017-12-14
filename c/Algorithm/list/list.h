/* struct sigle linked header */
#ifndef __ALGORITHM_LIST__H
#define __ALGORITHM_LIST__H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct listnode_ {
	int data;
	struct listnode_ *node_next;
} ListNode;

typedef struct list_ {
	int size;
	ListNode *list_head;
	ListNode *list_tail;
} List;

/* struct list init func
   parameters:
		List *list,
   return: void.
*/
void ListInit(List *list);

/* struct list insert func
   parameters:
		List *list,
		ListNode *list_node,
		int data,
   return: bool.
*/
bool ListInsert(List *list, ListNode *list_node, int data);

void ListShow(List *list);

#define NextNode(node) ((node)->node_next)

#endif /* __ALGORITHM_LIST__H */
