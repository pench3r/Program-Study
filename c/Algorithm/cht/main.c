#include "cht.h"

int main(int argc, char *argv[]) {
	Cht cht_t;
	ChtInit(&cht_t, 4);
	ChtInsert(&cht_t, 5);
	ChtInsert(&cht_t, 6);
	ChtInsert(&cht_t, 7);
	ChtInsert(&cht_t, 8);
	ChtInsert(&cht_t, 9);
	ChtShow(&cht_t);
	return 0;
}
