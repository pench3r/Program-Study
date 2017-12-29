#ifndef __ALGORITHM_PRIQUEUE__H
#define __ALGORITHM_PRIQUEUE__H

#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node_ {
	int priority;
	char *data;
} Node;

typedef struct priorityqueue_ {
	int size;
	int len;
	Node *nodes;
} PriorityQueue;

/* struct priorityqueue init func
   parameters:
		PriorityQueue *priqueue;
   return: void.
*/
void PriQueueInit(PriorityQueue *priqueue);

/* struct priorityqueue push func
   parameters:
		PriorityQueue *priqueue;
		int priority,
		char *data,
   return: bool.
*/
bool PriQueuePush(PriorityQueue *priqueue, int priority, char *data);

/* struct priorityqueue pop func
   parameters:
		PriorityQueue *priqueue,
   return: bool.
*/
bool PriQueuePop(PriorityQueue *priqueue);

/* struct priorityqueue show func
   parameters:
		PriorityQueue *priqueue,
   return: void.
*/
void PriQueueShow(PriorityQueue *priqueue);

#endif /* __ALGORITHM_PRIQUEUE__H */
