#include <mips/registers.h>
#include <mips/adresses.h>
#include <mips/bitmasks.h>
#include <mips/pcb_offsets.h>
#include <common/pcb.h>
#include <common/dispatcher.h>

.globl test_dispatcher
.globl context_switch
.extern print0
.extern print1

.set noreorder
.set RAMSIZE, PCB_SIZE * 5

.section .kdata
	pid: .word 0
	_pcb_adress_space: .word 0

.section .text


context_switch:

	# Get offending instruction, add 4, and store
	# it as the PC from where to resume next time
	mfc0	$k0, C0_EPC 	# EPC

	addi	$sp, -4
	sw		$ra, 0($sp) 	# Save $ra before jal
	jal 	get_pcb_adress 	# Adress is in $k1
	nop
	lw		$ra, 0($sp)
	addi	$sp, 4

	sw		$k0, 4($k1)		# Store PC in PCB

	addi	$sp, -4
	sw		$ra, 0($sp) 	# Save $ra before jal
	jal		save_context
	nop

	# pick a process in C
	jal 	process_switch # pid in $v0??
	nop

	jal		load_context
	nop

save_context:
	addi	$sp, -4
	sw		$ra, 0($sp)
	jal		get_context_adress # Adress of context is in $k1 efter this
	nop
	lw		$ra, 0($sp)
	addi	$sp, 4

	# Pop original $ra from the stack to store and restore the stack pointer
	addi	$sp, 4
	lw		$k0, 0($sp) # $ra

	sw		$fp, 108($k1)
	sw		$gp, 104($k1)
	sw		$s7, 100($k1)
	sw		$s6, 96($k1)
	sw		$s5, 92($k1)
	sw		$s4, 88($k1)
	sw		$s3, 84($k1)
	sw		$s2, 80($k1)
	sw		$s1, 76($k1)
	sw		$s0, 72($k1)
	sw		$a3, 68($k1)
	sw		$a2, 64($k1)
	sw		$a1, 60($k1)
	sw		$a0, 56($k1)
	sw		$v1, 52($k1)
	sw		$v0, 48($k1)
	sw		$t9, 44($k1)
	sw		$t8, 40($k1)
	sw		$t7, 36($k1)
	sw		$t6, 32($k1)
	sw		$t5, 28($k1)
	sw		$t4, 24($k1)
	sw		$t3, 20($k1)
	sw		$t2, 16($k1)
	sw		$t1, 12($k1)
	sw		$t0, 8($k1)
	sw		$k0, 4($k1) # $ra
	sw		$sp, 0($k1)
	jr		$ra
	nop

load_context:
	jal get_pcb_adress
	nop
	addi	$k1, 4	# adress to PC storing place
	mtc0	$k1, C0_EPC # Store old pc in EPC register

	jal		get_context_adress # Adress to context is in $k1
	nop

	lw		$fp, 108($k1)
	lw		$gp, 104($k1)
	lw		$s7, 100($k1)
	lw		$s6, 96($k1)
	lw		$s5, 92($k1)
	lw		$s4, 88($k1)
	lw		$s3, 84($k1)
	lw		$s2, 80($k1)
	lw		$s1, 76($k1)
	lw		$s0, 72($k1)
	lw		$a3, 68($k1)
	lw		$a2, 64($k1)
	lw		$a1, 60($k1)
	lw		$a0, 56($k1)
	lw		$v1, 52($k1)
	lw		$v0, 48($k1)
	lw		$t9, 44($k1)
	lw		$t8, 40($k1)
	lw		$t7, 36($k1)
	lw		$t6, 32($k1)
	lw		$t5, 28($k1)
	lw		$t4, 24($k1)
	lw		$t3, 20($k1)
	lw		$t2, 16($k1)
	lw		$t1, 12($k1)
	lw		$t0, 8($k1)
	lw		$ra, 4($k1)
	lw		$sp, 0($k1)

	eret						  # Returns from exception using EPC
	nop

# Puts the adress of the current process' CPU context in $k1
get_context_adress:
	addi	$sp, -4
	sw 		$ra, 0($sp)			# Save stack pointer due to jal
	jal		get_pcb_adress	# jump to get_pcb_adress and save position to $ra
	nop
	lw		$ra, 0($sp)
	addi	$sp, 4
	li		$k0, CONTEXT_OFFSET
	add		$k1, $k1, $k0		# Add context offset to PCB adress
	jr		$ra
	nop

# Puts the adress of the current process' PCB in $k1
get_pcb_adress:
	nop									# This must be here because of pseudo instruction 'la'
	la 		$k0, running_process	# Adress of current PCB
	lw		$k0, 0($k0)		# Current PID, (first byte in PCB)
	li		$k1, PCB_SIZE
	mult  $k0, $k1
	mflo	$k0						# Offset to PCB correct

	lw		$k1, pcb_adress_space
	add		$k1, $k1, $k0	# Add the offset and get the correct PCB adress

	jr		$ra
	nop

get_stack_adress:
	addi	$sp, -4
	sw 		$ra, 0($sp)			# Save stack pointer due to jal
	jal get_pcb_adress				# PCB adress is now in $k1
	nop
	addi	$k1, STACK_SIZE
	lw		$ra, 0($sp)
	addi	$sp, 4
	jr		$ra
	nop

.section .bss

ram:
	.space	RAMSIZE

_running:
	.space	0x4
