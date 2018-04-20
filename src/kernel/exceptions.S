.globl excp
.extern exception_overflow
.extern exception_trap
.extern STACKSIZE
.extern stack

.set noreorder
.set noat

.section .kdata
	#-1 if no process is in the state, else PID
	__running:		.word -1
	__ready:			.word 0		#NOT DONE
	__waiting:		.word 0		#NOT DONE
	__at:					.word 0
	__sp:					.word 0

	#Hantera context på annat sätt än array/list?
	__context_list:				.word __process0_context, __process1_context, __process2_context

.section .bss
	__process0_context:		.space 116		#Reserve memory for registers (all but $k0, $k1, $zero)
	__process1_context:		.space 116
	__process2_context:		.space 116

.section .ktext
.org 0x184

excp:

	move 		$k0, $at					#Copy $at to $k0
	move		$k1, $sp					#Copy $sp to $k1
	.set at
	sw			$k0, __at					#Store $k0 into __at
	sw			$k1, __sp					#Store $k1 into __sp

	la 			$sp, stack
	addiu		$sp, STACKSIZE - 32

	jal			save_context
	nop

	mfc0 		$k0, $13 					#Get the cause value
	andi 		$k1, $k0, 124			#Set all bits to 0 except 2-6
	srl 		$k1, $k1, 2				#Shift 2 steps to the right to get the value

	beqz 		$k1, interrupt		#Checks if the cause is an interrupt
	nop

	#else exception
	j 			exception
	nop

get_running_process:
	#Set the address to the context of the running process into $k1
	lw			$k0, __running		#Load PID into $k1
	sll			$k1, $k0, 2				#Multiply by 4 for "indexering"
	lw			$k1, __context_list($k1) #Get the context

	jr			$ra
	nop

save_context:

	addi 		$sp, $sp, -4
	sw			$ra, 0($sp)

	jal			get_running_process
	nop
	#$k1 = Address to context of PID

	#Save all registers (context)
	mfc0		$k0, $14 					#save EPC
	sw			$k0, 0($k1)
	lw			$k0, __at					#save at register
	sw			$k0, 4($k1)
	sw			$v0, 8($k1)
	sw			$v1, 12($k1)
	sw			$a0, 16($k1)
	sw			$a1, 20($k1)
	sw			$a2, 24($k1)
	sw			$a3, 28($k1)
	sw			$t0, 32($k1)
	sw			$t1, 36($k1)
	sw			$t2, 40($k1)
	sw			$t3, 44($k1)
	sw			$t4, 48($k1)
	sw			$t5, 52($k1)
	sw			$t6, 56($k1)
	sw			$t7, 60($k1)
	sw			$s0, 64($k1)
	sw			$s1, 68($k1)
	sw			$s2, 72($k1)
	sw			$s3, 76($k1)
	sw			$s4, 80($k1)
	sw			$s5, 84($k1)
	sw			$s6, 88($k1)
	sw			$s7, 92($k1)
	sw			$t8, 96($k1)
	sw			$t9, 100($k1)
	sw			$gp, 104($k1)
	sw			$sp, 108($k1)
	sw			$fp, 112($k1)
	sw			$ra, 116($k1)

	lw			$ra, 0($sp)
	addiu		$sp, $sp, 4

	jr			$ra
	nop

restore_context:

	addi 		$sp, $sp, -4
	sw			$ra, 0($sp)
	jal 		get_running_process
	nop

	#Restore all registers
	lw			$k0, 0($k1)
	mtc0		$k0, $14
	lw			$k0, 4($k1)
	lw			$v0, 8($k1)
	lw			$v1, 12($k1)
	lw			$a0, 16($k1)
	lw			$a1, 20($k1)
	lw			$a2, 24($k1)
	lw			$a3, 28($k1)
	lw			$t0, 32($k1)
	lw			$t1, 36($k1)
	lw			$t2, 40($k1)
	lw			$t3, 44($k1)
	lw			$t4, 48($k1)
	lw			$t5, 52($k1)
	lw			$t6, 56($k1)
	lw			$t7, 60($k1)
	lw			$s0, 64($k1)
	lw			$s1, 68($k1)
	lw			$s2, 72($k1)
	lw			$s3, 76($k1)
	lw			$s4, 80($k1)
	lw			$s5, 84($k1)
	lw			$s6, 88($k1)
	lw			$s7, 92($k1)
	lw			$t8, 96($k1)
	lw			$t9, 100($k1)
	lw			$gp, 104($k1)
	lw			$sp, 108($k1)
	lw			$fp, 112($k1)
	lw			$ra, 116($k1)

	lw			$ra, 0($sp)
	addi		$sp, $sp, 4

	jr			$ra
	nop

exception:

	beq 		$k1, 12, overflow #Overflow exception
	nop
	beq			$k1, 13, trap			#Trap exception
	nop

overflow:
	jal 		exception_overflow
	nop
	addi 		$t2, $t2, 2				#Testar restore context
	addiu		$a1, $a1, 100
	j 			resume_from_exception
	nop

trap:
	jal			exception_trap
	nop
	j				resume_from_exception
	nop

interrupt:

resume_from_exception:

	jal			get_running_process
	nop

	jal 		restore_context
	nop

	mfc0 		$k0, $14 				#Move the exception address to the next instruction
	addi		$k0, $k0, 4
	mtc0 		$k0, $14

	lw			$at, 4($k1)			#restore $at

	eret
	nop
