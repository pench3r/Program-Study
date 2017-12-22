#include "set.h"

// define set init func
void SetInit(Set *set) {
	ListInit(set);
}

// define set insert func
bool SetInsert(Set *set, int data) {
	if (ListSearch(set, data)>=0) return false;
	ListInsertNext(set, NULL, data);
	return true;
}

// define set remove func
bool SetRemove(Set *set, int data) {
	if (ListSearch(set, data) == -1) return false;
	ListRemove(set, data); 
	return true;
}

// define set diff func
bool SetDiff(Set *setd, Set *set_a, Set *set_b) {
	ListNode *tmp_node;
	tmp_node = ListHeadNode(set_a);
	for (int i=0; i<set_a->size; ++i) {
		if (ListSearch(set_b, tmp_node->data) == -1) {
			ListInsertNext(setd, NULL, tmp_node->data);	
		}	
		tmp_node = NextNode(tmp_node);
	}
	return true;
}

// define set intersec func
bool SetIntersec(Set *set_i, Set *set_a, Set *set_b) {
	ListNode *tmp_node;
	tmp_node = ListHeadNode(set_a);	
	for (int i=0; i<set_a->size; ++i) {
		if (ListSearch(set_b, tmp_node->data) >= 0) {
			ListInsertNext(set_i, NULL, tmp_node->data);
		}
		tmp_node = NextNode(tmp_node);
	}
	return true;
}

// define set union func
bool SetUnion(Set *set_u, Set *set_a, Set *set_b) {
	ListNode *tmp_node;
	SetDiff(set_u, set_a, set_b);
	tmp_node = ListHeadNode(set_b);
	for (int i=0; i<set_b->size; ++i) {
		ListInsertNext(set_u, NULL, tmp_node->data);
		tmp_node = NextNode(tmp_node);
	}	
	return true;
}

// define set is member func
bool SetIsMember(Set *set, int data) {
	return ListSearch(set, data);
}

// define set is subset func
bool SetIsSubset(Set *set_a, Set *set_b) {
	ListNode *tmp_node;
	tmp_node = set_a->size >= set_b->size ? ListHeadNode(set_b) : ListHeadNode(set_a);
	for (int i=0; i<set_b->size; ++i) {
		if (ListSearch(set_a, tmp_node->data) == -1) return false;
		tmp_node = NextNode(tmp_node);
	}
	return true;
}

// define set is equal func
bool SetIsEqual(Set *set_a, Set *set_b) {
	if (set_a->size != set_b->size) return false;
	ListNode *tmp_node;
	tmp_node = ListHeadNode(set_a);
	for (int i=0; i<set_b->size; ++i) {
		if (ListSearch(set_a, tmp_node->data) == -1) return false;	
		tmp_node = NextNode(tmp_node);
	}
	return true;
}

// define set show func
void SetShow(Set *set) {
	printf("Show the set information: \n");
	ListShow(set);
}

// define set destory func
void SetDestory(Set *set) {
	ListDestory(set);
	printf("The set has been destoryed!!!\n");
}
