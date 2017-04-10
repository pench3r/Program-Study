#ifndef __ALGORITHM_QUEUE__H
#define __ALGORITHM_QUEUE__H

#include <stdbool.h>

typedef struct QueueNode_ {
	int data;
	struct QueueNode_ *next_node;
}QueueNode;

typedef struct Queue_ {
	int size;
	QueueNode *queue_head;
	QueueNode *queue_tail;
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
		int data,
   return: bool.
*/
bool QueueEqueue(Queue *queue, int data);

/* struct queue dqueue func
   parameters:
		Queue *queue,
		int *data,
   return: bool.
*/
bool QueueDqueue(Queue *queue, int *data);

/* struct queue destory func
   parameters:
		Queue *queue,
   return: void.
*/
bool QueueDestory(Queue *queue);

/* struct queue show func
   parameters:
		Queue *queue,
   return: void.
*/
void QueueShow(Queue *queue);

#define QueuePeek(queue) ( (queue)->size == 0 ? -1 : ((queue)->queue_head->data))

#define QueueNextNode(node) ((node)->next_node)

#define QueueSize(queue) ((queue)->size)

#endif /* __ALGORITHM_QUEUE__H */
