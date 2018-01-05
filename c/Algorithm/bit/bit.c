#include "bit.h"

// define Is Odd func
bool IsOdd(int data) {
	if ((data & 1) == 1) return true;
	return false;
}

// define Get bit func
int GetBit(unsigned char *buf, int position) {
	return (buf[position/8] >> position & 1);
}

// define Set bit func
bool SetBit(unsigned char *buf, int position, int state) {
	unsigned char mask = 1 << position;
	if (state) {
		buf[position/8] = buf[position/8] | mask; 
	} else {
		buf[position/8] = buf[position/8] & (~mask);
	}
}

// define bit xor func
void BitXor(unsigned char *buf1, unsigned char *buf2, unsigned char *buf3, int size) {
	for (int i=0; i<size; ++i) {
		if (GetBit(buf1, i) != GetBit(buf2, i)) {
			SetBit(buf3, i, 1);
		} else {
			SetBit(buf3, i, 0);
		}
	}	
	return;
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
