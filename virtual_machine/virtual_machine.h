/*
This is a virtual machine program. it is designed to execute a custom machine language on multiple platforms.
it is a stack machine, it has only these registers:
	- stack pointer register [SPR] (32 bits): points to the first free element of the stack in memory.
	- instruction pointer register [IPR] (32 bits): points to the next instruction to be executed.
	- instruction register [IR] (8 bits): contains the currently executing instruction opcode.
	- memory address register [MAR] (32 bits): contains address of data to be read or to be stored from/in memory.
	- memory data register [MDR] (8 bits): contains data to be stored in memory, or just read from memory.
	- ALU registers [AR, BR, RR, FR](32 bits each): operand registers, result register, flags register.
all computation is done on the single stack of the machine.
all local variables and state information of procedures and micro-operations are stored on the stack.
local variables and parameters in functions are not used.

ALU flags: mode1 mode0 carry1 carry0 
	mode1 mode2  (control flags):  00-byte mode,     01-word mode,     10-double word mode, 11-quad word mode
	carry1 carry0 (status flags):  00-byte overflow, 01-word overflow, 10-dword overflow,   11-quadword overflow
*/
#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 512
#define STACK_SIZE 128

typedef u_int8_t	uint8_t;
typedef u_int16_t	uint16_t;
typedef u_int32_t	uint32_t;
typedef u_int64_t	uint64_t;

enum instruction_set	/* ISA definition */ 
{
	/* stack operations */
	POP_B,	// POP_B addr 	;pops a byte into memory[addr]
	POP_W,	// POP_W addr 	;pops a word into memory[addr], memory[addr+1] in little endian
	POP_D,	// POP_W addr 	;pops a double word into memory[addr] ... memory[addr+3] in little endian
	POP_Q,	// POP_W addr 	;pops a quad word into memory[addr] ... memory[addr+7] in little endian

	PUSH_B, // PUSH_B addr 	;pushes a byte from memory[addr] onto stack
	PUSH_W, // PUSH_W addr 	;pushes a word from memory[addr] onto stack
	PUSH_D, // PUSH_D addr 	;pushes a double word from memory[addr] onto stack
	PUSH_Q, // PUSH_Q addr 	;pushes a quad word from memory[addr] onto stack

	/* flow control */
	JMP,	// JMP addr 	;IPR <- addr
	CALL,	// CALL addr 	;IPR += 5; pushes IPR on stack; IPR <- addr;
	RET,	// RET 			;pops a double word from stack to IPR

	/* arithmetic */
	ADD_B,	// adds the topmost two bytes on stack and replaces them by the result
	ADD_W,
	ADD_D,
	ADD_Q,
};

enum FR_flags_masks 
{
	MODE1 = 0b1000000;
	MODE2 = 0b0100000;
	CARRY1= 0b0010000;
	CARRY2= 0b0001000;
};

/* memory elements */
extern uint8_t 	memory[MEMORY_SIZE];
extern uint8_t 	stack[STACK_SIZE];

extern uint32_t SPR;
extern uint32_t IPR;
extern uint32_t MAR;
extern uint8_t 	IR;
extern uint8_t 	MDR;

extern uint32_t AR;
extern uint32_t BR;
extern uint32_t RR;
extern uint8_t  FR; 	// mode1 mode0 carry1 carry0

/*************************** micro operations */
// stack operations
void push(void);	// stack[SPR] <- MDR; SPR++;
void pop(void);		// SPR--; MDR <- stack[SPR];
// memory operations
void load(void);	// MDR <- memory[MAR];
void store(void);	// memory[MAR] <- MDR;
// register operations
void lmar_mdr(void);	// MDR <- MAR[7:0]
void lmdr_mar(void);	// MAR[7:0] <- MDR
void lipr_mar(void); 	// MAR <- IPR
void lmar_ipr(void);	// IPR <- MAR
void inc_ipr(void);	// IPR++
void dec_ipr(void); // IPR--
void inc_mar(void);	// MAR++
void dec_mar(void);	// MAR--
void shl_mar(void); // MAR << 8;
void shr_mar(void); // MAR >> 8;
// ALU operations
void add(void);		// RR <- AR + BR; overflow and carry flags set accordingly
void sub(void);		// RR <- AR - BR; ...
void mul(void);		// RR <- AR * BR; ...
void div(void); 	// RR <- AR / BR; ...
// stages
void fetch(void);	// IR <- memory[IPR];
void execute(void);

/************************** instructions (ISA micro programs) */
void _PUSH_B(void);
void _PUSH_W(void);
void _PUSH_D(void);
void _PUSH_Q(void);

void _POP_B(void);
void _POP_W(void);
void _POP_D(void);
void _POP_Q(void);

void _JMP(void);
void _CALL(void);
void _RET(void);

/* auxiliary micro programs */
void uprogram_load_dword_operand_to_mar(void);
void uprogram_pop_mar(void);
void uprogram_push_mar(void);