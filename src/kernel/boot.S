#include <mips/registers.h>
#include <mips/adresses.h>
#include <mips/bitmasks.h>

.globl start
.extern main
.extern	init_timer
.set noreorder

.set STACKSIZE, 0x4000

.section .text

start:
	la 		$sp, stack
	addiu $sp, STACKSIZE - 32
	# Set the ebase register (exception entry point) to
	# where the kernel starts (0x80100000)
	li		T1, EBASE_ADDR
	mtc0	T1, C0_EBASE
	# Clear the status(bev) bit. This will make the CPU
	# use the RAM-based exception vector.
	li		T1, 0x0
	mtc0	T1, C0_STATUS

	# jal		init_timer


	#syscall # temporary

	nop
	jal main
	nop
	b	.

.section .bss

stack:
	.space STACKSIZE
