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
		BitreeRemoveRightNode(bitree, tmp_node);
		bitree_node->node_left = NULL;
		bitree->size--;
		free(tmp_node);
	}
	return true;
}

// define bitree remove right node func
bool BitreeRemoveRightNode(Bitree *bitree, BitreeNode *bitree_node) {
	if (bitree->size == 0) {
		printf("The bitree is empty, can not do bitree remove operation!!!\n");
		return false;
	}
	BitreeNode *tmp_node;
	
	if (bitree_node->node_right == NULL) {
		printf("The node don't have right node!!!\n");
		return false;
	}	
	if (bitree_node->node_right != NULL) {
		tmp_node = bitree_node->node_right;
		BitreeRemoveLeftNode(bitree, tmp_node);
		BitreeRemoveRightNode(bitree, tmp_node);
		bitree_node->node_right = NULL;
		bitree->size--;
		free(tmp_node);
	}

	return true;
}

// define bitree show func
void BitreeShow(Bitree *bitree) {
	printf("Begin to show bitree information: \n");
	printf("The tree root data is %d.\n", bitree->bitree_root->data);
	BitreePreorderTraversal(bitree, bitree->bitree_root);
}

// define bitree preorder traversal
void BitreePreorderTraversal(Bitree *bitree, BitreeNode *bitree_node) {
	if (bitree->size == 0) {
		printf("Please init bitree!!!\n");
		exit(1);
	}	
	printf("The preorder Traversal data is %d.\n", bitree_node->data);
	if ( bitree_node->node_left != NULL) {
		BitreePreorderTraversal(bitree, bitree_node->node_left);
	}
	if (bitree_node->node_right != NULL) {
		BitreePreorderTraversal(bitree, bitree_node->node_right);
	}
}

// define bitree inorder traversal
void BitreeInorderTraversal(Bitree *bitree, BitreeNode *bitree_node) {
	if (bitree->size == 0) {
		printf("Please init bitree!!!\n");
		exit(1);
	}
	if (bitree_node->node_left != NULL) {
		BitreeInorderTraversal(bitree, bitree_node->node_left);
	} else {
		printf("The Inorder Traversal data is %d.\n", bitree_node->data);
	}
	if (bitree_node->node_right != NULL) {
		BitreeInorderTraversal(bitree, bitree_node->node_right);
	}
}

// define bitree destory func
void BitreeDestory(Bitree *bitree) {
	BitreeNode *tmp_node;
	tmp_node = BitreeRootNode(bitree);
	BitreeRemoveLeftNode(bitree, tmp_node);
	BitreeRemoveRightNode(bitree, tmp_node);		
	free(tmp_node);
	bitree->size--;
	printf("The bitree destory compelte.\n");		
}
