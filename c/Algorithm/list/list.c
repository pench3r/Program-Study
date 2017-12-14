#include "list.h"

// define list init func
void ListInit(List *list) {
	list->size = 0;
	list->list_head = list->list_tail = NULL;	
}

// define list Insert func
bool ListInsert(List *list, ListNode *list_node, int data) {
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

// define list show func
void ListShow(List *list) {
	ListNode *tmp_node;
	printf("Show the list information: \n");
	printf("the list head data is %d.\n", list->list_head->data);
	printf("the list tail data is %d.\n", list->list_tail->data);
	tmp_node = list->list_head;
	for (int i = 0; i<list->size; ++i) {
		printf("\tThe list data is %d.\n", tmp_node->data);
		tmp_node = NextNode(tmp_node); 
	}
}
