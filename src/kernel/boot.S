.globl bootup
.extern main

.set noreorder

.set STACKSIZE, 0x4000

.section .text

bootup:

	la 		$sp, stack
	addiu $sp, STACKSIZE - 32

	li		$t1, 0x80100000		#  sets ebase
	mtc0	$t1, $15,1
	# Set status.bev to 0
	li		$t1, 0x0
	mtc0	$t1, $12,0

	syscall

	nop
	jal main
	nop
	b .
	nop

.section .bss

stack:
	.space STACKSIZE
