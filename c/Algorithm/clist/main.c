#include "clist.h"

int main(int argc, char *argv[]) {
	Clist clist_t;
	ClistNode *tmp_node;
	int *recv_num;
	ClistInit(&clist_t);
	ClistInsertNextNode(&clist_t, NULL, 10);
	ClistInsertNextNode(&clist_t, NULL, 20);
	ClistInsertNextNode(&clist_t, NULL, 30);
	ClistShow(&clist_t);
	tmp_node = ClistHeadNode(&clist_t);	
	printf("Get the head node and data is %d.\n", tmp_node->data);
	printf("Try to insert node after head node.\n");
	ClistInsertNextNode(&clist_t, tmp_node, 100);	
	ClistShow(&clist_t);
	tmp_node = ClistNextNode(tmp_node);
	printf("The insert node data is %d.\n", tmp_node->data);
	ClistRemoveNextNode(&clist_t, tmp_node, recv_num);
	printf("The remove node data is %d.\n", *recv_num);
	ClistShow(&clist_t);
	ClistDestory(&clist_t);
	return 0;
}
