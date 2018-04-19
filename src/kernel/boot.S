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
	li		$t0, 0x0
	mtc0	$t0, $12

	#li 	$t2, 0x7F7FFFFF
	#and 	$t3, $t0, $t2
	#mtc0 $t3, $12

	#Overflow exception
	li		$t4, 0x7fffffff
	addi 	$t5, $t4, 1

	nop
	jal main
	nop
	b .
	nop

.section .bss

stack:
	.space STACKSIZE
