#include "cht.h"

// define cht init func
void ChtInit(Cht *cht, int buckets) {
	cht->buckets = buckets;	
	cht->list_table = (List *)malloc(sizeof(List) * buckets);
	for (int i=0; i<cht->buckets; ++i) {
		ListInit(&cht->list_table[i]);
	}
}

// define cht insert func
bool ChtInsert(Cht *cht, int data) {
	int index, position;
	index = data % cht->buckets;
	if ( (position = ListSearch(&cht->list_table[index], data)) >= 0) return false;
	ListInsertNext(&cht->list_table[index], NULL, data);
	return true;
}

// define cht remove func
bool ChtRemove(Cht *cht, int data) {
	int index, position;
	index = data % cht->buckets;
	if ((position = ListSearch(&cht->list_table[index], data)) < 0) return false; 
	ListRemove(&cht->list_table[index], data);
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

// define cht destory func
void ChtDestory(Cht *cht) {
	for (int i=0; i<cht->buckets; ++i) {
		ListDestory(&cht->list_table[i]);
	}
	free(cht->list_table);	
	memset(cht, 0, sizeof(Cht));
	printf("The chained hash table have destoryed.\n");
} 
