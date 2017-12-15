#include "list.h"

int main(int argc, char *argv[]) {
	List list_t;
	ListInit(&list_t);
	ListInsertNext(&list_t, NULL, 10);
	ListInsertNext(&list_t, NULL, 20);
	ListInsertNext(&list_t, NULL, 30);
	ListShow(&list_t);
	ListRemove(&list_t, 30); 	
	ListShow(&list_t);
	ListRemove(&list_t, 10); 	
	ListShow(&list_t);
	ListDestory(&list_t);
	return 0;
}
