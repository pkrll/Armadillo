#include<stdlib.h>  // Ska raderas!
#include<stdio.h> 	// Ska raderas!

struct Stack_element {
	void *element;
	void *element_next;
	void *element_last;
} typedef Stack_element_t;

struct Stack {
	Stack_element_t element;
	Stack_element_t top;
	int size;
} typedef Stack_t;

Stack_t* initialize_stack() {
	Stack_t *stack_pointer  = calloc(1, sizeof(stack_pointer));
	//stack_pointer -> top = NULL;
	stack_pointer -> size = 0;
	return stack_pointer;
}

Stack_t* push_to_stack(Stack_t *stack_pointer, void *element) {
	Stack_element_t *new_element = calloc(1, sizeof(element));
	stack_pointer ->  element  = *new_element;
	stack_pointer ->  top  = *new_element;
	stack_pointer -> size = ((stack_pointer -> size)+1);

	new_element -> element = new_element;
	new_element -> element_next = NULL;
	new_element -> element_last = NULL;
	return stack_pointer;
}

Stack_element_t pop_from_stack(Stack_t *stack_pointer) {
	Stack_element_t popped_object = stack_pointer -> top;
	// Continue implementing here.
	return popped_object;
}

int main(int argc, char const *argv[]) {
	Stack_t *stack = initialize_stack();
	if (stack != NULL) {
		printf("Sucess\n");
	} else {
	printf("failure\n");
	}
	int f = 1; // Vi skapar en pekare *f som pekar på "F".
	push_to_stack(stack, &f); // Vi pushar pekaren till stacken.
	int *hej = ((int*)(pop_from_stack(stack))); // Vill poppa f-pekaren från stacken och spara den i char.
	if (*hej==1) {
		printf("Double Sucess\n");
	} else {
		printf("Failure\n");
	}
	return 0;
}
