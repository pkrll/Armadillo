/**
 * @file
 * @brief Stack data structure
 */
#ifndef __STACK_H__
#define __STACK_H__

typedef struct Stack stack_t;
typedef struct StackNode stack_node_t;

/**
 * Initializes the stack.
 * @return Pointer to a new stack.
 */
stack_t *stack_init();
/**
 * Deinitializes a stack.
 *
 * @param stack The stack to deinitialize.
 */
void stack_destroy(stack_t *stack);
/**
 * Pushes an element to the stack.
 *
 * @param stack   Pointer to the stack to populate.
 * @param element The element to add.
 */
void stack_push(stack_t *stack, void *element);
/**
 * Pops an element from the top of the stack, and returns it.
 *
 * @param stack  Pointer to the stack to populate.
 *
 * @return       The topmost element of the stack.
 */
void *stack_pop(stack_t *stack);
/**
 * Returns the size of the stack.
 *
 * @param  stack A stack.
 * @return       The size of the stack.
 */
int stack_size(stack_t *stack);

#endif
