#include "sort.h"

int main(int argc, char *argv[]) {
	int data[6] = {3, 4, 6, 1, 2, 5};
	int *tail_recursive_result = (int *)malloc(sizeof(int) * 6);
	ArrayShow(data, 6);
//	RecursiveInsertSort(data, 6);
//	ArrayShow(data, 6);
//	TailRecursiveInsertSort(data, tail_recursive_result, 0, 6);
//	ArrayShow(tail_recursive_result, 6);
	QuickSort(data, 0, 5);
	ArrayShow(data, 6);
	return 0;
}
