#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	Queue queue_t;
	int *recv_num  = (int *)malloc(sizeof(int));
	QueueInit(&queue_t);	
	QueueEqueue(&queue_t, 20);
	QueueEqueue(&queue_t, 30);
	QueueEqueue(&queue_t, 40);
	QueueEqueue(&queue_t, 50);
	QueueShow(&queue_t);
	QueueDqueue(&queue_t, recv_num);	
	printf("The dqueue number is %d.\n", *recv_num);
	QueueShow(&queue_t);
	QueueEqueue(&queue_t, 60);
	QueueShow(&queue_t);
	printf("The head data of queue is %d.\n", QueuePeek(&queue_t));
	QueueDqueue(&queue_t, recv_num);	
	QueueDqueue(&queue_t, recv_num);	
	QueueDqueue(&queue_t, recv_num);	
	QueueDqueue(&queue_t, recv_num);	
	QueueDqueue(&queue_t, recv_num);	
	QueueShow(&queue_t);
	QueueEqueue(&queue_t, 120);
	QueueEqueue(&queue_t, 130);
	QueueEqueue(&queue_t, 140);
	QueueEqueue(&queue_t, 150);
	QueueShow(&queue_t);
	free(recv_num);
	QueueDestory(&queue_t);
	return 0;
}
