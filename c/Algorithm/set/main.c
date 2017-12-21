#include "set.h"

int main(int argc, char *argv[]) {
	Set set_t;
	SetInit(&set_t);
	SetInsert(&set_t, 10);
	SetInsert(&set_t, 20);
	SetInsert(&set_t, 30);
	SetInsert(&set_t, 40);
	SetInsert(&set_t, 50);
	SetShow(&set_t);
	SetRemove(&set_t, 30);
	SetShow(&set_t);
	SetDestory(&set_t);
	return 0;
}
