#include "oaht.h"

static char vacated;

// define oaht init func
void OahtInit(Oaht *oaht, int slots) {
	oaht->slots = slots;
	oaht->hash_table = (void **)malloc(sizeof(void *) * slots);
	oaht->vacated = &vacated;
	for (int i=0; i<oaht->slots; ++i) {
		oaht->hash_table[i] = NULL;
	}
}

// define oaht insert func
bool OahtInsert(Oaht *oaht, void *data) {
	return true;
}
