#include "stack.h"

#include <stdlib.h>

struct stack *stack_init()
{
    struct stack *stack = (struct stack*)malloc(sizeof(struct stack));
    stack->top = NULL;
    return stack;
}

int stack_delete(struct stack *stack)
{
    if (stack == NULL) {
        return NULL_ARGUMENT;
    }
    struct node *junk = stack->top;
    struct node *tmp;
    while (junk != NULL) {
        tmp = junk->next;
        node_delete(junk);
        junk = tmp;
    }
    free(stack);
    return 0;
}

int stack_pile(struct stack *stack, void *data, size_t size)
{
    if (stack == NULL) {
        return NULL_ARGUMENT;
    }
    else if (size < 1) {
        return INVALID_ARGUMENT;
    }
    struct node *node = node_init(data, size);
    node->next = stack->top;
    stack->top = node;
    return 0;
}

int stack_ditch(struct stack *stack)
{
    if (stack == NULL) {
        return NULL_ARGUMENT;
    }
    else if (stack->top == NULL) {
        return EMPTY_STACK;
    }
    struct node *below = stack->top->next;
    node_delete(stack->top);
    stack->top = below;
    return 0;
}

void *stack_peek(struct stack *stack)
{
    if (stack == NULL) {
        return (void *)NULL_ARGUMENT;
    }
    else if (stack->top == NULL) {
        return (void *)EMPTY_STACK;
    }
    return stack->top->data;
}