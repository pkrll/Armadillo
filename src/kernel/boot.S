#include <mips/registers.h>
#include <mips/adresses.h>
#include <mips/bitmasks.h>

.globl start
.extern main
.extern	init_timer
.extern test_dispatcher

.set noreorder

.set STACKSIZE, 0x4000

.section .data
#	KBD_DATA_PORT: 	.word 0x60
	KBD_CMD_REG:		.word 0x64
	ENABLE_KBD: .word 0x00f4

.section .text

start:
	la 		$sp, stack
	addiu $sp, STACKSIZE - 32
	# Set the ebase register (exception entry point) to
	# where the kernel starts (0x80100000)
	li		T1, EBASE_ADDR
	mtc0	T1, C0_EBASE

	# Bits 8-15 is the interrupt mask
	mfc0	T1, C0_STATUS
	ori 	T2, T1, 0x1801
	mtc0 	T2, C0_STATUS

	# Clear the status(bev) bit. This will make the CPU
	# use the RAM-based exception vector.
	mfc0 	T1, C0_STATUS
	li		T2, 1
	sll 	T2, 22
	not 	T2, T2
	and 	T2, T2, T1
	mtc0	T2, C0_STATUS

	# ============================
	# Trying to enable keyboard
	# ============================
	lw 		T0, ENABLE_KBD

	lui 	T1, 0x8000 # Debugging line
	addi 	T1, 0x0000 # Debugging line
	#lw 		T1, KBD_CMD_REG, this is the value we want to load into T1
	sw		T0, 0(T1)
	# ============================
	#	End of enable keyboard
	# ============================


	# jal		init_timer
	#syscall # temporary
	nop
	jal main
	nop
	b	.




#get_stack_adress:
#	jal 	get_context_adress
#	nop
#	li		$t1, STACK_OFFSET
#	add		$k1, $k1, $t1
#	jr		$ra
#	nop

.section .bss

stack:
	.space 	STACKSIZE
