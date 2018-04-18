.globl start
.extern main
.extern excp

.set noreorder

.set STACKSIZE, 0x8000

.section .text

start:
	la $sp, stack
	addiu $sp, STACKSIZE - 32
	nop
	# li $s0, 0x7fffffff
	# addi $s1, $s0, 1
	nop
	jal main
	nop
	b .
	nop

.section .bss

stack:
	.space STACKSIZE
