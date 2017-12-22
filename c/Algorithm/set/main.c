#include "set.h"


int main(int argc, char *argv[]) {
	Set set_t1;
	Set set_t2;
	Set set_d;
	Set set_i;
	Set set_u;
	SetInit(&set_u);
	SetInit(&set_d);
	SetInit(&set_t1);
	SetInit(&set_t2);
	SetInit(&set_i);
	SetInsert(&set_t1, 10);
	SetInsert(&set_t1, 20);
	SetInsert(&set_t1, 30);
	SetShow(&set_t1);
	SetInsert(&set_t2, 10);
	SetInsert(&set_t2, 40);
	SetInsert(&set_t2, 50);
	SetShow(&set_t2);
	SetDiff(&set_d, &set_t1, &set_t2);
	SetShow(&set_d);
	SetIntersec(&set_i, &set_t1, &set_t2);
	SetShow(&set_i);
	SetUnion(&set_u, &set_t1, &set_t2);
	SetShow(&set_u);
	SetDestory(&set_t1);
	SetDestory(&set_t2);
	SetDestory(&set_d);
	SetDestory(&set_i);
	return 0;
}
