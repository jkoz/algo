#ifndef STACK_H_
#define STACK_H_

#include "list.h"

typedef List Stack;

#define stack_init list_init
#define stack_destroy list_destroy
int stack_push(Stack *stack, const void *data);
int stack_pop(Stack *stack, void **data);
#define stack_peek(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)
#define stack_size list_size
#define stack_print list_print

#endif
