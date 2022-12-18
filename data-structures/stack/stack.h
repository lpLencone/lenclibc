#ifndef stack_h
#define stack_h

#include "../node/node.h"

#include <stddef.h>

#ifndef NULL_ARGUMENT
#define NULL_ARGUMENT 11
#endif /* NULL_ARGUMENT */

#ifndef EMPTY_STACK
#define EMPTY_STACK   12
#endif /* EMPTY_STACK */

#ifndef INVALID_ARGUMENT
#define INVALID_ARGUMENT 13
#endif /* INVALID_ARGUMENT */

struct stack
{
    struct node *top;
};

int stack_pile(struct stack *stack, void *data, size_t size);
int stack_ditch(struct stack *stack);
void *stack_peek(struct stack *stack);

struct stack *stack_init();
int stack_destroy(struct stack *stack);

#endif /* stack_h */