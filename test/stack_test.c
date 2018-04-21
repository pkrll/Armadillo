#include <stdlib.h>  // Ska raderas!
#include <stdio.h> 	// Ska raderas!
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>
#include "stack.h"


struct Stack_element {
  void *element;
  struct Stack_element *next;
} typedef Stack_element_t;

struct Stack {
  Stack_element_t *top;
  int size;
} typedef Stack_t;


void test_stack_creation() {
  Stack_t *stack = initialize_stack();
  CU_ASSERT_TRUE(stack != NULL);
}

void test_push() {
  Stack_t *stack = initialize_stack();
  int elem1 = 1;
  push_to_stack(stack, &elem1);
  int elem2 = 2;
  push_to_stack(stack, &elem2);
  int elem3 = 3;
  push_to_stack(stack, &elem3);
  int elem4 = 4;
  push_to_stack(stack, &elem4);
  CU_ASSERT_TRUE(stack->size == 4);
}

void test_pop() {
  Stack_t *stack = initialize_stack();

  int elem1 = 1;
  push_to_stack(stack, &elem1);
  int elem2 = 2;
  push_to_stack(stack, &elem2);
  int elem3 = 3;
  push_to_stack(stack, &elem3);
  int elem4 = 4;
  push_to_stack(stack, &elem4);

  int *elem1_fetch = ((pop_from_stack(stack)));
  int elem1_converted = (*(elem1_fetch));
  CU_ASSERT_TRUE((elem1_converted) == 4);
  int *elem2_fetch = ((pop_from_stack(stack)));
  int elem2_converted = (*(elem2_fetch));
  int *elem3_fetch = ((pop_from_stack(stack)));
  int elem3_converted = (*(elem3_fetch));
  int *elem4_fetch = ((pop_from_stack(stack)));
  int elem4_converted = (*(elem4_fetch));

  CU_ASSERT_TRUE((stack->size) == 0);
}


int main(){
  CU_initialize_registry();
  CU_pSuite stack_test = CU_add_suite("Testing stack creation, push, pop and destruction", NULL, NULL);
  CU_add_test(stack_test, "Create stack", test_stack_creation);
  CU_add_test(stack_test, "Push elements to stack", test_push);
  CU_add_test(stack_test, "Pop elements from stack", test_pop);

  CU_basic_run_tests();

  CU_cleanup_registry();

  return CU_get_error();
}
