#include "queue.h"
#include <stdbool.h>
#include <stdio.h>

// defined Queue init func
void QueueInit(Queue *queue) {
	queue->size = 0;
	queue->queue_head = queue->queue_tail = NULL;		
}

// define Queue equeue func
bool QueueEqueue(Queue *queue, QueueNode *node) {
	if (queue->size == 0) {
		queue->queue_head = queue->queue_tail = node;
	}
	queue->size++;
	return true;
}

// define Queue show func
void QueueShow(Queue *queue) {
	printf("Begin to show Queue data: \n");
	printf("\tThe size of queue is %d.\n", queue->size);
}
