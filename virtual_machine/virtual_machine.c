#include "virtual_machine.h"

uint8_t 	memory[MEMORY_SIZE];
uint8_t 	stack[STACK_SIZE];

uint32_t 	SPR = 0;
uint32_t	IPR = 0;
uint32_t 	MAR = 0;
uint8_t 	IR  = 0;
uint8_t 	MDR = 0;

uint32_t AR;
uint32_t BR;
uint32_t RR;
uint32_t FR;

/**************************************************************************/
/***************************** Micro operations */
/* stack operations */
void push()	// stack[SPR] <- MDR; SPR++;
{
	stack[SPR] = MDR;
	SPR++;
}

void pop()	// SPR--; MDR <- stack[SPR];
{
	SPR--;
	MDR = stack[SPR];
}

/* memory operations */
void load()	// MDR <- memory[MAR];
{
	MDR = memory[MAR];
}

void store()	// memory[MAR] <- MDR;
{
	memory[MAR] = MDR;
}

/* register operations */
void lmar_mdr()
{
	MDR = (uint8_t) MAR;
}

void lmdr_mar()
{
	MAR &= 0xFFFFFF00;
	MAR |= (uint32_t) MDR;
}

void lipr_mar()
{
	MAR = IPR;
}

void lmar_ipr()
{
	IPR = MAR;
}

void inc_ipr()
{
	IPR++;
}

void dec_ipr()
{
	IPR--;
}

void shl_mar()
{
	MAR = MAR << 8;
}

void shr_mar()
{
	MAR = MAR >> 8;
}

void inc_mar()
{
	MAR++;
}

void dec_mar()
{
	MAR--;
}
/* ALU operations */

void add()
{ 
}

void sub()
{
	
}

void mul()
{
	
}

void div()
{
	
}

/* stage operations */
void fetch()	// IR <- memory[MAR];
{
	IR = memory[IPR];
}

void execute()
{
	switch(IR)
	{
		case POP_B:
			_POP_B();
			break;

		case POP_W:
			_POP_W();
			break;

		case POP_D:
			_POP_D();
			break;
			
		case POP_Q:
			_POP_Q();
			break;
	}
}

/**************************************************************************/
/************************* instruction micro programs */

void _POP_B()
{
	/*	get the address operand from within the pop instruction itself to MAR */
	uprogram_load_dword_operand_to_mar();	// also increments IPR by 4
	// now MAR has the whole address, we will now pop a byte from stack and store it there
	pop();
	store();
	inc_ipr();	// point to next instruction
}

void _POP_W()
{
	uprogram_load_dword_operand_to_mar();	// MAR now has the address of the pop location
	inc_mar();	// because we'll pop the high byte first to memory from stack
	pop();
	store();
	dec_mar();	// point to location of low byte
	pop();
	store();
	inc_ipr();	// point to next instruction
}

void _POP_D()
{
	uprogram_load_dword_operand_to_mar();	// MAR now has the address of the pop location
	
	inc_mar(); 
	inc_mar(); 
	inc_mar();	// because we'll pop the high byte first to memory from stack
	pop();
	store();
	dec_mar();
	pop();
	store();
	dec_mar();
	pop();
	store();
	dec_mar();
	pop();
	store();

	inc_ipr();	// point to next instruction
}

void _POP_Q()
{
	uprogram_load_dword_operand_to_mar();	// MAR now has the address of the pop location
	
	inc_mar();
	inc_mar();
	inc_mar(); 
	inc_mar();
	inc_mar(); 
	inc_mar(); 
	inc_mar();	// because we'll pop the high byte first to memory from stack
	pop();
	store();
	dec_mar();
	pop();
	store();
	dec_mar();
	pop();
	store();
	dec_mar();
	pop();
	store();
	dec_mar();
	pop();
	store();
	dec_mar();
	pop();
	store();
	dec_mar();
	pop();
	store();
	dec_mar();
	pop();
	store();

	inc_ipr();	// point to next instruction
}

void _PUSH_B()
{
	uprogram_load_dword_operand_to_mar();
	load();
	push();
	inc_ipr();	// next instruction
}

void _PUSH_W()
{
	uprogram_load_dword_operand_to_mar();
	load();
	push();
	inc_mar();
	load();
	push();

	inc_ipr();
}

void _PUSH_D()
{
	uprogram_load_dword_operand_to_mar();
	load();
	push();
	inc_mar();
	load();
	push();
	inc_mar();
	load();
	push();
	inc_mar();
	load();
	push();

	inc_ipr();
}

void _PUSH_Q()
{
	uprogram_load_dword_operand_to_mar();
	load();
	push();
	inc_mar();
	load();
	push();
	inc_mar();
	load();
	push();
	inc_mar();
	load();
	push();
	inc_mar();
	load();
	push();
	inc_mar();
	load();
	push();
	inc_mar();
	load();
	push();
	inc_mar();
	load();
	push();

	inc_ipr();	// next instruction
}

void _JMP()
{
	uprogram_load_dword_operand_to_mar();
	lmar_ipr();
}

void _CALL()
{
	// get the next instruction address into MAR
	lipr_mar();	// MAR now has the address of the current instruction
	inc_mar();
	inc_mar();
	inc_mar();
	inc_mar();
	inc_mar();	// MAR now has the address of the next instruction
	// push the next instruction address from MAR on the stack
	uprogram_push_mar();
	// load operand address (procedure address) into MAR
	uprogram_load_dword_operand_to_mar();
	// copy this to IPR to jump
	lmar_ipr();
}

void _RET()
{
	// restore the next instruction address from stack to MAR
	uprogram_pop_mar();	// MAR now has the return address
	lmar_ipr();
}

void _ADD_B()
{
	push(pop()+pop());
	inc_ipr();
}

void _ADD_W(
{

})
/************************************************************************/
/******************* auxiliary microprograms */
void uprogram_load_dword_operand_to_mar()
{
	// loads the double word operand from an instruction into MAR
	// side effects: increments IPR by 4
	inc_ipr();	// IPR++, IPR now points to the low byte of the operand address
	lipr_mar();	// MAR <- IPR, MAR now points to the low byte of operand address 
	load();		// loads the low byte into MDR
	push();		// pushes low byte on stack

	// do this 3 more times
	inc_ipr();
	lipr_mar();
	load();
	push();		// pushes second lowest byte of address on stack

	inc_ipr();
	lipr_mar();
	load();
	push();		// pushes second highest byte on stack

	inc_ipr();
	lipr_mar();
	load();
	push();		// pushes highest byte on stack

	// now stack has the address of the operand on top of it, we need to put it in MAR
	uprogram_pop_mar();
	// MAR now has the address, and the stack is restored, and IPR is incremented by 4
}

void uprogram_push_mar()
{
	// pushes MAR on stack
	// side effect: destroys value in MAR
	lmar_mdr();	// loads low byte of MAR to MDR
	push();
	shr_mar();

	lmar_mdr();
	push();
	shr_mar();

	lmar_mdr();
	push();
	shr_mar();

	lmar_mdr();
	push();
}

void uprogram_pop_mar()
{
	// pops an address from stack into MAR
	pop();		// pops the high byte of address into MDR
	lmdr_mar();	// loads this high byte into low byte of MAR
	shl_mar();	// shifts MAR left by one byte, to make space for the next byte

	pop();
	lmdr_mar();
	shl_mar();

	pop();
	lmdr_mar();
	shl_mar();

	pop();
	lmdr_mar();
}