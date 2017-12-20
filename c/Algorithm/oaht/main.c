#include "oaht.h"

int main(int argc, char *argv[]) {
	Oaht oaht_t;
	OahtInit(&oaht_t, hash);
	OahtInsert(&oaht_t, 78);
	OahtInsert(&oaht_t, 14);
	OahtInsert(&oaht_t, 37);
	OahtInsert(&oaht_t, 83);
	OahtInsert(&oaht_t, 97);
	OahtInsert(&oaht_t, 59);
	OahtRemove(&oaht_t, 14);
	OahtShow(&oaht_t);
	OahtDestory(&oaht_t);
	return 0;
}
