#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// A struct that represents the stack.
struct Stack {
	void *elem;
	int top;
	int maximum_size;
	int elem_size;
} typedef Stack_t;

// A function that initialize the Stack.
Stack_t *initialize_stack(Stack_t *stack_pointer, int elem_size, int maximum_size) {
	Stack_t *new_elem = calloc(1, sizeof *new_elem);
	new_elem->elem=calloc(1, sizeof(elem_size));
	stack_pointer->elem=new_elem;
	stack_pointer->maximum_size=maximum_size;
	stack_pointer->top=-1;
	stack_pointer->elem_size=elem_size;
	return new_elem;
}

// A function that destroys the stack and gives the memory back.
int destroy_stack(Stack_t *stack_pointer) {
	free(stack_pointer->elem);
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
	if((stack_pointer->top) >= ((stack_pointer->maximum_size)-1)) {
		return  true;
	} else {
		return false;
	}
}

// A function that pushes an element from the Stack.
int push_to_stack(Stack_t *stack_pointer, void *elem) {
	if(check_if_full) {
		printf("Stack is full\n");
	}
	stack_pointer->top++;
	void *size_holder = (char *)stack_pointer->elem+(stack_pointer->top*stack_pointer->elem_size);
	memcpy(size_holder, elem, stack_pointer->elem_size);
	return 0;
}

// A function that pops an element from the Stack.
int pop_from_stack(Stack_t *stack_pointer, void *target) {
	if(check_if_empty) {
		printf("Stack is empty\n");
	}
	void* source = (char*)stack_pointer->elem+(stack_pointer->top*stack_pointer->elem_size);
	memcpy(target, source, stack_pointer->elem_size);
	return 0;
}

int main(int argc, char const *argv[]) {
	initialize_stack(Stack_t *stack_pointer,int elem_size, int maximum_size) {

	return 0;
}
