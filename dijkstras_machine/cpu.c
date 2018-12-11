#include "stack_machine.h"

uint8_t 	stack[STACK_SIZE];
uint32_t 	memory_pointer_register;
uint16_t 	stack_pointer_register;
uint8_t 	fetch_register;

uint8_t pop()	
{
	if(stack_pointer_register == 0)
	{
		printf("CPU: FAULT: POP: stack underflow.\n");
		exit(1);
	}

	return stack[--stack_pointer_register];
}

void push(uint8_t c)
{
	if(stack_pointer == STACK_SIZE)
	{
		printf("CPU: FAULT: PUSH: stack overflow.\n");
		exit(1);
	}

	stack[stack_pointer++] = c;
}

void fetch()
{
	fetch_register = load(memory_pointer_register++);
}

void execute()
{
	switch(fetch_register)
	{
		case PUSH_B:
		case PUSH_W:
		case PUSH_D:
		case PUSH_Q:
			handle_pushing();
			break;

		case ADD_B:
		case ADD_W:
		case ADD_D:
		case ADD_Q:
		

	}
}

void handle_pushing()
{
	// NOTE: all push instructions are 5 bytes wide, that's why we increment the memory pointer
	// by 4 to get to the next instruction
	uint32_t old_memory_pointer = memory_pointer_register;
	switch(fetch_register)
	{
		case PUSH_B:
		{
			push_n_from_memory(1);
			memory_pointer_register = old_memory_pointer + 4;	// to next instruction
		} break;

		case PUSH_W:
		{
			push_n_from_memory(2);
			memory_pointer_register = old_memory_pointer + 4;	// to next instruction
		} break;

		case PUSH_D:
		{
			push_n_from_memory(4);
			memory_pointer_register = old_memory_pointer + 4;	// to next instruction
		} break;

		case PUSH_Q:
		{
			push_n_from_memory(8);
			memory_pointer_register = old_memory_pointer + 4;	// to next instruction
		} break;
	}
}

void push_n_from_memory(uint8_t n)
{
	// pushes n bytes from memory to stack
	// side effect: increments memory pointer by n
	for(uint8_t i = 0; i < n; i++)
	{
		fetch();
		push(fetch_register);
	}
}

void pop_n_to_memory(uint8_t n)
{
	// pops n bytes from stack into memory in reverse,
	// the address in memory_pointer_register should be the address
	// of the most significant byte of the data
	// side effect: decrements memory pointer by n
	for(uint8_t i = 0; i < n; i++)
	{
		store(memory_pointer_register--, pop());
	}
}

void pop_n_to_void(uint8_t n)
{
	for(uint8_t i = 0; i < n; i++)
	{
		pop();
	}
}

void save_memory_pointer()
{
	// pushes the memory_pointer_register on the stack
	push((uint8_t) memory_pointer_register);
	push((uint8_t)(memory_pointer_register >> 8));
	push((uint8_t)(memory_pointer_register >> 16));
	push((uint8_t)(memory_pointer_register >> 24));
}

void restore_memory_pointer()
{
	// pops an address from the stack to the memory_pointer_register
	memory_pointer_register = ((uint32_t) pop()) << 24;
	memory_pointer_register |= ((uint32_t) pop()) << 16;
	memory_pointer_register |= ((uint32_t) pop()) << 8;
	memory_pointer_register |= ((uint32_t) pop());
}