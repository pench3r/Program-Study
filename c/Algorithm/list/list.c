#include "list.h"

// define list init func
void ListInit(List *list) {
	list->size = 0;
	list->list_head = list->list_tail = NULL;	
}

// define list Insert func
bool ListInsertNext(List *list, ListNode *list_node, int data) {
	ListNode *new_list_node;
	new_list_node = (ListNode *)malloc(sizeof(ListNode));
	new_list_node->data = data;
	new_list_node->node_next = NULL;
	if (list_node == NULL && list->size == 0) {
		list->list_head = list->list_tail = new_list_node;
		list->size++;
		return true;
	}
	if (list_node == NULL) {
		list->list_tail->node_next = new_list_node;
		list->list_tail = new_list_node;	
	} else {
		new_list_node->node_next = list_node->node_next;
		list_node->node_next = new_list_node;
		if (new_list_node->node_next == NULL) {
			list->list_tail = new_list_node;
		}
	}
	list->size++;
	return true;
}

// define list remove func
bool ListRemove(List *list, int data) {
	if (list->size == 0) {
		printf("The list is empty, can not do remove operation.\n");
		exit(1);
	}
	ListNode *tmp_list_node, *prev_list_node;
	tmp_list_node = prev_list_node = ListHeadNode(list);
	int size = list->size;
	for (int i=0; i<size; ++i) {
		if (tmp_list_node->data == data) {
			if (list->list_head == tmp_list_node) {
				list->list_head = tmp_list_node->node_next;	
				if (list->list_tail == tmp_list_node) {
					list->list_tail = NULL;	
				}
			} else {
				prev_list_node->node_next = tmp_list_node->node_next;
				if (list->list_tail == tmp_list_node) {
					list->list_tail = prev_list_node;	
				}
			}
			free(tmp_list_node);
			list->size--;
			return true;
		} else {
			prev_list_node = tmp_list_node;
			tmp_list_node = NextNode(tmp_list_node);
		}
	}
	return false;
}

// define list search func
int ListSearch(List *list, int data) {
	ListNode *tmp_node;
	tmp_node = ListHeadNode(list);
	for (int i = 0; i < list->size; ++i) {
		if ( tmp_node->data == data) {
			printf("data have fouded!!!\n");
			return i;
		}
		tmp_node = NextNode(tmp_node);
	}
	return -1;
}

// define list show func
void ListShow(List *list) {
	ListNode *tmp_node;
	printf("Show the list information: \n");
	printf("the list head data is %d.\n", list->list_head? list->list_head->data: 0);
	printf("the list tail data is %d.\n", list->list_tail ? list->list_tail->data: 0);
	tmp_node = list->list_head;
	for (int i = 0; i<list->size; ++i) {
		printf("\tThe list data is %d.\n", tmp_node->data);
		tmp_node = NextNode(tmp_node); 
	}
}

// define list destory func
void ListDestory(List *list) {
	if (list->size == 0) {
		printf("The list is empty, don't need to destory.\n");
		exit(1);
	}
	ListNode *tmp_node;
	ListNode *old_node;
	tmp_node = ListHeadNode(list);	
	for (int i=0; i<list->size; ++i) {
		old_node = tmp_node;
		tmp_node = NextNode(tmp_node);
		free(old_node);
	}
	memset(list, 0, sizeof(List));
	printf("The list has destory complete.\n");
}
