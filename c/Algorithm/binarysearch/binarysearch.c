#include "binarysearch.h"

// define BinarySearch func
int BinarySearch(int array[], int left, int right, int data) {
	int middle = left + (right - left) / 2;
	if ( array[middle] > data) {
		return BinarySearch(array, left, middle, data);
	} else if (array[middle] < data) {
		return BinarySearch(array, middle, right, data);
	} else {
#ifdef DEBUG
		printf("The data is found, the index is %d.\n", middle);
#endif
		return middle;
	}
}
