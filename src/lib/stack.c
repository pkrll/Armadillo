#include <stdlib.h>
#include <common/stack.h>

struct StackElement {
  void *element;
  Stack_element_t *next;
};

struct Stack {
  Stack_element_t *top;
  int size;
};

stack_t *stack_init() {
  stack_t *stack = calloc(1, sizeof(stack));

	if (stack != NULL) {
		stack->size = 0;
	}

  return stack;
}

void stack_destroy(stack_t *stack) {
  if (stack != NULL) free(stack);
}

void stack_push(stack_t *stack, void *element) {
  Stack_element_t *new_element = calloc(1, sizeof(new_element));
  new_element->element = element;
  new_element->next = stack->top;
  stack->size = stack->size + 1;
  stack->top = new_element;
}

void *stack_pop(stack_t *stack) {
  if (stack->size > 0) {
    Stack_element_t *frame = stack->top;
    void *element = frame->element;

    stack->top = frame->next;

		free(frame);

    stack->size--;

    return element;
  }

  return 0;
}

int stack_size(stack_t *stack) {
	if (stack) {
		return stack->size;
	}

	return 0;
}
