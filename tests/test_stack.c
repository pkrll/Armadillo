#include <stddef.h>
#include <munit/unit.h>
#include <test_stack.h>
#include <common/stack.h>

static char *test_stack_init() {
	stack_t *stack = stack_init();

	mu_assert("Test failed: stack == NULL", stack != NULL);
	stack_destroy(stack);

	return 0;
}

static char *test_stack_push() {
	stack_t *stack = stack_init();

	mu_assert("Test failed: stack size != 0", stack_size(stack) == 0);

	int elem1 = 1;
  stack_push(stack, &elem1);
	mu_assert("Test failed: stack size != 1", stack_size(stack) == 1);

	int elem2 = 2;
  stack_push(stack, &elem2);
	mu_assert("Test failed: stack size != 2", stack_size(stack) == 2);

	int elem3 = 3;
  stack_push(stack, &elem3);
	mu_assert("Test failed: stack size != 3", stack_size(stack) == 3);

	int elem4 = 4;
  stack_push(stack, &elem4);
  mu_assert("Test failed: stack size != 4", stack_size(stack) == 4);

	stack_destroy(stack);

	return 0;
}

static char *test_stack_pop() {
  stack_t *stack = stack_init();

	mu_assert("Test failed: stack size != 0", stack_size(stack) == 0);

  int elem1 = 1;
  stack_push(stack, &elem1);
  int elem2 = 2;
  stack_push(stack, &elem2);
  int elem3 = 3;
  stack_push(stack, &elem3);
  int elem4 = 4;
  stack_push(stack, &elem4);

	mu_assert("Test failed: stack size != 4", stack_size(stack) == 4);

  int *elem1_fetch = stack_pop(stack);
	mu_assert("Test failed: popped element != 4", *elem1_fetch == 4);
	mu_assert("Test failed: stack size != 3", stack_size(stack) == 3);

  int *elem2_fetch = stack_pop(stack);
	mu_assert("Test failed: popped element != 3", *elem2_fetch == 3);
	mu_assert("Test failed: stack size != 2", stack_size(stack) == 2);

  int *elem3_fetch = stack_pop(stack);
	mu_assert("Test failed: popped element != 2", *elem3_fetch == 2);
	mu_assert("Test failed: stack size != 1", stack_size(stack) == 1);

  int *elem4_fetch = stack_pop(stack);
	mu_assert("Test failed: popped element != 1", *elem4_fetch == 1);
	mu_assert("Test failed: stack size != 0", stack_size(stack) == 0);

	stack_destroy(stack);

	return 0;
}

char *test_stack() {
	mu_run_test(test_stack_init);
	mu_run_test(test_stack_push);
	mu_run_test(test_stack_pop);

	return 0;
}
