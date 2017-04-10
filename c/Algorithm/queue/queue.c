#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

// defined Queue init func
void QueueInit(Queue *queue) {
	queue->size = 0;
	queue->queue_head = queue->queue_tail = NULL;		
}

// define Queue equeue func
bool QueueEqueue(Queue *queue, int data) {
	QueueNode *new_node = (QueueNode *)malloc(sizeof(QueueNode));
	new_node->next_node = NULL;
	new_node->data = data;
	if (QueueSize(queue) == 0) {
		queue->queue_head = queue->queue_tail = new_node;
		QueueSize(queue)++;
		return true;
	}
	queue->queue_tail->next_node = new_node;
	queue->queue_tail = new_node;
	QueueSize(queue)++;
	return true;
}

// define Queue dqueue func
bool QueueDqueue(Queue *queue, int *data) {
	if (QueueSize(queue) == 0) {
		printf("The queue is empty!! Can't Dqueue!!!\n");
		return false;
	}
	QueueNode *old_node;
	*data = queue->queue_head->data;
	old_node = queue->queue_head;
	queue->queue_head = queue->queue_head->next_node ? queue->queue_head->next_node : NULL;
	QueueSize(queue)--;
	free(old_node);
	return true;
}

// define Queue destory func
bool QueueDestory(Queue *queue) {
	if (QueueSize(queue) == 0) {
		printf("The queue is empty!! Can't Destory!!!\n");
		return false;
	}
	int *tmp_num = (int *)malloc(sizeof(int));
	for (int i = 0; i < QueueSize(queue); ++i) {
		QueueDqueue(queue, tmp_num);
	}	
	free(tmp_num);
	printf("The queue is destory complete.\n");
	return true;
}

// define Queue show func
void QueueShow(Queue *queue) {
	QueueNode *tmp_node;
	tmp_node = queue->queue_head;
	printf("Begin to show Queue data: \n");
	printf("\tThe size of queue is %d.\n", queue->size);
	printf("The queue each node data is:\n");
	for (int i = 0; i < queue->size; ++i){
		printf("\t The data is %d.\n", tmp_node->data);
		tmp_node = QueueNextNode(tmp_node);	
	}
}
