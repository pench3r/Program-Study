#include <stdlib.h>
#include <cstdio>
#include <time.h>

#define MIN 0
#define MAX 6

int main() {
	srand((unsigned)time(NULL));
	for (int i=0; i<20; i++) {
		printf("The random value is %d.\n", MIN + rand() % (MAX-MIN+1));
	}
	return 0;
}
