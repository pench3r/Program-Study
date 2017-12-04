#include "stack.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	Stack stack_t;
	StackInit(&stack_t, 4);
	bool result = StackPush(&stack_t, 10);
	if (result) printf("Stack insert value 10.\n");
	result = StackPush(&stack_t, 20);
	if (result) printf("Stack insert value 20.\n");
	result = StackPush(&stack_t, 30);
	if (result) printf("Stack insert value 30.\n");
	result = StackPush(&stack_t, 40);
	if (result) printf("Stack insert value 40.\n");
	int value = StackPop(&stack_t);
	printf("Stack pop value is %d.\n", value);
	result = StackPush(&stack_t, 50);
	if (result) printf("Stack insert value 50.\n");

	PrintStack(&stack_t);

	value = StackPop(&stack_t);
	printf("Stack pop value is %d.\n", value);

	PrintStack(&stack_t);

	value = StackPop(&stack_t);
	printf("Stack pop value is %d.\n", value);
	value = StackPop(&stack_t);
	printf("Stack pop value is %d.\n", value);
	value = StackPop(&stack_t);
	printf("Stack pop value is %d.\n", value);
	result = StackPush(&stack_t, 150);
	if (result) printf("Stack insert value 150.\n");
	result = StackPush(&stack_t, 250);
	if (result) printf("Stack insert 250.\n");
	result = StackPush(&stack_t, 350);
	if (result) printf("Stack insert 350.\n");
	result = StackPush(&stack_t, 450);
	if (result) printf("Stack insert 450.\n");
	PrintStack(&stack_t);
	StackDestory(&stack_t);
	return 0;
}
