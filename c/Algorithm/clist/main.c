#include "clist.h"

int main(int argc, char *argv[]) {
	Clist clist_t;
	ClistInit(&clist_t);
	ClistInsert(&clist_t, 10);
	ClistShow(&clist_t);
	return 0;
}
