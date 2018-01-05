#include "bit.h"

int main(int argc, char *argv[]) {
	unsigned char buff[] = "\xff";
	unsigned char buff1[] = "\x88";
	unsigned char *buffx = (unsigned char *)calloc(8, sizeof(unsigned char));
	printf("buff hex is \\x%x.\n", *buff);
	int retval = GetBit(buff, 0);
	printf("bit state is %d.\n", retval);
	SetBit(buff, 0, 0);
	printf("buff hex is \\x%x.\n", *buff);
	SetBit(buff, 1, 0);
	printf("buff hex is \\x%x.\n", *buff);
	BitXor(buff, buff1, buffx, 8);
	printf("buff hex is \\x%x.\n", *buffx);
	ShowPrimeNum(100);
	return 0;
}
