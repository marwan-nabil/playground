#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "stack.h"
#include "array.h"

struct stack *create_stack(unsigned int capacity)
{
    struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->contents = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

void extend_stack(struct stack *stack, unsigned int new_capacity)
{
    stack->capacity = new_capacity;
    stack->contents = (int *)realloc(stack->contents, new_capacity * sizeof(int));
}

void print_stack(struct stack *stack)
{
    printf("\nstack top:  %d", stack->contents[stack->top]);
    
    for(int i = (stack->top - 1); i > 0; i--)
    {
        printf("\n            %d", stack->contents[i]);
    }
    printf("\nstack base: %d\n", stack->contents[0]);
}
 
// stack is full when top is equal to the last index
bool is_stack_full(struct stack *stack)
{
    return (stack->top == stack->capacity - 1);
}
 
// stack is empty when top is equal to -1
bool is_stack_empthy(struct stack *stack)
{
    return (stack->top == -1);
}
 
// Function to add an item to stack.  It increases top by 1
void stack_push(struct stack *stack, int item)
{
    if (is_stack_full(stack))
    {
        // we can't push anything because stack is full
        // extend_stack(stack, (stack->capacity * 2));
        return;
    }
    else
    {
        stack->top++;
        stack->contents[stack->top] = item;
    }
}
 
// Function to remove an item from stack.  It decreases top by 1
int stack_pop(struct stack *stack)
{
    if (is_stack_empthy(stack))
    {
        // we can't pop anything becasue stack is empty
        printf("\n NOTE: stack is empty and you're trying to pop from it.\n");
        return 0; // invalid value
    }
    else
    {
        int value = stack->contents[stack->top];
        stack->top--;
        return value;
    }
}
 
// Function to return the top from stack without removing it
int stack_peek(struct stack *stack)
{
    if (is_stack_empthy(stack))
    {
        // we can't peek at anything becasue stack is empty
        printf("\n NOTE: stack is empty and you're trying to peek from it.\n");
        return 0; // invalid value
    }
    else
    {
        return stack->contents[stack->top]; 
    }
}
