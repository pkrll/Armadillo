#include <common/stack.h>
#include <common/stdlib.h>
#include <common/memory.h>

struct StackNode {
	void *element;
	stack_node_t *next;
};

struct Stack {
	stack_node_t *top;
	int size;
};

void node_destroy(stack_node_t *node);

stack_t *stack_init() {
	stack_t *stack = malloc(sizeof(stack_t));

	if (stack != NULL) {
		stack->size = 0;
	}

	return stack;
}

void stack_destroy(stack_t *stack) {
	if (stack != NULL) {
		node_destroy(stack->top);
		free(stack);
	}
}

void stack_push(stack_t *stack, void *element) {
	stack_node_t *node = malloc(sizeof(stack_node_t));

	if (node != NULL) {
		node->element = element;
		node->next 		= stack->top;
		stack->top 		= node;
		stack->size 	= stack->size + 1;
	}
}

void *stack_pop(stack_t *stack) {
	if (stack == NULL || stack->size == 0) return NULL;

	stack_node_t *node = stack->top;
	void *element = node->element;

	stack->top = node->next;
	stack->size--;

	free(node);

	return element;
}

int stack_size(stack_t *stack) {
	return (stack != NULL) ? stack->size : 0;
}

void node_destroy(stack_node_t *node) {
	if (node) {
		stack_node_t *next_node = node->next;
		free(node);

		node_destroy(next_node);
	}
}
