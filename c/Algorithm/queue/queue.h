#ifndef __ALGORITHM_QUEUE__H
#define __ALGORITHM_QUEUE__H

#include <stdbool.h>

typedef struct QueueNode_ {
	int data;
	struct QueueNode_ *next_node;
}QueueNode;

typedef struct Queue_ {
	int size;
	struct QueueNode *queue_head;
	struct QueueNode *queue_tail;
}Queue;

/* struct queue init func
   parameters:
		Queue *queue,
   return: void.
*/
void QueueInit(Queue *queue);

/* struct queue equeue func
   parameters:
		Queue *queue,
		QueueNode *node,
   return: bool.
*/
bool QueueEqueue(Queue *queue, QueueNode *node);

/* struct queue show func
   parameters:
		Queue *queue,
   return: void.
*/
void QueueShow(Queue *queue);

#endif /* __ALGORITHM_QUEUE__H */
