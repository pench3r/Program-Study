#include "bitree.h"

// define struct bitree init
void BitreeInit(Bitree *bitree) {
	bitree->size = 0;
	bitree->bitree_root = NULL;
}

// define struct bitree insert left node func
bool BitreeInsertLeftNode(Bitree *bitree, BitreeNode *bitree_node, int data) {
	BitreeNode *tmp_node;
	tmp_node = (BitreeNode *)malloc(sizeof(BitreeNode));	
	tmp_node->data = data;
	tmp_node->node_left = tmp_node->node_right = NULL;
	if (bitree->size == 0 && bitree_node == NULL) {
		bitree->bitree_root = tmp_node;
		bitree->size++;
		return true;
	}

	if (bitree_node == NULL || bitree_node->node_left != NULL) {
		free(tmp_node);
		printf("The node have left node or the node is NULL, can not do left insert operation!!!\n");
		return false;
	}
	bitree_node->node_left = tmp_node;	
	bitree->size++;
	return true;
}

// define bitree insert right node func
bool BitreeInsertRightNode(Bitree *bitree, BitreeNode *bitree_node, int data) {
	BitreeNode *tmp_node;
	tmp_node = (BitreeNode *)malloc(sizeof(BitreeNode));	
	tmp_node->data = data;
	tmp_node->node_left = tmp_node->node_right = NULL;
	if (bitree->size == 0 && bitree_node == NULL) {
		bitree->bitree_root = tmp_node;
		bitree->size++;
		return true;
	}

	if (bitree_node == NULL || bitree_node->node_right != NULL) {
		free(tmp_node);
		printf("The node have left node or the node is NULL, can not do left insert operation!!!\n");
		return false;
	}
	bitree_node->node_right = tmp_node;	
	bitree->size++;
	return true;
}

// define bitree remove left node func
bool BitreeRemoveLeftNode(Bitree *bitree, BitreeNode *bitree_node) {
	if (bitree->size == 0) {
		printf("The bitree is empty, can not do bitree remove operation!!!\n");
		return false;
	}
	BitreeNode *tmp_node;
	if (bitree_node->node_left == NULL ) {
		printf("The node don't have left node!!!\n");
		return false;
	}	
	if (bitree_node->node_left != NULL) {
		tmp_node = bitree_node->node_left;	
		BitreeRemoveLeftNode(bitree, tmp_node);
	} else if (bitree_node->node_right != NULL) {
		tmp_node = bitree_node->node_right;
		BitreeRemoveRightNode(bitree, tmp_node);
	}
	free(tmp_node);
	return true;
}


// define bitree show func
void BitreeShow(Bitree *bitree) {
	printf("Begin to show bitree information: \n");
	printf("The tree root data is %d.\n", bitree->bitree_root->data);
	printf("\tThe root left node data is %d.\n", bitree->bitree_root->node_left->data);
	printf("\tThe root right node data is %d.\n", bitree->bitree_root->node_right->data);
}
