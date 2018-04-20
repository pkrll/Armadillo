.globl start
.extern main
.extern	init_timer
.set noreorder

.set STACKSIZE, 0x4000

.section .text

start:
	la 		$sp, stack
	addiu $sp, STACKSIZE - 32

	# Clear the status(bev) bit. This will make the CPU
	# use the RAM-based exception vector.
	li		$t1, 0x0
	mtc0	$t1, $12,0

	jal		init_timer

	# Set the ebase register (exception entry point) to
	# where the kernel starts (0x80100000)
	li		$t1, 0x80100000
	mtc0	$t1, $15,1

	#syscall # temporary

	nop
	#jal main
	nop
	b	.

.section .bss

stack:
	.space STACKSIZE
