#include<stdlib.h>  // Ska raderas!
#include<stdio.h> 	// Ska raderas!
#include "stack.h"

struct Stack_element {
  void *element;
  struct Stack_element *next;
} typedef Stack_element_t;

struct Stack {
  Stack_element_t *top;
  int size;
} typedef Stack_t;

Stack_t *initialize_stack() {
  Stack_t *stack  = calloc(1, sizeof(stack));
  stack -> size = 0;
  return stack;
}

void destroy_stack(Stack_t *stack) {
  if (stack == NULL) {
    printf("There is no stack to destroy.");
    return;
  }
  free(stack);
}

void push_to_stack(Stack_t *stack, void *element) {
  Stack_element_t *new_element = calloc(1, sizeof(new_element));
  new_element -> element = element;
  new_element -> next = stack->top;
  stack -> size = ((stack -> size)+1);
  stack -> top = new_element;
  printf("Stackens storlek är nu %d\n", stack->size);

}

void *pop_from_stack(Stack_t *stack) {
  if (stack->size == 0) {
    printf("The stack is empty.");
    return 0;
  } 
  if (stack->size > 0) {
    Stack_element_t *frame = stack->top;
    void *element = frame->element;
    
    stack->top = frame->next;
    free(frame);
    stack -> size = ((stack -> size) -1);
    return element;
  }
}
