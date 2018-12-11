#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_SIZE 512
#define STACK_SIZE 128

typedef u_int8_t	uint8_t;
typedef u_int16_t	uint16_t;
typedef u_int32_t	uint32_t;
typedef u_int64_t	uint64_t;

/* NOTE: this is a little endian architecture, low significant bytes are stored in lower addresses */
enum Mnemonic	/* all instruction mnemonics */ 
{
	/* arithmetic */
	// addition: adds the top most 2 data values on the stack and replaces them by the result
	// overflow is unchecked
	ADD_B,	// signed byte addition
	ADD_W,	// signed 16-bit word addition
	ADD_D,	// signed 32-bit double word addition
	ADD_Q, 	// signed 64-bit quad word addition
	// negation: 2's complements the topmost data value on the stack and replaces it by the result
	NEG_B,	// negate a byte
	NEG_W,	// negate a word
	NEG_D,	// negate a double word
	NEG_Q,	// negate a quad word
	
	/* logical */
	NOT_B,	// bitwise not a byte
	NOT_W,	// bitwise not a word
	NOT_D,	// bitwise not a double word
	NOT_Q,	// bitwise not a quad word
	AND_B,	// bitwise and a byte
	AND_W,	// bitwise and a word
	AND_D,	// bitwise and a double word
	AND_Q,	// bitwise and a quad word
	OR_B,	// bitwise or a byte
	OR_W,	// bitwise or a word
	OR_D,	// bitwise or a double word
	OR_Q,	// bitwise or a quad word
	XOR_B,	// bitwise xor a byte
	XOR_W,	// bitwise xor a word
	XOR_D,	// bitwise xor a double word
	XOR_Q,	// bitwise xor a quad word

	/* flow control */
	JMP,	// pops a double word from the stack into memory_pointer_register and does a fetch() then an execute()
	
	/* stack pushing */
	// push instructions encode operand address in the 4 bytes following it in memory
	// they do 4 fetches and stack pushes to get the operand address into the stack, 
	// then fill out the memory_pointer_register with this operand address, popping it from the stack,
	// then fetch the whole operand from memory onto the stack
	PUSH_B,	// push a byte
	PUSH_W,	// push a word
	PUSH_D,	// push a double word
	PUSH_Q,	// push a quad word
};

extern uint8_t 	memory[MEM_SIZE];
extern uint8_t 	stack[STACK_SIZE];	// stack is part of the cpu and is limited
extern uint8_t 	fetch_register;	// where the fetched byte from memory resides (instructions and data)
extern uint32_t memory_pointer_register;	// points to the next byte to fetch from memory
extern uint16_t stack_pointer_register;	// pointing to the top of the stack which is free of data

/* prototypes */

// primitive cpu and memory operations
void fetch(void);	// fetches a byte from memory at [memory_pointer_register] into fetch_register
void execute(void);	// tries to execute the byte in fetch_register
void push(uint8_t);	// push a byte onto the stack
uint8_t pop(void);	// pop a byte from the stack

#define load(ADDR) memory[ADDR]
#define store(ADDR, BYTE) memory[ADDR] = BYTE

// derived operations
void handle_arithmetic(void);	// handles all addition instructions
void handle_pushing(void);	// handles pushing from memory instructions
void handle_logical(void);	// handles logical operations
void handle_flow_control(void);	// handles jumps and calls

// auxiliary functions
void restore_memory_pointer(void);
void save_memory_pointer(void);
void push_n_from_memory(uint8_t);
void pop_n_to_memory(uint8_t);
void pop_n_to_void(uint8_t);