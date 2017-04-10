#include "clist.h"

// define clist init func
void ClistInit(Clist *clist) {
	clist->size = 0;
	clist->clist_head = clist->clist_tail = NULL;
}

// define clist insert func
bool ClistInsert(Clist *clist, int data) {
	ClistNode *new_clist_node;
	new_clist_node = (ClistNode *)malloc(sizeof(ClistNode));
	new_clist_node->data = data;
	if (clist->size == 0) {
		clist->clist_head = clist->clist_tail = new_clist_node;
	}
	new_clist_node->next_clist_node = clist->clist_head;
	return true;
}


// define clist show func
void ClistShow(Clist *clist) {
	printf("Show clist information: \n");
	printf("\tThe size of clist is %d.\n", clist->size);
	printf("The head value is %d.\n", clist->clist_head->data);
}
