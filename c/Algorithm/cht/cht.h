/* the struct chained hash table header */
#ifndef __ALGORITHM_CHT__H
#define __ALGORITHM_CHT__H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../list/list.h"

typedef struct cht_ {
	int buckets;
	List *list_table;	
} Cht;

/* struct cht init func
   parameters:
		Cht *cht,
		int buckets,
   return: void.
*/
void ChtInit(Cht *cht, int buckets);

/* struct cht insert func
   parameters:
		Cht *cht,
		int data,
   return: bool.
*/
bool ChtInsert(Cht *cht, int data);

void ChtShow(Cht *cht);

#endif /* __ALGORITHM_CHT__H */
