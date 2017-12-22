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

/* struct set diff func
   parameters:
		Set *setd,
		Set *set_a,
		Set *set_b,
   return: bool.
*/
bool SetDiff(Set *setd, Set *set_a, Set *set_b);

/* struct set intersec func
   parameters:
		Set *seti,
		Set *set_a,
		Set *set_b,
   return: bool.
*/
bool SetIntersec(Set *seti, Set *set_a, Set *set_b);

/* struct set is member func
   parameters:
		Set *set,
		int data,
   return: bool.
*/
bool SetIsMember(Set *set, int data);

/* struct set union func
   parameters:
		Set *set_u,
		Set *set_a,
		Set *set_b,
   return: bool.
*/
bool SetUnion(Set *set_u, Set *set_a, Set *set_b);

/* struct set is subset func
   parameters:
		Set *set_a,
		Set *set_b,
   return: bool.
*/
bool SetIsSubset(Set *set_a, Set *set_b);

/* struct set is equal func
   parameters:
		Set *set_a,
		Set *set_b,
   return: bool.
*/
bool SetIsEqual(Set *set_a, Set *set_b);

void SetDestory(Set *set);

#endif /* __ALGORITHM_SET__H */
