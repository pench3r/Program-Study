#include "heap.h"

// define heap init func
void HeapInit(Heap *heap, int level) {
	heap->len = 0;
	heap->level = level;
	heap->size = (int)pow(2, level) - 1;
	heap->buf = (int *)calloc(heap->size, sizeof(int));
} 

// define heap insert1 func
bool HeapInsert1(Heap *heap, int index, int data) {
	if (index >= heap->size) return false;
	if (heap->buf[index] == 0) {
		heap->buf[index] = data;
		return true;
	}
	// insert left
	if (heap->buf[index] > data) {
		HeapInsert1(heap, index * 2 + 1, data); 	
	} else if (heap->buf[index] < data) {
	// insert right
		HeapInsert1(heap, index * 2 + 2, data);
	}
}

// define heap insert func
bool HeapInsert(Heap *heap, int data) {
	if (heap->len == heap->size) {
#ifdef DEBUG
		printf("The heap is full.\n");
#endif
		return false;
	}
	if (heap->buf[heap->len] == 0) {
		heap->buf[heap->len] = data;
		heap->len++;
	}
	if (heap->len <= 1) return true;
	HeapPrecolateUp(heap, heap->len-1);
	return true;
}

// define heap precolate up func
void HeapPrecolateUp(Heap *heap, int position) {
	if (position <= 0) return;
	if (heap->buf[position]	> heap->buf[NodeParent(position)]) {
		ArrayDataSwap(&heap->buf[position], &heap->buf[NodeParent(position)]);
		HeapPrecolateUp(heap, NodeParent(position));
	}
}

// define heap remove func
int HeapRemove(Heap *heap) {
	int node_data = heap->buf[0];
	heap->buf[0] = 0;
	ArrayDataSwap(&heap->buf[0], &heap->buf[heap->len-1]);
	heap->len--;
	HeapPrecolateDown(heap, 0);
	return node_data;
}

// define heap precolate down func
void HeapPrecolateDown(Heap *heap, int position) {
	int *max_node = heap->buf[NodeLeftChild(position)] > heap->buf[NodeRightChild(position)] ? &heap->buf[NodeLeftChild(position)] : &heap->buf[NodeRightChild(position)];
	if (heap->buf[position] < *max_node) {
		ArrayDataSwap(&heap->buf[position], max_node);
		HeapPrecolateDown(heap, max_node-heap->buf);
	}
	
}

// define heap show func
void HeapShow(Heap *heap) {
	printf("%.*s", (int)pow(2, heap->level-1), "                                               ");
	printf("%d\n", heap->buf[0]);
	for (int level=2; level <= heap->level; ++level) {
		printf("%.*s", (int)pow(2, heap->level-level+1), "                                                 ");
		for (int i = 0; i < pow(2, level-1); ++i) {
			printf("%d  ", heap->buf[(int)pow(2, level-1)-1+i]);
		}
		printf("\n");
	}	
}
