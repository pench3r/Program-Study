#include "clist.h"

// define clist init func
void ClistInit(Clist *clist) {
	clist->size = 0;
	clist->clist_head = clist->clist_tail = NULL;
}

// define clist insert func
bool ClistInsertNextNode(Clist *clist, ClistNode *clist_node, int data) {
	ClistNode *new_clist_node;
	new_clist_node = (ClistNode *)malloc(sizeof(ClistNode));
	new_clist_node->data = data;
	if (clist->size == 0) {
		clist->clist_head = clist->clist_tail = new_clist_node;
		new_clist_node->next_clist_node = new_clist_node;
		clist->size++;
		return true;
	}
	if (clist_node == NULL) {
		new_clist_node->next_clist_node = clist->clist_head;
		clist->clist_tail->next_clist_node = new_clist_node;
		clist->clist_tail = new_clist_node;
		clist->size++;
		return true;
	}
	new_clist_node->next_clist_node = clist_node->next_clist_node;	
	clist_node->next_clist_node = new_clist_node;
	clist->size++;
	return true;
}

// define clist node remove func
bool ClistRemoveNextNode(Clist *clist, ClistNode *clist_node, int *data) {
	if (clist->size == 0) {
		printf("clist is empty, can not do Remove operation!!!\n");
		return false;
	}
	ClistNode *old_clist_node;
	old_clist_node = clist_node->next_clist_node;
	if (old_clist_node == clist->clist_head) {
		printf("can not remove head node of clist!!!\n");
		return false;
	}
	*data = old_clist_node->data;
	clist_node->next_clist_node = clist_node->next_clist_node->next_clist_node;
	clist->size--;
	free(old_clist_node);
	return true;
}

// define clist destory func
void ClistDestory(Clist *clist) {
	if (clist->size == 0) {
		printf("clist is empty, can not do destory operation!!!\n");
		exit(1);
	}
	ClistNode *tmp_node;
	tmp_node = ClistHeadNode(clist);
	for (int i=0; i < clist->size; ++i) {
		free(tmp_node);
		tmp_node = ClistNextNode(tmp_node);	
	}	
	printf("The clist destory complete.\n");
}


// define clist show func
void ClistShow(Clist *clist) {
	ClistNode *tmp_node;
	printf("Show clist information: \n");
	printf("\tThe size of clist is %d.\n", clist->size);
	printf("\tThe head value is %d.\n", clist->clist_head->data);
	printf("\tThe data of clist is: begin to head node\n");
	tmp_node = ClistHeadNode(clist);
	for (int i = 0; i < clist->size; ++i) {
		printf("\t\tdata is %d.\n", tmp_node->data);
		tmp_node = ClistNextNode(tmp_node);	
	}
}
