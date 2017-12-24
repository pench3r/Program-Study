#include "sort.h"

int main(int argc, char *argv[]) {
	int data[6] = {3, 4, 6, 1, 2, 5};
	ArrayShow(data, 6);
	RecursiveInsertSort(data, 6);
	ArrayShow(data, 6);
	return 0;
}
