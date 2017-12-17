#include "cht.h"

// define cht init func
void ChtInit(Cht *cht, int buckets) {
	cht->buckets = buckets;	
	cht->list_table = (List *)malloc(sizeof(List) * buckets);
}

// define cht insert func
bool ChtInsert(Cht *cht, int data) {
	int index, position;
	index = data % cht->buckets;
	if ( (position = ListSearch(&cht->list_table[index], data)) >= 0) return false;
	ListInsertNext(&cht->list_table[index], NULL, data);
	return true;
}

// define cht show func
void ChtShow(Cht *cht) {
	printf("Show the chained hash table info: \n");
	for (int i=0; i<cht->buckets; ++i) {
		printf("The %d number buckets info: \n", i);
		ListShow(&cht->list_table[i]);
		printf("\n");
	}	
}
