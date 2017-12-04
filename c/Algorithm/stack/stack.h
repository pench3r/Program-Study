#ifndef __ALGORITHM_STACK__H
#define __ALGORITHM_STACK__H
#include <stdbool.h>

// define stack struct
typedef struct stack_ {
	int size;
	int current_size;
	int *stack_top;
	int *stack_base;
	int *stack_data;
}Stack;

// struct stack init func
/* parameters: 
		Stack *stack,
		int size,
   return void.
*/
void StackInit(Stack *stack, int size);

/* struct stack push func
   parameters:
		Stack *stack,
		int node_num,
   return bool.
*/
bool StackPush(Stack *stack, int node_num);

/* struct stack pop func
   parameters:
		Stack *stack,
   return int.
*/
int StackPop(Stack *stack);

/* struct stack destory func
   parameters:
		Stack *stack,
   return bool.
*/
bool StackDestory(Stack *stack);

void PrintStack(Stack *stack);

#define StackOverBuffer(stack) (((stack)->current_size >= (stack)->size)? true:false)

#define StackIsEmpty(stack) (((stack)->current_size == 0)? true:false)
#endif /* __ALGORITHM_STACK__H */
