#ifndef __STACK_H__
#define __STACK_H__

typedef struct Stack Stack_t;
typedef struct Stack_element Stack_element_t;

Stack_t *initialize_stack();
void destroy_stack(Stack_t *stack);
void push_to_stack(Stack_t *stack, void *element);
void *pop_from_stack(Stack_t *stack);

#endif
