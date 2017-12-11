#include "dlist.h"

int main(int argc, char *argv[]) {
	Dlist dlist_t;
	DlistNode *tmp_node;
	DlistInit(&dlist_t);
	DlistInsertNextNode(&dlist_t, NULL, 10);
	tmp_node = DlistHeadNode(&dlist_t);	
	printf("Begin to insert a node and data is %d.\n", 20);
	DlistInsertNextNode(&dlist_t, tmp_node, 20);
	printf("Begin to insert a node and data is %d.\n", 30);
	DlistInsertNextNode(&dlist_t, tmp_node, 30);
	DlistShow(&dlist_t);
	return 0;
}
