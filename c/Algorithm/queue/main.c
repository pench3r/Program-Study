#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	Queue queue_t;
	QueueInit(&queue_t);	
	QueueShow(&queue_t);
	return 0;
}
