#include <mips/registers.h>

.globl start
.extern main

.set noreorder

.set STACKSIZE, 0x4000

.section .text

start:
	la 		$sp, stack
	addiu $sp, STACKSIZE - 32
	# Set the ebase register (exception entry point) to
	# where the kernel starts (0x80100000)
	li		T1, 0x80100000
	mtc0	T1, C0_EBASE
	# Clear the status(bev) bit. This will make the CPU
	# use the RAM-based exception vector.
	li		T1, 0x0
	mtc0	T1, C0_STATUS

	syscall # temporary

	nop
	jal main
	nop
	b .
	nop

.section .bss

stack:
	.space STACKSIZE
