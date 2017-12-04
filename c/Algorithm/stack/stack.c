#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// implement stack init func
void StackInit(Stack *stack, int size) {
	stack->size = size;
	stack->current_size = 0;
	stack->stack_data = (int *)malloc(sizeof(int) * size);
	for (int index = 0; index < size; index++)
	{
		*(stack->stack_data + index) = 0;
	}
	stack->stack_top = stack->stack_base = stack->stack_data;
}

// implement stack push func
bool StackPush(Stack *stack, int node_num) {
	if (StackOverBuffer(stack)) {
		printf("The Stack is overbuffer.\n");
		return false;
	}
	stack->current_size++;
	stack->stack_top = stack->stack_base + (stack->current_size - 1);
	*(stack->stack_top) = node_num;	
	return true;
}

// implement stack pop func
int StackPop(Stack *stack) {
	if (StackIsEmpty(stack)) {
		printf("The stack is empty, can not pop!!!\n");
		return -1;
	}
	int pop_value = *(stack->stack_top);
	stack->current_size--;	
	if (stack->current_size == 0) {
		stack->stack_top = stack->stack_base;
		return pop_value;
	}
	stack->stack_top = stack->stack_base + stack->current_size - 1;
	return pop_value;		
}

// implement stack destory func
bool StackDestory(Stack *stack) {
	stack->stack_top = stack->stack_base = NULL;
	free(stack->stack_data);
	printf("struct stack destory complete.\n");
}

// implement stack show func
void PrintStack(Stack *stack) {
	printf("Begin to print stack...\n");
	printf("The stack size is %d.\n", stack->size);
	printf("The stack current size is %d.\n", stack->current_size);
	printf("The top is %d.\n", *(stack->stack_top));
	printf("The base is %d.\n", *(stack->stack_base));
	printf("The stack data is: \n");
	for (int index = stack->current_size-1; index >= 0; --index)
	{
		printf("\tThe value is \t%d.\n", *(stack->stack_data + index));
	}
}
