#include "binarysearch.h"

int main(int argc, char *argv[]) {
	int data[10] = {0,1,2,3,4,5,6,7,8,9};
	ArrayShow(data, 10);
	BinarySearch(data, 0, 9, 7);
	return 0;
}
