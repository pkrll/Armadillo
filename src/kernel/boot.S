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

	mfc0 	$t3, $12 	#	Load contents of Status register
	addi	$t4, 1		# $t4 = 1
	sll		$t4, 15		# $t4 = 1000 0000 0000 0000
	ori		$t4, 1		# Add 'enable interrupt' to the mask, $t4 = 1000 0000 0000 0001
	or		$t4, $t4, $t3	# Mask the contents of Status register
	mtc0	$t4, $12	# Store the contents in Status register

	li		$t1, 0x80100000
	mtc0	$t1, $15,1
	# Clear the status(bev) bit. This will make the CPU
	# use the RAM-based exception vector.
	li		$t1, 0x0
	mtc0	$t1, $12,0

	#syscall # temporary

	nop
	#jal main
	nop

trap_timer:
	mfc0	$t3, $13 	# This should change when an interrupt occurs
	li		$t1, 0x1
	li		$t2, 0x1
	#	Set both Compare and Count registers to 0x1,
	#	should cause an immediate interrupt
	mtc0 	$t2, $11
	mtc0	$t1, $9
	b trap_timer
	nop

.section .bss

stack:
	.space STACKSIZE
