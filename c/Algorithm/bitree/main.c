#include "bitree.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	Bitree bitree_t;
	BitreeNode *tmp_node;
	BitreeInit(&bitree_t);
	BitreeInsertLeftNode(&bitree_t, NULL, 15);
	printf("Init bitree root node data is %d.\n", 15);

	tmp_node = BitreeRootNode(&bitree_t);

	BitreeInsertLeftNode(&bitree_t, tmp_node, 10);
	printf("Insert Left Node data is %d.\n", 10);

	BitreeInsertRightNode(&bitree_t, tmp_node, 20);
	printf("Insert Right Node data is %d.\n", 20);
	tmp_node = LeftNode(tmp_node);

	BitreeInsertRightNode(&bitree_t, tmp_node, 12);
	printf("Insert Right Node data is %d.\n", 12);

	printf("Begin to remove node\n");
	tmp_node = BitreeRootNode(&bitree_t);
	BitreeRemoveRightNode(&bitree_t, tmp_node);
	BitreeShow(&bitree_t);
	BitreeDestory(&bitree_t);
	return 0;
}
