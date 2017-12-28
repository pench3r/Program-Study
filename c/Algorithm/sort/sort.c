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

// define tail recursive insertion sort fun
int * TailRecursiveInsertSort(int array[], int tmp[], int tmp_size, int array_size) {
	if (array_size == 0) return tmp;
	tmp[tmp_size] = array[tmp_size];
	for (int i=tmp_size; i>=1; --i) {
		if (tmp[i] < tmp[i-1]) {
			ArrayDataSwap(&tmp[i], &tmp[i-1]);
		}
	}
	return TailRecursiveInsertSort(array, tmp, tmp_size+1, array_size-1);	
}

// define quick sort func
void QuickSort(int array[], int left, int right) {
	if (left >= right) return;
	int pivot = array[right];	
	int store_index = left;
	for (int i=left; i<right; ++i) {
		if (array[i] <= pivot) {
			ArrayDataSwap(&array[i], &array[store_index]);
			store_index++;
		}
	}
	ArrayDataSwap(&array[right], &array[store_index]);
	QuickSort(array, left, store_index-1);
	QuickSort(array, store_index+1, right);
}

// define merge sort func
void MergeSort(int array[], int left, int right) {
	if (right-left < 1) return;
	int middle = left + (right - left) / 2; 
	MergeSort(array, left, middle);
	MergeSort(array, middle+1, right);
	for (int i = middle+1; i <= right; ++i) {
		int tmp = array[i];
		int index = i-1; 
		while (index >= 0 && (tmp < array[index])) {
			array[index+1] = array[index];
			index--;
		}
		array[index+1] = tmp;
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
	if (x == y) return;
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;	
}
