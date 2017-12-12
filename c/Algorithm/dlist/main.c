#include "dlist.h"

int main(int argc, char *argv[]) {
	Dlist dlist_t;
	DlistNode *tmp_node;
	int *recv_num;
	DlistInit(&dlist_t);
	DlistInsertNextNode(&dlist_t, NULL, 10);
	tmp_node = DlistHeadNode(&dlist_t);	
	printf("Begin to insert next node and data is %d.\n", 20);
	DlistInsertNextNode(&dlist_t, tmp_node, 20);
	printf("Begin to insert next node and data is %d.\n", 30);
	DlistInsertNextNode(&dlist_t, tmp_node, 30);
	
	printf("Begin to insert prev node and data is %d.\n", 100);
	DlistInsertPrevNode(&dlist_t, tmp_node, 100);
	DlistShow(&dlist_t);
	
	tmp_node = DlistHeadNode(&dlist_t);
	
	DlistRemoveNextNode(&dlist_t, tmp_node, recv_num);
	printf("remove next node and data is %d.\n", *recv_num);
	DlistShow(&dlist_t);
	DlistDestory(&dlist_t);
	return 0;
}
