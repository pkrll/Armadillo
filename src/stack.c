#include<stdlib.h>  // Ska raderas!
#include<stdio.h> 	// Ska raderas!

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
  }}

int main(int argc, char const *argv[]) {
  Stack_t *stack = initialize_stack();
  if (stack != NULL) {
    printf("Sucess\n");
  } else {
    printf("failure\n");
  }
  
  int elem1 = 1;
  push_to_stack(stack, &elem1);
  int* elem1_fetch = ((pop_from_stack(stack)));
  int elem1_converted = (*(elem1_fetch));

  int elem2 = 2;
  push_to_stack(stack, &elem2);
  int* elem2_fetch = ((pop_from_stack(stack)));
  int elem2_converted = (*(elem2_fetch));

  int elem3 = 3;
  push_to_stack(stack, &elem3);
  int* elem3_fetch = ((pop_from_stack(stack)));
  int elem3_converted = (*(elem3_fetch));

  int elem4 = 4;
  push_to_stack(stack, &elem4);
  int* elem4_fetch = ((pop_from_stack(stack)));
  int elem4_converted = (*(elem4_fetch));
  
  printf("elem1: %d\n", elem1_converted);
  printf("elem2: %d\n", elem2_converted);
  printf("elem3: %d\n", elem3_converted);
  printf("elem4: %d\n", elem4_converted);
  return 0;
}
