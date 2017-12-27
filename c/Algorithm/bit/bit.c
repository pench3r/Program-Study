#include "bit.h"

// define Is Odd func
bool IsOdd(int data) {
	if ((data & 1) == 1) return true;
	return false;
}

// define Show prime number
void ShowPrimeNum(int range) {
	if (range > 128) return;
	printf("Begin to show prime number that in range %d: \n", range);
	int index = 0;
	int mask[4] = {0};
	int *prime = (int *)malloc(sizeof(int) * (range/3 + 1));
	for (int i=2; i<range; ++i) {
		if ((mask[i/32] & 1 << (i % 32)) == 0) {
			prime[index++] = i;	
			for (int j=i; j<range; j += i) {
				mask[j/32] |= 1 << (j % 32);
			}
		}	
	}
	for (int i=0; i<index; ++i) {
		printf("%d ", prime[i]);
	}
	printf("\n");
}
