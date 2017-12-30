#include "heap.h"

// define heap init func
void HeapInit(Heap *heap, int level) {
	heap->len = 0;
	heap->level = level;
	heap->size = (int)pow(2, level) - 1;
	heap->buf = (int *)calloc(heap->size, sizeof(int));
} 

// define heap insert func
bool HeapInsert(Heap *heap, int index, int data) {
	if (index >= heap->size) return false;
	if (heap->buf[index] == 0) {
		heap->buf[index] = data;
		return true;
	}
	// insert left
	if (heap->buf[index] > data) {
		HeapInsert(heap, index * 2 + 1, data); 	
	} else if (heap->buf[index] < data) {
	// insert right
		HeapInsert(heap, index * 2 + 2, data);
	}
}

// define heap show func
void HeapShow(Heap *heap) {
	printf("%d\n", heap->buf[0]);
	for (int level=2; level <= heap->level; ++level) {
		for (int i = 0; i < pow(2, level-1); ++i) {
			printf("%d  ", heap->buf[(int)pow(2, level-1)-1+i]);
		}
		printf("\n");
	}	
}
