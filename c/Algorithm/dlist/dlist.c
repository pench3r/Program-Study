#include "dlist.h"

// define dlist init func
void DlistInit(Dlist *dlist) {
	dlist->size = 0;
	dlist->dlist_head = dlist->dlist_tail = NULL;
}

//define dlist insert next func
bool DlistInsertNextNode(Dlist *dlist, DlistNode *dlist_node, int data) {
	DlistNode *tmp_node;
	tmp_node = (DlistNode *)malloc(sizeof(DlistNode));
	tmp_node->data = data;
	tmp_node->node_prev = tmp_node->node_next = NULL;
	if (dlist->size == 0 && dlist_node == NULL) {
		dlist->dlist_head = dlist->dlist_tail = tmp_node;
		dlist->size++;
		return true;
	}
	if (dlist_node->node_next != NULL) {
		tmp_node->node_next = dlist_node->node_next;
		dlist_node->node_next->node_prev = tmp_node;
		dlist_node->node_next = tmp_node;
		tmp_node->node_prev = dlist_node;		
	} else {
		tmp_node->node_prev = dlist_node;
		dlist_node->node_next = tmp_node;
		dlist->dlist_tail = tmp_node;
	}
	dlist->size++;
	return true;
}

// define dlist show func
void DlistShow(Dlist *dlist) {
	DlistNode *tmp_node;
	tmp_node = dlist->dlist_head;
	printf("Show the dlist information: \n");
	printf("The dlist head data is %d.\n", tmp_node->data);
	printf("The dlist tail data is %d.\n", dlist->dlist_tail->data);
	for (int i=0; i < dlist->size; ++i) {
		printf("\tThe dlist data is %d.\n", tmp_node->data);
		tmp_node = NextNode(tmp_node); 
	}
}
