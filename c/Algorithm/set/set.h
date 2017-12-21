/* struct set header file */
#ifndef __ALGORITHM_SET__H
#define __ALGORITHM_SET__H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../list/list.h"

typedef List Set;

/* struct set init func
   parameters:
		Set *set,
   return: void.
*/
void SetInit(Set *set);

/* struct set insert func
   parameters:
		Set *set,
		int data,
   return: bool.
*/
bool SetInsert(Set *set, int data);

/* struct set remove func
   parameters:
		Set *set,
   return: bool.
*/
bool SetRemove(Set *set, int data);

/* struct set show func
   parameters:
		Set *set,
   return: void.
*/
void SetShow(Set *set);

void SetDestory(Set *set);

#endif /* __ALGORITHM_SET__H */
