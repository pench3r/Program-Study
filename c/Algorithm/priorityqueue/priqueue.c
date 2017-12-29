#include "priqueue.h"

// define priorityqueue init fuc
void PriQueueInit(PriorityQueue *priqueue) {
	priqueue->len = 0;
	priqueue->size = 6;
	priqueue->nodes = (Node *)calloc(priqueue->size, sizeof(Node));
}

// define priorityqueue push func
bool PriQueuePush(PriorityQueue *priqueue, int priority, char *data) {
	if (priqueue->len == priqueue->size) return false; 
	int position;
	bool found_flag = false;
	Node *tmp_node = (Node *)malloc(sizeof(Node));
	tmp_node->priority = priority;
	tmp_node->data = data;
	for (int index=priqueue->len; index > 0; index--) {
		if ((priqueue->nodes+(index-1))->priority <= 0) {
#ifdef DEBUG
			printf("Founded free position %d.\n", index - 1);
#endif
			position = index-1;
			found_flag = true;
			break;
		}
	}
	if (found_flag) {
		memcpy((priqueue->nodes+position), tmp_node, sizeof(Node));
	} else {
		memcpy(priqueue->nodes+priqueue->len, tmp_node, sizeof(Node));
		priqueue->len++;
	}
	return true;
}

// define priorityqueue pop func
bool PriQueuePop(PriorityQueue *priqueue) {
	Node *tmp_node;
	tmp_node = &priqueue->nodes[0];	
	for (int i=1; i<priqueue->len; i++) {
		if (tmp_node->priority < priqueue->nodes[i].priority) {
			tmp_node = &priqueue->nodes[i];
		}	
	}
#ifdef DEBUG
	printf("The pop node priority is %d, data is %s.\n", tmp_node->priority, tmp_node->data);
#endif
	if (tmp_node != NULL) {
		tmp_node->priority = -1;
		tmp_node->data = NULL;
		return true;
	} else {
		return false;
	}
}

// define priorityqueue show func
void PriQueueShow(PriorityQueue *priqueue) {
	printf("Begine to show priority queue info: \n");
	for (int i=0; i<priqueue->len; i++) {
		printf("priority: %d, value is %s.\n", (&(priqueue->nodes[i]))->priority, (&(priqueue->nodes[i]))->data);
	} 
}
