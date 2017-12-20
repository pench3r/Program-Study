/* open address hash table header file */
#ifndef __ALGORITHM_OAHT__H
#define __ALGORITHM_OAHT__H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct oaht_ {
	int slots;
	int *hash_table;
	int (*hash)(int key, int index);
	void *vacated;
} Oaht;

/* struct oaht init func
   parameters:
		Oaht *oaht,
		int (*hash)(int, int),
   return: void.
*/
void OahtInit(Oaht *oaht, int (*hash)(int, int));

/* struct oaht insert func
   parameters:
		Oaht *oaht,
		int data,
   return: bool.
*/
bool OahtInsert(Oaht *oaht, int data);

/* struct oaht remove func
   parameters:
		Oaht *oaht,
		int data,
   return: bool.
*/
bool OahtRemove(Oaht *oaht, int data);

void OahtDestory(Oaht *oaht);

void OahtShow(Oaht *oaht);

/* hash func, return key % mod */
int hash(int key, int index);

#endif /* __ALGORITHM_OAHT__H */
