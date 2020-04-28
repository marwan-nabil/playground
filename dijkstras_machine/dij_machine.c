/* a simple stack machine invented by E.W. Dijkstra
 * allowed symbols on the stack are:
 * 	a number like 1, 2, 180 , -23
 * 	an operator: + - / *
 * 	the print stack directive: P, dumps stack contents to stdout, with formatting.
 * 	the execute directive	 : E, calculates the last operation on the stack and stores the result on it
 *	all other characters are treated like numbers, i.e. cast into an int.
 *
 * the user enters all symbols for an expression, possibly with intervening 'P' directives,
 * and the machine starts computing on the stack once the EOF is detected.
 *
 * Author: marwan nabil
 */

#include "dij_machine.h"
symbol input_buffer[MAXSTACK];
symbol stack[MAXSTACK];
symbol *sp = stack;
int err_status;

void main(void){
	printf("Hello\n");
	// fill the stack with symbols the user provides to a shell and stop on EOF
	fill_stack();
	// compute the whole expression on the stack or return an error status
	int err_status;
	compute_expression();
	// print the final result or "error: bad input expression"
	print_result(err_status);
	return ;	
}

void print_result(int e){
	if(e){
		printf("Error: invalid Expression.\n");
		return ;
	} else {
		print_stack_contents();
		return ;
	}
}

void print_stack_contents(void){
	printf("\nStack contents:\n\t");
	symbol *index = stack;
	for (symbol *i = stack; i < sp; i++){
		if(i->type == NUM)
			printf("%d ", i->value );
		else if(i->type == OP)
			printf("%c ", i->value );
		else if(i->type == EXE)
			printf("E ");
	}
}

void push(symbol s){
	if(sp - stack < MAXSTACK)
		sp++ = s;
	else { 
		printf("error: stack overflow detected.\n");
		err_status = 1;
	}
	return ;
}

symbol pop(void){
	if(sp > stack)
		return *(--sp);
	else {
		printf("error: stack underflow detected.\n");
		err_status = 1;
	}
}

void execute(void){
	symbol op = *(sp - 1);
	if(op.type != OP ){
		printf("error: invalid stack operation, only operators are executable.\n");
		err_status = 1;
	} else {
		
	}

}





