#include <stdlib.h>  // Ska raderas!
#include <stdio.h> 	// Ska raderas!
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>
#include <common/stack.h>

void test_stack_creation() {
  Stack_t *stack = stack_init();
  CU_ASSERT_TRUE(stack != NULL);
	stack_destroy(stack);
}

void test_push() {
  Stack_t *stack = stack_init();
	CU_ASSERT_TRUE(stack_size(stack) == 0);

	int elem1 = 1;
  stack_push(stack, &elem1);
	CU_ASSERT_TRUE(stack_size(stack) == 1);

	int elem2 = 2;
  stack_push(stack, &elem2);
	CU_ASSERT_TRUE(stack_size(stack) == 2);

	int elem3 = 3;
  stack_push(stack, &elem3);
	CU_ASSERT_TRUE(stack_size(stack) == 3);

	int elem4 = 4;
  stack_push(stack, &elem4);
  CU_ASSERT_TRUE(stack_size(stack) == 4);

	stack_destroy(stack);
}

void test_pop() {
  Stack_t *stack = stack_init();
	CU_ASSERT_TRUE(stack_size(stack) == 0);

  int elem1 = 1;
  stack_push(stack, &elem1);
  int elem2 = 2;
  stack_push(stack, &elem2);
  int elem3 = 3;
  stack_push(stack, &elem3);
  int elem4 = 4;
  stack_push(stack, &elem4);

	CU_ASSERT_TRUE(stack_size(stack) == 4);

  int *elem1_fetch = stack_pop(stack);
  int elem1_converted = (*(elem1_fetch));
  CU_ASSERT_TRUE((elem1_converted) == 4);

	CU_ASSERT_TRUE(stack_size(stack) == 3);

  int *elem2_fetch = stack_pop(stack);
  int elem2_converted = (*(elem2_fetch));
  CU_ASSERT_TRUE((elem2_converted) == 3);

	CU_ASSERT_TRUE(stack_size(stack) == 2);

  int *elem3_fetch = stack_pop(stack);
  int elem3_converted = (*(elem3_fetch));
  CU_ASSERT_TRUE((elem3_converted) == 2);

	CU_ASSERT_TRUE(stack_size(stack) == 1);

  int *elem4_fetch = stack_pop(stack);
  int elem4_converted = (*(elem4_fetch));
  CU_ASSERT_TRUE((elem4_converted) == 1);

  CU_ASSERT_TRUE((stack_size(stack)) == 0);
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
