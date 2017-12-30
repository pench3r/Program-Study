#include "heap.h"

int main(int argc, char *argv[]) {
	Heap heap_t;
	HeapInit(&heap_t, 4);
	HeapInsert(&heap_t, 0, 50);
	HeapInsert(&heap_t, 0, 40);
	HeapInsert(&heap_t, 0, 60);
	HeapShow(&heap_t);
	return 0;
}
