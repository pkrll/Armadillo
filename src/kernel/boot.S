#include <mips/registers.h>
#include <mips/adresses.h>
#include <mips/bitmasks.h>
#include <mips/pcb.h>

.globl start
.globl context_switch
.extern main
.extern	init_timer
.extern init_process_1


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
	jal init_process_1
	nop
#	jal		init_timer


	#syscall # temporary

	nop
#	jal main
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
