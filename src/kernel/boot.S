#include <mips/registers.h>
#include <mips/adresses.h>
#include <mips/bitmasks.h>
#include <mips/pcb.h>

.globl start
.extern main
.extern __context_switch
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

# Initiate process 0 and 1
init_processes:
	li		$a0, 0	# Initial PID

init_loop:
	#PCB adress will be in $v0, PID must be in $a0
	jal 	pcb_adress
	add		$t2, $zero, $a0		# Transfer PID to $t2
	add		$t0, $v0, $zero		# Transfer PCB adress to $t0
	sw		$t2, 0($t0)				# Spara PID på första minnesplatsen i PCB:n
	addi	$t0, $t0, PID_SIZE

	li		$t3, 0			# 0 = ready
	sw		$t3, 0($t0)	#	Spara state
	addi	$t0, $t0, STATE_SIZE # $t0 is now at adress of Context ($ra) so that we can store the start adress

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

	beq	$t2, 1,	set_starting_pid # If 1, we're done...
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

start_process_0:
	li		$t1, 0xDEADBEEF
	jal context_switch
	nop
	b start_process_0
	nop

start_process_1:
	li		$t1, 0xB000B1E5
	jal context_switch
	nop
	b start_process_1

context_switch:
	# Make room for 5 registers
	addi	$sp, -20

	# These will be used in the saving process and needs to be stored away
	sw		$v0, 16($sp)
	sw		$a0, 12($sp)
	sw		$t1, 8($sp)
	sw		$t0, 4($sp)
	sw		$ra, 0($sp)

	la		$t0, running_process
	lw		$t1, 0($t0)			# PID of the running process
	add		$a0, $t1, $zero	# Put PID as argument to pcb_adress, $v0 now contains adress to running PCB
	jal 	pcb_adress
	nop
	add		$a0, $v0, $zero # Put PCB as argument to save_context
	b		save_context
	nop

# Determine what process to switch to, this will be changed to a queue
check:
	la    $t1, running_process
	lw    $t2, 0($t1)
	beq		$t2, 1, switch_from_1	# Switch on the current PID
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
	sw		$a0, 0($t1)  # Save the new PID as the current process
	jal		pcb_adress	 # Adress to new PCB is now in $v0
	nop
	add		$t0, $zero, $zero
	addi	$t0, CONTEXT_OFFSET
	add		$t0, $v0, $t0	# Adress of context

	lw		$fp, 108($t0)
	lw		$gp, 104($t0)
	lw		$s7, 100($t0)
	lw		$s6, 96($t0)
	lw		$s5, 92($t0)
	lw		$s4, 88($t0)
	lw		$s3, 84($t0)
	lw		$s2, 80($t0)
	lw		$s1, 76($t0)
	lw		$s0, 72($t0)
	lw		$a3, 68($t0)
	lw		$a2, 64($t0)
	lw		$a1, 60($t0)
	lw		$a0, 56($t0)
	lw		$v1, 52($t0)
	lw		$v0, 48($t0)
	lw		$t9, 44($t0)
	lw		$t8, 40($t0)
	lw		$t7, 36($t0)
	lw		$t6, 32($t0)
	lw		$t5, 28($t0)
	lw		$t4, 24($t0)
	lw		$t3, 20($t0)
	lw		$t2, 16($t0)
	lw		$t1, 12($t0)
	lw		$sp, 4($t0)
	lw		$ra, 0($t0)
	lw    $t0, 8($t0)
	jr		$ra
	nop

	# Adress of process PCB is in $a0
save_context:
	addi	$t0, $a0, CONTEXT_OFFSET

	# Pop registers from the stack and save in the context instead
	# Context adress remains in $t0 for now
	lw		$v0, 16($sp)
	lw		$a0, 12($sp)
	lw		$t1, 8($sp)
	lw		$ra, 0($sp)

	sw		$fp, 108($t0)
	sw		$gp, 104($t0)
	sw		$s7, 100($t0)
	sw		$s6, 96($t0)
	sw		$s5, 92($t0)
	sw		$s4, 88($t0)
	sw		$s3, 84($t0)
	sw		$s2, 80($t0)
	sw		$s1, 76($t0)
	sw		$s0, 72($t0)
	sw		$a3, 68($t0)
	sw		$a2, 64($t0)
	sw		$a1, 60($t0)
	sw		$a0, 56($t0)
	sw		$v1, 52($t0)
	sw		$v0, 48($t0)
	sw		$t9, 44($t0)
	sw		$t8, 40($t0)
	sw		$t7, 36($t0)
	sw		$t6, 32($t0)
	sw		$t5, 28($t0)
	sw		$t4, 24($t0)
	sw		$t3, 20($t0)
	sw		$t2, 16($t0)
	sw		$t1, 12($t0)
	sw		$ra, 0($t0)

	# Let $t1 (already saved) take over as holder of context adress
	# and save $t0 too
	add   $t1, $zero, $zero
	addi  $t1, $t0, 0
	lw		$t0, 4($sp)
	sw		$t0, 8($t1)
	addi	$sp, 20       # Restore stackpointer
	# Finally save stack pointer
	sw    $sp, 4($t1)

	# ALL REGISTERS CLEAR!
	b check
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


.section .bss

stack:
	.space 	STACKSIZE

ram:
	.space	RAMSIZE

ready_queue:
	.space	0x8

running_process:
	.space	0x4
