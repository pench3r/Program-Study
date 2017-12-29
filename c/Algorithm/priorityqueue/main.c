#include "priqueue.h"

int main(int argc, char *argv[]) {
	PriorityQueue priqueue_t;
	PriQueueInit(&priqueue_t);
	PriQueuePush(&priqueue_t, 4, "bamboo");
	PriQueuePush(&priqueue_t, 1, "zhano");
	PriQueuePush(&priqueue_t, 5, "baoo");
	PriQueuePush(&priqueue_t, 7, "tianoo");
	PriQueuePush(&priqueue_t, 2, "feioo");
	PriQueuePop(&priqueue_t);
	PriQueuePop(&priqueue_t);
	PriQueuePop(&priqueue_t);
	PriQueuePop(&priqueue_t);
	PriQueuePush(&priqueue_t, 3, "huilaile");
	PriQueueShow(&priqueue_t);
	return 0;
}
