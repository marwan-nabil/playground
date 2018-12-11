// old functions that i don't want to delete

void _POP_B()
{
	// get the address operand from within the pop instruction itself to MAR
	MAR = 0;
	MAR |= ((uint32_t) memory[IPR+4])<<24;
	MAR |= ((uint32_t) memory[IPR+3])<<16;
	MAR |= ((uint32_t) memory[IPR+2])<<8;
	MAR |= ((uint32_t) memory[IPR+1]);
	pop();
	store();
	IPR += 5;	// point to next instruction
}

void _POP_W()
{
	// get the address operand from within the pop instruction itself to MAR
	MAR = 0;
	MAR |= ((uint32_t) memory[IPR+4])<<24;
	MAR |= ((uint32_t) memory[IPR+3])<<16;
	MAR |= ((uint32_t) memory[IPR+2])<<8;
	MAR |= ((uint32_t) memory[IPR+1]);
	
	// store the most significant byte first
	MAR++;
	pop();
	store();
	MAR--;
	pop();
	store();
	IPR += 5;	// point to next instruction
}

void _POP_D()
{
	// get the address operand from within the pop instruction itself to MAR
	MAR = 0;
	MAR |= ((uint32_t) memory[IPR+4])<<24;
	MAR |= ((uint32_t) memory[IPR+3])<<16;
	MAR |= ((uint32_t) memory[IPR+2])<<8;
	MAR |= ((uint32_t) memory[IPR+1]);
	
	// store the most significant byte first
	MAR+=3;
	pop();
	store();
	MAR--;
	pop();
	store();
	MAR--;
	pop();
	store();
	MAR--;
	pop();
	store();

	IPR += 5;	// point to next instruction
}

void _POP_Q()
{
	// get the address operand from within the pop instruction itself to MAR
	MAR = 0;
	MAR |= ((uint32_t) memory[IPR+4])<<24;
	MAR |= ((uint32_t) memory[IPR+3])<<16;
	MAR |= ((uint32_t) memory[IPR+2])<<8;
	MAR |= ((uint32_t) memory[IPR+1]);
	
	// store the most significant byte first
	MAR+=7;
	pop();
	store();
	MAR--;
	pop();
	store();
	MAR--;
	pop();
	store();
	MAR--;
	pop();
	store();
	MAR--;
	pop();
	store();
	MAR--;
	pop();
	store();
	MAR--;
	pop();
	store();
	MAR--;
	pop();
	store();

	IPR += 5;	// point to next instruction
}


void _PUSH_B()
{
	// get the address operand from within the push instruction itself to MAR
	MAR = 0;
	MAR |= ((uint32_t) memory[IPR+4])<<24;
	MAR |= ((uint32_t) memory[IPR+3])<<16;
	MAR |= ((uint32_t) memory[IPR+2])<<8;
	MAR |= ((uint32_t) memory[IPR+1]);

	load();
	push();

	IPR += 5;	// point to next instruction
}

void _PUSH_W()
{
	// get the address operand from within the push instruction itself to MAR
	MAR = 0;
	MAR |= ((uint32_t) memory[IPR+4])<<24;
	MAR |= ((uint32_t) memory[IPR+3])<<16;
	MAR |= ((uint32_t) memory[IPR+2])<<8;
	MAR |= ((uint32_t) memory[IPR+1]);

	load();
	push();
	MAR++;
	load();
	push();

	IPR += 5;	// point to next instruction
}

void _PUSH_D()
{
	// get the address operand from within the push instruction itself to MAR
	MAR = 0;
	MAR |= ((uint32_t) memory[IPR+4])<<24;
	MAR |= ((uint32_t) memory[IPR+3])<<16;
	MAR |= ((uint32_t) memory[IPR+2])<<8;
	MAR |= ((uint32_t) memory[IPR+1]);

	load();
	push();
	MAR++;
	load();
	push();
	MAR++;
	load();
	push();
	MAR++;
	load();
	push();

	IPR += 5;	// point to next instruction
}

void _PUSH_Q()
{
	// get the address operand from within the push instruction itself to MAR
	MAR = 0;
	MAR |= ((uint32_t) memory[IPR+4])<<24;
	MAR |= ((uint32_t) memory[IPR+3])<<16;
	MAR |= ((uint32_t) memory[IPR+2])<<8;
	MAR |= ((uint32_t) memory[IPR+1]);

	load();
	push();
	MAR++;
	load();
	push();
	MAR++;
	load();
	push();
	MAR++;
	load();
	push();
	MAR++;
	load();
	push();
	MAR++;
	load();
	push();
	MAR++;
	load();
	push();
	MAR++;
	load();
	push();

	IPR += 5;	// point to next instruction
}

void _JMP()
{
	// copy the jump address from the jump instruction to MAR
	MAR = 0;
	MAR |= ((uint32_t) memory[IPR+4])<<24;
	MAR |= ((uint32_t) memory[IPR+3])<<16;
	MAR |= ((uint32_t) memory[IPR+2])<<8;
	MAR |= ((uint32_t) memory[IPR+1]);
	// copy the MAR to the IPR
	IPR = MAR;
}