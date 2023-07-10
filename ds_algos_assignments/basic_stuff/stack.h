#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include "doubly_linked_list.h"

struct stack {
    int *contents;
    int top; // index of the top element in stack
    unsigned int capacity;
};


// top:                                    v
// contents:  [                            5   4]
// capacity: 20

// stack_push(stack, 5)
// stack_push(stack, 6)
// stack_push(stack, 15)

// 15 = stack_pop(stack)
// stack_push(stack, -4)

// -4 = peek_stack(stack)


struct stack *create_stack(unsigned int capacity);
void extend_stack(struct stack *stack, unsigned int new_capacity);
void print_stack(struct stack *stack);


bool is_stack_full(struct stack *stack);
bool is_stack_empthy(struct stack *stack);

void stack_push(struct stack *stack, int item);
int stack_pop(struct stack *stack);
int stack_peek(struct stack *stack);
