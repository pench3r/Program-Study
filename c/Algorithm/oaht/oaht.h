#ifndef __ALGORITHM_OAHT__H
#define __ALGORITHM_OAHT__H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct oaht_ {
	int slots;
	void **hash_table;
	void *vacated;
} Oaht;

/* struct oaht init func
   parameters:
		Oaht *oaht,
		int slots,
   return: void.
*/
void OahtInit(Oaht *oaht, int slots);

/* struct oaht insert func
   parameters:
		Oaht *oaht,
		void *data,
   return: bool.
*/
bool OahtInsert(Oaht *oaht, void *data);

#endif /* __ALGORITHM_OAHT__H */
