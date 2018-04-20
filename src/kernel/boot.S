#include <mips/registers.h>
#include <mips/adresses.h>
#include <mips/bitmasks.h>
#include <mips/pcb.h>

.globl start
.extern main
.extern	init_timer
.set noreorder

.set STACKSIZE, 0x4000
.set RAMSIZE, PCB_SIZE * 5

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
	jal init_processes
#	jal		init_timer


	#syscall # temporary

	nop
#	jal main
	nop
	b	.


init_processes:
	li		$a0, 0	# Initial PID

init_loop:
	#PCB adress will be in $v0, PID must be in $a0
	jal 	pcb_adress
	add		$t2, $zero, $a0		# Transfer PID to $t2
	add		$t0, $v0, $zero		# Transfer PCB adress to $t0
	sw		$t2, 0($t0)				# Spara PID på första minnesplatsen
	addi	$t0, $t0, PID_SIZE

	li		$t3, 0			# 0 = ready
	sw		$t3, 0($t0)	#	Spara state
	addi	$t0, $t0, STATE_SIZE

	beq		$t2, 1, pr1_ra

pr0_ra:
	la		$t4, start_process_0	# Save dummy $ra of process 0
	sw		$t4, 4($t0)		#
	b rest
	nop

pr1_ra:
	la		$t4, start_process_1	# Save dummy $ra of process 1
	sw		$t4, 4($t0)

addi	$t0, $t0, CONTEXT_SIZE

rest:
	#addi	$t0, $t0, MEM_IMAGE_SIZE
	#addi	$t0, $t0, SCHEDULE_SIZE
	#addi	$t0, $t0, PC_SIZE
	#addi	$t0, $t0, SP_SIZE

	beq	$t2, 1,	set_starting_pid
	nop

	addi	$t2, $t2, 1 		# Increment PID
	add		$a0, $t2, $zero	# Transfer PID to $a0

	b init_loop
	nop

set_starting_pid:
	la		$t1, running_process
	li		$t2, 0
	sw		$t2, 0($t1)		# Set current PID to 0
	b 		start_process_0
	nop

context_switch:
	addi	$sp, -8
	sw		$t1, 4($sp)
	sw		$ra, 0($sp)		#

	la		$t1, running_process
	lw		$t2, 0($t1)			# Current PID
	add		$a0, $t2, $zero	# Put PID as argument to pcb_adress
	jal 	pcb_adress
	nop
	add		$a0, $v0, $zero # Put PCB as argument to save_context
	jal		save_context
	nop
	beq		$s2, 1, switch_from_1	# Switch on the current PID
	nop

switch_from_0:
	li		$a0, 1 # Put the new PID as argument to load_context
	jal 	load_context
	nop

switch_from_1:
	li		$a0, 0	# Put the new PID as argument to load_context
	jal 	load_context
	nop

# PID of process to load is in $a0
load_context:
	la		$t1, running_process
	sw		$a0, 0($t1) # Save the new PID as the current process
	jal		pcb_adress				# Adress to new PCB will be in $v0
	nop
	add		$t0, $zero, $zero
	addi	$t0, CONTEXT_OFFSET
	add		$t0, $t0, $v0
	lw		$t1, 0($t0)		# Restore $t1
	lw		$ra, 4($t0)		# Restore $ra
	jr		$ra
	nop
# Adress of process PCB is in $a0
save_context:
	addi	$t0, $a0, CONTEXT_OFFSET
	lw		$t1, 4($sp)

	sw		$t1, 0($t0)
	sw		$ra, 4($t0)
	jr		$ra
	nop

# PID is in $a0, adress of PCB is put in $v0
pcb_adress:
		la		$t0, ram				# RAMBASE
		li		$t1, PCB_SIZE		# PCBSIZE
		mult	$t1, $a0				# PCBSIZE * PID
		mflo	$t1							# OFFSET
		add		$v0, $t1, $t0		# Startadressen för PCBn = RAMBASE + OFFSET + INNEROFFSET= $t0
		jr		$ra
		nop

start_process_0:
		li		$t1, 0xDEADBEEF		#  = 0xDEADBEEF
		jal context_switch
		nop
		b start_process_0
		nop

start_process_1:
		li		$t1, 0xB00BB00B		#  = 0xDEADBEEF
		jal context_switch
		nop
		b start_process_1
		nop

.section .bss

stack:
	.space 	STACKSIZE

ram:
	.space	RAMSIZE

ready_queue:
	.space	0x8

running_process:
	.space	0x4
