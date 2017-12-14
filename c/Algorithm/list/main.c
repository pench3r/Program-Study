#include "list.h"

int main(int argc, char *argv[]) {
	List list_t;
	ListInit(&list_t);
	ListInsert(&list_t, NULL, 10);
	ListInsert(&list_t, NULL, 20);
	ListInsert(&list_t, NULL, 30);
	ListShow(&list_t);
	return 0;
}
