#include <mips/registers.h>


.globl context_switch
.extern get_running_pcb
.extern get_current_context
.extern get_running_pc

.set noreorder
.section .data
	__at: 			.word 0
.section .text


context_switch:

	move $k0, $at
	sw   $k0, __at
	# Get offending instruction, add 4, and store
	# it as the PC from where to resume next time
	mfc0	K0, C0_EPC 	# EPC

	# Before saving anything, we need the adress to the current PCB
	addi	SP, -8
	sw		V0, 4(SP)		#save V0 before function call
	sw		RA, 0(SP) 	# Save RA before jal
	jal 	get_current_pcb #current PID in V0?
	nop
	move 	K1, V0			#  Move PCB adress to K1
	lw		V0, 4(SP)		# restore V0
	lw		RA, 0(SP)
	addi	SP, 8

	# Now we can start saving stuff to the PCB adress in K1
	addi	K0, 4				# add to offending instruction
	sw		K0, 4(K1)		# Store PC in PCB

	addi	SP, -4
	sw		RA, 0(SP) 	# Save RA before jal
	jal		save_context
	nop

	# switch process in C
	jal 	process_switch # pid in V0??
	nop

	jal		load_context
	nop

save_context:
	# Make room on the stack for RA and V0 since these will be overwritten by the jal
	addi	SP, -8
	sw		V0, 4(SP)
	sw		RA, 0(SP)
	jal		get_current_context # Adress of context is in V0 efter this
	nop

	# Move context adress into K1 wich is not saved and restore V0 and RA
	move 	K1, V0
	lw		V0, 4(SP)
	lw		RA, 0(SP)
	addi	SP, 8

	# Pop original RA from the stack and store in K0 (NOT in RA since we need to return from this function).
	# Also restore the stack pointer for saving.
	addi	SP, 4
	lw		K0, 0(SP) # RA

	sw		FP, 108(K1)
	sw		GP, 104(K1)
	sw		S7, 100(K1)
	sw		S6, 96(K1)
	sw		S5, 92(K1)
	sw		S4, 88(K1)
	sw		S3, 84(K1)
	sw		S2, 80(K1)
	sw		S1, 76(K1)
	sw		S0, 72(K1)
	sw		A3, 68(K1)
	sw		A2, 64(K1)
	sw		A1, 60(K1)
	sw		A0, 56(K1)
	sw		V1, 52(K1)
	sw		V0, 48(K1)
	sw		T9, 44(K1)
	sw		T8, 40(K1)
	sw		T7, 36(K1)
	sw		T6, 32(K1)
	sw		T5, 28(K1)
	sw		T4, 24(K1)
	sw		T3, 20(K1)
	sw		T2, 16(K1)
	sw		T1, 12(K1)
	sw		T0, 8(K1)
	sw		K0, 4(K1) # Actually RA
	sw		SP, 0(K1)
	lw    K0, __at
	sw 		K0, 112(K1)
	jr		RA
	nop

load_context:
	jal		get_running_pc
	nop
	mtc0	V0, C0_EPC # Store the process' previous PC in EPC register

	jal		get_current_context # Adress to context is now in V0
	nop

	#  Move context adress into K1 and start restoring registers
	move 	K1, V0
	lw		FP, 108(K1)
	lw		GP, 104(K1)
	lw		S7, 100(K1)
	lw		S6, 96(K1)
	lw		S5, 92(K1)
	lw		S4, 88(K1)
	lw		S3, 84(K1)
	lw		S2, 80(K1)
	lw		S1, 76(K1)
	lw		S0, 72(K1)
	lw		A3, 68(K1)
	lw		A2, 64(K1)
	lw		A1, 60(K1)
	lw		A0, 56(K1)
	lw		V1, 52(K1)
	lw		V0, 48(K1)
	lw		T9, 44(K1)
	lw		T8, 40(K1)
	lw		T7, 36(K1)
	lw		T6, 32(K1)
	lw		T5, 28(K1)
	lw		T4, 24(K1)
	lw		T3, 20(K1)
	lw		T2, 16(K1)
	lw		T1, 12(K1)
	lw		T0, 8(K1)
	lw		SP, 0(K1)
	lw		RA, 4(K1)

	# Return from exception using the adress in EPC
	lw 		$at, 112(K1)
	eret
	nop

.section .bss
