	# this is a minimal os kernel
	# it just writes 0xcafebabe in %eax
	# and sticks in a loop
	.equ MAGIC, 0x1badb002
	.equ FLAGS, 0x0
	.equ CHKSUM, - MAGIC

	.section .text
	.align 4
	# the header
	.long MAGIC
	.long FLAGS
	.long CHKSUM
	# the code
	.global loader
loader:
	movl $0xcafebabe, %eax
loop:
	jmp loop
