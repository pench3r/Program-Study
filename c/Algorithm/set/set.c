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
