/* struct sigle linked header */
#ifndef __ALGORITHM_LIST__H
#define __ALGORITHM_LIST__H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
bool ListInsertNext(List *list, ListNode *list_node, int data);

/* struct list remove func
   parameters:
		List *list,
		int data,
   return: bool.
*/
bool ListRemove(List *list, int data);

/* struct list search func
   parameters:
		List *list,
		int data,
   return: int.
*/
int ListSearch(List *list, int data);

void ListShow(List *list);

void ListDestory(List *list);

#define NextNode(node) ((node)->node_next)

#define ListHeadNode(list) ((list)->list_head)

#endif /* __ALGORITHM_LIST__H */
