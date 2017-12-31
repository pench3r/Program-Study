#include "heap.h"

int main(int argc, char *argv[]) {
	Heap heap_t;
	HeapInit(&heap_t, 4);
	HeapInsert(&heap_t, 40);
	HeapInsert(&heap_t, 50);
	HeapInsert(&heap_t, 70);
	HeapInsert(&heap_t, 55);
	HeapInsert(&heap_t, 56);
	HeapInsert(&heap_t, 51);
	HeapInsert(&heap_t, 100);
	HeapInsert(&heap_t, 58);
	HeapShow(&heap_t);
	return 0;
}
