#include<stdio.h>
#include<stdlib.h>

typedef struct {
	enum {NUM,OP,EXE} 	type;
	int			value;
} symbol;

#define MAXSTACK 200
// globals
symbol stack[MAXSTACK];
symbol *sp;

// auxiliary functionality
void push(symbol);
symbol pop(void);
void execute(void);
void print_stack_contents(void);

// high level functionality (used in main)
void fill_stack(void);
int compute_expression(void);
void print_result(int);

