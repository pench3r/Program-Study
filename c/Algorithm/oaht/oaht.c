#include "oaht.h"

#define SLOTS 11 

static char vacated;

// define oaht init func
void OahtInit(Oaht *oaht, int (*hash)(int, int)) {
	oaht->slots = SLOTS;
	oaht->hash_table = (int *)malloc(sizeof(int) * oaht->slots);
	oaht->vacated = &vacated;
	oaht->hash = hash;
	for (int i=0; i<oaht->slots; ++i) {
		oaht->hash_table[i] = 0;
	}
}

// define oaht insert func
bool OahtInsert(Oaht *oaht, int data) {
	int index;
	for (int i=0; i<oaht->slots; ++i) {
		index = oaht->hash(data, i);
		if (oaht->hash_table[index] == 0) {
			oaht->hash_table[index] = data;
			return true;
		}
	}
	printf("Can not insert, because of the oaht table is full.\n");
	return false;
}

// define oaht remove func
bool OahtRemove(Oaht *oaht, int data) {
	int index;
	for (int i=0; i<oaht->slots; ++i) {
		index = oaht->hash(data, i); 
		if (oaht->hash_table[index] == data) {
			printf("success remove data %d.\n", data);
			oaht->hash_table[index] = 0;
			return true;
		}
	}	
	printf("oaht table doesn't contain %d.\n", data);
	return false;
}

// define hash func
int hash(int key, int index) {
	int h1, h2;
	h1 = key % SLOTS;
	h2 = index * (1 + key % (SLOTS - 2));
	return (h1 + h2) % SLOTS;
}

// define oaht show func
void OahtShow(Oaht *oaht) {
	printf("The open addressed hash table info: \n");
	for (int i=0; i<oaht->slots; ++i) {
		printf("The slot %d data is %d.\n", i, oaht->hash_table[i]);
	}
}

// define oaht destory func
void OahtDestory(Oaht *oaht) {
	free(oaht->hash_table);
	memset(oaht, 0, sizeof(Oaht));
	printf("The hash table has be destoryed.\n");
}
