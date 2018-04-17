#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// A struct that represents the stack.
struct Stack {
	void *stack_content;
	int top;
	int maximum_size;
	int elem_size;
} typedef Stack_t;

// A function that initialize the Stack.
Stack_t *initialize_stack(int elem_size, int maximum_size) {
	Stack_t *stack_pointer = calloc(1, sizeof (*stack_pointer));
	stack_pointer->top = -1;
	stack_pointer->maximum_size=maximum_size;
	stack_pointer->elem_size = elem_size;
	stack_pointer->stack_content=calloc(1, sizeof(elem_size));
	return stack_pointer;
}

// A function that destroys the stack and gives the memory back.
int destroy_stack(Stack_t *stack_pointer) {
	free(stack_pointer->stack_content);
  free(stack_pointer);
  return 0;
}
// A function	that checks if the Stack is empty.
bool check_if_empty(Stack_t *stack_pointer) {
	if (stack_pointer->top==-1) {
		return true;
	} else {
		return false;
	}
}

// A function that checks if the Stack is full.
bool check_if_full(Stack_t *stack_pointer) {
	if((stack_pointer->top) == ((stack_pointer->maximum_size)-1)) {
		return  true;
	} else {
		return false;
	}
}

// A function that pushes an element to the Stack.
int push_to_stack(Stack_t *stack_pointer, void *elem) {
	if(check_if_full) {
		printf("Stack is full\n");
		return 0;
	}
	stack_pointer->top++;
	void *size_holder = (char *)stack_pointer->stack_content+(stack_pointer->top*stack_pointer->elem_size);
	memcpy(size_holder, elem, stack_pointer->elem_size);
	return 0;
}

// A function that pops an element from the Stack.
int pop_from_stack(Stack_t *stack_pointer, void *target) {
	if(check_if_empty) {
		printf("Stack is empty\n");
	}
	void* source = (char*)stack_pointer->stack_content+(stack_pointer->top*stack_pointer->elem_size);
	memcpy(target, source, stack_pointer->elem_size);
	return 0;
}

int main(int argc, char const *argv[]) {
	Stack_t *test_stack=initialize_stack(sizeof(int), 5);
	push_to_stack(test_stack, (void*)1);
	push_to_stack(test_stack, (void*)2);
	printf("Stack created and pushed\n");
	return 0;
}
