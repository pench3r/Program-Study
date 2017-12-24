#include "sort.h"

// define insert sort version 1 func
void InsertSort_1(int array[], int size) {
	int *tmp = (int *)malloc(sizeof(int) * size);
	for (int i=0; i<size; ++i) {
		tmp[i] = 0;
	}
	for (int i=0; i<size; ++i) {
		tmp[i] = array[i];
		for (int j=i; j>=1; --j) {
			if (tmp[j] < tmp[j-1]) {
				ArrayDataSwap(&tmp[j], &tmp[j-1]);
			}
		}
	}
	memcpy(array, tmp, size * sizeof(int));
	free(tmp);
}

// define insert sort version 2 func
void RecursiveInsertSort(int array[], int size) {
	size = size - 1;
	if (size > 0) {
		RecursiveInsertSort(array, size);	
		int insert_num = array[size];
		int index = size-1;
		while (index >=0 && (insert_num < array[index])) {
			array[index+1] = array[index];	
			index--;	
		}
		array[index+1] = insert_num;
	} else {
		return;
	}
}

// define array show func
void ArrayShow(int array[], int size) {
	printf("The array data is:\n");
	for (int i=0; i<size; ++i) {
		printf("\tdata is %d.\n", array[i]);	
	}
}

// define array data swap func
void ArrayDataSwap(int *x, int *y) {
	*x = *y ^ *x;
	*y = *y ^ *x;
	*x = *y ^ *x;	
}
