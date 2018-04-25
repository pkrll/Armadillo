#include <mips/registers.h>
#include <mips/adresses.h>
#include <mips/bitmasks.h>
#include <mips/pcb.h>

.globl test_dispatcher
.globl  context_switch
.extern print0
.extern print1

.set noreorder
.set RAMSIZE, PCB_SIZE * 5

.section .text

test_dispatcher:

init_process_1:
	nop
	la		$t1, _running

	add		$t0, $zero, $zero
	addi	$t0, 1
	sw		$t0, 0($t1)		# Set _running to 1

	jal 	get_pcb_adress 			# PCB Adress is in $k1
	nop
	li		$t1, 0
	sw		$t1, 0($k1)		# Store PID

	jal get_context_adress 	# Context adress is in $k1
	nop
	la		$t1, process_1
	sw		$t1, 112($k1)		# Starting point of the process
	
	move 	$t0, $k1		#  Transfer context adress to $t0
	jal		get_stack_adress # jump to get_stack_adress and save position to $ra
	nop
	sw		$k1, 0($t0)		# Init stack pointer to first byte of process stack


init_process_0:
	nop
	la		$t1, _running
	add		$t0, $zero, $zero
	sw		$t0, 0($t1)		# Set _running to 0

	jal get_pcb_adress 	# PCB Adress is in $k1
	nop
	li		$t1, 0
	sw		$t1, 0($k1)		# Store PID

	jal get_context_adress 	# Context adress is in $k1
	nop
	la		$t1, process_0
	sw		$t1, 112($k1)		  # Starting point of the process

# Arbetsyta för process 0
process_0:
	li		$t1, 0xDEADBEEF
	jal		print0
	nop
	syscall
	nop
	b process_0
	nop

# Arbetsyta för process 1
process_1:
	li		$t1, 0xB000B1E5
	jal print1
	nop
	syscall
	nop
	b process_1

context_switch:
	addi	$sp, -4
	sw		$ra, 0($sp) # Save $ra before jal
	jal		save_context
	nop

	# pick_process, hardcoded for now
	la 		$k0, _running	# Adress of current PID
	li		$t0, 1
	lw		$t1, 0($k0)		# Value of current PID
	xor		$t0, $t1, $t0	# Flip the current PID
	sw		$t0, 0($k0)		# Store new PID

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
	lw		$k0, 0($sp) # $ra
	addi	$sp, 4

	# Get offending instruction, add 4, and store
  # it as the PC from where to resume next time
	mfc0	$k0, C0_EPC # EPC
	addi	$k0, $k0, 4

	sw		$k0, 112($k1)	# pc
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
	jal		get_context_adress # Adress to context is in $k1
	nop

	lw		$k0, 112($k1)		# pc, adress to resume execution from
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
	lw		$ra, 4($k1) # Dessa skiter sig
	lw		$sp, 0($k1)
	mtc0	$k0, C0_EPC # Store old pc in EPC register
	eret						  # Returns from exception using EPC
	nop

# Puts the adress of the current process' CPU context in $k1
get_context_adress:
	addi	$sp, -4
	sw 		$ra, 0($sp)			# Save stack pointer due to jal
	jal		get_pcb_adress	# jump to get_pcb_adress and save position to $ra
	nop
	addi	$k1, CONTEXT_OFFSET
	lw		$ra, 0($sp)
	addi	$sp, 4
	jr		$ra
	nop

# Puts the adress of the current process' PCB in $k1
get_pcb_adress:
	nop									# This must be here because of pseudo instruction 'la'
	la 		$k0, _running	# Adress of current PID
	lw		$k0, 0($k0)		# Current PID
	li 		$k1, PCB_SIZE
	mult  $k0, $k1			# Offset
	mflo	$k0
	la 		$k1, ram			# Adress to ram
	add		$k1, $k1, $k0	#	Adress to PCB
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
